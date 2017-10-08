#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int cmp(void *left, void *right)
{
    int *a = (int *)left;
    int *b = (int *)right;
	printf("\na=%d b=%d ", *a, *b);

    if (*a < *b)
        return -1;
    else if (*a == *b)
        return 0;
    else
        return 1;
}
swap(char* left, char* right, size_t size)
{
    char temp;
	for (int i = 0; i<size;i++)
	{
		temp = *(right + i);
		*(right + i) = *(left + i);
		*(left + i) = temp;
	}
}
void sink(int i, char* _ptr,  size_t count, size_t size)
{
    if (2*i+2>count)	//нет детей
        return;	
	if (2*i+2 ==count)	//один ребёнок
	{
		if(cmp(_ptr + i*size, _ptr + (2 * i + 1)* size) < 0)
			swap(_ptr + i*size, _ptr + (2 * i + 1)*size, size);//переделать swap чтобы можно было это прочесть
		return;
	}

	if (cmp(_ptr + i*size, _ptr + (2 * i + 1)* size) < 0)
	{
		if (cmp(_ptr + (2 * i + 1) *size, _ptr + (2 * i + 2) *size) < 0)
		{
			swap(_ptr + i*size, _ptr + (2 * i + 2)*size, size);
			sink(2 * i + 2, _ptr, count, size);
		}
		else
		{
			swap(_ptr + i*size, _ptr + (2 * i+1)*size, size);
			sink(2 * i + 1, _ptr, count, size);
		}
	}
	else
	{
		if (cmp(_ptr + i *size, _ptr + (2*i + 2)*size) < 0)
		{
			swap(_ptr + i*size, _ptr + (2 * i + 2)*size, size);
		}
	}
        return;
}
void heapsort(void *ptr, int count, size_t size,
    int(*cmp)(const void *, const void *))
{
    char*_ptr = (char*)ptr;

    for (int i = count/2; i >= 0; i--)	//делает пирамиду
    {
        sink(i, _ptr, count, size);
    }
	printf(" \n");

    for (int sorted = 1;sorted<count;  sorted++)
    {
		swap(_ptr , _ptr+(count-sorted)*size, size);
        sink(0, _ptr, count-sorted, size);
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
    int sorted[4] = { 1, 2, 3, 4};
    heapsort(sorted, 4, sizeof(int), cmp);
    assert(check_sort(sorted, 4));

	int repeats[4] = { 1, 1, 1, 1 };
	heapsort(repeats, 4, sizeof(int), cmp);
	assert(check_sort(repeats, 4));

    int arr[7] = { 9,2,3,9,5,6,1};
    heapsort(arr, 7, sizeof(int), cmp);
	assert(check_sort(arr, 7));

    for (int i = 10; i <= 100000000; i *= 2)
    {
    	printf("%d", i);
    	time_t rstart = time(NULL);
    	int *arr = random_arr(i, 19);
    	time_t start = time(NULL);
		printf(" \n");
		for (int j = 0; j < i; j++)
		{
			printf(" %d", arr[j]);
		}

    	heapsort(arr, i, sizeof(int), cmp);	
		printf(" \n");
		for (int j = 0; j < i; j++)
		{
			printf(" %d", arr[j]);
		}

    	time_t stop = time(NULL);
    	printf(" %d sec\n", stop - start);
    	assert(check_sort(arr, i));
    	free(arr);
    }
}