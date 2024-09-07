#include <stdio.h>

// time ./exo_2_a : 0m0.109s

int main() {
    FILE *file = fopen("beaucoupde0_a.txt", "w");

    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier");
        return 1;
    }

    for (int i = 0; i < 1e7; i++) {
        fwrite("0", sizeof(char), 1, file);
    }

    fclose(file);
    return 0;
}