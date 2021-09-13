/*Assigned by:
1. Daniel_Ashorov 313458242 // Group: 61108-37
2. Ori_Goldenberg 311119523 // Group: 61108-34
*/

typedef int data_type;
// ******************************** Ex3 ******************************** 
typedef struct item {
	int i, j, data;
}Item;

typedef struct node {
	Item Number;
	struct node *next;
} Node;
Node *creatingNode(data_type data) { 
	Node *tmp = (Node*) malloc (sizeof(Node));
	tmp->Number.data = data;
	tmp->next = NULL;
	return tmp;
}
Node *addStart(Node *start, data_type data) { //adding a number to start of list
	Node *tmp = creatingNode(data);
	tmp->next = start;
	return tmp;
}

// ******************************** Ex3 ******************************** 

typedef struct Node2 {
	data_type data;
	struct Node2 *next;
}Node2;

Node2 *createNode2(data_type data) {
	Node2 *temp = (Node2*)malloc(sizeof(Node2));
	temp->data = data;
	temp->next = NULL;
	return temp;
}
Node2 *addFirstSecond(Node2 *Start, data_type data) {
	Node2 *temp = createNode2(data);
	temp->next = Start;
	return temp;
}
Node2 *addLastSecond(Node2 *Start, data_type data) {
	Node2 *p = Start;
	Node2 *temp = createNode2(data);
	if (Start == NULL)
		return temp;
	while (p->next != NULL)
		p = p->next;
	p->next = temp;
	return Start;
}

Node2* insert_list() { // function getting numbers until the user put -1
	int Number;
	Node2 *Start = NULL;
	printf("Enter numbers for your list (enter -1 when you finish): \n");
	scanf("%d", &Number);
	while (Number != -1) {
		Start = addLastSecond(Start, Number); // new number will be last number
		scanf("%d", &Number);
	}
	return Start;
}