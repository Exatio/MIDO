# TP5 : Manipulation de fichiers

## Exercice 1 : Echo

```C
#include <stdio.h>

void main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
}
```

## Exercice 2 : Affichage d'une image

On remarque que les fichiers sont bien au format PGM ASCII car les lignes correspondent bien aux lignes d'un fichier binaire PGM.

## Exercice 3 : Lecture d'un fichier PGM

```C
#include <stdio.h>  
  
void printPGM(const char *filename) {  
    FILE *file = fopen(filename, "r");  
  
    if (file == NULL) {  
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);  
        return;  
    }  
    char magic[2];  
    int width, height, maxval;  
  
    if (fscanf(file, "%2s %d %d %d", magic, &width, &height, &maxval) != 4 || magic[0] != 'P' || magic[1] != '2') {  
        printf("Erreur : Format de fichier PGM invalide pour le fichier %s.\n", filename);  
        fclose(file);  
        return;  
    }  
    printf("Fichier : %s\n", filename);  
    printf("Largeur : %d\n", width);  
    printf("Hauteur : %d\n", height);  
  
    fclose(file);  
}  
  
int main(int argc, char *argv[]) {  
    if (argc < 2) {  
        printf("Usage: %s fichier1.pgm fichier2.pgm ...\n", argv[0]);  
        return 1;  
    }  
    for (int i = 1; i < argc; i++) {  
        printPGM(argv[i]);  
        printf("\n");  
    }  
    return 0;  
}
```

## Exercice 4 : 

```C
#include <stdio.h>  
#include <stdlib.h>  
  
void loadImage(const char *filename, int *w, int *h, int *vMax, int ***matrix) {  
    FILE *file = fopen(filename, "r");  
  
    if (file == NULL) {  
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);  
        return;  
    }  
    char magicNumber[3];  
    fscanf(file, "%s", magicNumber);  
  
    fscanf(file, "%d %d %d", w, h, vMax);  
  
    *matrix = (int **) malloc(*h * sizeof(int *));  
    for (int i = 0; i < *h; i++) {  
        (*matrix)[i] = (int *) malloc(*w * sizeof(int));  
        for (int j = 0; j < *w; j++) {  
            fscanf(file, "%d", &(*matrix)[i][j]);  
        }    }  
    fclose(file);  
}  
  
void saveImage(int **matrix, int h, int w, int vMax, const char *filename) {  
    FILE *file = fopen(filename, "w");  
  
    if (file == NULL) {  
        printf("Erreur : Impossible de créer le fichier %s.\n", filename);  
        return;  
    }  
    fprintf(file, "P2\n");  
    fprintf(file, "%d %d\n%d\n", w, h, vMax);  
  
    for (int i = 0; i < h; i++) {  
        for (int j = 0; j < w; j++) {  
            fprintf(file, "%d ", matrix[i][j]);  
        }        fprintf(file, "\n");  
    }  
    fclose(file);  
}  
  
int main(int argc, char *argv[]) {  
  
    if (argc != 3) {  
        printf("Usage: %s input.pgm output.pgm\n", argv[0]);  
        return 1;  
    }  
    int width, height, maxVal;  
    int **imageMatrix;  
  
    loadImage(argv[1], &width, &height, &maxVal, &imageMatrix);  
  
    printf("Fichier : %s\n", argv[1]);  
    printf("Largeur : %d\n", width);  
    printf("Hauteur : %d\n", height);  
    printf("Valeur maximale : %d\n", maxVal);  
  
    saveImage(imageMatrix, height, width, maxVal, argv[2]);  
  
    for (int i = 0; i < height; i++) {  
        free(imageMatrix[i]);  
    }    free(imageMatrix);  
  
    return 0;  
}
```

## Exercice 5 : Traitement d'images PGM

En réutilisant les fonctions ci-dessus

### Inversion

```C
void invertColors(int **matrix, int h, int w, int vMax) {  
    for (int i = 0; i < h; i++) {  
        for (int j = 0; j < w; j++) {  
            matrix[i][j] = vMax - matrix[i][j];  
        }    
        
    }
}  
  
int main(int argc, char *argv[]) {  
    if (argc != 2) {  
        printf("Usage: %s input.pgm\n", argv[0]);  
        return 1;  
    }  
    int width, height, maxVal;  
    int **imageMatrix;  
  
    loadImage(argv[1], &width, &height, &maxVal, &imageMatrix);  
  
    invertColors(imageMatrix, height, width, maxVal);  
  
    saveImage(imageMatrix, height, width, maxVal, "inv.pgm");  
  
    for (int i = 0; i < height; i++) {  
        free(imageMatrix[i]);  
    }    free(imageMatrix);  
  
    return 0;  
}
```


