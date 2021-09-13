/*Assigned by:
1. Daniel_Ashorov 313458242 // Group: 61108-37
2. Ori_Goldenberg 311119523 // Group: 61108-34
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h> 

/*Functions Declaration: */ 
void freeMatrix(char **c, int n);
void printMatrix(char **a, int rows);
char* creatingString(void);
int sizeCheck(char *str, int *i);
void printFile(char* filename);
char **split(char *str, char letter, int *size);
char* clearDigitsAndSpaces(char *);
char commonestLetter(char* filename);
void createFile(char* filename);
char checkingLetter(int *arr);
void decode(char *str);
void memoryReport(char *, char *);

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();
void Ex4();
void Ex5();

/* Declarations of other functions */

/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= 5; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-5 : ");
				scanf("%d", &select);
			} while ((select < 0) || (select > 5));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			case 4: Ex4(); break;
			case 5: Ex5(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}

///////////////////////////////////helping functions//////////////////////////

void freeMatrix(char **c, int n) { // free dynamic matrix
	int i;
	for (i = 0; i < n; i++)
		free(c[i]);
	free(c);
}

char* creatingString(void) { // creating minimal string
	int size;
	char temp[100], *NewString;
	fgets(temp, sizeof(temp), stdin);
	size = strlen(temp);
	NewString = (char*) malloc (size * sizeof(char));
	assert (NewString);
	if (size > 0 && temp[size - 1] == '\n') {
		temp[size - 1] = '\0';
	}
	strcpy (NewString, temp);
	return NewString;
}

void printMatrix(char **a, int rows) { // printing dynamic matrix
	int i, j;
	if (a == NULL) {
		printf("f");
		return;
	}
	for (i = 0; i < rows; i++) {
		printf("(%d)  ", i + 1);
		j = 0;
		while (a[i][j] != '\0') {
			printf("%c", a[i][j]);
			j++;
		}
		printf("\n");
	}
}

void printFile(char* filename) { // printing file data
	FILE *file;
	if (!(file = fopen(filename, "r"))) {
		printf("Cannot open file \"input.txt\"\n");
		return;
	}
	while (!(feof(file)))
		printf("%c", fgetc(file));
	fclose(file);
}

int sizeCheck(char *string, int *i) {
	int size = 0;
	if (string[*i] != '\0') {
		if (string[*i] != '[') {
			(*i)++;
			return 1;
		}
		(*i)++;
		while (string[*i] != ']') {
			size = size * 10 + (string[*i] - '0');
			(*i)++;
		}
		(*i)++;
		if (string[*i] == '=')
			while (string[*i] != '}' && string[*i] != '"')
				(*i)++;
		while (string[*i] != ';' && string[*i] != ',')
			(*i)++;
		(*i)++;
	}
	return size;
}

/////////////////////////////////////////////    EX1     ///////////////////////////////////////////////////


void Ex1() {
	char *string, letter;
	char** Matrix;
	int dynamic;
	printf("Please enter your text: \n");
	while (getchar() != '\n'); 
	string = creatingString();
	printf("Please enter a lower-case (words that statring with this lower case will apper): \n");
	scanf("%c", &letter);
	Matrix = split(string, letter, &dynamic);
	if (dynamic) {
		printf("The words that begin with '%c' at the begging are: \n", letter);
		printMatrix(Matrix, dynamic);
	}
	else
		printf("There are no words that begin with the lower-case '%c' at thier beginning!\n", letter);
	freeMatrix(Matrix, dynamic);
	free(string);
	printf("\n");
}

int CountWords(char *str, char letter) {
	int i = 0, counter = 0;
	for (i; str[i] != '\0'; i++) {
		if (i == 0 && (str[i] == letter || tolower(str[i]) == letter))
			counter++;
		else if ((str[i] == letter || tolower(str[i]) == letter) && str[i - 1] == ' ')
			counter++;
	}
	return counter;
}

char **split(char *str, char letter, int *size) {
	char **list;
	int i, j = 0, counter = 0;
	*size = CountWords(str, letter);
	if (*size == 0)
		return 0; //masho
	list = (char**)malloc(sizeof(char*)*(*size));
	assert(list);
	for (i = 0; str[i] != '\0'; i++) {
		if ((i == 0 && (str[i] == letter || tolower(str[i]) == letter)) || ((str[i] == letter || tolower(str[i]) == letter) && str[i - 1] == ' ')) {
			while ((str[i] != ' ') && (str[i] != '\0')) {
				counter++;
				i++;
			}
			list[j] = (char*)malloc((counter + 1) * sizeof(char));
			assert(list[j]);
			strncpy(list[j], str + i - counter, counter);
			list[j][counter] = '\0';
			j++;
		}
		counter = 0;
	}
	return list;
}

/////////////////////////////////////////////    EX2     ///////////////////////////////////////////////////

void Ex2() {
	char *string, *newStr;
	printf("Please enter your string: ");
	while (getchar() != '\n'); 
	string = creatingString();
	newStr = clearDigitsAndSpaces(string);
	printf("Your new string after deleting:\n");
	puts(newStr);
	free(newStr);
	free(string);
	printf("\n");
}

