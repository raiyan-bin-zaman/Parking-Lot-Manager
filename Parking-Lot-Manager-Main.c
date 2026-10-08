#include <stdio.h>

int main(void)
{
    int slot;
    char plate[16];
    int type;
    int minuteIn;
    int minuteOut;
    double charge;

    int minutes;
    int hours;
    double ratePerHour = 30.0;   /* taka per hour */

    /* Welcome screen */
    printf("========================================\n");
    printf("        PARKING LOT MANAGER\n");
    printf("   Cars in, cars out, fair charges\n");
    printf("========================================\n\n");

    /* Menu */
    printf("---------------- MENU ------------------\n");
    printf("  1. Park a vehicle\n");
    printf("  2. Release and charge   <-- this version\n");
    printf("  3. Show free slots\n");
    printf("  4. Search by plate\n");
    printf("  5. Day's earnings\n");
    printf("  6. Save & load\n");
    printf("  0. Exit\n");
    printf("----------------------------------------\n");
    printf("Rate: %.2f taka per hour (part hour rounds up)\n\n", ratePerHour);

    /* Read one record */
    printf("-------- ENTER VEHICLE DETAILS ---------\n");
    printf("Slot no.        (whole number, e.g. 7)       : ");
    scanf("%d", &slot);
    printf("Vehicle plate   (no spaces, e.g. DHAKA-1234) : ");
    scanf("%15s", plate);
    printf("Vehicle type    (whole number, e.g. 1)       : ");
    scanf("%d", &type);
    printf("Minute in       (whole number, e.g. 540)     : ");
    scanf("%d", &minuteIn);
    printf("Minute out      (whole number, e.g. 635)     : ");
    scanf("%d", &minuteOut);

    /* Compute */
    minutes = minuteOut - minuteIn;
    hours = (minutes + 59) / 60;
    charge = hours * ratePerHour;

    /* Display */
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

    return 0;
}
