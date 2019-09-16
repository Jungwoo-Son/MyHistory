#include <stdio.h>
#include <stdlib.h>
#define array_number 50
#define true 1
#define false 0

typedef int data;

typedef struct _node {
	_node* next;
	data cdata;
	data idata;
} node;

typedef struct _polynomiallinkedlist {
	node* head;
	node* cur;
	node* before;
	int numofdata;
	int (*comp)(data d1, data d2);
} polynomiallinkedlist;

typedef polynomiallinkedlist list;

void listinit(list*);
void insert(list*, data, data);
void print(list*);
int isfirst(list*);
data remove(list*);
int count(list*);
int rule(data, data);
void setsortrule(list*, int (*comp)(data d1, data d2));
list* merge(list*, list*);

int main() {
	int item1[array_number] = { 3, 1, 4, 7, 5, 5, 3, 10, 4, 9, 5, 12, 6, 13, 7, 14, 4, 0, 0, -1 };
	int item2[array_number] = { -2, 4, -5, 1, 3, 7, -5, 5, 13, 11, 5, 0, 0,-1 };

	list* list1 = (list*)malloc(sizeof(list));
	list* list2 = (list*)malloc(sizeof(list));

	listinit(list1);
	listinit(list2);
	setsortrule(list1, rule);
	setsortrule(list2, rule);

	for (int i = 0; item1[i]; i += 2) insert(list1, item1[i], item1[i + 1]);
	for (int i = 0; item2[i]; i += 2) insert(list2, item2[i], item2[i + 1]);
	printf("다항식 1 출력...\n");
	print(list1);
	printf("다항식 2 출력...\n");
	print(list2);

	list * list3 = merge(list1, list2);
	printf("다항식 합 출력...\n");
	print(list3);

	return 0;
}

void listinit(list * list) {
	list->before = NULL;
	list->cur = NULL;
	list->head = (node*)malloc(sizeof(node));
	list->numofdata = 0;
	list->comp = NULL;
	list->head->next = NULL;
}

void insert(list * list, data cdata, data idata) {
	node* newnode = (node*)malloc(sizeof(node));
	if (isfirst(list)) {
		list->head->next = newnode;
		newnode->next = NULL;
	}
	else {
		list->before = list->head;
		while (list->before->next != NULL && list->comp(idata, list->before->next->idata) != true) {
			list->before = list->before->next;
		}
		newnode->next = list->before->next;
		list->before->next = newnode;
	}
	newnode->idata = idata;
	newnode->cdata = cdata;
	(list->numofdata)++;
}

void print(list * list) {
	for (list->cur = list->head->next; list->cur != NULL; list->cur = list->cur->next) {
		printf("[%d, %d] ", list->cur->cdata, list->cur->idata);
	}
	printf("\n");
}

list* merge(list * list1, list * list2) {
	list* list3 = (list*)malloc(sizeof(list));
	listinit(list3);
	setsortrule(list3, rule);

	list1->cur = list1->head->next;
	list2->cur = list2->head->next;
	list3->cur = list3->head;

	while (list1->cur != NULL || list2->cur != NULL) {
		node* newnode = (node*)malloc(sizeof(node));
		newnode->next = NULL;
		if ((list1->comp(list1->cur->idata, list2->cur->idata)) == -1) {
			if (list1->cur->cdata + list2->cur->cdata == 0) {
				free(newnode);
				list1->cur = list1->cur->next;
				list2->cur = list2->cur->next;
				continue;
			}
			else {
				newnode->idata = list1->cur->idata;
				newnode->cdata = list1->cur->cdata + list2->cur->cdata;
				list3->cur->next = newnode;
				list1->cur = list1->cur->next;
				list2->cur = list2->cur->next;
			}
		}
		else if (list1->comp(list1->cur->idata, list2->cur->idata)) {
			newnode->idata = list1->cur->idata;
			newnode->cdata = list1->cur->cdata;
			list3->cur->next = newnode;
			list1->cur = list1->cur->next;
		}
		else {
			newnode->idata = list2->cur->idata;
			newnode->cdata = list2->cur->cdata;
			list3->cur->next = newnode;
			list2->cur = list2->cur->next;
		}
		list3->cur = list3->cur->next;
	}

	return list3;
}

int count(list * list) {
	return list->numofdata;
}

int isfirst(list * list) {
	if ((list->head->next) == NULL) return true;
	return false;
}

int rule(data d1, data d2) {
	if (d1 > d2) return true;
	else if (d1 < d2) return false;
	else return -1;
}

void setsortrule(list * list, int (*comp)(data d1, data d2)) {
	list->comp = comp;
}