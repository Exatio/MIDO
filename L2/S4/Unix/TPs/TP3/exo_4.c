#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 2048

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Veuillez donnez 1 ou 2 arguments : nom de fichier source, nom de fichier destination (sortie standard par défaut).\n");
        return 1;
    }


    int source = open(argv[1], O_RDONLY);
    if (source == -1) {
        printf("Impossible d'ouvrir le fichier source\n");
        return 1;
    }

    if (argc == 3) {
        int dest = open(argv[2], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
        if (dest == -1) {
            printf("Impossible d'ouvrir le fichier destination\n");
            return 1;
        }
        close(1);
        dup(dest);
    }


    char buf[SIZE];
    int read_size;
    while((read_size = read(source, buf, SIZE)) > 0) {
        printf("%s", buf);
    }

    if (read_size == -1) {
        close(1);
        dup(stdout->_fileno); // remettre la sortie standard sur 1
        printf("Impossible de lire le fichier source\n");
        return 1;
    }

    return 0;
}
