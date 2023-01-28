#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int ALPHABETS = 26;

string ciphering(string plain, string k)
{
    int pl = strlen(plain);
    int key = atoi(k);
    for (int i = 0; i < pl; i++)
    {
        if (isalpha(plain[i]))//見てる文字がアルファベットなら変換
        {

            if (islower(plain[i]))//小文字なら
            {
                plain[i] = 'a' + ((plain[i] - 'a' + key) % 26);
            }
            //小文字で変換
            else //大文字なら
            {
                plain[i] = 'A' + ((plain[i] - 'A' + key) % 26);
            }
            //返還後も大文字に戻す
        }
    }

    return plain;
}

int main(int argc, string argv[])
{
    if (argc != 2)      //引数が2以外なら終了
    {
        printf("Usage: ./substution [key]\n");
        return 1;
    }

    int l = strlen(argv[1]);
    for (int i = 0; i < l; i++)
    {
        //数字でなければ異常終了
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar [key]");
            return 1;
        }
    }

    string plain = get_string("plaintext:  ");

    string ans = ciphering(plain, argv[1]);

    printf("ciphertext: %s\n", ans);

}