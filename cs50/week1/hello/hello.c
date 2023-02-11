/*
hello, {取得文字列}
を表示するプログラム
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n"); //名前を取得
    printf("hello, %s\n", name); //取得した名前の表示
}
