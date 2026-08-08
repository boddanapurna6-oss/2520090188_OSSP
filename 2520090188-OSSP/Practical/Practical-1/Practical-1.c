























#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char command[100];
    char *args[20];
    int i = 0;
    pid_t pid;
    int status;

    printf("Enter a Linux command: ");
    fgets(command, sizeof(command), stdin);

    // Remove newline character
    command[strcspn(command, "\n")] = '\0';

    // Split command into arguments
    char *token = strtok(command, " ");

    while (token != NULL && i < 19)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    else if (pid == 0)
    {
        // Child process
        printf("\nChild Process\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        // Execute the command
        execvp(args[0], args);

        // Executes only if execvp fails
        perror("execvp failed");
        exit(1);
    }

    else
    {
        // Parent process
        printf("\nParent Process\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        // Wait for child process to finish
        wait(&status);

        printf("\nChild process completed.\n");
    }

    return 0;
}
