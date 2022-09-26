// Pour compiler: gcc indexer.c -o indexer
// Pour executer: ./indexer [file]

#include <errno.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"
#define BUF_SIZE 2048


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]){

  char c;
  int fd, idx_fd, nwrite, nread, count = 0;

  verifier(argc == 2, "il faut un paramètre.");

  int l = strlen(argv[1]);
  char idx_filename[l + strlen(SUFFIXE) + 1];

  // construire le chemin au fichier index
  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);

  // open files
  fd = open(argv[1], O_RDONLY);
  verifier(fd != -1, "Error opening input file");
  idx_fd = open(idx_filename, O_WRONLY | O_CREAT | O_TRUNC, 0640);
  verifier(idx_fd != -1, "Error opening index file");


  // index all line breaks
  nread = read(fd, &c, 1);
  while (nread == 1) {
    if (c == '\n') {
      nwrite = write(idx_fd, &count, sizeof(int));
      verifier(nwrite != -1, "Error writing to index file");
    }
    count++;
    nread = read(fd, &c, 1);
  }
  verifier(nread != -1, "Error reading from input file");

  // close files
  close(fd);
  close(idx_fd);

  return EXIT_SUCCESS;
}
