// Pour compiler: gcc fcopy.c -o fcopy
// Pour executer: ./fcopy [input-file-name] [output-file-name]

#include <stdio.h>
#include <stdlib.h>


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}


void verifier_et_fermer_fichier_dentree(int cond, char *s, FILE* input_fd) {
  if (!cond){
    perror(s);
    fclose(input_fd);
    exit(EXIT_FAILURE);
  }
}


int main(int argc, char **argv)
{
  int nread, nwrite, nclose;
  char c;
  FILE *input_fptr, *output_fptr;

  verifier(argc >= 3, "Invalid number of arguments");

  input_fptr = fopen(argv[1], "r");
  verifier(input_fptr != NULL, "Error opening input file");
  output_fptr = fopen(argv[2], "w");
  verifier_et_fermer_fichier_dentree(output_fptr != NULL,
    "Error opening output file", input_fptr);
  
  nread = fread(&c, sizeof(c), 1, input_fptr);
  while (nread == 1) {
    nwrite = fwrite(&c, sizeof(c), 1, output_fptr);;
    verifier(nwrite == 1, "Error writing to output file");
    nread = fread(&c, sizeof(c), 1, input_fptr);
  }
  
  nclose = fclose(input_fptr);
  nclose = fclose(output_fptr);
  
  return EXIT_SUCCESS;
}
