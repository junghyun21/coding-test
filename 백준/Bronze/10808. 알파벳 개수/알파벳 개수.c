#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define ALPHABET 26

int main()
{
	int i, idx, len, alphabet[ALPHABET] = {0, };
	char str[MAX_SIZE];

	scanf("%s", str);

	len = strlen(str);

	for(i = 0; i < len; i++){
		idx = str[i] > 'Z' ? str[i] - 'a' : str[i] - 'A';
		++alphabet[idx];
	}
	
	for(i = 0; i < ALPHABET; i++)
		printf("%d ", alphabet[i]);
	printf("\n");

	return 0;
}