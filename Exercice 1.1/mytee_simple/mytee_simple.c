// Pour compiler:  gcc mytee_simple.c -o mytee_simple
// Pour executer: ./mytee_simple

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void verifier(int cond, char *s) {
    if (!cond) {
        perror(s);
        exit(EXIT_FAILURE);
    }
}


int main()
{
    int nwrite, nread;
    char c;

    nread = read(STDIN_FILENO, &c, 1);

    while (nread == 1) {
        nwrite = write(STDOUT_FILENO, &c, 1);
        verifier(nwrite != -1, "Error writing to standard output");
        nread = read(STDIN_FILENO, &c, 1);
    }

    verifier(nread != -1, "Error reading from standard output");
    
    return EXIT_SUCCESS;
}
