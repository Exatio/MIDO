#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Erreur, donnez une commande à exécuter\n");
        return 1;
    }

    int pid = fork();
    
    if (pid == 0) { 
        execvp(argv[1], &argv[1]);
    } else {
        int r;
        int p = wait(&r);
        printf("Le fils (%d) s'est terminé avec le code %d\n", p, WEXITSTATUS(r)); 
    }

    return 0;
}
