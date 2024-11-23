#ifndef PROCESSORLIBRARY
#define PROCESSORLIBRARY

#include "double_linked_list.h"
#include <errno.h>
#include <unistd.h>

#define TM 2		// фиксированное процессорное время

typedef struct{
	unsigned int pid;		// идентификационный номер задачи (уникальный)
	unsigned int status;	// статус задачи: 0 - не поступил, 1 - в list, 2 - в do_list, 3 - в MEM, 4 - отклонена, 5 - выполнена
	unsigned int time_act;	// время исполнения задачи (tm в единицах времени ОС)
	unsigned int mem;		// необходимое количество памяти для загрузки задачи
	unsigned int time;		// время поступления задачи
}Task;

typedef struct{
	Task * add;
	unsigned int start;
	unsigned int lenght;
}CellMEM;

Double_Linked_Circle * searchMaxMEM (Double_Linked_Circle * );
void checkTask(unsigned int , Task * , Double_Linked_Circle * , unsigned int , unsigned int , unsigned int * );
void getoutTask(unsigned int , Double_Linked_Circle * , Double_Linked_Circle * , unsigned int );
void putinMEM(unsigned int , Double_Linked_Circle * , Double_Linked_Circle * );

#endif