#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SIZE 2048

int main(int argc, char *argv[]) {

    if(argc != 3) {
        printf("Erreur, donnez : nom de fichier source, nom de fichier destination\n");
        return 1;
    }

    int pipefd[2];
    pipe(pipefd);

    int pid = fork();
    
    if (pid != 0) { // parent
        close(pipefd[0]);
        int source = open(argv[1], O_RDONLY);
        if (source == -1) {
            printf("Impossible d'ouvrir le fichier source\n");
            return 1;
        }

        char buf[SIZE];
        int read_size;
        while((read_size = read(source, buf, SIZE)) > 0) {
            write(pipefd[1], buf, read_size);
        }
        close(pipefd[1]);
        
        int r;
        int p = wait(&r);
        printf("Le fils (%d) s'est terminé avec le code %d\n", p, WEXITSTATUS(r)); 

        close(source);

    } else { // enfant
        close(pipefd[1]);
        int dest = open(argv[2], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
        if (dest == -1) {
            printf("Impossible d'ouvrir le fichier destination\n");
            return 1;
        }

        char buf[SIZE];
        int read_size;
        while((read_size = read(pipefd[0], buf, SIZE)) > 0) {
            write(dest, buf, read_size);
        }
        close(pipefd[0]);
        close(dest);
        
    }

    return 0;
}
