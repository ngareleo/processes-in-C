#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

#define stars() for (int i = 0; i < 50; i++) printf("%c", (i != 49) ? '*' : '\n');

#define MAX_SIZE 100

/*
	Demonstrate processes
*/

void illegal_func() {
	int size = 11;
	int buffer[10];
	for (int i = 0; i < size; i++)
		buffer[i] = i; 

	for (int j = 0; j < size; j++)
		printf("%d%c", buffer[j], (j != size - 1) ? ' ' : '\n'); // reading the buffer
	printf("\n");
}

void normal_func(){

	// this doesn't oveflow because the memory is dynamic and is implemented as a heap
	int *buffer, size = 20;
	buffer = calloc(10, sizeof(int));
	for (int i = 0; i < size; i++)
		*(buffer + i) = i; // adding more elements than the buffer can hold
		
	for (int j = 0; j < size; j++)
		printf("%d%c", *(buffer + j), (j != size - 1)? ' ' : '\n'); // reading the buffer
	printf("\n");
}


int main(int argc, char* argv) {
	
	pid_t illegal_pid, normal_pid, my_pid;
	my_pid = getpid();
	
	printf("Parent process pid is ");
	printf(ANSI_COLOR_BLUE "%d\n\n" ANSI_COLOR_RESET, my_pid);
	
	stars();
	printf("%s\n", "THE NORMAL PROCESS");
	printf("%s\n\n", "Dynamic memory allocation\nAttempt to oveflow a buffer, but the buffer is implemented using a heap instead of a stack");
	normal_pid = fork();	
	if (normal_pid == -1) {
		perror("fork");
	}
	else if (!normal_pid) {
		normal_func();
		exit(EXIT_SUCCESS);
	}
	

	int status;
	pid_t waiting = wait(&status);
	
	if (waiting == -1) 
		perror("wait");
	else {
		if (WIFEXITED(status))
			printf(ANSI_COLOR_GREEN "The normal process pid %d ended normally with exit code %d\n" ANSI_COLOR_RESET, waiting, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf(ANSI_COLOR_RED "Normal process pid %d killed by signal %d : %s\n" ANSI_COLOR_RESET,waiting, WTERMSIG(status), WCOREDUMP(status)? "(Core dumped)": "");
		else if (WIFSTOPPED(status))
			printf(ANSI_COLOR_RED "Normal process pid %d stopped by signal %d\n"ANSI_COLOR_RESET, waiting, WSTOPSIG(status));		
	}			
	stars();
	printf("\n");
	stars();

	printf("%s\n", "THE ILLEGAL PROCESS");
	printf("%s\n\n", "Static Memory Allocation\nAttempt to oveflow a buffer implemented using a stack.");
	illegal_pid = fork();	
	if (illegal_pid == -1) {
		perror("fork");
	}
	else if (!illegal_pid) {
		illegal_func();
		exit(EXIT_SUCCESS);
	}
	
	waiting = wait(&status);
	
	if (waiting == -1) 
		perror("wait");
	else {
		if (WIFEXITED(status))
			printf(ANSI_COLOR_GREEN "The process pid %d ended normally with exit code %d\n" ANSI_COLOR_RESET, waiting, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf(ANSI_COLOR_RED "Process pid %d killed by signal %d : %s\n" ANSI_COLOR_RESET,waiting, WTERMSIG(status), WCOREDUMP(status)? "(Core dumped)": "");
		else if (WIFSTOPPED(status))
			printf(ANSI_COLOR_RED "Process pid %d stopped by signal %d\n" ANSI_COLOR_RESET, waiting, WSTOPSIG(status));
	}			
	stars();
	return 0;
}
