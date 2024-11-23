#ifndef DOUBLE_LINKED_LIST_LIBRARY
#define DOUBLE_LINKED_LIST_LIBRARY

//==================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Double_Linked_Circle_Barrier (void *) 0xD1C00000DEADFA11

//==================================================

typedef struct Double_Linked_Circle_Element 
{
	struct Double_Linked_Circle_Element * next;
	struct Double_Linked_Circle_Element * prev;
	void * data;
}Double_Linked_Circle;

//==================================================

//const void * Double_Linked_Circle_Barrier = (void *) 0xD1C00000DEADFA11;

void double_linked_circle_init (Double_Linked_Circle * );
Double_Linked_Circle * double_linked_circle_create ();
void double_linked_circle_insert_next(Double_Linked_Circle * , Double_Linked_Circle * );
void double_linked_circle_insert_prev(Double_Linked_Circle * , Double_Linked_Circle * );
void double_linked_circle_remove(Double_Linked_Circle * );
Double_Linked_Circle * double_linked_circle_delete(Double_Linked_Circle * );
void double_linked_circle_push_next(Double_Linked_Circle * , void * );
void double_linked_circle_push_prev(Double_Linked_Circle * , void * );
void * double_linked_circle_pop(Double_Linked_Circle * );
char double_linked_circle_is_empty(Double_Linked_Circle * );
void double_linked_circle_clear(Double_Linked_Circle * );
void double_linked_circle_free (Double_Linked_Circle * );

#endif