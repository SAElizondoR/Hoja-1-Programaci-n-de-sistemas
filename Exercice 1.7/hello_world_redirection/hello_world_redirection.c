// Pour compiler: gcc hello_world_redirection.c -o hello_world_redirection
// Pour executer: ./hello_world_redirection

#include <stdio.h>
#include <unistd.h>


int main()
{
    FILE* fptr = freopen("test.txt", "w", stdout);

    printf("hello\n");
    fflush(stdout);
    write(1,"world", 5);

    fclose(fptr);

    return 1;
}
