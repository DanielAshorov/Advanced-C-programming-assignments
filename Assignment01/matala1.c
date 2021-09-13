/*Assigned by:
1. Daniel_Ashorov 313458242 // Group: 61108-37
2. Ori_Goldenberg 311119523 // Group: 61108-34
*/

#define _CRT_SECURE_NO_WARNINGS

//for ex2//
#define	N 4
#define M 4
#define P 4

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matala1.h"

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();
void Ex4();
void Ex5();

/* Declarations of other functions */
unsigned int* powerArray(int);
void print_array(int*, int); //פונקציה המדפיסה מערך
void freeDynMatrix(int **c, int n);
void printDynMatrix(int **a, int rows, int cols);
void printMatrixA(int A[][N], int rows, int cols);
void printMatrixB(int B[][P], int rows, int cols);
void matrixARandom(int A[][N], int rows, int cols);
void matrixBRandom(int B[][P], int rows, int cols);
int** matrixResult(int r, int c);
int** Result_Matrix(int A[][N], int B[][P], int rowsA, int colsARowB, int colsB);
typedef int data_type;
void printListSecond(Node2 *Start);
void FreeListSecond(Node2 *Start);
int createList(Node2 *);
void Insert(Node2 **, int);
void Delete(Node2 **, Node2 **);


/* ------------------------------- */

int main() {
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

/* Function definitions */

/* ------------------- */

/////////////////////////////////   EX1   //////////////////////////////////////////////////
void Ex1() {
	int n;
	unsigned int *p;
	printf("Please enter a number: ");
	scanf_s("%d", &n);
	p = powerArray(n);
	print_array(p, n);
	free(p);
}

void print_array(int *arr, int size) { // function to print an array 
	int i;
	for (i = 0; i < size; i++)
		printf("%u ", *(arr + i));
	printf("\n");
}

unsigned int* powerArray(int n) {
	int i;
	unsigned int  *arr;
	arr = (unsigned int*) malloc(n * sizeof (unsigned int));
	if (n < 1) {
		printf("Please enter a positive number!\n");
		return NULL;
	}
	if (!arr) {
		printf("There is no memory.\n");
		return NULL;
	}
	arr[0] = 1;
	for (i = 1; i < n; i++) {
		if (i % 32 != 0)
			arr[i] = arr[i - 1] * 2;
		else
			arr[i] = 1;
	}
	return arr;
}

/////////////////////////////////   EX2   //////////////////////////////////////////////////

void freeDynMatrix(int **x, int n) {
	int i;
	for (i = 0; i < n; i++)
		free(x[i]);
	free(x);
}
void printDynMatrix(int **a, int rows, int cols) { // printing dynamic matrix
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++)
			printf("%d  ", a[i][j]);
		printf("\n");
	}
}
void printMatrixA(int A[][N], int rows, int cols) {
	int i, j;
	printf("Matrix A is:\n");
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			printf("%d  ", A[i][j]);
		printf("\n");
	}
}
void printMatrixB(int B[][P], int rows, int cols) { 

	int i, j;
	printf("Matrix B is:\n");
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			printf("%d  ", B[i][j]);
		printf("\n");
	}
}
void matrixARandom(int A[][N], int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			A[i][j] = 2 * i + j;
}
void matrixBRandom(int B[][P], int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			B[i][j] = 2 * i + j;
}
int** matrixResult(int r, int c) {
	int **a, i;
	a = (int**)calloc(r, sizeof(int*));
	if (!a)  
		return NULL;
	for (i = 0; i < r; i++) {
		a[i] = (int*) calloc (c, sizeof(int));
		if (!a[i])  {
			freeDynMatrix(a, i);
			return NULL;
		}
	}
	return a; // returing pointer
}
int** Result_Matrix(int A[][N], int B[][P], int rowsA, int colsARowB, int colsB) {
	int **C = matrixResult(rowsA, colsB);
	int i, j, k;
	for (i = 0; i < rowsA; i++)
		for (k = 0; k < colsB; k++)
			for (j = 0; j < colsARowB; j++)
				C[i][k] += A[i][j] * B[j][k];
	return C;
}

void Ex2() {
	int **C;
	int A[M][N], B[N][P];
	matrixARandom(A, M, N);
	matrixBRandom(B, N, P);
	printMatrixA(A, M, N);
	printMatrixB(B, N, P);
	C = Result_Matrix(A, B, M, N, P);
	printf("The Result of A * B is:\n");
	printDynMatrix(C, M, P);
	freeDynMatrix(C, M);
}

/////////////////////////////////   EX3   //////////////////////////////////////////////////

typedef int data_type;

void createThreeList(Node *Start) { // printing linked list
	Node *p = Start;
	int i = 1;
	while (p != NULL) {
		printf("(%d) i = %d, j = %d, Item = %d\n", i++, p->Number.i, p->Number.j, p->Number.data);
		p = p->next;
	}
	printf("\n");
}

void Free_List(Node *Start) {
	Node *temp = Start;
	while (temp != NULL) {
		Start = Start->next;
		free(temp);
		temp = Start;
	}
}

void EnterMatrixNumbers(int **a, int row, int col){ 
	int i, j;
	printf("Enter numbers for your matrix (the size is: %dx%d):\n", row, col);
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			scanf("%d", &a[i][j]);
}

