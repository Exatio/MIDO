#include <stdio.h> // printf()
#include <unistd.h> // write()
#include <fcntl.h> // open()

// time ./exo_2_b : 0m7.634s

int main() {
    int file = open("beaucoupde0_b.txt", O_WRONLY | O_CREAT, S_IWUSR);
    
    if (file == -1) {
        printf("Impossible d'ouvrir le fichier");
        return 1;
    }

    for (int i = 0; i < 1e7; i++) {
        write(file, '0', 1 * sizeof(char));
    }

    close(file);

    return 0;
}