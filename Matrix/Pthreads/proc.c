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

    pid_t pid = 1;
    int i, test = 0;

    for(i = 0; i < 3; i++)
{
    if (pid == 0) {	/* child process */
		doWork(pid);
        test += 100;
        printf("valor: %i\n", test);
		exit(0);
    }
    else if (pid > 1) {		
		//printf("sou o pai e vou acabar logo");
		doWork(pid);
        test += 100;
        printf("valor: %i\n", test);
        pid = fork();
		waitpid(pid,0,0);
    }
    else {
        test += 100;
        printf("valor: %i\n", test);
        pid = fork();
    }
}
    return 0;
}
