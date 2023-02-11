/*
クレジットカードの番号が実際に存在するか
チェックサムなどの条件を満たしているか調べるプログラム
*/

#include <cs50.h>
#include <stdio.h>

int digitsum(int x)  //各桁の合計を出す
{
    int ans = 0;
    while (x > 0)
    {
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

int main(void)
{
    long a[100];
    int p, odd = 0, even = 0, i = 0;
    long n = get_long("Number: ");

    while (n > 0)  //配列に一の位から順に各桁の値を代入
    {
        a[i] = n % 10;
        n /= 10;
        i++;
    }

    for (int j = 0; j <= i; j++)  //iの偶奇で判断
    {
        if (j % 2 == 1)
        {
            p = 2 * a[j];
            odd += digitsum(p);  //奇数なら2倍して各桁の和をとる
        }
        else
        {
            even += a[j]; //偶数ならそのまま各桁の和をとる
        }
    }


    if ((odd + even) % 10 != 0)//偶奇の和が10で割り切れなければ不適
    {
        printf("INVALID\n");
        return 0;
    }


    //各カード判別
    if (a[i - 1] == 4 && (i == 13 || i == 16))
    {
        printf("VISA\n");
    }
    else if (i == 16 && a[i - 1] == 5 && a[i - 2] < 6 && a[i - 2] > 0)
    {
        printf("MASTERCARD\n");
    }
    else if (i == 15 && a[i - 1] == 3 && ((a[i - 2] == 3) || (a[i - 2] == 7)))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
