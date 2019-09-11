#include "os.h"
const int quantus[4]= {4,8,16,255}; //array of quantum for each waiting line
const int max_waiting[4] = {255,128,64,32};


OS* OS_init(int argc, char ** argv,FILE* f){
	OS* os = (OS*)malloc(sizeof(OS));
	os->step = -1;
	os->running = NULL;
	os->q = -1;
	os->IO = List_init();
	os->toArrive = List_init();
	for(int j = 1; j<argc; j++){
		PCB * p = Process_create(argv[j]);
		pushBack(os->toArrive,(ListElem*)p);
		fprintf(f,"creato processo da %s\n",argv[j]);
		PCB_print_info(p,f);
		fprintf(f,"\n");
	}
	for(int i = 0; i<4; i++)
		os->waiting[i] = List_init();
	return os;
	os->running_event = NULL;

}


int OS_step(OS* os,FILE * f){
	fprintf(f,"************************************************************************************\n");
	fprintf(f,"STEP: %d \n",os->step);
	OS_print_info( os,f); //TODO

	os->step ++;
	//check end
	if(check_end(os) == 1){ 
		fprintf(f,"END");
		return 0;
	}

	//check for new process
	new_arrivals(os); //TODO
	

	//check running process
	if(os->running == NULL ){
		printf("getting next running\n");
		if(get_next_running(os) == 0) //TODO
			printf("no process running\n");
		else {
			os->running->in_status = 0;
			printf("got next running: %d\n",os->running->pid);
		}
	}

	else{
		os->running->in_status ++;

		printf("running %d", os->running->pid);	
		printf("for %d\n", os->running->in_status);

		Event* e=(Event*) os->running->events->head;
		printf("running has a burst %d long\n",e->duration);

	 	if(os->running->in_status >= os->q){
	 		if(quantum_end(os)==0) //TODO
				printf("no process running\n");
			else printf("got next running\n");
		}

	 	else if( os->running->in_status >= e->duration){
			if(burst_end(os)== 0) //TODO
				printf("no process running\n");
			else {
				os->running->in_status = 0;
				printf("got next running\nos->running->in status = %d\n",os->running->in_status );
			}	
		}
	 	
	 	else
	 		printf("not changing running\n");
		
	}
	//manage the waiting lists
	waiting(os); //TODO

	// manage the IO
	io(os); //TODO

	return 1;
}


int check_end(OS* os){
	if(os->step <= 1)
		return 0;
	for(int i= 0; i<4; i++){
		if(os->waiting[i]->lenght >0)
			return 0;
	}
	if(os->running != NULL) return 0;
	if(os->IO->lenght > 0) return 0;
	if(os->toArrive->lenght > 0) return 0;
	return 1;
}