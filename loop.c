#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int
main(int argc, char **argv)
{    
    if (argc != 2) {
        printf(2, "exactly one argument allowed, %d given\n", argc);
        exit();
    }
    int sleepT = atoi(argv[1]);
    sleep(sleepT);

    int i = 0, j = 0;
    while (i < 800000000) {
        j += i * j + 1;
        i++;
    }
    
    struct pstat p;
    getpinfo(&p);
    exit();
}
