#include<stdio.h>       // necessary for printf(), scanf() and other basic functionalities.
#include<stdlib.h>      // necessary for certain basic functionalities like atoi(), and exit() functions.
#include<pthread.h>     // necessary for thread-creation and joining and essentially exiting(essentially waiting for the thread to complete.)
#include<math.h>        // necessary for math functions.

#define NO_OF_T 16      // NO_OF_T here is a MACRO(essentially a constant) used to represent the total number of threads used in this multi-threading approach.
#define MIN_PID 100     // MIN_PID here is a MACRO(essentially a constant) used to specify the minimum value of process id.
#define MAX_PID 1000    // MAX_PID here is a MACRO(essentially a constant) used to specify the maximum value of process id.

#define RANGE  MAX_PID - MIN_PID        //to prevent variably modification of array error.

int pid[RANGE]; //bitmap not used instead, an array is used here. And hence no function is defined as :
               // int allocate_map(void){...}

int allocate_pid(void) {        // function that allocates process ids(if available) to the new process created.
        int i;
        int flag = 0;
        for(i=0;i<RANGE;i++) {
                if(pid[i]==0) {         // process_id(pid) is available.
                        pid[i] = 1;
                        flag=1;
                        break;
                }
        }
        if(flag == 1) return i;         // process gets the process id.
        else return -1;                 // process fails to get any process id.
}

void release_pid(int param) {   // param here refers to the process id of a process.
        pid[param] = 0;
}

void* threadFunction(void* arg) {       // defines the functionality performed by threadFunction.
        int id = allocate_pid();        // assigning a process id to the thread.

        int tid = *((int *)arg);        //type casting the void pointer argument to integer pointer so as to get the thread id of the current thread.

        if(id == -1) printf("No PID is available. Please try again later.\n");  // fails to get a valid process id.
        else {  // gets a valid process id
                printf("Thread with ID %3d  has been allocated the following process id:\t%3d\n", tid, id + MIN_PID);

                // SLEEPING FOR A RANDOM PERIOD OF TIME.
                int r = 1 + (rand()/pow(10, 9));
                sleep(r);

                // RELEASING THE THREAD BY REVOKING THE PROCESS ID PROVIDED TO IT.
                printf("Thread %3d with PID %3d is released after %d second/s\n", tid, id + MIN_PID, r);
                release_pid(id);
        }
        pthread_exit(NULL);     // STOPPING THE EXECUTION OF CURRENT THREAD.
}
int main(void) {
        pthread_t thread_arr[NO_OF_T];  // Thread variable(a kind of pointer to thread) definition.
        int i;
        for(i = 0;i < NO_OF_T;i++) {
                if(pthread_create(&thread_arr[i], NULL, threadFunction, (void*)&i) < 0) {       // Creating a new thread pointed through 'thread_arr[i]' element.
                //Indicates an error in thread creation. [Since pthread_create will return a non-zero value which is often less than zero in most cases.]
                        printf("Error in thread %d's creation!\n", i);
                }
                pthread_join(thread_arr[i], NULL);      // The parent process waiting for the thread to complete.
        }

        sleep(2);

        printf("---------------------------------------------------------------------------------------------\n");

        sleep(2);

        printf("PROGRAM EXECUTION SUCCESSFUL\n");      // Indicates a successful termination of thread via the parent process.

        return 0;
}
