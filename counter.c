/* Task 5 (B) - File 1: global counter definition */
int token = 1000;

int next_global_token(void)
{
    return ++token;
}
