#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

void doWork(char *arg) {
    printf("%s\n", arg);
}

int main()
{
    /*Spawn a new process to run alongside us.*/
    pid_t pid = fork();
    pid = fork();
    pid = fork();
    if (pid == 0) {		/* child process */
		doWork("child");
		exit(0);
    }
    else {			/* pid!=0; parent process */
		//printf("sou o pai e vou acabar logo");
		doWork("parent");
        printf("%i\n", pid);
		waitpid(pid,0,0);	/* wait for child to exit */
    }
    return 0;
}