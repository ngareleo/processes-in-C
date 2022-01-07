
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define STARS() for(int i = 0; i < 30; i++)printf("*");
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char* argv[]){

	if (argc == 1){
		printf("Usage: p_f2 filename\n");
		exit(EXIT_FAILURE);
	}
	
	pid_t parent_id, child_id, creat_pid, pid;	
	
	int status;
	parent_id = getpid();	//  calling process
	printf(ANSI_COLOR_RED "pid of parent process is %d\n\n" ANSI_COLOR_RESET, parent_id);
	
	
	creat_pid = fork();
	if (creat_pid == -1){
		perror("fork");
		return -1;
		
	}else if (!creat_pid) { // pid != 0
		pid_t my_pid = getpid();
		printf("\n\nI'm the file creation process\nMy pid is %d\n\n", my_pid);
		int create_f = execl("/bin/touch", "touch", *(argv+1), NULL);
		exit(EXIT_SUCCESS);
	}
	
	
	printf("Checking my process exit status\n");
	pid_t child_1 = wait(&status);
	if (child_1 == -1)
		perror("wait");
	if (WIFEXITED(status))
		printf("Process with pid %d exited normally with exit status %d\n", child_1, WEXITSTATUS(status));
	// waiting
	
	
	// terminated process
	
	
	return 0;
}
