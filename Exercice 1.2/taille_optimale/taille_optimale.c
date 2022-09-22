// Pour compiler:
// gcc copy_taille_osync.c -o copy_taille_osync
// gcc taille_optimale.c -o taille_optimale

// Pour executer: ./taille_optimale [input-file-name]

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// De combian la taille augmente à chaque fois qu'une expérience est effectuée
#define increment i 


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}


int main(int argc, char **argv)
{
  char* thread_argv[5];
  int meilleur_i;
  clock_t meilleur_temps = INT_MAX;

  thread_argv[0] = "copy_taille";
  thread_argv[1] = argv[1];
  thread_argv[2] = "test";
  thread_argv[4] = NULL;

  verifier(argc >= 2, "Invalid number of arguments");

  for (int i = 1; i <= 100000; i += increment) {
    char i_str[7];
    clock_t begin, end, temps_i;
    pid_t pid;

    sprintf(i_str, "%d", i);
    thread_argv[3] = i_str;

    begin = clock();
    pid = fork();
    if (pid == 0) {
      execv("copy_taille", thread_argv);
      exit(127);
    }
    else {
      waitpid(pid, 0, 0);
      end = clock();

      temps_i = end - begin;
      if (temps_i < meilleur_temps) {
        meilleur_i = i;
        meilleur_temps = temps_i;
      }
    }
  }

  printf("Taille optimale: %d\n\n", meilleur_i);

  
  return EXIT_SUCCESS;
}
