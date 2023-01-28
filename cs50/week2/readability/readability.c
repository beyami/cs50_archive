#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text)
{
    int ltrs = 0, l = strlen(text);

    for (int i = 0; i < l; i++)
    {
        if (isalnum(text[i]))//英数字ならカウント増加
        {
            ltrs++;
        }
    }

    return ltrs;
}

int count_words(string text)
{
    int words = 0, l = strlen(text);
    for (int i = 0; i < l; i++)
    {
        if (text[i] == ' ')//スペース区切りで単語判定
        {
            words++;
        }
    }

    return words + 1;
}

int count_sentences(string text)
{
    int stcs = 0, l = strlen(text);
    for (int i = 0; i < l; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            //ピリオド、!,?なら文の区切り
            stcs++;
        }
    }

    return stcs;
}

int main(void)
{
    string text = get_string("Text: ");

    int ltrs = count_letters(text);
    int words = count_words(text);
    int stcs = count_sentences(text);

    float L = (float)ltrs / words * 100.0, S = (float)stcs / words * 100.0;
    //係数の計算

    float index = 0.0588 * L - 0.296 * S - 15.8;
    //指数計算

    int ans = (int)round(index);
    if (ans >= 16)
    {
        printf("Grade 16+\n");
    }//16以上なら例外表示
    else if (ans < 1)
    {
        printf("Before Grade 1\n");
    }//1未満でも例外表示
    else
    {
        printf("Grade %d\n", ans);
    }//上記以外の場合,そのまま表示

    return 0;
}