int** Allocate_Matrix(int r, int c) {
	int **a, i;
	a = (int**) calloc (r, sizeof(int*));
	if (!a)  
		return NULL;
	for (i = 0; i < r; i++) {
		a[i] = (int*)calloc(c, sizeof(int));
		if (!a[i])  {
			freeDynMatrix(a, i);
			return NULL;
		}
	}
	return a; // returing pointer
}

int createArrayAndList(int** arr, int r, int c, Item **Array_Ans, Node **Start) {
	Node *p = NULL;
	int i, j, count_list = 0;
	for (i = r - 1; i >= 0; i--)
		for (j = c - 1; j >= 0; j--)
			if (arr[i][j] == i + j) {
				*Start = addStart(*Start, i + j);
				(*Start)->Number.i = i;
				(*Start)->Number.j = j;
				count_list++; 
			}
	*Array_Ans = (Item*) malloc (count_list * sizeof(Item)); 
	assert(*Array_Ans); 
	p = *Start; 
	i = 0;
	while (p != NULL) { 
		(*Array_Ans)[i++] = p->Number;
		p = p->next;
	}
	return count_list; 
}

void createThreeArr(Item *arr, int size) { 
	int i;
	for (i = 0; i < size; i++) {
		printf("(%d) i = %d, j = %d, Item = %d\n", i + 1, arr[i].i, arr[i].j, arr[i].data);
	}
	printf("\n");
}

void Ex3() {
	int **arr;
	int count_list_array, Rows, Cols;
	Node *List = NULL;
	Item *Array;
	printf("Enter rows number: ");
	scanf_s("%d", &Rows);
	printf("Enter columns number: ");
	scanf_s("%d", &Cols);
	arr = Allocate_Matrix(Rows, Cols); 
	EnterMatrixNumbers(arr, Rows, Cols);  
	printf("You matrix is: \n");
	printDynMatrix(arr, Rows, Cols);
	count_list_array = createArrayAndList(arr, Rows, Cols, &Array, &List);  
	printf("There are %d numbers in your list\n", count_list_array);
	printf("Array print:\n");
	createThreeArr(Array, count_list_array);
	printf("List print:\n");
	createThreeList(List);
	freeDynMatrix(arr, Rows);
	free(Array); 
	Free_List(List); 	
}

/////////////////////////////////   EX4   //////////////////////////////////////////////////

void Ex4() {
	Node2 *head = NULL;
	Node2 *odd_list = NULL;
	head = insert_list(); 
	printf("Your list is: \n");
	printListSecond(head);
	odd_list = createList(head);
	printf("The Odds list is: \n");
	printListSecond(odd_list);
	FreeListSecond(odd_list);
}

int createList(Node2 *Start){ 
	Node2 *odd_list = NULL;
	Node2 *temp, *step, *prev = NULL; 
	if (Start == NULL) // if the list is empty
		return NULL;
	while (Start != NULL && Start->data % 2) { 
		Insert(&odd_list, Start->data);
		temp = Start;
		Start = Start->next;
		free(temp);
	}
	step = Start; 
	while (step != NULL) {  
		if (step->data % 2) { 
			Insert(&odd_list, step->data);
			Delete(&step, &prev);
		}
		else {
			prev = step;
			step = step->next;
		}
	}
	step = NULL;
	printf("The even list is:\n");
	printListSecond(Start);
	FreeListSecond(Start);
	return odd_list;
}

void Delete(Node2 **step, Node2 **prev) {
	Node2 *temp = *step; 
	*step = (*step)->next; 
	(*prev)->next = *step; 
	free(temp); 
}

void Insert(Node2 **Start, int Number) { 
	*Start = addLastSecond(*Start, Number);
}

void printListSecond(Node2 *Start) {
	Node2 *p = Start;
	while (p != NULL) {
		printf("%d  ", p->data);
		p = p->next;
	}
	printf("\n");
}

void FreeListSecond(Node2 *Start) {
	Node2 *temp = Start;
	while (temp != NULL) {
		Start = Start->next;
		free(temp);
		temp = Start;
	}
}

/////////////////////////////////   EX5   //////////////////////////////////////////////////

Node2* createList2(Node2 **head_even) {
	Node2 *p = *head_even, *headOdd = NULL, *currentOdd = NULL, *current_even = NULL;
	int degel = 0; 
	if (!*head_even) {
		return NULL;
	}
	while (p && p->data % 2 == 0) { 
		current_even = p;
		p = p->next;
		degel = 1;
	}
	if (!p)    
		return headOdd;
	headOdd = p;
	currentOdd = p;
	p = p->next; 
	while (p && p->data % 2) { 
		currentOdd = p;
		p = p->next;
	}
	if (!p && degel == 0){
		*head_even = NULL;
		return headOdd;
	}
	if (degel == 0){
		*head_even = p;
		current_even = p;
		p = p->next; 
	}
	while (p) {
		if (p->data % 2) {
			currentOdd->next = p;
			currentOdd = currentOdd->next;
		}
		else {
			current_even->next = p;
			current_even = current_even->next;
		}
		p = p->next;
	}
	currentOdd->next = NULL;
	current_even->next = NULL;
	return headOdd; // returing pointer
}

void Ex5() {
	Node2 *OriginList = NULL;
	Node2 *odd_list = NULL;
	OriginList = insert_list();
	printf("Your list is: \n");
	printListSecond(OriginList); // priting users list
	odd_list = createList2(&OriginList);
	printf("The odd list is:\n");
	printListSecond(odd_list);  // printing odds list
	FreeListSecond(odd_list);
	printf("The even list is:\n");
	printListSecond(OriginList);  // printing even list 
	FreeListSecond(OriginList);
}