/*
 * Task 3 - Unions and Memory Layout
 * Weather-station sensor packets using a tagged union.
 */
#include <stdio.h>

enum kind
{
    TEMPERATURE,
    HUMIDITY,
    STATUS
};

/* Structure holding all fields at the same time */
struct normal_packet
{
    float celsius;
    int percent;
    char status[8];
};

/* Tagged union: tag says which member is valid */
struct reading
{
    enum kind type;
    union
    {
        float celsius;
        int percent;
        char status[8];
    } value;
};

void show(const struct reading *r)
{
    switch (r->type)
    {
        case TEMPERATURE:
            printf("Temp %.1f C\n", r->value.celsius);
            break;
        case HUMIDITY:
            printf("Humidity %d %%\n", r->value.percent);
            break;
        case STATUS:
            printf("Status %s\n", r->value.status);
            break;
    }
}

int main(void)
{
    struct reading log[3] =
    {
        {TEMPERATURE, {.celsius = 31.5f}},
        {HUMIDITY,    {.percent = 68}},
        {STATUS,      {.status = "OK"}}
    };

    printf("sizeof struct normal_packet = %zu\n", sizeof(struct normal_packet));
    printf("sizeof union = %zu, sizeof struct reading = %zu\n",
           sizeof log[0].value,
           sizeof log[0]);

    for (int i = 0; i < 3; i++)
        show(&log[i]);

    /* Task 3.4 - Misuse experiment: reading the wrong (inactive) member.
     * The result is not a valid humidity; it is just the float's bit
     * pattern reinterpreted as an int. Never do this in real code. */
    struct reading r;
    r.type = TEMPERATURE;
    r.value.celsius = 31.5f;
    printf("\nMisuse experiment (temperature read as humidity): %d\n",
           r.value.percent);

    return 0;
}
