#include "../include/regex.h"

int isUpper(char c) {
	return (c > 65 && c < 91);
}

int isLower(char c) {
	return (c > 96 && c < 123);
}

int isAlpha(char c) {
	return (isUpper(c) || isLower(c));
}

int isDigit(char c) {
	return (c > 47 && c < 58);
}

int isAlNum(char c) {
	return (isAlpha(c) || isDigit(c));
}

//find char c in a string str, starting from the end of str
int find(char* str, char c) {
	int i = strlen(str) - 1;
	while(i >= 0) {
		if(str[i] == c) {
			return i;
		}
		--i;
	}
}

//return a string based on the start and finish index, exclusive
char* substr(char* str, int start, int end) {
	char* ret = malloc((end - start) * sizeof(char));
	int i = 0;
	int j = 0;
	for(i = start + 1; i < end; ++i) {
		ret[j] = str[i];
		++j;
	}
	ret[j] = '\0';
	return ret;
}

int checkChar(char* str, char c) {
	int i = strlen(str) - 1;
	int count = 0;
	while(i >= 0) {
		if(str[i] == c) {
			count++;
		}
		--i;
	}
	return count;
}

//create a rule struct
void makeRule(char* r, rule* new_rule) {
	new_rule->r = r;
}

//create a rule struct, and add internals of range rule
void set(char* regexp, rule* new_rule) {
	makeRule("[]", new_rule);
	new_rule->internals = constructTree(regexp, strlen(regexp));
}

//create a rule to match a group
void group(char* regexp, rule* new_rule) {

}

//create a rule based on an escape character or a special escaped rule
void backslash(char* regexp, rule* new_rule) {

}

//make the complete set of chars based on a range (a-z) inside []
int makeRange(char* regexp, rule* new_rule) {

}

//rule to exactly match a string
int makeExact(char* regexp, rule* new_rule) {
	int i = 0;
	int len = strlen(regexp);
	while(isAlNum(regexp[i]) && i < len) {
		++i;
	}
	makeRule(substr(regexp, 0, i - 1), new_rule);
	return i;
}

//create the tree-based regex, using a recursive approach
rule* constructTree(char *regexp, int regexp_len) {
	rule* head = malloc(sizeof(rule));
	switch(regexp[0]) {
		case '.': makeRule(".", head);
			head->next = constructTree(substr(regexp, 1, strlen(regexp)), strlen(regexp));
			break;
		case '[': set(substr(regexp, 0, find(regexp, ']')), head);
			head->next = constructTree(substr(regexp, find(regexp, ']'), strlen(regexp)), strlen(regexp) - find(regexp, ']'));
			break;
		case '(': group(regexp, head);
			break;
		case '\\': backslash(regexp, head);
			break;
		default:
			if(isAlNum(regexp[0])) {
				int end = 0;
				if(checkChar(regexp, '-') > 0) {
					end = makeRange(regexp, head);
				} else {
					end = makeExact(regexp, head);
				}
				head->next = constructTree(substr(regexp, end, strlen(regexp)), strlen(regexp) - end);
			}
	}

}

int match(char* str, int str_len, char* regexp, int regexp_len) {
	rule* tree = constructTree(regexp, regexp_len);

	return 1;
}
