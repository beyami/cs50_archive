#include <cs50.h>
#include <stdio.h>

void brick(int w, int h)
{
    for (int i = 0; i < h - w; i++)//w段目はh-wだけ空白出力
    {
        printf(" ");
    }

    for (int i = 0; i < w; i++)//残ったwだけ#出力
    {
        printf("#");
    }

    printf("\n");
}

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8); //条件に合うまで入力を取得

    for (int i = 1; i <= n; i++)//各行についてbrick
    {
        brick(i, n);
    }
}