#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

void doWork(pid_t arg) {
    printf("%i\n", arg);
}

int main()
{
    /*Spawn a new process to run alongside us.*/

    pid_t pid = 0;
    int i;

    for(i = 0; i < 3; i++)
{
    if (pid == 0) {	/* child process */
		doWork(pid);
		pid = fork();
		exit(0);
    }
    else {		
		//printf("sou o pai e vou acabar logo");
		doWork(pid);
		waitpid(pid,0,0);
    }
}
    return 0;
}
