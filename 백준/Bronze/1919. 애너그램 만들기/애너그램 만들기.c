#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000
#define ALPHABET 26

int main()
{
	char str1[MAX_SIZE], str2[MAX_SIZE];
	int str1_alphabet[ALPHABET] = {0, };
	int str2_alphabet[ALPHABET] = {0, };
	int str1_len, str2_len, i, cnt = 0;

	scanf("%s", str1);
	scanf("%s", str2);

	str1_len = strlen(str1);
	str2_len = strlen(str2);

	for(i = 0 ; i < str1_len; i++)
		++str1_alphabet[str1[i] - 'a'];

	for(i = 0 ; i < str2_len; i++)
		++str2_alphabet[str2[i] - 'a'];

	for(i = 0; i < ALPHABET; i++)
		if(str1_alphabet[i] != str2_alphabet[i])
			cnt += (str1_alphabet[i] > str2_alphabet[i] ? str1_alphabet[i] - str2_alphabet[i] : str2_alphabet[i] - str1_alphabet[i]);

	printf("%d\n", cnt);

	return 0;
}