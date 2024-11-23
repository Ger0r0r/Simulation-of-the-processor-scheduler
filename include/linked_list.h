#ifndef LINKED_CIRCLE_LIBRARY
#define LINKED_CIRCLE_LIBRARY

//==================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//==================================================

typedef struct Linked_Circle_Element
{
	struct Linked_Circle_Element * next; 
	void * data;
}Linked_Circle;

//==================================================

const void * Linked_Circle_Barrier = (void *) 0x1C000000DEADFA11;

//==================================================

Linked_Circle * linked_circle_create ()
{
	Linked_Circle * temp = calloc(1, sizeof(Linked_Circle));
	temp->data = (void *) Linked_Circle_Barrier;
	temp->next = temp;
	return temp;
}

//--------------------------------------------------

char linked_circle_is_empty (Linked_Circle * check)
{
	if (check->next == check && check->data == Linked_Circle_Barrier)
		return 1;
	return 0;
}

//--------------------------------------------------

void linked_circle_push_next (Linked_Circle * lc, void * x)
{
	Linked_Circle * temp = calloc(1, sizeof(Linked_Circle));
	temp->data = x;
	temp->next = lc->next;
	lc->next = temp;
}

//--------------------------------------------------

void linked_circle_push_prev (Linked_Circle * lc, void * x)
{
	Linked_Circle * temp = calloc(1, sizeof(Linked_Circle));
	temp->data = lc->data;
	temp->next = lc->next;
	lc->data = x;
	lc->next = temp;
}

//--------------------------------------------------

unsigned int linked_circle_size(Linked_Circle * lc)
{
	int size = 0;
	while (lc->data != Linked_Circle_Barrier)
	{
		size++;
		lc = lc->next;
	}
	
	return size;
}

//--------------------------------------------------

void linked_circle_remove_element(Linked_Circle * elc)
{
	Linked_Circle * temp = elc->next;
	elc->next = temp->next;
	elc->data = temp->data;
}

//--------------------------------------------------

Linked_Circle * linked_circle_delete_element(Linked_Circle * elc)
{
	Linked_Circle * temp = elc->next;
	elc->data = temp->data;
	elc->next = temp->next;
	free(temp);
	return elc;
}

//--------------------------------------------------

void * linked_circle_get (Linked_Circle * lc)
//ЗАЧЕМ???
{
	return lc->data;
}

//--------------------------------------------------

void * linked_circle_pop (Linked_Circle * lc)
{
	void * temp = lc->data;
	linked_circle_delete_element(lc);
	return temp;
}

//--------------------------------------------------

void linked_circle_clear (Linked_Circle * lc)
{
	lc->data = (void *) Linked_Circle_Barrier;
	lc = lc->next;
	while (!linked_circle_is_empty(lc))
		lc = linked_circle_delete_element(lc);
}

//--------------------------------------------------

void linked_circle_free (Linked_Circle * lc)
{
	linked_circle_clear(lc);
	free(lc);
}

#endif