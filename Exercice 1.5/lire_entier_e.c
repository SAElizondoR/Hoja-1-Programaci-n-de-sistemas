// Pour compiler: gcc lire_entier_e.c -o lire_entier_e
// Pour executer: ./lire_entier_e [nom-du-fichier] [position]

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void verifier(int cond, char *s){
  if (!cond){
    int err_d = open("ERREURS_LIRE.log", O_WRONLY | O_CREAT | O_APPEND, 0666);
    dup2(err_d, STDERR_FILENO);
    perror(s);
    close(err_d);
    exit(EXIT_FAILURE);
  }
}


int main(int argc, char **argv)
{
  int fd, pos, n_seek, nread;
  off_t val;
  
  verifier(argc == 3, "Invalid number of arguments");
  
  fd = open(argv[1], O_RDONLY);
  verifier(fd != -1, "Error opening file");
  pos = atoi(argv[2]);
  
  n_seek = lseek(fd, pos * sizeof(off_t), SEEK_SET);
  verifier(n_seek != -1, "Error trying to set pointer to given position");
  nread = read(fd, &val, sizeof(off_t));
  verifier(nread != -1, "Error reading from file");
  
  close(fd);

  printf("\n%ld\n\n", val);
 
  return EXIT_SUCCESS;
}
