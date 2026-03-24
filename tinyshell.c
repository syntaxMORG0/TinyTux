#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    char buf[256], *argv[16];
    while (1) {
        write(1, "$ ", 2);
        int n = read(0, buf, 255);
        if (n <= 0) break;
        buf[n-1] = 0; // remove newline
        if (strcmp(buf, "exit") == 0) break;

        int argc = 0;
        char *p = buf;
        while (*p) {
            while (*p==' '||*p=='\t') *p++=0;
            if (*p) argv[argc++] = p;
            while (*p && *p!=' ' && *p!='\t') p++;
        }
        argv[argc] = 0;

        if (fork() == 0) {
            execve(argv[0], argv, 0);
            write(2, "not found\n", 10);
            _exit(1);
        } else waitpid(-1, 0, 0);
    }
    return 0;
}
