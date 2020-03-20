#include<stdio.h>	// necessary for printf(), scanf() and other basic functionalities.
#include<stdlib.h>	// necessary for certain basic functionalities like atoi(), and exit() functions.
#include<pthread.h>	// necessary for thread-creation and joining(essentially waiting for the thread to complete.)
#include<math.h>

#define MIN_PID 100	// MIN_PID here is a MACRO(essentially a constant) used to specify the minimum value of process id.
#define MAX_PID 1000	// MAX_PID here is a MACRO(essentially a constant) used to specify the maximum value of process id.

#define RANGE  MAX_PID - MIN_PID	//to prevent variably modification of array error.

int pid[RANGE];	//bitmap not used instead, an array is used here. And hence no function is defined as :
			// int allocate_map(void){...}

int allocate_pid(void) {	// function that allocates process ids(if available) to the new process created.
	int i;
	int flag = 0;
	for(i=0;i<RANGE;i++) {
		if(pid[i]==0) {		// process_id(pid) is available.
			pid[i] = 1;
			flag=1;
			break;
		}
	}
	if(flag == 1) return i;		// process gets the process id.
	else return -1;			// process fails to get any process id.
}

void release_pid(int param) {	// param here refers to the process id of a process.
	pid[param] = 0;
}

void* threadFunction(void* arg) {	// defines the functionality performed by threadFunction.
	int id = allocate_pid();	// assigning a process id to the thread.

	if(id == -1) printf("No PID is available. Please try again later.\n");	// fails to get a valid process id.
	else {	// gets a valid process id
		printf("Thread has been allocated the following process id:\t%d\n", id + MIN_PID);

		// SLEEPING FOR A RANDOM PERIOD OF TIME.
		int r = 1 + (rand()/pow(10, 9));
		sleep(r);

		// RELEASING THE THREAD BY REVOKING THE PROCESS ID PROVIDED TO IT.
		printf("Thread with PID %d is released after %d seconds\n", id + MIN_PID, r);
		release_pid(id);
	}
	pthread_exit(NULL);	// EXITING THE THREAD
}

int main(void) {
	pthread_t a_thread;	// Thread variable(a kind of pointer for thread) definition.

	pthread_create(&a_thread, NULL, threadFunction, NULL);	// Creating a new thread pointed through 'a_thread' variable.

	pthread_join(a_thread, NULL);	// The parent process waiting for the thread to complete.

	sleep(2);

	printf("SUCCESSFUL EXIT.\n");	// Indicates a successful termination of thread via the parent process.

	return 0;
}
