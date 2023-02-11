/*
与えられた高さ(1-8)のマリオのレンガのような#を表示するプログラム
例:高さ3の場合
  # #
 ## ##
### ###
*/

#include <cs50.h>
#include <stdio.h>

void brick(int w, int h)
{
    for (int i = 0; i < h - w; i++)
    {
        printf(" ");
    }

    for (int i = 0; i < w; i++)
    {
        printf("#");
    }

    printf("  ");

    for (int i = 0; i < w; i++)
    {
        printf("#");
    }

    printf("\n");
}

int main(void)
{
    int h;
    do
    {
        printf("Height: ");
        scanf("%d", &h);
    }
    while (h < 1 || h > 8);

    for (int i = 1; i <= h; i++)
    {
        brick(i, h);
    }
}
