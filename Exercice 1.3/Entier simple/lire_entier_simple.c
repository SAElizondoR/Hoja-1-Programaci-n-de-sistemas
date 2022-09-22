// Pour compiler: gcc lire_entier_simple.c -o lire_entier_simple
// Pour executer: ./lire_entier_simple [nom-du-fichier]

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}


int main(int argc, char **argv)
{
  int fd, nread;
  off_t val;

  verifier(argc == 2, "Invalid number of arguments");

  fd = open(argv[1], O_RDONLY);
  verifier(fd != -1, "Error opening file");
  
  nread = read(fd, &val, sizeof(off_t));
  verifier(nread != -1, "Error reading from file");
  
  close(fd);

  printf("\n%ld\n\n", val);
 
  return EXIT_SUCCESS;
}
