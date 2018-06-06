#include <stdlib.h>
#include <stdio.h>

void *bsearch(const void *key, const void *base,
			  size_t nmemb, size_t size,
			  int (*compar)(const void *, const void *));
int intcompare(const void *a, const void *b);
int charcmp(const void* a, const void* b);

int main(int argc, char const *argv[])
{
	// integers
	int n = 8;
	int intkey = 30;
	int inttab[8] = {10,20,30,40,50,60,70,80};
	void* intoutput = bsearch(&intkey, inttab, n, sizeof(int), intcompare);
	if(intoutput != NULL)
		printf("%d\n", *(int*)intoutput);

	// chars
	n = 12;
	char charkey = 'c';
	char chartab[12] = {'a','b','c','d','e','f','g','h','i','j','k','l'};
	void* charoutput = bsearch(&charkey, chartab, n, sizeof(char), charcmp);
	if(charoutput != NULL)
		printf("%c\n", *(char*)charoutput);

	return 0;
}

void *bsearch(const void *key, const void *base,
			  size_t nmemb, size_t size,
			  int (*compar)(const void *, const void *))
{
	int low, high, mid, compValue;
	void* midElement;

	low = 0;
	high = nmemb - 1;

	while(low <= high && low < (nmemb - 1) && high >= 0)
	{
		mid = ((high - low) / 2) + low;
		midElement = ((char*) base) + (mid * size);
		compValue = compar(midElement, key);

		if(compValue < 0)
			low = mid + 1;
		else if(compValue > 0)
			high = mid - 1;
		else
			return midElement;
	}
	return NULL;
}

int intcompare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int charcmp(const void* a, const void* b)
{
	return (*(char*)a - *(char*)b);
}
