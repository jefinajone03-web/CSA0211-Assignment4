/* Task 5 (C) - register variable as loop counter */
#include <stdio.h>

int main(void)
{
    for (register int i = 1; i <= 5; i++)
        printf("%d ", i);
    printf("\n");
    /* &i is not allowed for a register variable */
    return 0;
}
