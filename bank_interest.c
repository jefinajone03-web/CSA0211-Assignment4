/*
 * Task 4 - Structure Forensics
 * Corrected bank savings-account program.
 *
 * Original defects:
 *   1. addInterest(struct account a, float rate) took the structure BY VALUE,
 *      so only a copy was changed and balances stayed the same.
 *   2. p.number / p.balance were used on a pointer; the arrow operator
 *      (p->number, p->balance) is required.
 */
#include <stdio.h>

struct account
{
    int number;
    float balance;
};

/* Pass by pointer so the original structure is modified */
void addInterest(struct account *a, float rate)
{
    printf("Address inside function: %p\n", (void *)a);
    a->balance = a->balance + a->balance * rate / 100;
}

int main(void)
{
    struct account list[3] =
    {
        {101, 5000},
        {102, 12000},
        {103, 800}
    };
    struct account *p = list;

    printf("Address in main: %p\n", (void *)p);

    for (int i = 0; i < 3; i++)
        addInterest(&list[i], 4);

    printf("\nUpdated Account Details:\n");
    for (int i = 0; i < 3; i++)
        printf("%d %.2f\n", (p + i)->number, (p + i)->balance);

    return 0;
}
