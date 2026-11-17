/*
 * Task 1 - Data Design Review
 * Repair of a poor (parallel-array) patient register using
 * structures, nested structures and structure pointers.
 */
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Date
{
    int day;
    int month;
    int year;
};

struct BloodPressure
{
    int systolic;
    int diastolic;
};

struct Patient
{
    char name[30];
    int age;
    char phone[11];            /* 10 digits + '\0' */
    struct BloodPressure bp;
    struct Date visitDate;
};

/* Fills one patient record through a structure pointer */
void addPatient(struct Patient *p,
                const char n[],
                int a,
                const char ph[],
                int sys,
                int dia,
                struct Date d)
{
    strncpy(p->name, n, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';
    p->age = a;
    strncpy(p->phone, ph, sizeof(p->phone) - 1);
    p->phone[sizeof(p->phone) - 1] = '\0';
    p->bp.systolic = sys;
    p->bp.diastolic = dia;
    p->visitDate = d;
}

int main(void)
{
    struct Patient patients[MAX];
    int count = 0;
    struct Date d = {15, 11, 2026};

    /* Capacity check before inserting */
    if (count < MAX)
    {
        addPatient(&patients[count],
                   "Arun", 25, "9876543210",
                   120, 80, d);
        count++;
    }

    printf("Patient Details\n");
    printf("Name: %s\n", patients[0].name);
    printf("Age: %d\n", patients[0].age);
    printf("Phone: %s\n", patients[0].phone);
    printf("Blood Pressure: %d/%d\n",
           patients[0].bp.systolic,
           patients[0].bp.diastolic);
    printf("Visit Date: %02d/%02d/%d\n",
           patients[0].visitDate.day,
           patients[0].visitDate.month,
           patients[0].visitDate.year);

    printf("\nsizeof(struct Patient) = %zu bytes\n", sizeof(struct Patient));
    return 0;
}
