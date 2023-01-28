#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const int TRIAL_COUNT = 1000000; // 試行回数
const int STRLEN_MIN = 3; // 最小文字数
const int STRLEN_MAX = 8; // 最大文字数
const int HASH_RANGE = 256; // ハッシュ値の範囲

unsigned int hash(const string);
char* gen_random_string(const int min, const int max);

int main(void)
{
    // ハッシュ値の出現回数をカウントする配列
    int hash_value_counts[HASH_RANGE] = {0};

    // ランダムに生成した3-8文字で試行回数分ハッシュ値の出現回数を取得する
    srand( (int)time(NULL) );
    for (int i = 0; i < TRIAL_COUNT; i++)
    {
        hash_value_counts[hash(gen_random_string(STRLEN_MIN, STRLEN_MAX))]++;
    }

    // 最も少ないカウントと最も大きなカウントを取得して表示する
    int min = TRIAL_COUNT;
    int max = 0;
    for (int i = 0; i < HASH_RANGE; i++)
    {
        if (min > hash_value_counts[i])
        {
            min = hash_value_counts[i];
        }
        if (max < hash_value_counts[i])
        {
            max = hash_value_counts[i];
        }
    }
    printf("min:%d\n", min);
    printf("max:%d\n", max);
    printf("dif:%d\n", max - min);

    return 0;
}

char* gen_random_string(const int min, const int max) {
    const char alphabets[] = "ABCDEFGHllcIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int size = sizeof(alphabets);
    const int len = rand() % (max - min + 1) + min; // 文字数をランダムに取得する

    char *s = (char *)malloc(sizeof(char)*len);
    for (int i = 0; i < len; ++i) {
        s[i] = alphabets[rand() % (size - 1)];
    }
    s[len] = 0;

    return s;
}

// ハッシュ関数
unsigned int hash(const string word)
{
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += (2 * word[i] * word[i] + 3 * word[i]);
    }
    return (unsigned int)(sum % 256);
}
