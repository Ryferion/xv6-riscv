#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (clone())
    {
        printf("fail\n");
    }
    exit(0);
}
