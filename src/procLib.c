#include "procLib.h"

Double_Linked_Circle * searchMaxMEM (Double_Linked_Circle * MEM)
// поиск максимально большого участка свободной памяти MAX
{
	MEM = MEM->next;
	Double_Linked_Circle * MAX = NULL;
	unsigned int wide = 0;
	while (((CellMEM *)(MEM->data)) != Double_Linked_Circle_Barrier)
	{
		if (((CellMEM *)(MEM->data))->add == NULL)
			if (((CellMEM *)(MEM->data))->lenght > wide)
			{
				wide = ((CellMEM *)(MEM->data))->lenght;
				MAX = MEM;
			}
		MEM = MEM->next;
	}
	return MAX;
}

void checkTask(unsigned int time, Task * Manager, Double_Linked_Circle * list, unsigned int nTask, unsigned int wMEM, unsigned int * count)
//
// проверяет поступление новых задач, ставит задачи в очередь, отклоняет невыполняемые задачи
//
{	
	for(int i = *count; i < nTask; ++i)
	{
		if(Manager[i].time <= time)
		{
			if(Manager[i].mem <= wMEM)
			{
				Manager[i].status = 1;
				double_linked_circle_push_prev(list, Manager + i);
			}
			else
				Manager[i].status = 4;
			(*count)++;
		}
		else
			break;
	}
}

void getoutTask(unsigned int time, Double_Linked_Circle * do_list, Double_Linked_Circle * MEM, unsigned int wMEM)
//
// выгружает задачи из памяти в очередь
//
{
	// создание необходимых переменных
	void * x;
	MEM = MEM->next;

	while (((CellMEM *)(MEM->data)) != Double_Linked_Circle_Barrier)
	// просматриваем все области памяти и выгружаем те задачи что уже пролежали TM
	{
		// проверка что здесь лежит задача
		if (((CellMEM *)(MEM->data))->add != NULL) 
			// проверка что задача лежит уже время = TM
			if (time - ((CellMEM *)(MEM->data))->add->time == TM) 
			{
				// смена времени для удобства работы далее
				((CellMEM *)(MEM->data))->add->time = time;

				// проверка что задача выполнена -- выходит, иначе в do_list
				if (((CellMEM *)(MEM->data))->add->time_act <= TM)
				{
					((CellMEM *)(MEM->data))->add->status = 5;
				}
				else
				{
					((CellMEM *)(MEM->data))->add->status = 2;
					double_linked_circle_push_prev(do_list, ((CellMEM *)(MEM->data))->add);
				}

				// уменьшение времени оставшегося выполнения
				((CellMEM *)(MEM->data))->add->time_act -= TM;

				// очистка (пока что) заполненных ячеек памяти
				((CellMEM *)(MEM->data))->add = NULL;
				if (((CellMEM *)(MEM->data))->start != 0 && ((CellMEM *)(MEM->prev->data))->add == NULL)
				{
					x = MEM->data;
					MEM = double_linked_circle_delete(MEM);
					MEM = MEM->prev;
					((CellMEM *)(MEM->data))->lenght += ((CellMEM *)(x))->lenght;
					free(x);
				}
				if (((CellMEM *)(MEM->data))->start + ((CellMEM *)(MEM->data))->lenght != wMEM && ((CellMEM *)(MEM->next->data))->add == NULL)
				{
					x = MEM->next->data;
					MEM->next = double_linked_circle_delete(MEM->next);
					((CellMEM *)(MEM->data))->lenght += ((CellMEM *)(x))->lenght;
					free(x);
				}
			}
		MEM = MEM->next;
	}
}

void putinMEM(unsigned int time, Double_Linked_Circle * list, Double_Linked_Circle * MEM)
//
// загружает задачи в память из очереди
//
{
	list = list->next;
	while (list->data != Double_Linked_Circle_Barrier) // проверка списка на пустоту
	{
		// максимамльный по области участок памяти
		Double_Linked_Circle * maxMEM = searchMaxMEM(MEM);

		if(maxMEM != NULL && ((CellMEM *)(maxMEM->data))->lenght >= ((Task *)(list->data))->mem)
		// проверка что задача влезает в maxMEM
		{
			if(((CellMEM *)(maxMEM->data))->lenght > ((Task *)(list->data))->mem)
			// задача влезает в maxMEM оставляя место
			{
				// выделение свободной области памяти как части dlc
				CellMEM * inputCell = calloc(1, sizeof(CellMEM));
				inputCell->add = NULL;
				inputCell->start = ((CellMEM *)(maxMEM->data))->start + ((Task *)(list->data))->mem;
				inputCell->lenght = ((CellMEM *)(maxMEM->data))->lenght - ((Task *)(list->data))->mem;
				double_linked_circle_push_next(maxMEM, inputCell);

				// переброс задачи в память
				((CellMEM *)(maxMEM->data))->add = list->data;
				((CellMEM *)(maxMEM->data))->lenght = ((Task *)(list->data))->mem;
				((Task *)(list->data))->status = 3;
				((Task *)(list->data))->time = time;

				// удаление вставленной задачи из списка
				list = double_linked_circle_delete(list);
				list = list->prev;

				putinMEM(time, list, MEM);
				return;
			}
			else
			// задача влезает в maxMEM полностью
			{
				// переброс задачи в память
				((CellMEM *)(maxMEM->data))->add = list->data;
				((Task *)(list->data))->status = 3;
				((Task *)(list->data))->time = time;

				// удаление вставленной задачи из списка
				list = double_linked_circle_delete(list);
				list = list->prev;

				// рекурсивный вызов со следующей задачей из списка
				putinMEM(time, list, MEM);
				return;			
			}
		}
		// переход к проверке следующей задачи из списка
		list = list->next;	
	}	
}