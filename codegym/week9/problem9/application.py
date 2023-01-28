from flask import Flask, render_template, request
from cs50 import SQL

app = Flask(__name__)



# https://{ドメイン}/
# にアクセスした際に「hello, world」と表示する
@app.route("/")
def index():
    return "hello, world"

# TODO1
# https://{ドメイン}/page1
# templates/page1.htmlの内容を表示する
# ヒント：render_template関数をインポートしましょう
@app.route("/page1")
def page1():
    return render_template("page1.html")

# TODO2
# https://{ドメイン}/page2
# templates/page2.htmlの内容を表示する
# GETパラメータnameの値を、nameというパラメータ名でテンプレートに渡す
# ヒント：requestをインポートしましょう
@app.route("/page2")
def page2():
    return render_template("page2.html", name=request.args.get("name", "World"))

# TODO3
# https://{ドメイン}/page3
# データベース(codegym.db)に接続
# 次のSQLの結果をprefecturesという変数に代入する
#   SELECT id, name, population FROM prefectures ORDER BY population DESC
# templates/page3.htmlを表示する
#   その際に、変数prefecturesを、prefecturesというパラメータ名でテンプレートに渡す
# ヒント：CS50ライブラリからSQL関数をインポートしましょう
@app.route("/page3")
def page3():
    db = SQL("sqlite:///codegym.db")
    prefectures = db.execute("SELECT id, name, population FROM prefectures ORDER BY population DESC")
    return render_template("page3.html", prefectures=prefectures)
