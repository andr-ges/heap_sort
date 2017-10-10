#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int cmp_int(void *left, void *right)
{
    int *a = (int *)left;
    int *b = (int *)right;
 //   printf("\na=%d b=%d ", *a, *b);

    if (*a < *b)
        return -1;
    else if (*a == *b)
        return 0;
    else
        return 1;
}
swap(char* left, char* right, size_t size)
{
    for (int i = 0; i<size; i++)
    {
        char temp = right[i];
        *(right + i) = *(left + i);
        *(left + i) = temp;
    }
}
void sink(int i, char* _ptr, size_t count, size_t size, int(*cmp)(const void *, const void *))
{
    int parent = i;
    int child1 = 2 * i + 1;
    int child2 = 2 * i + 2;
    if (child2>count)	//нет детей
        return;
    if (child2== count)	//один ребёнок
    {
        if (cmp(_ptr + parent*size, _ptr + child1* size) < 0)
            swap(_ptr + parent*size, _ptr + child1*size, size);
        return;
    }

    int max;
    if (cmp(_ptr + parent*size, _ptr + child1* size) < 0)
        max = child1;
    else if (cmp(_ptr + child1 *size, _ptr + child2 *size) < 0)
        max = child2;
    else 
        max = parent;

    if (max != parent)
    {
        swap(_ptr + parent*size, _ptr + max*size, size);
        sink(max, _ptr, count, size, cmp);
    }
}
void heapsort(void *ptr, int count, size_t size,
    int(*cmp)(const void *, const void *))
{
    char*_ptr = (char*)ptr;

    for (int i = count / 2; i >= 0; i--)	//делает пирамиду
    {
        sink(i, _ptr, count, size, cmp);
    }

    for (int sorted = 1; sorted < count; sorted++)
    {
        swap(_ptr, _ptr + (count - sorted)*size, size);
        sink(0, _ptr, count - sorted, size, cmp);
    }

}
int* random_arr(size_t size, time_t rstart)
{
    srand(rstart);
    int* arr = malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand();
    }  return arr;
}
bool check_sort(int*arr, size_t count)
{
    if (count == 0)
        return (true);
    count;
    for (int i = 1; i < count; i++)
    {
        if (arr[i - 1]>arr[i])
        {
            printf("\n%d\n", i);
            return false;
        }
    }
    return true;
}
main()
{
    int sorted[4] = { 1, 2, 3, 4 };
    heapsort(sorted, 4, sizeof(int), cmp_int);
    assert(check_sort(sorted, 4));

    int repeats[4] = { 1, 1, 1, 1 };
    heapsort(repeats, 4, sizeof(int), cmp_int);
    assert(check_sort(repeats, 4));

    int arr[7] = { 9, 2, 3, 9, 5, 6, 1 };
    heapsort(arr, 7, sizeof(int), cmp_int);
    assert(check_sort(arr, 7));

    for (int i = 10; i <= 100000000; i *= 2)
    {
        printf("%d", i);
        time_t rstart = time(NULL);
        int *arr = random_arr(i, time(NULL));
        time_t start = time(NULL);

        heapsort(arr, i, sizeof(int), cmp_int);
      
        time_t stop = time(NULL);
        printf(" %d sec\n", stop - start);
        assert(check_sort(arr, i));
        free(arr);
    }
}