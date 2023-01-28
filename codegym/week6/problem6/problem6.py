import time
import csv

# TODO 任意：より高速に動作するようにしてください
def main():

    # TODO target_post_codes を昇順に並び替える
    target_post_codes.sort()

    result = ""

    for post_code in target_post_codes:
        row = search_csv_by_post_code(post_code)
        # 行が取得できていれば、7つ目のカラムの1文字目を取得する
        if row != None:
            # TODO 7つ目のカラムの1文字目を取得しresultの末尾に結合する
            result += row[6][0]

    # 結果出力
    print(result)


# CSVから該当の郵便番号の行を返す
# 該当する郵便番号がない場合は、Noneを返却する
def search_csv_by_post_code(post_code):
    with open("KEN_ALL_ROME.CSV", "r", encoding="shift-jis") as file:
        reader = csv.reader(file)
        # TODO CSVから1行ずつ読み込んで1つめのカラムと郵便番号が一致していれば、その行を返す
        for row in reader:
            if row[0] == post_code:
                return row

    return None


# ここから下は編集不可 -------------------------------------------------------------

# 検索する郵便番号
target_post_codes = ['3212111', '8360086', '1987921', '4610002', '6068407', '5192505', '0202279', '0552314', '7992464']

# 開始時間
start_time = time.process_time()

main()

# 終了時間
end_time = time.process_time()
# 処理時間を表示
process_time_ms = (end_time - start_time) * 1000
print(f'{process_time_ms}ms')


# CSVは以下からダウンロードしたものです
# https://www.post.japanpost.jp/zipcode/dl/roman-zip.html
