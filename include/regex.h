#ifndef REGEX_H
#define REGEX_H

#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 *	Rules
 *		. = any char
 *		* = {0,}
 *		+ = {1,}
 *		? = {0,1}
 *		{n} = n occurences
 *		{n,m} = n to m occurences
 *		[...] = match char from list
 *		(...) = group
 *		| = match one or the other group
 *		\ = escape
 *		\w = alphanumeric or _
 *		\W = !\w
 *		\d = digits = [0-9]
 *		\D = !\d
 *		\s = whitespace
 *		\S = !\s
 *
 ******************************************************************************/

typedef struct Rule {
	char*			r;
	struct Rule*	internals;
	struct Rule* 	next;
	struct Rule*	prev;
} rule;

int isUpper(char c);

int isLower(char c);

int isAlpha(char c);

int isDigit(char c);

int isAlNum(char c);

//find char c in a string str, starting from the end of str
int find(char* str, char c);

//return a string based on the start and finish index, exclusive
char* substr(char* str, int start, int end);

//create a rule struct
void makeRule(char* r, rule* new_rule);

//create a rule struct, and add internals of range rule
void set(char* regexp, rule* new_rule);

//make the complete set of chars based on a range (a-z) inside []
int makeRange(char* regexp, rule* new_rule);

//rule to exactly match a string
int makeExact(char* regexp, rule* new_rule);

//create the tree-based regex, using a recursive approach
rule* constructTree(char *regexp, int regexp_len);

int match(char* str, int str_len, char* regexp, int regex_len);

#endif //REGEX_H
