#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //引数不正の場合使い方を返し異常終了
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "r");

    //cdファイルが存在しなかった場合返却
    if (raw_file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }


    //処理を進めるためここで初めて変数を宣言
    FILE *out_file = NULL;
    BYTE buffer[512];
    int jpeg = 0;
    char fname[8] = {0};

    //ファイルの最後まで読み込み
    while (fread(&buffer, sizeof(char), 512, raw_file))
    {
        //最初がjpegならば処理
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //一回目以外は以前開いてたファイルを閉じる
            if (jpeg != 0)
            {
                fclose(out_file);
            }

            sprintf(fname, "%03d.jpg", jpeg++);
            out_file = fopen(fname, "w");
        }

        //回数が0でない ==　ファイルが見つかっている場合、書き込み
        if (jpeg != 0)
        {
            fwrite(&buffer, sizeof(char), 512, out_file);
        }

    }

    //ファイルを閉じる
    fclose(raw_file);
    fclose(out_file);

    return 0;

}