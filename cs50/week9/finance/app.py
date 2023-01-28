import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # 表示する所持株とユーザ情報をそれぞれstockとusrに保存
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ? AND shares > 0", session["user_id"])
    usr = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    if not usr:
        # usrがない==セッション情報のみ残っている->セッションクリアして再度ログイン
        session.clear()
        return redirect("/")
    cash = usr[0]["cash"]
    for stock in stocks:
        # 各株の情報を最新のものに更新
        tmp = lookup(stock["symbol"])
        stock["name"] = tmp["name"]
        stock["price"] = tmp["price"]
    return render_template("index.html", stocks=stocks, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # postリクエストならデータを更新して表示
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        usr = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        cash = usr[0]["cash"]
        if stock is not None and request.form.get("shares").isdecimal():
            # stockがない=symbolが不適でない　かつ　sharesが正整数の場合

            if cash < stock["price"] * int(request.form.get("shares")):
                # 所持金より購入金額が多い場合はapology
                return apology("too many shares", 400)
            else:
                # 取引時刻をtimenowに保存
                timenow = datetime.now().replace(microsecond=0)
                db.execute("INSERT INTO history (user_id, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?)",
                           session["user_id"], stock["symbol"], request.form.get("shares"), stock["price"],
                           timenow)
                totalbuy = float(request.form.get("shares")) * stock["price"]
                cash = cash - totalbuy
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

                nowstock = db.execute("SELECT * FROM stocks WHERE symbol = ? AND user_id = ?", stock["symbol"], session["user_id"])

                if len(nowstock) == 0:
                    # ユーザidと株名で検索して存在しないなら新たに作成
                    db.execute("INSERT INTO stocks (symbol, user_id, shares) VALUES(?, ?, ?)",
                               stock["symbol"], session["user_id"], request.form.get("shares"))
                else:
                    # そうでないなら現在の値に加算して更新
                    shares = nowstock[0]["shares"] + int(request.form.get("shares"))
                    db.execute("UPDATE stocks SET shares = ? WHERE symbol = ? AND user_id = ?",
                               shares, stock["symbol"], session["user_id"])

                stocks = db.execute("SELECT * FROM stocks WHERE user_id = ? AND shares > 0", session["user_id"])
                # 表示用に現在持っている株の情報を取得、現在の株価に更新
                for stock in stocks:
                    tmp = lookup(stock["symbol"])
                    stock["name"] = tmp["name"]
                    stock["price"] = tmp["price"]
                return render_template("bought.html", stocks=stocks, cash=cash)
        else:
            return apology("Invalid symbol or shares.", 400)
    else:
        # getリクエストなら購入株を訪ねるhtmlを返す
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # リストを取得して表示
    histories = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", histories=histories)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # シンボルをlookupで検索
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        if stock is not None:
            # Noneでなければ値を返却
            return render_template("quoted.html", name=stock["name"], symbol=stock["symbol"], price=stock["price"])

        else:
            # Noneなら値不適としてapology
            return apology("Invalid symbol", 400)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # ユーザ名の空白確認
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # パスワードの空白確認
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # パスワード確認の空白確認
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        # ユーザネームの被り検出
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) > 0:
            return apology("Sorry, the name was already used.", 400)

        # パスワードの一致確認
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Could not confirm password.", 400)

        # パスワードをハッシュ
        hash = generate_password_hash(request.form.get("password"))
        # ユーザの追加
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), hash)

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # リクエストがpostの場合
        # まずデータを用意
        # stocksにはユーザが持っている売りたい株の情報を保存

        symbol = request.form.get("symbol")

        if symbol is not None and request.form.get("shares"):
            soldshares = int(request.form.get("shares"))
            # ユーザが売りたい株のデータをstockで保存
            stock = db.execute("SELECT * FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)

            if stock[0]["shares"] < soldshares or soldshares < 1:
                return apology("invalid shares.")
            # 今ログインしているユーザの持っている金額をcashに保存
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

            # 株価を最新の情報に更新
            stock[0]["price"] = lookup(symbol)["price"]

            # 個数×価格をcashに加算   ＝ 実際に売る
            soldcash = float(soldshares) * stock[0]["price"]
            cash[0]["cash"] += soldcash

            # 計算したcashと持っている株の個数を更新
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash[0]["cash"], session["user_id"])
            db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?",
                       stock[0]["shares"]-int(soldshares), session["user_id"], symbol)

            # 履歴に保存
            timenow = datetime.now().replace(microsecond=0)
            db.execute("INSERT INTO history (user_id, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?)",
                       session["user_id"], symbol, soldshares * -1, stock[0]["price"],
                       timenow)

            stocks = db.execute("SELECT * FROM stocks WHERE user_id = ? AND shares > 0", session["user_id"])
            for stock in stocks:
                tmp = lookup(stock["symbol"])
                stock["name"] = tmp["name"]
                stock["price"] = tmp["price"]
            return render_template("sold.html", stocks=stocks, cash=cash[0]["cash"])

        else:
            # Noneなら値不適としてapology
            return apology("Invalid symbol or Shares", 400)
    else:
        stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", stocks=stocks)