// Pour compiler: gcc copy_taille_osync.c -o copy_taille_osync
// Pour executer: ./copy_taille_osync [input-file-name] [output-file-name] [taille]

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER_LEN 100000


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
  int input_fd, output_fd, taille, nread, nwrite, nclose;
  char buffer[MAX_BUFFER_LEN];  // buffer de taille fixe

  verifier(argc >= 4, "Invalid number of arguments");

  input_fd = open(argv[1], O_RDONLY);
  verifier(input_fd != -1, "Error opening input file");
  output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC | O_SYNC, 0640);
  verifier_et_fermer_fichier_dentree(output_fd != -1,
    "Error opening output file", input_fd);
  taille = atoi(argv[3]);

  nread = read(input_fd, &buffer, taille);
  while (nread > 0) { // on continue à copier tant qu'il y a des octets à lire
    nwrite = write(output_fd, &buffer, nread);
    verifier(nwrite != -1, "Error writing to output file");
    nread = read(input_fd, &buffer, taille);
  }

  verifier(nread != -1, "Error reading from input file");   
  nclose = close(input_fd);
  verifier(nclose != -1,"Error closing input file");
  nclose = close(output_fd);
  verifier(nclose != -1,"Error closing output file");
  
  return EXIT_SUCCESS;
}
