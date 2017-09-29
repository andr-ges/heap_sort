#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


void heapsort(void *ptr, size_t count, size_t size,
	int(*cmp)(const void *, const void *))
{	
	

	for(int sorted = 0; sorted<count ;sorted++)
	{
		for (int i = (count-sorted) / 2; i != 0; i--)
		{
			if (cmp((char*)ptr + i*size,
				(char*)ptr + 2 * i*size) < 0) 
			{
				if (cmp((char*)ptr + 2 * i*size,
					(char*)ptr + (2 * i + 1)*size) < 0)
					;//swap 2i+1 and i
				else
					;//swap 2i and  i
			}
			if (cmp((char*)ptr + 2 * i*size,
				(char*)ptr + (2 * i + 1)*size) < 0)

				;//swap 2i and  i
		}
		;//swap sorted and 0
	}
}





int cmp(const void *a, const void *b)
{
	if (&a < &b)
		return 1;
	else if(&a == &b)
		return 0;
	else return -1;
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
bool check_sort(int*arr, size_t size)
{
	if (size == 0)
		return (true);
	size -= 1;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > arr[i + 1])//Выход за размеры массива
			return false;
	}
	return true;
}
main()
{
	int sorted[5] = { 1, 2, 3, 4, 5 };
	heapsort(sorted, 5,sizeof(int),cmp);
	assert(check_sort(sorted, 5));


	int arr[5] = { 5, 1, 4, 2, 3 };
	heapsort(arr, 5,sizeof(int), cmp);
	assert(check_sort(arr, 5));

	for (int i = 10; i <= 100000000; i *= 2)
	{
		printf("%d", i);
		time_t rstart = time(NULL);


		int *arr = random_arr(i, rstart);
		time_t start = time(NULL);
		heapsort(arr, i, sizeof(int), cmp);
		time_t stop = time(NULL);
		printf(" %d sec\n", stop - start);
		assert(check_sort(arr, i));
		free(arr);
	}
}