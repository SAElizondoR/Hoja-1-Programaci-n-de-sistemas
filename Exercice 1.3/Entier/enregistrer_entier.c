// Pour compiler: gcc enregistrer_entier.c -o enregistrer_entier
// Pour executer: ./enregistrer_entier [nom-du-fichier] [position] [valeur]

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
  int fd, pos, nseek, nwrite;
  off_t val;

  verifier(argc == 4, "Invalid number of arguments");

  fd = open(argv[1], O_WRONLY | O_CREAT, 0640);
  verifier(fd != -1, "Error opening file");
  pos = atoi(argv[2]);
  val = atoi(argv[3]);

  nseek = lseek(fd, pos * sizeof(off_t), SEEK_SET);
  verifier(nseek != -1, "Error trying to set pointer to given position");
  nwrite = write(fd, &val, sizeof(off_t));
  verifier(nwrite != -1, "Error writing to file");
  
  close(fd);
 
  return EXIT_SUCCESS;
}
