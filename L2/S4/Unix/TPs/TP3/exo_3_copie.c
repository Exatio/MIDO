#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 2048

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Veuillez donnez 2 arguments : nom de fichier source, nom de fichier destination.\n");
        return 1;
    }


    int source = open(argv[1], O_RDONLY);
    if (source == -1) {
        printf("Impossible d'ouvrir le fichier source\n");
        return 1;
    }

    int dest = open(argv[2], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
    if (dest == -1) {
        printf("Impossible d'ouvrir le fichier destination\n");
        return 1;
    }


    char buf[SIZE];
    int read_size;
    while((read_size = read(source, buf, SIZE)) > 0) {
        write(dest, buf, read_size);
    }

    if (read_size == -1) {
        printf("Impossible de lire le fichier source\n");
        return 1;
    }

    printf("Copié\n");

    return 0;
}
