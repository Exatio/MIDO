#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();
    
    if (pid == 0) {
        printf("Fils: PID enfant : %d, PID parent : %d\n", getpid(), getppid());
        sleep(10);
        printf("Fils: j'ai fini!\n");
    } else {
        printf("Parent: PID parent : %d, PID enfant : %d\n", getpid(), pid);
        int r;
        int p = wait(&r);
        printf("Parent: Le fils (%d) s'est terminé avec le code %d\n", p, WEXITSTATUS(r));
    }

    return 0;
}
