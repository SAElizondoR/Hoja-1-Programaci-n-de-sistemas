// Pour compiler: gcc copy.c -o copy
// Pour executer: ./copy [input-file-name] [output-file-name]

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}


void verifier_et_fermer_fichier_dentree(int cond, char *s, int input_fd) {
  if (!cond){
    perror(s);

    int nclose = close(input_fd);
    verifier(nclose != -1,"Error closing file");

    exit(EXIT_FAILURE);
  }
}


int main(int argc, char **argv)
{
  int input_fd, output_fd, nread, nwrite, nclose;
  char c;

  verifier(argc >= 3, "Invalid number of arguments");

  input_fd = open(argv[1], O_RDONLY);
  verifier(input_fd != -1, "Error opening input file");
  output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0640);
  verifier_et_fermer_fichier_dentree(output_fd != -1,
    "Error openingoutput file", input_fd);
  
  nread = read(input_fd, &c, 1);
  while (nread == 1) {
    nwrite = write(output_fd, &c, 1);
    verifier(nwrite != -1, "Error writing to output file");
    nread = read(input_fd, &c, 1);
  }

  verifier(nread != -1, "Error reading from input file");   
  nclose = close(input_fd);
  verifier(nclose != -1,"Error closing input file");
  nclose = close(output_fd);
  verifier(nclose != -1,"Error closing output file");
  
  return EXIT_SUCCESS;
}
