#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv)
{
    int ppSon[2];
    int ppFa[2];

    // pipe 0 read 1 write
    pipe(ppSon); // Fa -> Son
    pipe(ppFa);  // Son -> Fa
    if (fork() != 0)
    { // Fa
        write(ppSon[1], "1", 1);
        char buf;
        read(ppFa[0], &buf, 1);
        printf("%d: received pong\n", getpid());
    }
    else
    { // Son
        char buf;
        read(ppSon[0], &buf, 1); // 3. Fa->Son
        printf("%d: received ping\n", getpid());
        write(ppFa[1], &buf, 1); // Son->Fa
    }
    exit(0);
}