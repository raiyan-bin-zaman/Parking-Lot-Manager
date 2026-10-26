#include <stdio.h>

/* Function prototypes */
void banner(const char title[]);
void menu(double ratePerHour);

int input(int *slot, char plate[], int *type,
          int *minuteIn, int *minuteOut);

double compute(int minuteIn, int minuteOut,
               int *minutes, int *hours,
               double ratePerHour);

void display(int slot, const char plate[], int type,
             int minuteIn, int minuteOut,
             int minutes, int hours, double charge);

int main(void)
{
    int slot;
    char plate[16];
    int type;
    int minuteIn;
    int minuteOut;
    int minutes;
    int hours;

    double ratePerHour = 30.0;
    double charge;

    banner("PARKING LOT MANAGER");
    menu(ratePerHour);

    input(&slot, plate, &type, &minuteIn, &minuteOut);

    charge = compute(minuteIn, minuteOut,
                     &minutes, &hours, ratePerHour);

    display(slot, plate, type, minuteIn, minuteOut,
            minutes, hours, charge);

    return 0;
}

/* Function 1: Display the banner */
void banner(const char title[])
{
    printf("========================================\n");
    printf("        %s\n", title);
    printf("   Cars in, cars out, fair charges\n");
    printf("========================================\n\n");
}

/* Function 2: Display the menu */
void menu(double ratePerHour)
{
    printf("---------------- MENU ------------------\n");
    printf("  1. Park a vehicle\n");
    printf("  2. Release and charge\n");
    printf("  3. Show free slots\n");
    printf("  4. Search by plate\n");
    printf("  5. Day's earnings\n");
    printf("  6. Save & load\n");
    printf("  0. Exit\n");
    printf("----------------------------------------\n");

    printf("Rate: %.2f taka per hour\n", ratePerHour);
    printf("Part hour rounds up\n\n");

    printf("Choose an option: 2\n\n");
}

/* Function 3: Take vehicle information */
int input(int *slot, char plate[], int *type,
          int *minuteIn, int *minuteOut)
{
    printf("========================================\n");
    printf("        RELEASE AND CHARGE\n");
    printf("       ENTER VEHICLE DETAILS\n");
    printf("========================================\n\n");

    printf("Slot no.        : ");
    scanf("%d", slot);

    printf("Vehicle plate   : ");
    scanf("%15s", plate);

    printf("-------------- Vehicle type -----------------\n");
    printf("  1. Car\n");
    printf("  2. Bike\n");
    printf("  3. Bicycle\n");

    printf("Vehicle type    : ");
    scanf("%d", type);

    printf("Minute in       : ");
    scanf("%d", minuteIn);

    printf("Minute out      : ");
    scanf("%d", minuteOut);

    return 1;
}

/* Function 4: Calculate parking charge */
double compute(int minuteIn, int minuteOut,
               int *minutes, int *hours,
               double ratePerHour)
{
    *minutes = minuteOut - minuteIn;
    *hours = (*minutes + 59) / 60;

    return *hours * ratePerHour;
}

/* Function 5: Display the receipt */
void display(int slot, const char plate[], int type,
             int minuteIn, int minuteOut,
             int minutes, int hours, double charge)
{
    printf("\n--------------- RECEIPT ----------------\n");

    printf("  Slot no.      : %d\n", slot);
    printf("  Vehicle plate : %s\n", plate);
    printf("  Vehicle type  : %d\n", type);
    printf("  Minute in     : %d\n", minuteIn);
    printf("  Minute out    : %d\n", minuteOut);
    printf("  Time parked   : %d min\n", minutes);
    printf("  Billed hours  : %d\n", hours);
    printf("  Charge        : %.2f taka\n", charge);

    printf("----------------------------------------\n");
}