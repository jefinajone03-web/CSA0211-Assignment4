/*
 * Task 2 - From Requirement to Nested Structures
 * Courier parcel tracking: nested structures, selection sort by weight,
 * listing parcels by receiver city, access through structure pointers.
 */
#include <stdio.h>
#include <string.h>

typedef struct
{
    int day, month, year;
} Date;

typedef struct
{
    char city[20];
    int pincode;
} Address;

typedef struct
{
    char name[30];
    Address address;
} Person;

typedef struct
{
    int id;
    float weight;
    Date booked;
    Person sender;
    Person receiver;
    int service;
    float charge;
} Parcel;

void print_parcel(const Parcel *p)
{
    printf("%d  %.1f kg  %s-%d  %02d/%02d/%04d\n",
           p->id,
           p->weight,
           p->receiver.address.city,
           p->receiver.address.pincode,
           p->booked.day,
           p->booked.month,
           p->booked.year);
}

/* Selection sort by weight (ascending) */
void sort_by_weight(Parcel p[], int n)
{
    int i, j, min;
    Parcel temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (p[j].weight < p[min].weight)
                min = j;
        }
        if (min != i)
        {
            temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}

/* List all parcels delivered to a given city */
void list_by_city(const Parcel p[], int n, const char *city)
{
    int found = 0;

    printf("\nParcels for %s:\n", city);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(p[i].receiver.address.city, city) == 0)
        {
            print_parcel(&p[i]);
            found = 1;
        }
    }
    if (!found)
        printf("No parcels found.\n");
}

int main(void)
{
    Parcel list[3] =
    {
        {
            501, 4.5f,
            {12, 10, 2026},
            {"Ravi", {"Madurai", 625001}},
            {"Arun", {"Madurai", 625001}},
            1, 100
        },
        {
            502, 1.2f,
            {12, 10, 2026},
            {"Bala", {"Chennai", 600077}},
            {"Kavi", {"Chennai", 600077}},
            2, 150
        },
        {
            503, 2.8f,
            {13, 10, 2026},
            {"Raja", {"Salem", 636001}},
            {"Devi", {"Coimbatore", 641001}},
            1, 120
        }
    };

    sort_by_weight(list, 3);

    printf("Parcels sorted by weight:\n");
    for (int i = 0; i < 3; i++)
        print_parcel(&list[i]);

    list_by_city(list, 3, "Chennai");

    /* Access paths (Task 2.4) */
    Parcel *p = &list[2];
    printf("\nlist[2].receiver.address.pincode = %d\n",
           list[2].receiver.address.pincode);
    printf("p->receiver.address.pincode       = %d\n",
           p->receiver.address.pincode);

    printf("\nsizeof(Parcel) = %zu bytes\n", sizeof(Parcel));
    return 0;
}
