#include "helpers.h"
#include "stdio.h"
#include "math.h"

int min_value(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int l = 0; l < height; l++)
    {
        for (int c = 0; c < width; c++)
        {
            int avg = round((image[l][c].rgbtBlue + image[l][c].rgbtGreen + image[l][c].rgbtRed) / 3.0);
            image[l][c].rgbtBlue = avg;
            image[l][c].rgbtGreen = avg;
            image[l][c].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int l = 0; l < height; l++)
    {
        int mid = width / 2;
        for (int i = 0; i < mid; i++)
        {
            RGBTRIPLE aux = image[l][i];
            image[l][i] = image[l][width - i - 1];
            image[l][width - i - 1] = aux;
        }
    }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE old_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            old_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
            old_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            old_image[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    
    for (int l = 0; l < height; l++)
    {
        for (int c = 0; c < width; c++)
        {
            RGBTRIPLE final;
            int rgbtBlue = old_image[l][c].rgbtBlue;
            int rgbtGreen = old_image[l][c].rgbtGreen;
            int rgbtRed = old_image[l][c].rgbtRed;
            int pixels = 1;
            if (l > 0)
            {
                // upper
                rgbtBlue += old_image[l - 1][c].rgbtBlue;
                rgbtGreen += old_image[l - 1][c].rgbtGreen;
                rgbtRed += old_image[l - 1][c].rgbtRed;
                pixels++;
                if (c > 0)
                {
                    // upper-left
                    rgbtBlue += old_image[l - 1][c - 1].rgbtBlue;
                    rgbtGreen += old_image[l - 1][c - 1].rgbtGreen;
                    rgbtRed += old_image[l - 1][c - 1].rgbtRed;
                    pixels++;
                }
                if (c < width - 1)
                {
                    // upper-right
                    rgbtBlue += old_image[l - 1][c + 1].rgbtBlue;
                    rgbtGreen += old_image[l - 1][c + 1].rgbtGreen;
                    rgbtRed += old_image[l - 1][c + 1].rgbtRed;
                    pixels++;
                }
            }
            if (l < height - 1)
            {
                // down
                rgbtBlue += old_image[l + 1][c].rgbtBlue;
                rgbtGreen += old_image[l + 1][c].rgbtGreen;
                rgbtRed += old_image[l + 1][c].rgbtRed;
                pixels++;
                if (c > 0)
                {
                    // down-left
                    rgbtBlue += old_image[l + 1][c - 1].rgbtBlue;
                    rgbtGreen += old_image[l + 1][c - 1].rgbtGreen;
                    rgbtRed += old_image[l + 1][c - 1].rgbtRed;
                    pixels++;
                }
                if (c < width - 1)
                {
                    // down-right
                    rgbtBlue += old_image[l + 1][c + 1].rgbtBlue;
                    rgbtGreen += old_image[l + 1][c + 1].rgbtGreen;
                    rgbtRed += old_image[l + 1][c + 1].rgbtRed;
                    pixels++;
                }
            }
            if (c > 0)
            {
                // left
                rgbtBlue += old_image[l][c - 1].rgbtBlue;
                rgbtGreen += old_image[l][c - 1].rgbtGreen;
                rgbtRed += old_image[l][c - 1].rgbtRed;
                pixels++;
            }
            if (c < width - 1)
            {
                // right
                rgbtBlue += old_image[l][c + 1].rgbtBlue;
                rgbtGreen += old_image[l][c + 1].rgbtGreen;
                rgbtRed += old_image[l][c + 1].rgbtRed;
                pixels++;
            }
            final.rgbtBlue = round(rgbtBlue / (1.0 * pixels));
            final.rgbtGreen = round(rgbtGreen / (1.0 * pixels));
            final.rgbtRed = round(rgbtRed / (1.0 * pixels));
            image[l][c] = final;
        }
    }
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE old_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            old_image[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx_red;
            float Gx_blue;
            float Gx_green;
            float Gy_red;
            float Gy_blue;
            float Gy_green;
            Gx_red = Gx_blue = Gx_green = Gy_red = Gy_blue = Gy_green = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (j + l < 0 || j + l >= width || i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    Gx_red += old_image[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_green += old_image[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_blue += old_image[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_red += old_image[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_green += old_image[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_blue += old_image[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }

            image[i][j].rgbtRed = min_value(255, round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red)));
            image[i][j].rgbtGreen = min_value(255, round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green)));
            image[i][j].rgbtBlue = min_value(255, round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue)));
        }
    }

    return;
}
