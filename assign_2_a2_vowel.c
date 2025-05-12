#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
    char str[100];
    int vowels = 0;
    pid_t pid;
    int fd[2]; 
    if (pipe(fd) == -1) 
	{
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid == 0) 
	{ 
        close(fd[0]); 
        printf("Enter a sentence: ");
        fgets(str, sizeof(str), stdin);
        write(fd[1], str, strlen(str) + 1); 
        close(fd[1]); 
        exit(0);
    } 
    else 
	{ 
        wait(NULL); 
        close(fd[1]); 
        read(fd[0], str, sizeof(str)); 
        close(fd[0]); 

        for (int i = 0; str[i] != '\0'; i++) 
		{
            if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || 
                str[i] == 'o' || str[i] == 'u' || str[i] == 'A' || 
                str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
                vowels++;
            }
        }

        printf("Number of vowels: %d\n", vowels);
    }

    return 0;
}