### Noir et blanc

```C
void blackAndWhite(int **matrix, int h, int w, int vMax) {  
    for (int i = 0; i < h; i++) {  
        for (int j = 0; j < w; j++) {  
            matrix[i][j] = (matrix[i][j] < vMax / 2) ? 0 : vMax;  
        }    }}  
  
int main(int argc, char *argv[]) {  
    if (argc != 2) {  
        printf("Usage: %s input.pgm\n", argv[0]);  
        return 1;  
    }  
    int width, height, maxVal;  
    int **imageMatrix;  
  
    loadImage(argv[1], &width, &height, &maxVal, &imageMatrix);  
  
    blackAndWhite(imageMatrix, height, width, maxVal);  
  
    saveImage(imageMatrix, height, width, maxVal, "bw.pgm");  
  
    for (int i = 0; i < height; i++) {  
        free(imageMatrix[i]);  
    }    free(imageMatrix);  
  
    return 0;  
}
```

### Flou

```C
void blur(int **matrix, int h, int w) {  
    int **tempMatrix = (int **) malloc(h * sizeof(int *));  
    for (int i = 0; i < h; i++) {  
        tempMatrix[i] = (int *) malloc(w * sizeof(int));  
        for (int j = 0; j < w; j++) {  
            tempMatrix[i][j] = matrix[i][j];  
        }
    }  
    for (int i = 1; i < h - 1; i++) {  
        for (int j = 1; j < w - 1; j++) {  
            matrix[i][j] = (tempMatrix[i - 1][j] + tempMatrix[i + 1][j] + tempMatrix[i][j - 1] + tempMatrix[i][j + 1]) / 4;  
        }
    }  
    for (int i = 0; i < h; i++) {  
        free(tempMatrix[i]);  
    }
    free(tempMatrix);  
}  
  
int main(int argc, char *argv[]) {  
    if (argc != 2) {  
        printf("Usage: %s input.pgm\n", argv[0]);  
        return 1;  
    }  
    int width, height, maxVal;  
    int **imageMatrix;  
  
    loadImage(argv[1], &width, &height, &maxVal, &imageMatrix);  
  
    blur(imageMatrix, height, width);  
  
    saveImage(imageMatrix, height, width, maxVal, "blurred.pgm");  
  
    for (int i = 0; i < height; i++) {  
        free(imageMatrix[i]);  
    }    
    free(imageMatrix);  
  
  
    return 0;  
}
```


## Exercice 6 : Bufferisation

```C
#include <stdio.h>  
#include <time.h>  
  
void copyFileCharByChar(FILE *source, FILE *destination) {  
    int c;  
    while ((c = fgetc(source)) != EOF) {  
        fputc(c, destination);  
    }
}  
  
void copyFileWithBuffer(FILE *source, FILE *destination, int bufferSize) {  
    char buffer[bufferSize];  
    int bytesRead;  
  
    while ((bytesRead = fread(buffer, sizeof(char), bufferSize, source)) > 0) {  
        fwrite(buffer, sizeof(char), bytesRead, destination);  
    }
}  
  
int main() {  
    FILE *sourceFile = fopen("gutenberg.txt", "r");  
    FILE *charByCharFile = fopen("gutenberg_char.txt", "w");  
    FILE *bufferFile;  
  
    clock_t start, end;  
    double cpu_time_used;  
  
    start = clock();  
    copyFileCharByChar(sourceFile, charByCharFile);  
    end = clock();  
    cpu_time_used = ((double) (end -  start) * 1000) / CLOCKS_PER_SEC;  
    printf("Time taken for character by character copy: %f ms\n", cpu_time_used);  
  
  
    for (int i = 1; i <= 32; i++) {  
        fseek(sourceFile, 0, SEEK_SET);  // pas mentionné dans l'énoncé, mais on a besoin de ça pour réinitialiser le curseur  
  
        bufferFile = fopen("gutenberg_buf.txt", "w");  
        start = clock();  
        copyFileWithBuffer(sourceFile, bufferFile, i);  
        end = clock();  
        cpu_time_used = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;  
        printf("Time taken for buffer size %d: %fms\n", i, cpu_time_used);  
  
        fclose(bufferFile);  
    }  
    fclose(sourceFile);  
    fclose(charByCharFile);  
  
    return 0;  
}
```
