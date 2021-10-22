#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int main()
{
    time_t start = time(NULL);
    for (int i = 0; i < 1000000; i++)
    {
        system("echo \">\" | ./minishell >> result_file");
    }
    time_t end = time(NULL);
    printf("it took %ld seconds \n", start - end);

}