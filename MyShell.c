#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    // Child process id
    pid_t   childpid;

    // Status code returned from child process to parent process.
    int status;

    // This will hold current working directory path
    char directory[1000] = "";

    // Get current working directory of process.
    getcwd(directory, sizeof(directory));

    while(1)
    {
        int fd[2];
        pipe(fd);

        char command[60];

        printf("%s>", directory);
        fgets(command, 60, stdin);

        // Remove newline character from the command we got
        int ln = strlen(command) - 1;
        if (command[ln] == '\n')
            command[ln] = '\0';

        if(strlen(command) > 0)
        {
            // Handle exit command
            if(strcmp(command, "exit") == 0)
                break;

            strcat(command, " && pwd"); // add pwd to get last working directory after command.

            // Create child process
            if((childpid = fork()) == -1)
            {
                perror("fork");
                exit(1);
            }

            // child process
            if(childpid == 0)
            {
                /* Child process closes up input side of pipe */
                close(fd[0]);

                // redirect stdout(1) to pipe, stderr(2)
                dup2(fd[1], 1);

                if(strlen(directory) > 0){
                    chdir(directory);
                }
                char *const parmList[] = {"/bin/sh", "-c", command, NULL};
                execv("/bin/sh", parmList);
            }
            else
            {
                wait(&status);
                close(fd[1]);

                char readbuffer[90000] = "";
                read(fd[0], readbuffer, sizeof(readbuffer));

                // Child process exited normally or not,
                // and if exited normally then status should be zero for success command execution
                if(WIFEXITED(status) && WEXITSTATUS(status)==0) {

                    if(strlen(readbuffer) > 0)
                    {
                        // count lines of the read buffer
                        int count = 0; int i;
                        for(i = 0; readbuffer[i] != '\0'; i++) {
                          if(readbuffer[i] == '\n') count++;
                        }
                        // Get last element, with the path of current working directory
                        char* pch = NULL;
                        pch = strtok(readbuffer, "\n");
                        char* pwdResult = NULL;
                        int index = 0;
                        while (pch != NULL)
                        {
                           pwdResult = pch;
                           if(index != count - 1)     // do not print last line which holds current directory
                              printf("%s\n", pch);
                           pch = strtok(NULL, "\n");
                           index++;
                        }

                        if(pwdResult[0] == '/')
                            strcpy(directory, pwdResult);
                        }
                     }
                }
            }
        }
    return(0);
}