char* clearDigitsAndSpaces(char *string) {
	int i, j = 0, size;
	char *newStr;
	size = strlen(string);
	newStr = (char*)malloc(size * sizeof(char)); // creating a new string 
	assert(newStr); // For checking allocation 
	for (i = 0; i < size; i++)
		if ((string[i] > '9') || (string[i] < '0') && string[i] != ' ')
			newStr[j++] = string[i];
	newStr = (char*) realloc (newStr, (j + 1) * sizeof(char));
	newStr[j] = '\0'; // when finished
	return newStr;
}

/////////////////////////////////////////////    EX3     ///////////////////////////////////////////////////

void Ex3() {
	char character;
	while (getchar() != '\n'); 
	character = commonestLetter("input.txt");
	if (character)
		printf("The commonest letter in the file is: %c\n", character);
	else
		printf("No letters in the file! please try again.\n");
	printf("\n");
}

void createFile(char* filename) {
	FILE *file;
	char *str;
	if (!(file = fopen(filename, "w"))) {
		printf("Impossible to open file \"input.txt\"\n Please fix it.\n");
		return;
	}
	printf("Please enter your data: \n");
	str = creatingString();
	fputs(str, file);
	fclose(file);
	free(str);
}

char commonestLetter(char* filename) {
	FILE *file;
	int counter[26] = { 0 }; 
	char character = 'c';
	createFile("input.txt"); // Creating a file as requested
	if (!(file = fopen(filename, "r"))) { 
		printf("Impossible to open file \"input.txt\"\n Please fix it.");
		return 0;
	}
	character = fgetc(file);
	while (!(feof(file))) { 
		if (isalpha(character)) { // checking if abc charactars
			character = toupper (character); // converting lower-case letters to uppercase letters
			counter [character - 'A']++;
		}
		character = fgetc(file);
	}
	if (ftell(file)) 
		character = checkingLetter(counter);
	else // if the file is empty
		character = 0;
	fclose(file);
	return character;
}

char checkingLetter(int *arr) {
	int i, letter = 0, CommonLetter = 0, position = 0; 
	for (i = 25; i >= 0; i--)
		if (arr[i] > CommonLetter) {
			CommonLetter = arr[i];
			position = i; // saves the location
			letter = 1; 
		}
	if (position != -1)
		return 'A' + position;
	else
		return '\0';
}

/////////////////////////////////////////////    EX4     ///////////////////////////////////////////////////

void Ex4() {
	char *string;
	printf("Please enter your encrypted text: ");
	while (getchar() != '\n');
	string = creatingString();
	decode(string);
	if (!string[0])
		printf("Your string is empty! Please fix it. \n");
	else {
		printf("Your text after finishing decoding is: ");
		puts(string);
	}
	free(string);
	printf("\n");
}

void decode(char *string) {
	int character = 1, size, i;
	size = strlen(string);
	for (i = 0; i < size; i++) {
		if (string[i] != ' ')
			string[i] = string[i] - character++;
		else
			character = 1;
	}
}

/////////////////////////////////////////////    EX5     ///////////////////////////////////////////////////

void Ex5() {
	char *declaration, *filename;
	printf("Please enter your data: ");
	while (getchar() != '\n'); 
	declaration = creatingString();
	printf("Please enter your file name to create (Do not forget .txt): \n");
	filename = creatingString();
	memoryReport(declaration, filename);
	free(declaration);
	free(filename);
}

void memoryReport(char *declaration, char *filename) {
	int i = 0, typeSize, flag = 0;
	char whichType;
	FILE *file;
	if (!(file = fopen(filename, "w"))) { // Check and open the file 
		printf("Can't open the file! Please try again.\n");
		return;
	}
	while (!isalpha(declaration[i]))
		i++;
	whichType = declaration[i];
	switch (whichType) {
		case 'i': { // first case - if int
			typeSize = sizeof(int);    
			break; 
		}
		case 's': { // second case - if short
			typeSize = sizeof(short);
			break;
		}
		case 'c': { // third case - if char
			typeSize = sizeof(char);   
			break; 
		}
		case 'd': { // fourth case - if double
			typeSize = sizeof(double);
			break;
		}
		case 'f': { // fifth case - if float
			typeSize = sizeof(float);  
			break; 
		}
		default: 
		i = i + 5;   // for long or long long - identifies if the string is long or long long
		if (declaration[i++] == 'l') {
			typeSize = sizeof(long long) + sizeof(long long);
			break;
		}
		i = 4;
		typeSize = sizeof(long long); 
		break;
		}
	
	while (declaration[i] != '\0') {
		if (flag == 1 || declaration[i] == '*')
			flag = 1;
		else
			flag = 0;
		if (isalpha(declaration[i])) {
			while (declaration[i] != ',' && declaration[i] != ';' && declaration[i] != '[') {
				if (declaration[i] == '=') {
					while (declaration[i] != ';' && declaration[i] != ',')
						i++;
					break;
				}
				if (declaration[i] != ' ' && declaration[i] != '*') {
					fputc(declaration[i], file);
					i++;
				}
				else
					i++;
			}
			if (flag) {
				fputs(" are require a ", file);
				fprintf(file, "%d", sizeof(int*));
				fputs(" bytes from the memory\n", file);
				i++;
				flag = 0;
			}
			else { // if not a pointer then
				fputs(" are require a ", file);
				fprintf(file, "%d", typeSize * sizeCheck(declaration, &i));
				fputs(" bytes from the memory\n", file);
			}
		}
		else
			i++;
	}
	fclose(file);
	printf("\nThe file %s was created as you requested.\n", filename);
	printf("Printing from your file -> %s:\n", filename);
	printFile(filename);
}