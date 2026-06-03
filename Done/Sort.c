#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int *arr;
int n;
void print()
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
    }
}

void merge(int l, int m1, int m2, int r)
{
    int temp[r - l + 1];
    int i = l;
    int j = m1 + 1;
    int k = m2 + 1;
    int index = 0;
    while (i <= m1 && j <= m2 && k <= r)
    {
        if (arr[i] <= arr[j] && arr[i] <= arr[k])
            temp[index++] = arr[i++];
        else if (arr[j] <= arr[i] && arr[j] <= arr[k])
            temp[index++] = arr[j++];
        else if (arr[k] <= arr[j] && arr[k] <= arr[i])
            temp[index++] = arr[k++];
    }
    while (i <= m1 && j <= m2)
    {
        if (arr[i] <= arr[j])
            temp[index++] = arr[i++];
        else if (arr[j] <= arr[i])
            temp[index++] = arr[j++];
    }
    while (j <= m2 && k <= r)
    {
        if (arr[j] <= arr[k])
            temp[index++] = arr[j++];
        else if (arr[k] <= arr[j])
            temp[index++] = arr[k++];
    }
    while (i <= m1 && k <= r)
    {
        if (arr[i] <= arr[k])
            temp[index++] = arr[i++];
        else if (arr[k] <= arr[i])
            temp[index++] = arr[k++];
    }
    while (i <= m1)
        temp[index++] = arr[i++];
    while (j <= m2)
        temp[index++] = arr[j++];
    while (k <= r)
        temp[index++] = arr[k++];

    for (int i = 0; i < index; i++)
    {
        arr[l + i] = temp[i];
    }
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int pivot(int start, int end)
{
    int p = arr[end];
    int i = start - 1;
    for (int j = start; j < end; j++)
    {
        if (arr[j] <= p)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[end]);
    return i + 1;
}
void quickSort(int start, int end)
{
    if (start >= end)
        return;
    int p = pivot(start, end);
    quickSort(start, p - 1);
    quickSort(p + 1, end);
}
void mergeSort(int start, int end)
{
    if (start >= end)
        return;
    int m1 = start + (end - start) / 3;
    int m2 = start + 2 * (end - start) / 3;
    mergeSort(start, m1);
    mergeSort(m1 + 1, m2);
    mergeSort(m2 + 1, end);
    merge(start, m1, m2, end);
}
int main()
{
    printf("Enter the number of elements : ");
    scanf("%d", &n);
    printf("Enter the elements : ");
    arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    quickSort(0, n - 1);
    print();
}