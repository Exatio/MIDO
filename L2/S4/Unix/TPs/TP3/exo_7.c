#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    
    char *bin = "wc";
    char *args[] = { bin, "-l", "exo_2_a.c", NULL };
    execvp(bin, args);
    return 0;
}
