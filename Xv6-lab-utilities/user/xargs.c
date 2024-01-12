#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("The number of invalid parameters\n");
        exit(0);
    }
    char *args[32];
    int args_index = 0;

    for (int i = 1; i < argc; i++)
    {
        args[args_index++] = argv[i];
    }
    char p = '\0';
    char cc[30];
    int cnt = 0;
    while (read(0, &p, sizeof(char)))
    {
        if (p == '\n')
        {
            cc[cnt] = '\0';
            args[args_index] = cc;
            int ret = fork();
            if (ret < 0)
            {
                printf("fork func error\n");
                exit(1);
            }
            if (!ret)
            {
                if (exec(argv[1], args) < 0)
                {
                    printf("xargs: exec echo failed\n");
                    exit(1);
                }
                exit(0);
            }
            wait(0);
            cnt = 0;
        }
        else
        {
            cc[cnt++] = p;
        }
    }
    return 0;
}