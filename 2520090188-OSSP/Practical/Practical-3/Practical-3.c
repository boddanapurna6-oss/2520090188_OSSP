#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Parent process started.\n");
    printf("Parent PID  : %d\n", getpid());
    printf("Parent PPID : %d\n", getppid());
    fflush(stdout);

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("\n--- CHILD PROCESS ---\n");
        printf("Child PID  : %d\n", getpid());
        printf("Child PPID : %d\n", getppid());

        printf("Child is running...\n");
        fflush(stdout);

        printf("Child is now waiting for 10 seconds...\n");
        fflush(stdout);

        sleep(10);

        printf("Child resumed running after waiting.\n");
        fflush(stdout);

        printf("Child terminating...\n");
        return 0;
    }
    else
    {
        // Parent process
        printf("\n--- PARENT PROCESS ---\n");
        printf("Parent PID  : %d\n", getpid());
        printf("Parent PPID : %d\n", getppid());

        printf("Parent is running...\n");
        fflush(stdout);

        printf("Parent is waiting for the child to terminate...\n");
        fflush(stdout);

        wait(NULL);

        printf("Child has terminated.\n");
        printf("Parent terminating...\n");
    }

    return 0;
}
