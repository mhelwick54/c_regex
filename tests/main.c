#include "../include/regex.h"

#include <stdio.h>
#include <string.h>

#define REGEX_LEN 128
#define STR_LEN 512

void stripNewline(char* str);

int main() {
	printf("Enter regex: ");
	char* regexp = malloc(REGEX_LEN * sizeof(char));
	fgets(regexp, REGEX_LEN - 1, stdin);
	stripNewline(regexp);

	printf("Enter string to be matched: ");
	char* str = malloc(STR_LEN * sizeof(char));
	fgets(str, STR_LEN - 1, stdin);
	stripNewline(str);

	if(match(str, strlen(str), regexp, strlen(regexp))) {
		printf("%s matches %s\n", str, regexp);
	} else {
		printf("%s does not match %s\n", str, regexp);
	}

	free(str);
	free(regexp);

	return 0;
}

void stripNewline(char* str) {
	int i = strlen(str) - 1;
	while(str[i] != '\n') {
		--i;
	}
	str[i] = '\0';
}
