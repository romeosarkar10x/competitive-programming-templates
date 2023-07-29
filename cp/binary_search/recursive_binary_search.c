#include <stdio.h>
#include <stdlib.h>

int recursive_binary_search_key;
int recursive_binary_search(int arr[], int size)
{
    switch(size)
    {
        case 0:
            return -1;
        case 1:
            return (recursive_binary_search_key == arr[0]) ? 0 : -1;
        default:
            break;
    }

    int mid = size + 1 >> 1;
    if(arr[mid] < recursive_binary_search_key)
    {
        int ret = recursive_binary_search(arr + mid + 1, size - mid - 1);
        if(-1 == ret)
        {
            return -1;
        }
        return ret + mid + 1;
    }
    else if(arr[mid] == recursive_binary_search_key)
    {
        return mid;
    }
    else
    {
        int ret = recursive_binary_search(arr, mid);
        if(-1 == ret)
        {
            return -1;
        }
        return ret;
    }
}

int binary_search(int arr[], int size, int key)
{
    recursive_binary_search_key = key;
    recursive_binary_search(arr, size);
}

int *arr_generate(int size)
{
    int *arr = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++)
    {
        arr[i] = (i << 1) + 1;
    }

    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return arr;
}

int main()
{
    int n = 100;
    int *arr = arr_generate(n);

    for(int i = 0; i <= n << 1; i++)
    {
        int ret = binary_search(arr, n, i);
        if(ret >= 0)
        {
            printf("%d ", ret);
        }
        else
        {
            printf("\e[90m-1\e[m ");
        }
    }

    return 0;
}