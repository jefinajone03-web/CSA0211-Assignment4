/* Task 5 (B) - File 2: uses the global counter through extern
 * Compile: gcc main.c counter.c -o counter
 */
#include <stdio.h>

extern int token;
int next_global_token(void);

int main(void)
{
    /* Separate variables guarantee increasing order
       (argument evaluation order in printf is unspecified). */
    int g1 = next_global_token();
    int g2 = next_global_token();
    int g3 = next_global_token();

    printf("Global: %d %d %d\n", g1, g2, g3);
    printf("token (extern) = %d\n", token);
    return 0;
}
