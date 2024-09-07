#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("Dauphine\n");
    write(1, "MIDO", 4);
    printf("paris\n");
    return 0;
}
