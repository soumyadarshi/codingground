#include <stdio.h>
/*
This programm will solve maximum subarray problem;
given an array, we need to find out the contiguous memory chunk
in which sum of the elements are maximum.
*/

int findMaxCrossingMid(int *a, int low, int mid,
                int high, int *max_left, int *max_right)
{
    int left_sum = -999999;
    int right_sum = -999999;
    int sum = 0;
    int i;
    
    static int x = 0;
    //printf("hi [%d]\n", x++);
    
    
    for (i = mid; i >= low; i--) {
        sum += a[i];
        if (sum > left_sum) {
            left_sum = sum;
            *max_left = i;
        }
    }
    
    sum = 0;
    for (i = mid + 1; i <= high; i++) {
        sum += a[i];
        if (sum > right_sum) {
            right_sum = sum;
            *max_right = i;
        }
    }
    //printf("sss max_left[%d] max_right[%d] sum[%d]\n", *max_left, *max_right, right_sum + left_sum);
    return right_sum + left_sum;
}

int findMaxSubArray(int *a, int low, int high, int *result_low, int *result_high)
{
    int mid = (high + low)/2;
    int left_low, left_high, right_low, right_high, cross_low, cross_high;
    int left_sum, right_sum, cross_sum;
    
    if (low == high) {
        *result_low = *result_high = low;
        return a[low];
    }
    
    left_sum = findMaxSubArray(a, low, mid, &left_low, &left_high);
    //printf("1st low[%d] mid[%d] high[%d]\n", low, mid, high);
    right_sum = findMaxSubArray(a, mid + 1, high, &right_low, &right_high);
    //printf("2st low[%d] mid[%d] high[%d]\n", low, mid, high);
    cross_sum = findMaxCrossingMid(a, low, mid, high, &cross_low, &cross_high);
    //printf("cross_low[%d] cross_high[%d]\n", cross_low, cross_high);

    if (left_sum >= right_sum && left_sum >= cross_sum) {
        *result_low = left_low; *result_high = left_high;
        return left_sum;
    } else if (right_sum >= left_sum && right_sum >= cross_sum) {
        *result_low = right_low; *result_high = right_high;
        return right_sum;
    } else {
        *result_low = cross_low; *result_high = cross_high;
        return cross_sum;
    }
}

int main()
{
    int maxSum, low, high;
    int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    //int a[] = {5, 6, -20, 3, 4};
    maxSum = findMaxSubArray(a, 0, 15, &low, &high);
    printf("maxSum[%d] low[%d] high[%d]\n", maxSum, low, high);
    return 0;
}

