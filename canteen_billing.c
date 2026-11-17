/*
 * Task 6 - Design Challenge
 * College canteen inventory and billing system.
 * Uses structures, nested structures, a tagged union, arrays of
 * structures and structure pointers.
 */
#include <stdio.h>

/* Date structure */
struct Date
{
    int day, month, year;
};

/* Time structure */
struct Time
{
    int hour, minute;
};

/* Item types */
enum Type
{
    PACKAGED,
    COOKED,
    COMBO
};

/* Item with tagged union */
struct Item
{
    int id;
    char name[30];
    float price;
    int stock;
    enum Type type;
    union
    {
        struct Date expiry;      /* PACKAGED */
        struct Time prepared;    /* COOKED   */
        struct                   /* COMBO    */
        {
            int id[3];
            int qty[3];
            int count;
        } combo;
    } details;
    float revenue;
};

/* Find item using ID; returns index or -1 */
int findItem(struct Item item[], int n, int id)
{
    for (int i = 0; i < n; i++)
    {
        if (item[i].id == id)
            return i;
    }
    return -1;
}

/* Convert date into a day number */
int dateValue(struct Date d)
{
    int days = d.year * 365;

    for (int y = 1; y < d.year; y++)
    {
        if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
            days++;
    }

    int monthDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (d.year % 400 == 0 || (d.year % 4 == 0 && d.year % 100 != 0))
        monthDays[1] = 29;

    for (int i = 0; i < d.month - 1; i++)
        days += monthDays[i];

    days += d.day;
    return days;
}

/* Check stock and record a sale */
void sellItem(struct Item item[], int n, int id, int quantity)
{
    int index = findItem(item, n, id);

    if (index == -1 || quantity <= 0)
    {
        printf("Invalid item or quantity\n");
        return;
    }

    struct Item *p = &item[index];

    if (p->type == COMBO)
    {
        /* Check all component stocks first */
        for (int i = 0; i < p->details.combo.count; i++)
        {
            int k = findItem(item, n, p->details.combo.id[i]);

            if (k == -1 ||
                item[k].stock < p->details.combo.qty[i] * quantity)
            {
                printf("Insufficient stock for combo %s\n", p->name);
                return;
            }
        }
        /* Then update component stock */
        for (int i = 0; i < p->details.combo.count; i++)
        {
            int k = findItem(item, n, p->details.combo.id[i]);
            item[k].stock -= p->details.combo.qty[i] * quantity;
        }
    }
    else
    {
        if (p->stock < quantity)
        {
            printf("Insufficient stock for %s\n", p->name);
            return;
        }
        p->stock -= quantity;
    }

    p->revenue += p->price * quantity;
    printf("Sold %d x %s = %.2f\n", quantity, p->name, p->price * quantity);
}

/* Warn about packaged items expiring within two days */
void expiryWarning(struct Item item[], int n, struct Date today)
{
    printf("\nExpiry Warning:\n");

    for (int i = 0; i < n; i++)
    {
        if (item[i].type == PACKAGED && item[i].stock > 0)
        {
            int diff = dateValue(item[i].details.expiry) - dateValue(today);

            if (diff >= 0 && diff <= 2)
                printf("%s expires within %d day(s)\n", item[i].name, diff);
        }
    }
}

/* Sort by revenue, highest first (bubble sort) */
void sortRevenue(struct Item item[], int n)
{
    struct Item temp;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (item[j].revenue < item[j + 1].revenue)
            {
                temp = item[j];
                item[j] = item[j + 1];
                item[j + 1] = temp;
            }
        }
    }
}

void displaySummary(struct Item item[], int n)
{
    sortRevenue(item, n);

    printf("\nDaily Revenue Summary:\n");
    for (int i = 0; i < n; i++)
        printf("%s : Rs. %.2f\n", item[i].name, item[i].revenue);
}

int main(void)
{
    struct Item item[4] =
    {
        { 1, "Milk",    30,  10, PACKAGED, {.expiry = {16, 11, 2026}}, 0 },
        { 2, "Dosa",    40,  20, COOKED,   {.prepared = {9, 30}},      0 },
        { 3, "Combo",  100,   0, COMBO,    {.combo = {{1, 2}, {2, 1}, 2}}, 0 },
        { 4, "Biscuit", 20,  15, PACKAGED, {.expiry = {25, 11, 2026}}, 0 }
    };
    int n = 4;
    struct Date today = {15, 11, 2026};

    printf("CANTEEN BILLING SYSTEM\n\n");

    sellItem(item, n, 1, 1);   /* Test 1: sell one milk          */
    sellItem(item, n, 2, 2);   /* sell two dosa                  */
    sellItem(item, n, 3, 1);   /* Test 2: sell one combo         */
    sellItem(item, n, 1, 20);  /* Test 3: insufficient stock     */

    expiryWarning(item, n, today);  /* Test 4: expiry warning    */
    displaySummary(item, n);        /* Test 5: revenue summary   */

    return 0;
}
