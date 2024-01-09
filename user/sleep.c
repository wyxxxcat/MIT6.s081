#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage:sleep need a number eg. sleep 2\n");
    }
    if (sleep(atoi(argv[1])))
    {
        printf("sleep Error\n");
    }
    exit(0);
}