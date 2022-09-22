// Pour compiler:  gcc mytee.c -o mytee
// Pour executer: ./mytee [output-file-name]

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void verifier(int cond, char *s) {
    if (!cond) {
        perror(s);
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[])
{
    int fd, nwrite, nread, nclose;
    char c;

    verifier(argc == 2, "Invalid number of arguments");

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0640);
    verifier(fd != -1, "Error opening file");

    nread = read(STDIN_FILENO, &c, 1);
    while(nread == 1) {
        nwrite = write(fd, &c, 1);
        verifier(nwrite != -1, "Error writing to file");
        nwrite = write(STDOUT_FILENO, &c, 1);
        verifier(nwrite != -1, "Error writing to standard output");
        nread = read(STDIN_FILENO, &c, 1);
    }
    verifier(nread != -1, "Error reading from standard input");
       
    nclose = close(fd);
    verifier(nclose != -1, "Error closing file");

    return EXIT_SUCCESS;
}
