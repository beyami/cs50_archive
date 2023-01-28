#include <cs50.h>
#include <stdio.h>

// 都道府県の件数
const int PREFECTURES_COUNT = 47;

// 構造体 都道府県
typedef struct
{
    string name; // 名前
    float area;  // 面積
}
prefecture;

void get_prefectures(prefecture[PREFECTURES_COUNT]);
void rsort_by_area(prefecture[PREFECTURES_COUNT]);
void print_rank(prefecture[PREFECTURES_COUNT]);

// TODO：スワップ関数のプロトタイプ宣言
void swap(prefecture *a, prefecture *b);

int main(void)
{
    // 都道府県を格納する変数を定義
    prefecture prefectures[PREFECTURES_COUNT];
    // 都道府県情報を格納
    get_prefectures(prefectures);
    // 人口の多い順にソート
    rsort_by_area(prefectures);
    // ランキングを簡易グラフ付きでコンソールに出力する
    print_rank(prefectures);

    return 0;
}

// 面積の大きい順(降順)にソート(バブルソート)を行う
void rsort_by_area(prefecture prefectures[PREFECTURES_COUNT])
{
    int exchange; // 交換回数

    do
    {
        exchange = 0;

        // 先頭のデータから最後尾の１つ手前のデータまで繰り返す
        for (int i = 0; i < PREFECTURES_COUNT - 1; i++)
        {
            // もし大小関係が逆であれば、データを交換
            if (prefectures[i].area < prefectures[i + 1].area)
            {
                // prefectures[i]とprefectures[i + 1]をスワップする
                // TODO：スワップ関数の呼び出し
                swap(&prefectures[i], &prefectures[i + 1]);

                // 交換が行われた回数をカウント
                exchange++;
            }
        }

    }
    while (exchange > 0); // 交換が発生していれば処理を続ける
}

// 簡易グラフ付きでコンソールに出力する
void print_rank(prefecture prefectures[PREFECTURES_COUNT])
{
    for (int i = 0; i < PREFECTURES_COUNT; i++)
    {
        // ランキングを出力
        printf("Rank%02d:%s ", i + 1, prefectures[i].name);
        // グラフを描画
        int graph_length = prefectures[i].area / 1000;
        for (int j = 0; j < graph_length; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// スワップ関数
// TODO：引数はポインタで受けとる
//       引数1つ目(a)と引数2つめ(b)の実体(値)を交換する
void swap(prefecture *a, prefecture *b)
{
    prefecture tmp = *a;
    *a = *b;
    *b = tmp;

    return;
}


// 都道府県情報を格納
void get_prefectures(prefecture prefectures[PREFECTURES_COUNT])
{
    prefectures[0].name = "Hokkaido "; prefectures[0].area = 83424.31000;
    prefectures[1].name = "Aomori   "; prefectures[1].area = 9645.59000;
    prefectures[2].name = "Iwate    "; prefectures[2].area = 15275.01000;
    prefectures[3].name = "Miyagi   "; prefectures[3].area = 7282.22000;
    prefectures[4].name = "Akita    "; prefectures[4].area = 11637.54000;
    prefectures[5].name = "Yamagata "; prefectures[5].area = 9323.15000;
    prefectures[6].name = "Fukushima"; prefectures[6].area = 13783.74000;
    prefectures[7].name = "Ibaraki  "; prefectures[7].area = 6097.06000;
    prefectures[8].name = "Tochigi  "; prefectures[8].area = 6408.09000;
    prefectures[9].name = "Gunma    "; prefectures[9].area = 6362.28000;
    prefectures[10].name = "Saitama  "; prefectures[10].area = 3797.75000;
    prefectures[11].name = "Chiba    "; prefectures[11].area = 5157.65000;
    prefectures[12].name = "Tokyo    "; prefectures[12].area = 2190.93000;
    prefectures[13].name = "Kanagawa "; prefectures[13].area = 2415.83000;
    prefectures[14].name = "Niigata  "; prefectures[14].area = 12584.1000;
    prefectures[15].name = "Toyama   "; prefectures[15].area = 4247.61000;
    prefectures[16].name = "Ishikawa "; prefectures[16].area = 4186.09000;
    prefectures[17].name = "Fukui    "; prefectures[17].area = 4190.49000;
    prefectures[18].name = "Yamanashi"; prefectures[18].area = 4465.27000;
    prefectures[19].name = "Nagano   "; prefectures[19].area = 13561.56000;
    prefectures[20].name = "Gifu     "; prefectures[20].area = 10621.29000;
    prefectures[21].name = "Shizuoka "; prefectures[21].area = 7777.42000;
    prefectures[22].name = "Aichi    "; prefectures[22].area = 5172.48000;
    prefectures[23].name = "Mie      "; prefectures[23].area = 5774.4000;
    prefectures[24].name = "Shiga    "; prefectures[24].area = 4017.38000;
    prefectures[25].name = "Kyoto    "; prefectures[25].area = 4612.19000;
    prefectures[26].name = "Osaka    "; prefectures[26].area = 1905.14000;
    prefectures[27].name = "Hyogo    "; prefectures[27].area = 8400.96000;
    prefectures[28].name = "Nara     "; prefectures[28].area = 3690.94000;
    prefectures[29].name = "Wakayama "; prefectures[29].area = 4724.69000;
    prefectures[30].name = "Tottori  "; prefectures[30].area = 3507.05000;
    prefectures[31].name = "Shimane  "; prefectures[31].area = 6708.24000;
    prefectures[32].name = "Okayama  "; prefectures[32].area = 7114.5000;
    prefectures[33].name = "Hiroshima"; prefectures[33].area = 8479.45000;
    prefectures[34].name = "Yamaguchi"; prefectures[34].area = 6112.3000;
    prefectures[35].name = "Tokushima"; prefectures[35].area = 4146.65000;
    prefectures[36].name = "Kagawa   "; prefectures[36].area = 1876.72000;
    prefectures[37].name = "Ehime    "; prefectures[37].area = 5676.11000;
    prefectures[38].name = "Kochi    "; prefectures[38].area = 7103.93000;
    prefectures[39].name = "Fukuoka  "; prefectures[39].area = 4986.4000;
    prefectures[40].name = "Saga     "; prefectures[40].area = 2440.68000;
    prefectures[41].name = "Nagasaki "; prefectures[41].area = 4132.09000;
    prefectures[42].name = "Kumamoto "; prefectures[42].area = 7409.35000;
    prefectures[43].name = "Oita     "; prefectures[43].area = 6340.71000;
    prefectures[44].name = "Miyazaki "; prefectures[44].area = 7735.31000;
    prefectures[45].name = "Kagoshima"; prefectures[45].area = 9186.94000;
    prefectures[46].name = "Okinawa  "; prefectures[46].area = 2281.12000;
}
