#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


void heapsort(void *ptr, size_t count, size_t size,
	int(*cmp)(const void *, const void *))
{	
	void *temp = malloc(size);
	if (temp == NULL)
		printf("out of memory");

	char*_ptr = (char*)ptr;

	for(int sorted = 0; sorted<count; sorted++)
	{
		for (int i = (count-sorted) / 2; i != 0; i--)
		{
			if (cmp(_ptr + i*size,
				_ptr + 2 * i*size) < 0) 
			{
				if (cmp(_ptr + 2 * i*size,
					_ptr + (2 * i + 1)*size) < 0)
				{	//swap 2i+1 and i
					memcpy(temp,_ptr + (2 * i)+1*size,size);
					memcpy(_ptr + (2 * i + 1)*size, _ptr + i*size, size);
					memcpy(_ptr + i*size, temp, size);
				}
				else	
				{	//swap 2i and  i
					memcpy(temp, _ptr + (2 * i) * size, size);
					memcpy(_ptr + (2 * i)*size, _ptr + i*size, size);
					memcpy(_ptr + i*size, temp, size);
				}
			}
			if (cmp(_ptr + 2 * i*size,
				_ptr + (2 * i + 1)*size) < 0)
			{	//swap 2i and  i
				memcpy(temp, _ptr + (2 * i) * size, size);
				memcpy(_ptr + (2 * i)*size, _ptr + i*size, size);
				memcpy(_ptr + i*size, temp, size);
			}
				
		}
		
		{	//swap sorted and 0
			memcpy(temp, _ptr + (sorted)* size, size);
			memcpy(_ptr + (sorted)*size, _ptr, size);
			memcpy(_ptr, temp, size);	
		}
	}
	free(temp);
}


int cmp(void *left, void *right)

{
	int *a = (int *)left;
	int *b = (int *)right;

	if (*a < *b)
		return 1;
	else if (*a == *b)
		return 0;
	else
		return -1;
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
		if (arr[i] > arr[i + 1])
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