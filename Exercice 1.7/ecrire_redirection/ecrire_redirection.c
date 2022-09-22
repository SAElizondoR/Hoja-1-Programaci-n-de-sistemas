// Pour compiler: gcc ecrire_redirection.c -o ecrire_redirection
// Pour executer: ./ecrire_redirection

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
