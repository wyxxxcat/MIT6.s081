#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
char *find_file_name(char *pathname)
{
    char *prev = 0;
    char *curr = strchr(pathname, '/');
    while (curr != 0)
    {
        prev = curr;
        curr = strchr(curr + 1, '/');
    }
    return prev;
}

void find(char *path, char *target)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    if ((fd = open(path, O_RDONLY)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }
    char *f_name;
    switch (st.type)
    {
    case T_FILE:
        f_name = find_file_name(path);
        int flag = 1;
        if (f_name == 0 || strcmp(f_name + 1, target) != 0)
        {
            flag = 0;
        }
        if (flag)
            printf("%s\n", path);
        break;

    case T_DIR:
        memset(buf, 0, sizeof buf);
        int size = strlen(path);
        memcpy(buf, path, size);
        buf[size] = '/';
        p = buf + size + 1;
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0 || strcmp(de.name, ".") == 0 ||
                strcmp(de.name, "..") == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            find(buf, target);
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Need more than 3 argument\n");
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}