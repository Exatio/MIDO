#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 2048

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Erreur, veuillez fournir une commande.\n");
        return 1;
    }

    int pipefd[2];
    pipe(pipefd);

    int pid = fork();

    if(pid != 0) { // parent
        close(pipefd[1]); 

        char buf[SIZE];
        int read_size;
        while((read_size = read(pipefd[0], buf, SIZE)) > 0) {
            printf("%s", buf);
        }

        close(pipefd[0]); 
        
        int r;
        int p = wait(&r);
        printf("Le fils (%d) s'est terminé avec le code %d\n", p, WEXITSTATUS(r)); 

    } else {
        close(pipefd[0]); 
        // sortie standard devient écriture du pipe 
        close(1);
        dup(pipefd[1]);
        
        execlp(argv[1], argv[1], NULL);

        close(pipefd[1]); 
    }

    return 0;
}
