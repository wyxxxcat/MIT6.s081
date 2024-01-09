#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void f(int p_id)
{
    int flag = 0;
    int num = 0;
    int pipe_[2];
    int num_ = 0;
    while (1)
    {
        if (!read(p_id, &num_, 4))
        {
            close(p_id);
            if (flag)
            {
                close(pipe_[1]);

                int ch_id;
                wait(&ch_id);
            }
            exit(0);
        }
        // is prime
        if (num == 0)
        {
            num = num_;
            printf("prime %d\n", num);
        }
        // is not prime
        if (num_ % num != 0)
        {
            if (!flag)
            {
                pipe(pipe_);
                flag = 1;
                if (!fork())
                {
                    close(pipe_[1]);
                    close(p_id);
                    f(pipe_[0]);
                }
                else
                {
                    close(pipe_[0]);
                }
            }
            write(pipe_[1], &num_, 4);
        }
    }
}
int main()
{
    int primes[2];
    pipe(primes);

    for (int i = 2; i <= 35; i++)
    {
        write(primes[1], &i, 4);
    }
    close(primes[1]);
    f(primes[0]);
    exit(0);
}