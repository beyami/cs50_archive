//都道府県の面積を#でグラフの様に表示するプログラム

#include <cs50.h>
#include <stdio.h>

// 都道府県の件数
const int PREFECTURES_COUNT = 47;

// 構造体 都道府県
typedef struct
{
    string name;
    int population;
}
prefecture;

void get_prefectures(prefecture[PREFECTURES_COUNT]);
void rsort_by_population(prefecture[PREFECTURES_COUNT]);

int main(void)
{
    // 都道府県を格納する変数を定義
    prefecture prefectures[PREFECTURES_COUNT];
    // 都道府県情報を格納
    get_prefectures(prefectures);
    // 人口の多い順にソート
    rsort_by_population(prefectures);

    for (int i = 0; i < PREFECTURES_COUNT; i++)
    {
        printf("No%02d:%s ", i + 1, prefectures[i].name);
        // TODO：(任意)人口250,000毎に#を1つ出力する
        //       端数は切り捨てる。例えば260,000の場合は、#は1つ
        //       Noと都道府県名の出力文字数はすでに揃っている
        // 　例：No01:Tokyo     ####################################
        // 　　　No02:Kanagawa  ######################
        //       ※例の#の数は正確ではありません
        for (int j = 0; j < (prefectures[i].population / 250000); j++)
        {
            printf("#");
        }


        printf("\n");
    }

    return 0;
}

// 人口の多い順(降順)にソート(バブルソート)を行う
void rsort_by_population(prefecture prefectures[PREFECTURES_COUNT])
{
    int exchange; // 交換回数

    do
    {
        exchange = 0;

        // 先頭のデータから最後尾の１つ手前のデータまで繰り返す
        for (int i = 0; i < PREFECTURES_COUNT - 1; i++)
        {

            // もし大小関係が逆であれば、データを交換
            // TODO：prefectures[i]とprefectures[i + 1]の人口(population)の大きを比較する
            // 　　　降順となるように並び替える
            if (prefectures[i].population < prefectures[i + 1].population)
            {
                // データを交換(スワップ)
                // TODO：prefectures[i] と prefectures[i + 1] を交換する
                prefecture tmp = prefectures[i];
                prefectures[i] = prefectures[i + 1];
                prefectures[i + 1] = tmp;

                // 交換が行われた回数をカウント
                exchange++;
            }
        }

    }
    while (exchange > 0); // 交換が発生していれば処理を続ける */
}


// 都道府県情報を格納
void get_prefectures(prefecture prefectures[PREFECTURES_COUNT])
{
    prefectures[0].name = "Hokkaido "; prefectures[0].population = 5250000;
    prefectures[1].name = "Aomori   "; prefectures[1].population = 1246000;
    prefectures[2].name = "Iwate    "; prefectures[2].population = 1227000;
    prefectures[3].name = "Miyagi   "; prefectures[3].population = 2306000;
    prefectures[4].name = "Akita    "; prefectures[4].population = 966000;
    prefectures[5].name = "Yamagata "; prefectures[5].population = 1078000;
    prefectures[6].name = "Fukushima"; prefectures[6].population = 1846000;
    prefectures[7].name = "Ibaraki  "; prefectures[7].population = 2860000;
    prefectures[8].name = "Tochigi  "; prefectures[8].population = 1934000;
    prefectures[9].name = "Gunma    "; prefectures[9].population = 1942000;
    prefectures[10].name = "Saitama  "; prefectures[10].population = 7350000;
    prefectures[11].name = "Chiba    "; prefectures[11].population = 6259000;
    prefectures[12].name = "Tokyo    "; prefectures[12].population = 13921000;
    prefectures[13].name = "Kanagawa "; prefectures[13].population = 9198000;
    prefectures[14].name = "Niigata  "; prefectures[14].population = 2223000;
    prefectures[15].name = "Toyama   "; prefectures[15].population = 1044000;
    prefectures[16].name = "Ishikawa "; prefectures[16].population = 1138000;
    prefectures[17].name = "Fukui    "; prefectures[17].population = 768000;
    prefectures[18].name = "Yamanashi"; prefectures[18].population = 811000;
    prefectures[19].name = "Nagano   "; prefectures[19].population = 2049000;
    prefectures[20].name = "Gifu     "; prefectures[20].population = 1987000;
    prefectures[21].name = "Shizuoka "; prefectures[21].population = 3644000;
    prefectures[22].name = "Aichi    "; prefectures[22].population = 7552000;
    prefectures[23].name = "Mie      "; prefectures[23].population = 1781000;
    prefectures[24].name = "Shiga    "; prefectures[24].population = 1414000;
    prefectures[25].name = "Kyoto    "; prefectures[25].population = 2583000;
    prefectures[26].name = "Osaka    "; prefectures[26].population = 8809000;
    prefectures[27].name = "Hyogo    "; prefectures[27].population = 5466000;
    prefectures[28].name = "Nara     "; prefectures[28].population = 1330000;
    prefectures[29].name = "Wakayama "; prefectures[29].population = 925000;
    prefectures[30].name = "Tottori  "; prefectures[30].population = 556000;
    prefectures[31].name = "Shimane  "; prefectures[31].population = 674000;
    prefectures[32].name = "Okayama  "; prefectures[32].population = 1890000;
    prefectures[33].name = "Hiroshima"; prefectures[33].population = 2804000;
    prefectures[34].name = "Yamaguchi"; prefectures[34].population = 1358000;
    prefectures[35].name = "Tokushima"; prefectures[35].population = 728000;
    prefectures[36].name = "Kagawa   "; prefectures[36].population = 956000;
    prefectures[37].name = "Ehime    "; prefectures[37].population = 1339000;
    prefectures[38].name = "Kochi    "; prefectures[38].population = 698000;
    prefectures[39].name = "Fukuoka  "; prefectures[39].population = 5104000;
    prefectures[40].name = "Saga     "; prefectures[40].population = 815000;
    prefectures[41].name = "Nagasaki "; prefectures[41].population = 1327000;
    prefectures[42].name = "Kumamoto "; prefectures[42].population = 1748000;
    prefectures[43].name = "Oita     "; prefectures[43].population = 1135000;
    prefectures[44].name = "Miyazaki "; prefectures[44].population = 1073000;
    prefectures[45].name = "Kagoshima"; prefectures[45].population = 1602000;
    prefectures[46].name = "Okinawa  "; prefectures[46].population = 1453000;
}
