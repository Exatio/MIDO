#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();
    
    if (pid == 0) {
        printf("Le bloc 'si' est exécuté. PID enfant : %d, PID parent : %d\n", getpid(), getppid());
    } else {
        printf("Le bloc 'sinon' est exécuté. PID parent : %d, PID enfant : %d\n", getpid(), pid);
    }

    return 0;
}

/*
On a que fork() duplique son processus et continue son exécution. si fork() est lancé depuis le parent, il renvoie le pid de l'enfant, sinon 0
Alors, le temps que le nouveau processus se "lance" (réservation de mémoire, etc), on a en général que
le processus parent continue son exécution avant le processus enfant, d'où l'affichage qu'on obtient :

(depuis le parent)
Le bloc 'sinon' est exécuté. PID parent : 21364, PID enfant : 21365
(depuis l'enfant)
Le bloc 'si' est exécuté. PID enfant : 21365, PID parent : 21364
*/ 