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
  int line_number, fd, idx_fd, idx_size, nseek, nread, line_index;
  int l = strlen(argv[1]);
  char idx_filename[l + strlen(SUFFIXE) + 1], c;

  verifier(argc == 3, "il faut deux paramètres.");

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

  // get line index
  nseek = lseek(idx_fd, line_number * sizeof(int), SEEK_SET);
  verifier(nseek != -1, "Error trying to set pointer to given position");
  verifier(nseek < idx_size, "The entered index doesn't exist");
  nread = read(idx_fd, &line_index, sizeof(int));
  verifier(nread != -1, "Error reading from file");
  nseek = lseek(fd, line_index + 1, SEEK_SET);
  verifier(nseek != -1, "Error trying to set pointer to given position");

  // read line
  nread = read(fd, &c, 1);
  while (nread == 1 && c != '\n') {
    printf("%c", c);
    nread = read(fd, &c, 1);
  }
  printf("\n");
  verifier(nread != -1, "Error reading from input file");  
  
  // close files
  close(fd);
  close(idx_fd);

  return EXIT_SUCCESS;
}
