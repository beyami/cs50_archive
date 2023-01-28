import cs50

c = -1.0
while c < 0:  # 負の値, 0を拒否
    c = cs50.get_float("Change owed: ")

c = int(c * 100)
otr = 0
otr += c // 25
c %= 25  # 整数除算で25で割り、答えを代入、cをあまりに置き換え

otr += c // 10
c %= 10  # 整数除算で10で割り、答えを代入、cをあまりに置き換え

otr += c // 5
c %= 5  # 整数除算で5で割り、答えを代入、cをあまりに置き換え

otr += c // 1
# 整数除算でで割り、答えを代入
print(otr)