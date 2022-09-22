// Pour compiler: gcc enregistrer_entier_simple.c -o enregistrer_entier_simple
// Pour executer: ./enregistrer_entier_simple [nom-du-fichier] [valeur]

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
  int fd, nwrite;
  off_t val;

  verifier(argc == 3, "Invalid number of arguments");

  fd = open(argv[1], O_WRONLY | O_CREAT, 0640);
  verifier(fd != -1, "Error opening file");
  val = atoi(argv[2]);

  nwrite = write(fd, &val, sizeof(off_t));
  verifier(nwrite != -1, "Error writing to file");
  
  close(fd);
 
  return EXIT_SUCCESS;
}
