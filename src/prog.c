#include "procLib.h"

int main (int argc, char ** argv)
{
	FILE * txt, * res;

	if (argc < 1)
	{
		printf("Введите названия файлов при запуске программы");
		exit(-1);
	}
	
	res = fopen ("log.txt", "w");
	
	txt = fopen (argv[1], "r");
	
    if (txt == NULL) 
	{
        fprintf(stderr, "Ошибка открытия: %s\n", argv[1]);
        return -1;
    }

	unsigned int wMEM, nTask;

	unsigned int count = 0;
	
	fscanf(txt, "%u", &wMEM);
	fscanf(txt, "%u", &nTask);

	Task *Manager = calloc(nTask, sizeof(Task));

	Double_Linked_Circle * MEM = double_linked_circle_create();
	CellMEM * fCell = calloc(1, sizeof(CellMEM));
	fCell->add = NULL;
	fCell->start = 0;
	fCell->lenght = wMEM;
	
	double_linked_circle_push_next(MEM, fCell);

	for(int i = 0; i < nTask; ++i)
		fscanf(txt, "%X %u %u %u", &Manager[i].pid, &Manager[i].mem, &Manager[i].time_act, &Manager[i].time);

	Double_Linked_Circle * list = double_linked_circle_create();
	Double_Linked_Circle * do_list = double_linked_circle_create();

	char end = 1;

	for (unsigned int i = 0; end != 0; i++)
	{
		checkTask(i, Manager, list, nTask, wMEM, &count);
		getoutTask(i, do_list, MEM, wMEM);
		putinMEM(i, do_list, MEM);
		putinMEM(i, list, MEM);
		
		if(count == nTask && ((CellMEM *)MEM->next->data)->add == NULL && ((CellMEM *)(MEM->next->data))->lenght == wMEM)
			end = 0;
		
	}

	for (int i = 0; i < nTask; i++)
		fprintf(res, "%X\t%u\t%u\n", Manager[i].pid, Manager[i].status, Manager[i].time);
	
	double_linked_circle_free(MEM);
	double_linked_circle_free(list);
	double_linked_circle_free(do_list);
	free(Manager);
	free(fCell);
	fclose(res);
	fclose(txt);
	return 0;
}