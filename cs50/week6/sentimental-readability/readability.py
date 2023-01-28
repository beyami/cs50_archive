# TODO
import cs50
from decimal import Decimal, ROUND_HALF_UP


def main():
    text = cs50.get_string("Text: ")
    ltrs = count_letters(text)
    words = count_words(text)
    texts = count_texts(text)

    # 指数、係数の計算
    L = ltrs * 100.0 / words
    S = texts * 100.0 / words
    idx = 0.0588 * L - 0.296 * S - 15.8
    if idx < 1:
        print("Before Grade 1")
    elif idx >= 16:
        print("Grade 16+")
    else:
        print("Grade ", Decimal(str(idx)).quantize(Decimal('0'), rounding=ROUND_HALF_UP))


def count_letters(text):
    # text中の文字数を数える
    ctr = 0
    for c in text:
        if (c.isalnum()):
            ctr += 1

    return ctr


def count_words(text):
    # 単語のカウント
    # print(text.count(" ") + 1)
    return text.count(" ") + 1


def count_texts(text):
    counts = 0
    counts += text.count(".")
    counts += text.count("!")
    counts += text.count("?")
    # print(counts)
    return counts


if __name__ == "__main__":
    main()