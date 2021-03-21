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
    // printf(1, "pid is %d\n", pid);
    // setslice(pid, 3);
    // struct pstat ps;
    // getpinfo(&ps);

    // sleep(37);
    // getpinfo(&ps);


    // ========================== //
    if (argc != 6) {
        printf(2, "exactly five arguments allowed\n");
        exit();
    }
    char* sliceA = argv[1];
    char* sleepA = argv[2];
    char* sliceB = argv[3];
    char* sleepB = argv[4];
    char* sleepParent = argv[5];
    // TODO
    // arguments for loop
    char *argvA[3] = { "loop", sleepA, '\0' };
    // printf(1, "arg0: %s\n", argvA[0]);
    // printf(1, "arg1: %d\n", atoi(argvA[1]));
    // printf(1, "arg2: %s\n", argvA[2]);
    //char *argvB[] = { "loop", (char*)sleepB };

    // spawn two children processes
    int pidA = fork2(atoi(sliceA));

    // child A runs
    if (pidA == 0) {
        // printf(1, "child A runs\n");
        if (exec(argvA[0],argvA) == -1) {
            printf(1, "command not found\n");
            exit();
        }
    }
    char *argvB[3] = { "loop", sleepB, '\0' };
    // printf(1, "arg0: %s\n", argvB[0]);
    // printf(1, "arg1: %d\n", atoi(argvB[1]));
    // printf(1, "arg2: %s\n", argvB[2]);

    int pidB = fork2(atoi(sliceB));
    if (pidB == 0) {
        // printf(1, "child B runs\n");
        if (exec(argvB[0],argvB) == -1) {
            printf(1, "command not found\n");
            exit();
        }
    } 

    // write(1, "parent going to sleep now\n", 26);
    // printf(1, "Sleep durationnnnn is %d\n", atoi(sleepParent));
    sleep(atoi(sleepParent));
    // write(1, "parent waking up now\n", 21);
    struct pstat p;
    getpinfo(&p);
    int compticksA = 0;
    int compticksB = 0;
    for (int i = 0; i < NPROC; ++i) {
        if (p.pid[i] == pidA) {
            compticksA = p.compticks[i];
        }
        if (p.pid[i] == pidB) {
            compticksB = p.compticks[i];
        }
    }
    printf(1, "%d %d\n", compticksA, compticksB);

    if (pidA != 0) {
        // printf(1, "parent wait for A\n");
        wait();
    }
    if (pidB != 0) {
        // printf(1, "parent wait for B\n");
        wait();
    }
    // printf(1, "pidA: %d\n", pidA);
    // printf(1, "pidB: %d\n", pidB);
    
    // printf(1, "prepare to exit\n");
    // printf(1, "%d %d\n", compticksA, compticksB);

    exit();
}