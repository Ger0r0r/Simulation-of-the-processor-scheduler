#ifndef PROCESSOR_LIST_LIBRARY
#define PROCESSOR_LIST_LIBRARY

//==================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//==================================================

typedef Task * Data;

typedef struct Nod
{
	Data data;
	struct Nod * next; 
}Node;

typedef struct List
{
	Node *head;
	Node *tail;
}List;

//==================================================

List * list_create ()
{
	List * tmp = calloc(1, sizeof(List));
	return tmp;
}

int list_is_empty(List * q)
{
	return (q->head == 0 && q->tail == 0);
}

void list_push (List * q, Data x)
{
	Node * h = calloc(1, sizeof(Node));
	h->data = x;
	h->next = 0;
	if (list_is_empty(q))
	{
		q->head = h;
		q->tail = h;
	}
    else
    {
        q->tail->next = h;
        q->tail = h;
    }
}

int list_size(List * q)
{
	Node * p = q->head;
	int size = 0;
	
	while (p)
	{
		size++;
		p = p->next;
	}
	
	return size;
}

Data list_pop (List * q)
{
	Data list_data = q->head->data;
	Node * h = q->head;
	if (list_size(q) == 1)
	{
		q->head = 0;
		q->tail = 0;
	}
	
	else
	{
		q->head = q->head->next;
	}
	free(h);
	return list_data;
}

Data list_get (List * q)
{
	return q->head->data;
}

/*void list_print (List * q)
{
	if (list_is_empty(q))
	{
		printf("Empty list\n");
		return;
	}
	
	Node * p = q->head;
	
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	
	printf("\n");
}*/

void list_clear(List * q)
{
	Node * p = q->head;
	Node * prev = 0;
	while (p)
	{
		prev = p;
		p = p->next;
		free(prev);
	}
	free(q);
}

void list_delete_element(Node * rm)
{
	Node * nt = rm->next;
	rm = nt;
	free(nt);
}
#endif