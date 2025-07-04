/*
 *  Name: Lucas Kalani Ross
 *  UID: 506372478
 */

#include <stdlib.h>
#include <omp.h>

#include "utils.h"
#include "parallel.h"

/*
 *  PHASE 1: compute the mean pixel value
 *  This code is buggy! Find the bug and speed it up.
 */
void mean_pixel_parallel(const uint8_t img[][NUM_CHANNELS], int num_rows, int num_cols, double mean[NUM_CHANNELS])
{
    int row, col;
    long count = num_rows * num_cols;

    mean[0] = 0.0;
    mean[1] = 0.0;
    mean[2] = 0.0;

    //I arbitrarily choose 5 threads ngl
    #pragma omp parallel for num_threads(5)
    for (row = 0; row < num_rows; row++){ 
        int r_count = 0;
        int g_count = 0;
        int b_count = 0;

        for (col = 0; col < num_cols; col++){
            r_count += img[row * num_cols + col][0];
            g_count += img[row * num_cols + col][1];
            b_count += img[row * num_cols + col][2];
        }
        #pragma omp atomic
        mean[0] += r_count;
        #pragma omp atomic
        mean[1] += g_count;
        #pragma omp atomic
        mean[2] += b_count;
    }
    
    mean[0] /= count;
    mean[1] /= count;
    mean[2] /= count;
}

/*
 *  PHASE 2: convert image to grayscale and record the max grayscale value along with the number of times it appears
 *  This code is NOT buggy, just sequential. Speed it up.
 */
void grayscale_parallel(const uint8_t img[][NUM_CHANNELS], int num_rows, int num_cols, uint32_t grayscale_img[][NUM_CHANNELS], uint8_t *max_gray, uint32_t *max_count)
{
    int row, col, final;
    
    *max_count = 0;
    *max_gray = 0;

    int mg = 0;
    int mc = 0;

    int NT = 50;
    
    #pragma omp parallel for collapse(2) num_threads(NT)
    for (row = 0; row < num_rows; row++){
        for (col = 0; col < num_cols; col++){
            final = (img[row * num_cols + col][0] + img[row * num_cols + col][1] + img[row * num_cols + col][2]) / NUM_CHANNELS;

            grayscale_img[row * num_cols + col][0] = final;
            grayscale_img[row * num_cols + col][1] = final;
            grayscale_img[row * num_cols + col][2] = final;
        }
    }

    #pragma omp parallel for collapse(2) num_threads(NT) reduction(max:mg)
    for (row = 0; row < num_rows; row++){
        for (col = 0; col < num_cols; col++){
            final = grayscale_img[row * num_cols + col][0];
            if (final > mg){
                mg = final;
            }
        }
    }

    #pragma omp parallel for collapse(2) num_threads(NT) reduction(+:mc)
    for (row = 0; row < num_rows; row++){
        for (col = 0; col < num_cols; col++){
            final = grayscale_img[row * num_cols + col][0];
            if (final == mg){
                mc += 3;
            }
        }
    }

    *max_gray = mg;
    *max_count = mc;
}

/*
 *  PHASE 3: perform convolution on image
 *  This code is NOT buggy, just sequential. Speed it up.
 */
void convolution_parallel(const uint8_t padded_img[][NUM_CHANNELS], int num_rows, int num_cols, const uint32_t kernel[], int kernel_size, uint32_t convolved_img[][NUM_CHANNELS])
{
    int row, col, kernel_row, kernel_col;
    int kernel_norm, i;
    int conv_rows, conv_cols;

    // compute kernel normalization factor
    kernel_norm = 0;
    for (i = 0; i < kernel_size * kernel_size; i++)
    {
        kernel_norm += kernel[i];
    }

    // compute dimensions of convolved image
    conv_rows = num_rows - kernel_size + 1;
    conv_cols = num_cols - kernel_size + 1;

    // perform convolution
    #pragma omp parallel for collapse(2) num_threads(150)
    for (row = 0; row < conv_rows; row++)
    {
        for (col = 0; col < conv_cols; col++)
        {
                convolved_img[row * conv_cols + col][0] = 0;
                convolved_img[row * conv_cols + col][1] = 0;
                convolved_img[row * conv_cols + col][2] = 0;
                for (kernel_row = 0; kernel_row < kernel_size; kernel_row++)
                {
                    for (kernel_col = 0; kernel_col < kernel_size; kernel_col++)
                    {
                        convolved_img[row * conv_cols + col][0] += padded_img[(row + kernel_row) * num_cols + col + kernel_col][0] * kernel[kernel_row * kernel_size + kernel_col];
                        convolved_img[row * conv_cols + col][1] += padded_img[(row + kernel_row) * num_cols + col + kernel_col][1] * kernel[kernel_row * kernel_size + kernel_col];
                        convolved_img[row * conv_cols + col][2] += padded_img[(row + kernel_row) * num_cols + col + kernel_col][2] * kernel[kernel_row * kernel_size + kernel_col];
                    }
                }
                convolved_img[row * conv_cols + col][0] /= kernel_norm;
                convolved_img[row * conv_cols + col][1] /= kernel_norm;
                convolved_img[row * conv_cols + col][2] /= kernel_norm;
        }
    }
}