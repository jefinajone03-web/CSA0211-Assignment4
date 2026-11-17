/* Task 5 - Alternative: caller-owned counters passed by pointer.
 * Supports independent veg / non-veg counters. */
#include <stdio.h>

int next_token(int *counter)
{
    return ++(*counter);
}

int main(void)
{
    int veg = 1000;
    int nonveg = 2000;

    int v1 = next_token(&veg);
    int v2 = next_token(&veg);
    int n1 = next_token(&nonveg);
    int n2 = next_token(&nonveg);

    printf("Veg: %d %d\n", v1, v2);
    printf("Non-Veg: %d %d\n", n1, n2);
    return 0;
}
