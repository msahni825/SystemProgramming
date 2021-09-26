-----------------CREATION OF A SHELL------------------

gcc my_shell.c
./a.out

Including Header Files:

#include<sys/wait.h>
	waitpid() and related macros

#include<unistd.h>
	chdir()
	fork()
	execv()
	pid_t
	getcwd()

#include<stdlib.h>
	exit()

#include<stdio.h>
	printf()
	getchar()
	fgets()
	
#include<string.h>
	strcmp()
	strtok()

 main()

FUNCTIONS USED
1. char *getcwd(char *buf, size_t size)

The getcwd() function copies an absolute pathname of current working directory to array pointed to by buf,of length size.



2. char *strcat(char *dest, const char *src)

The above function takes 2 arguments, i.e, either 2 strings or 2 character arrays and stores the resultant concatenated string 
in the first argument.



3. char *strtok(char *str, const char *delimiters)
The above function splits the input(str) to tokens, which are sequences of contiguous characters separated by any of the 
characters that are the part of delimiters 


4. wait(int *stat_loc)
The above function wait() blocks the calling process until one of its child processes exits or a signal is received. 


5. chdir(const char *path)
The above command changes the current working directory to the one that is specified in path.

 
6. execv(const char *path, char *const argv[])
The above command uses the current process to abandon the program that it is running and start running the program in file path. 
Parameter argv is the argument vector for the command, with a null pointer at the end. It is an array of strings. 


7. dup2(int oldfd, int newfd)
The above command creates a copy of the file descriptor for the new descriptor.


ADDITIONAL INFORMATION:
  a)fd(0):redaing end of pipe, standard input
  b)fd(1): writing end of pipe, standard output
  c)WIFEXITED(int status)
   Returns True if status was returned for a child that terminated normally
  d)WEXITSTATUS(int status)
   To fetch the value that the child passed to exit, _exit,or _Exit.



