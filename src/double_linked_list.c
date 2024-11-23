#include "double_linked_list.h"

void double_linked_circle_init (Double_Linked_Circle * dlc)
{
	dlc->data = (void *) Double_Linked_Circle_Barrier;
	dlc->next = dlc;
	dlc->prev = dlc;
}

Double_Linked_Circle * double_linked_circle_create ()
{
	Double_Linked_Circle * temp = calloc(1, sizeof(Double_Linked_Circle));
	double_linked_circle_init(temp);
	return temp;
}

void double_linked_circle_insert_next(Double_Linked_Circle * dlc, Double_Linked_Circle * edlc)
{
	Double_Linked_Circle * tist = dlc->next;
	tist->prev = edlc;
	dlc->next = edlc;
	edlc->next = tist;
	edlc->prev = dlc;
}

void double_linked_circle_insert_prev(Double_Linked_Circle * dlc, Double_Linked_Circle * edlc)
{
	Double_Linked_Circle * tist = dlc->prev;
	tist->next = edlc;
	dlc->prev = edlc;
	edlc->prev = tist;
	edlc->next = dlc;
}

void double_linked_circle_remove(Double_Linked_Circle * edlc)
{
	Double_Linked_Circle * list = edlc->next;
	Double_Linked_Circle * tist = edlc->prev;
	tist->prev = list;
	list->next = tist;
}

Double_Linked_Circle * double_linked_circle_delete(Double_Linked_Circle * edlc)
{
	Double_Linked_Circle * list = edlc->next;
	Double_Linked_Circle * tist = edlc->prev;
	tist->next = list;
	list->prev = tist;
	free(edlc);
	return list;
}

void double_linked_circle_push_next(Double_Linked_Circle * dlc, void * new_data)
{
	Double_Linked_Circle * temp = malloc(sizeof(Double_Linked_Circle));
	temp->data = new_data;
	double_linked_circle_insert_next(dlc, temp);
}

void double_linked_circle_push_prev(Double_Linked_Circle * dlc, void * new_data)
{
	Double_Linked_Circle * temp = malloc(sizeof(Double_Linked_Circle));
	temp->data = new_data;
	double_linked_circle_insert_prev(dlc, temp);
}

void * double_linked_circle_pop(Double_Linked_Circle * dlc)
{
	void * temp = dlc->data;
	dlc = double_linked_circle_delete(dlc);
	return temp;
}

char double_linked_circle_is_empty(Double_Linked_Circle * dlc)
{
	if (dlc->next == dlc && dlc->next->data == Double_Linked_Circle_Barrier)
		return 1;
	return 0;
}

void double_linked_circle_clear(Double_Linked_Circle * dlc)
{
	dlc->data = (void *) Double_Linked_Circle_Barrier;
	dlc = dlc->next;
	while(!double_linked_circle_is_empty(dlc))
		dlc = double_linked_circle_delete(dlc);
}

void double_linked_circle_free (Double_Linked_Circle * dlc)
{
	double_linked_circle_clear(dlc);
	free(dlc);
}