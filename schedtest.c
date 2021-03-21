#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

// spawn two children processes, each running loop
// parent calls fork2 and exec for two children, A then B
int
main(int argc, char **argv)
{
    if (argc != 6) {
        printf(2, "exactly five arguments allowed\n");
        exit();
    }
    char* sliceA = argv[1];
    char* sleepA = argv[2];
    char* sliceB = argv[3];
    char* sleepB = argv[4];
    char* sleepParent = argv[5];

    // arguments for loop
    char *argvA[3] = { "loop", sleepA, '\0' };
    // spawn two children processes
    int pidA = fork2(atoi(sliceA));

    // child A runs
    if (pidA == 0) {
        if (exec(argvA[0],argvA) == -1) {
            printf(1, "command not found\n");
            exit();
        }
    }
    char *argvB[3] = { "loop", sleepB, '\0' };
    int pidB = fork2(atoi(sliceB));
    if (pidB == 0) {
        if (exec(argvB[0],argvB) == -1) {
            printf(1, "command not found\n");
            exit();
        }
    } 
    sleep(atoi(sleepParent));
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
        wait();
    }
    if (pidB != 0) {
        wait();
    }
    exit();
}