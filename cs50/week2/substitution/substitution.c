#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int ALPHABETS = 26;

bool check_alpha(string text)
{
    int l = strlen(text);
    for (int i = 0; i < l; i++)
    {
        if (!isalpha(text[i]))//アルファベット出ない文字がカギなら終了
        {
            return false;
        }
    }

    for (int i = 0; i < l; i++)
    {
        for (int j = i + 1; j < l; j++)
        {
            if (text[i] == text[j])//文字被りも終了
            {
                return false;
            }
        }
    }

    return true;//それ以外はok
}

string ciphering(string plain, string cpr)
{
    int pl = strlen(plain);
    for (int i = 0; i < pl; i++)
    {
        if (isalpha(plain[i]))//見てる文字がアルファベットなら変換
        {

            if (islower(plain[i]))//小文字なら
            {
                plain[i] = tolower(cpr[plain[i] - 'a']);
            }
            //変換後も小文字に戻す
            else //大文字なら
            {
                plain[i] = toupper(cpr[plain[i] - 'A']);
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

    int l  = strlen(argv[1]);
    if (l != ALPHABETS)  //長さが26文字以外でも終了
    {
        printf("key must include 26 alphabets\n");
        return 1;
    }

    if (!check_alpha(argv[1]))  //かぶりとアルファベットのチェック
    {
        printf("key must include 26 alphabets\n");
        return 1;
    }

    string plain = get_string("plaintext:  ");

    string ans = ciphering(plain, argv[1]);

    printf("ciphertext: %s\n", ans);

}