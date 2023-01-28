#include <math.h>
#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //各ijに対し計算した平均値を丸めて割り当て
            float ave =  round((image[i][j].rgbtRed +  image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = ave;
            image[i][j].rgbtGreen = ave;
            image[i][j].rgbtBlue = ave;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //各ijに対しセピア色のrgbを式に従い計算
            sepiaRed = round(.393 *  image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            sepiaGreen = round(.349 *  image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            sepiaBlue = round(.272 *  image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            //値を代入
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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
    float t;
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
