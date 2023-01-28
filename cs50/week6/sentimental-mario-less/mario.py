import cs50
# TODO
h = 0
while (h < 1) | (h > 8):  # 大きさが制限外なら聞き続ける
    h = cs50.get_int("Height: ")

for i in range(h):
    s = ''  # 行の変数を用意、初期化
    for j in range(h - i - 1):  # 空白の出力
        s += " "
    for k in range(i + 1):  # "#"の出力
        s += "#"
    print(s)  # 表示