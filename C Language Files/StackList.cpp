#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LENGTH 50
#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node {
	struct _node* next;
	Data data;
} Node;

typedef struct _stackLinkedList {
	Node* head;
	Node* temp;
	int numOfData;
} StackLinkedList;

typedef StackLinkedList List;

void ListInit(List*);
void Insert(List*, Data);
void FindAll(List*);
Data Remove(List*);
int isEmpty(List*);
int isNext(List*);
int Count(List*);

int main() {
	List* list = (List*)malloc(sizeof(List));
	Data data[ARRAY_LENGTH] = { 3, 7, 1, 2, 5 };

	printf("---------------\n");
	printf("| Stack Start |\n");
	printf("---------------\n");
	ListInit(list);
	printf("Insert Start\n");
	for (int i = 0; data[i]; i++) {
		Insert(list, data[i]);
		FindAll(list);
	}
	printf("\n");

	printf("Remove Start\n");
	for (int i = 0; data[i]; i++)
		printf("%d ", Remove(list));
	printf("%d ", Remove(list));
	printf("\n");

	return 0;
}

void ListInit(List* list) {
	list->head = NULL;
	list->temp = NULL;
	list->numOfData = 0;
}

void Insert(List* list, Data data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (isEmpty(list)) {
		list->head = newNode;
		newNode->next = NULL;
	}
	else {
		newNode->next = list->head;
		list->head = newNode;
	}
	newNode->data = data;
	(list->numOfData)++;
}

void FindAll(List* list) {
	for (list->temp = list->head; list->temp != NULL; list->temp = list->temp->next)
		printf("%d ", list->temp->data);
	printf("\n");
}

Data Remove(List* list) {
	if (isEmpty(list)) {
		return -1;
	}
	Data temp = list->head->data;
	list->head = list->head->next;
	(list->numOfData)--;
	return temp;
}

int isEmpty(List* list) {
	if (list->numOfData) {
		return FALSE;
	}
	return TRUE;
}

int Count(List* list) {
	return list->numOfData;
}