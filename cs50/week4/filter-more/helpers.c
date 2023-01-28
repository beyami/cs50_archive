#include <math.h>
#include <stdio.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //各ijに対し計算した平均値を丸めて割り当て
            double ave =  round((image[i][j].rgbtRed +  image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = ave;
            image[i][j].rgbtGreen = ave;
            image[i][j].rgbtBlue = ave;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //水平方向に反転
            RGBTRIPLE swap = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //返還前の値をコピー
            copy[i][j] = image[i][j];
        }
    }

    int ave_Red, ave_Green, ave_Blue;
    double t;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            t = 0.0;
            ave_Red = 0;
            ave_Green = 0;
            ave_Blue = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k < height) && (i + k >= 0) && (j + l < width) && (j + l >= 0))
                    {
                        //注目ピクセルが範囲内なら平均値用の変数に加算
                        ave_Red += image[i + k][j + l].rgbtRed;
                        ave_Green += image[i + k][j + l].rgbtGreen;
                        ave_Blue += image[i + k][j + l].rgbtBlue;
                        t += 1.0;
                    }
                }
            }
            copy[i][j].rgbtRed = round(ave_Red / t);
            copy[i][j].rgbtGreen = round(ave_Green / t);
            copy[i][j].rgbtBlue = round(ave_Blue / t);
            //加算した回数で除して平均を得、丸めてコピーに代入
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //コピーを戻す
            image[i][j] = copy[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int r, g, b;
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //返還前の値をコピー
            copy[i][j] = image[i][j];
        }
    }

    int gx_r, gx_g, gx_b, gy_r, gy_g, gy_b;
    int cnlx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int cnly[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //それぞれのフィルター後の値を代入するための6つの変数を用意
            gx_r = 0;
            gx_g = 0;
            gx_b = 0;
            gy_r = 0;
            gy_g = 0;
            gy_b = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k < height) && (i + k >= 0) && (j + l < width) && (j + l >= 0))
                    {
                        //注目ピクセルが範囲内ならフィルタをかけた値をそれぞれgx,gyに加算
                        gx_r += cnlx[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                        gx_g += cnlx[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                        gx_b += cnlx[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;
                        gy_r += cnly[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                        gy_g += cnly[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                        gy_b += cnly[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;

                    }
                }
            }

            //２乗和の平方根を最近点丸めで代入
            r = round(sqrt((gx_r * gx_r) + (gy_r * gy_r)));
            g = round(sqrt((gx_g * gx_g) + (gy_g * gy_g)));
            b = round(sqrt((gx_b * gx_b) + (gy_b * gy_b)));

            //r,g,bのそれぞれと255のうち小さい方を返却
            (r > 255) ? (copy[i][j].rgbtRed = 255) : (copy[i][j].rgbtRed = r);
            (g > 255) ? (copy[i][j].rgbtGreen = 255) : (copy[i][j].rgbtGreen = g);
            (b > 255) ? (copy[i][j].rgbtBlue = 255) : (copy[i][j].rgbtBlue = b);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //コピーを戻す
            image[i][j] = copy[i][j];
        }
    }
    return;
}
