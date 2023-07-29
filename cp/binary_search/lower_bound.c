#include <stdio.h>
#include <stdlib.h>

int floor_division(int a, int b)
{
    return a + b >> 1;
}
int ceiling_division(int a, int b)
{
    return a + b + 1 >> 1;
}

int lower_bound_0(int arr[], int size, int key)
{
    int left = 0, right = size - 1;
    
    if(key < arr[left])
    {
        return left - 1;
    }
    
    while(left < right - 1)
    {
        int mid = floor_division(right, left);
        if(arr[mid] <= key)
        {
            left = mid;
        }
        else
        {
            right = mid - 1;
        }
    }

    if(arr[right] <= key)
    {
        return right;
    }
    return left;
}
int lower_bound_1(int arr[], int size, int key)
{
    int left = 0, right = size - 1;
    
    if(arr[left] > key)
    {
        return left - 1;
    }

    while(left < right)
    {
        int mid = ceiling_division(right, left);
        
        if(arr[mid] <= key)
        {
            left = mid;
        }
        else
        {
            right = mid - 1;
        }
    }
    return left;
}

int lower_bound_2(int arr[], int size, int key)
{
    int idx = -1;
    int left = 0, right = size - 1;
    
    while(left <= right)
    {
        int mid = left + right >> 1;
        if(arr[mid] <= key)
        {
            idx = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return idx;
}


int *arr_generate(int max, int rep)
{
    int *arr = malloc(sizeof(int) * max * rep);
    
    int idx = 0;
    for(int i = 0; i < max; i++)
    {
        for(int j = 0; j < rep; j++)
        {
            arr[idx] = i + 1, idx++;
        }
    }

    // for(int i = 0; i < max * rep; i++)
    // {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");

    return arr;
}

void evaluate(int key, int arr[], int size)
{
    int val = arr[0];
    for(int i = 0; i < size; i++)
    {
        if(arr[i] != val)
        {
            printf("\e[31merror:\e[m key: %d | ", key);
            for(int i = 0; i < size; i++)
            {
                printf("%d ", arr[i]);
            }
            printf("\n");
            exit(EXIT_FAILURE);
        }
    }
    // printf("(%d) ", val);
}

int main()
{
    int max = 101, rep = 5;

    int *arr = arr_generate(max, rep);
    int size = max * rep;
    
    for(int i = 0; i <= max; i++)
    {
        // printf("%d ", lower_bound_1(arr, size, i));
        int ans[] = {lower_bound_0(arr, size, i), lower_bound_1(arr, size, i), lower_bound_2(arr, size, i)};

        evaluate(i, ans, sizeof(ans) / sizeof(int));
    }
    printf("\e[1;32mOK\e[m!\n");

    return 0;
}