#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
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

    exit();
}