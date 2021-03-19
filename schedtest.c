#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

//#include "stdlib.h"
// spawn two children processes, each running loop
// parent calls fork2 and exec for two children, A then B
int
main(int argc, char **argv)
{
    // int pid = getpid();
    // struct pstat ps;
    // printf(1, "pointer in user program is %p\n", &ps);

    // //printf(1, "pid is %d\n", pid);
    
    // int res = getslice(pid);
    // printf(1, "res code is %d\n", res);
    // getpinfo(&ps);


    // ========================== //
    if (argc != 6) {
        printf(2, "exactly five arguments allowed\n");
        exit();
    }
    int sliceA = atoi(argv[1]);
    int sleepA = atoi(argv[2]);
    int sliceB = atoi(argv[3]);
    int sleepB = atoi(argv[4]);
    int sleepParent = atoi(argv[5]);

    // TODO
    // arguments for loop
    char *argvA[] = { "sh", (char*)&sleepA };
    char *argvB[] = { "sh", (char*)&sleepB };

    // spawn two children processes
    int pidA = fork2(sliceA);
    int pidB = fork2(sliceB);
    // child runs
    if (pidA == 0) {
        if (exec("loop",argvA) == -1) {
            printf(1, "command not found\n");
            exit();
        }
    } else {
        sleep(sleepParent);
        wait();
    }
    if (pidB == 0) {
        if (exec("loop",argvB) == -1) {
            printf(1, "command not found\n");
            exit();
        }
    } else {
        sleep(sleepParent);
        wait();
    }
    sleep(sleepParent);
    struct pstat p;
    getpinfo(&p);
    printf(1, "prepare to exit\n");
    exit();
}