// Pour compiler: gcc lire_entier.c -o lire_entier
// Pour executer: ./lire_entier [nom-du-fichier] [position]

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}


int main(int argc, char **argv)
{
  int fd, pos, nseek, nread;
  off_t val;
  
  verifier(argc == 3, "Invalid number of arguments");
  
  fd = open(argv[1], O_RDONLY);
  verifier(fd != -1, "Error opening file");
  pos = atoi(argv[2]);
  
  nseek = lseek(fd, pos * sizeof(off_t), SEEK_SET);
  verifier(nseek != -1, "Error trying to set pointer to given position");
  nread = read(fd, &val, sizeof(off_t));
  verifier(nread != -1, "Error reading from file");
  
  close(fd);

  printf("\n%ld\n\n", val);
 
  return EXIT_SUCCESS;
}
