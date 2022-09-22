// Pour compiler: gcc ecrire.c -o ecrire
// Pour executer: ./ecrire

#include <stdio.h>
#include <unistd.h>


int main()
{
    // Lorsque la fonction principale commence à s'exécuter, elle appelle
    // d'abord la fonction printf, qui exécute une procédure plus
    // complexe dans laquelle un buffer est configuré pour stocker la chaîne
    // de caractères ; A noter que cette chaîne n'est pas imprimé
    // immédiatement, mais reste stockée dans le buffer, puisque la fonction
    // printf cherche à minimiser le nombre d'appels système d'écriture qu'elle.
    printf("hello ");
    // On voit que si nous remplaçons la première chaîne par "hello\n",
    // l'appel système write se fera immédiatement. En effet, lorsqu'il y a
    // un saut de ligne, la fonction printf effectue l'appel système avec la
    // chaîne de caractères qu'elle a mise en buffer.

    // Donc, dans la fonction main la
    // ligne suivante est exécutée ; Puisqu'il s'agit d'un appel système, cela
    // est exécuté directement, c'est-à-dire qu'aucun autre code n'est exécuté
    // à part l'appel système lui-même.
    write(1,"world", 5);
    // On observe dans le terminal qu'en fait l'appel système imprime son
    // texte avant celui de la fonction d'impression, 
    // c'est pourquoi le texte "world"
    // apparaît en premier dans le terminal, imprimé par l'appel système, puis
    // le texte "hello ", imprimé par le fonction printf.

    return 1;
}
