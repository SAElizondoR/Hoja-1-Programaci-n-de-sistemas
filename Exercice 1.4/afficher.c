// Pour compiler: gcc afficher.c -o afficher
// Pour executer: ./afficher [file] [line]

#include <errno.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"

void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]){
  int line_number, fd, idx_fd, idx_size, n_seek, nread, line_index;

  verifier(argc == 3, "il faut deux paramètres.");

  int l = strlen(argv[1]);
  char idx_filename[l + strlen(SUFFIXE) + 1], c;

  // construire le chemin au fichier index
  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);
  line_number = atoi(argv[2]);

  // open files
  fd = open(argv[1], O_RDONLY);
  verifier(fd != -1, "Error opening file");
  idx_fd = open(idx_filename, O_RDONLY);
  verifier(idx_fd != -1, "Error opening index file");
  idx_size = lseek(idx_fd, 0, SEEK_END);
  verifier(line_number < idx_size / sizeof(int), "The entered line index doesn't exist");

  if (line_number == 0)
    line_index = 0;
  else {
    // le premier élément de l'index est la deuxième ligne
    n_seek = lseek(idx_fd, (line_number - 1) * sizeof(int), SEEK_SET);
    verifier(n_seek != -1, "Error trying to set pointer to given position");
    nread = read(idx_fd, &line_index, sizeof(int));
    verifier(nread != -1, "Error reading from file");
    // on passe à la lettre après le saut de ligne
    line_index++;
  }

  n_seek = lseek(fd, line_index, SEEK_SET);
  verifier(n_seek != -1, "Error trying to set pointer to given position");

  // read line
  nread = read(fd, &c, 1);
  while (nread == 1 && c != '\n') {
    printf("%c", c);
    nread = read(fd, &c, 1);
  }
  verifier(nread != -1, "Error reading from input file");  
  printf("\n");
  
  // close files
  close(fd);
  close(idx_fd);

  return EXIT_SUCCESS;
}
