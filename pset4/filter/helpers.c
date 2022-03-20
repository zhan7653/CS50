#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum[3] = {0};
            float number = 0.0;
            for (int k1 = i - 1; k1 <= i + 1; k1++)
            {
                if (k1 < 0 || k1 >= height)
                {
                    continue;
                }
                for (int k2 = j - 1; k2 <= j + 1; k2++)
                {
                    if (k2 < 0 || k2 >= width)
                    {
                        continue;
                    }
                    
                    sum[0] += image[k1][k2].rgbtRed;
                    sum[1] += image[k1][k2].rgbtGreen;
                    sum[2] += image[k1][k2].rgbtBlue;
                    number++;
                }
            }
            tmp[i][j].rgbtRed = round(sum[0] / number);
            tmp[i][j].rgbtGreen = round(sum[1] / number);
            tmp[i][j].rgbtBlue =  round(sum[2] / number);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}

// Limit a number to 255
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    int kernelx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernely[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx[3] = {0};
            int gy[3] = {0};
            int value[3] = {0};

            for (int k1 = -1; k1 <= 1; k1++)
            {
                if (k1 + i < 0 || k1 + i >= height)
                {
                    continue;
                }
                
                for (int k2 = -1; k2 <= 1; k2++)
                {
                    if (k2 + j < 0 || k2 + j >= width)
                    {
                        continue;
                    }
                    
                    gx[0] += kernelx[k1 + 1][k2 + 1] * image[k1 + i][k2 + j].rgbtRed;
                    gy[0] += kernely[k1 + 1][k2 + 1] * image[k1 + i][k2 + j].rgbtRed;
                    gx[1] += kernelx[k1 + 1][k2 + 1] * image[k1 + i][k2 + j].rgbtGreen;
                    gy[1] += kernely[k1 + 1][k2 + 1] * image[k1 + i][k2 + j].rgbtGreen;
                    gx[2] += kernelx[k1 + 1][k2 + 1] * image[k1 + i][k2 + j].rgbtBlue;
                    gy[2] += kernely[k1 + 1][k2 + 1] * image[k1 + i][k2 + j].rgbtBlue;
                }
            }
            for (int n = 0; n < 3; n++)
            {
                value[n] = limit(round(sqrt(gx[n] * gx[n] + gy[n] * gy[n])));
            }
            tmp[i][j].rgbtRed = value[0];
            tmp[i][j].rgbtGreen = value[1];
            tmp[i][j].rgbtBlue =  value[2];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}


