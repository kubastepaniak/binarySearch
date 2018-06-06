#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *bsearch(const void *key, const void *base,
			  size_t nmemb, size_t size,
			  int (*compar)(const void *, const void *));
int intcompare(const void *a, const void *b);
int charcmp(const void* a, const void* b);
int floatcmp(const void* a, const void* b);
int stringcmp(const void* a, const void* b);

int main(int argc, char const *argv[])
{
	// integers
	int n = 8;
	int intkey = 30;
	int inttab[8] = {10,20,30,40,50,60,70,80};
	void* intoutput = bsearch(&intkey, inttab, n, sizeof(int), intcompare);
	if(intoutput != NULL)
		printf("found: %d\n", *(int*)intoutput);
	else
		printf("%d not found\n", intkey);

	// chars
	n = 12;
	char charkey = 'c';
	char chartab[12] = {'a','b','c','d','e','f','g','h','i','j','k','l'};
	void* charoutput = bsearch(&charkey, chartab, n, sizeof(char), charcmp);
	if(charoutput != NULL)
		printf("found: %c\n", *(char*)charoutput);
	else
		printf("%c not found\n", charkey);

	// floats
	n = 10;
	float floatkey = 2.0;
	float floattab[10] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 2.0, 2.5, 3.0, 4.6};
	void* floatoutput = bsearch(&floatkey, floattab, n, sizeof(float), floatcmp);
	if(floatoutput != NULL)
		printf("found: %f\n", *(float*)floatoutput);
	else
		printf("%f not found\n", floatkey);

	// strings
	n = 9;
	char stringkey[30] = "Zgierska";
	char stringtab[][30] = {"Aleksandrowska", "Brzezinska", "Gdanska", "Konstantynowska", "Lodzka"
						 "Pabianicka", "Szczecinska", "Warszawska", "Zgierska"}; 
	void* stringoutput = bsearch(&stringkey, stringtab, n, sizeof(stringtab[0]), stringcmp);
	if(stringoutput != NULL)
		printf("found: %s\n", (char*)stringoutput);
	else
		printf("%s not found\n", stringkey);

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

int floatcmp(const void* a, const void* b)
{
	if(*(float*)a - *(float*)b > 0) return 1;
	if(*(float*)a - *(float*)b < 0) return -1;
	return 0;
}

int stringcmp(const void* a, const void* b)
{
	return strcmp((const char*)a, (const char*)b);
}