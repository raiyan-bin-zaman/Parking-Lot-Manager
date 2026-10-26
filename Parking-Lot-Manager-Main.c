#include <stdio.h>
#include<math.h>
void Banner(void)
{
    printf("========================================\n");
    printf("        PARKING LOT MANAGER\n");
    printf("   Cars in, cars out, fair charges\n");
    printf("========================================\n\n");
}


void Menu(double rate_per_hour)
{
    printf("---------------- MENU ------------------\n");
    printf("  1. Park a vehicle\n");
    printf("  2. Release and charge   <-- this version\n");
    printf("  3. Show free slots\n");
    printf("  4. Search by plate\n");
    printf("  5. Day's earnings\n");
    printf("  6. Save & load\n");
    printf("  0. Exit\n");
    printf("----------------------------------------\n");
    printf("Rate: %.2f taka per hour (part hour rounds up)\n\n", rate_per_hour);
    printf("Choose an option: 2 \n\n");

    printf("========================================\n");
    printf("        RELEASE AND CHARGE\n");
    printf("       ENTER VEHICLE DETAILS\n");
    printf("========================================\n\n");
}


int read_number(void)
{
    int value;

    scanf("%d", &value);
    return value;
}


int calc_hours(int minutes)
{
    return (minutes + 59) / 60;
}


double calc_charge(int hours, double rate_per_hour)
{
    return hours * rate_per_hour;
}


void show_receipt(int slot, int number, int type,
                  int minutein, int minuteout,
                  int minutes, int hours, double charge)
{
    printf("\n--------------- RECEIPT ----------------\n");
    printf("  Slot no.       : %d\n", slot);
    printf("  Vehicle number : %d\n", number);
    printf("  Vehicle type   : %d\n", type);
    printf("  Minute in      : %d\n", minutein);
    printf("  Minute out     : %d\n", minuteout);
    printf("  Time parked    : %d min\n", minutes);
    printf("  Billed hours   : %d\n", hours);
    printf("  Charge         : %.2f taka\n", charge);
    printf("----------------------------------------\n");
}

int main(void)
{
    int slot;
    int number;
    int type;
    int minutein;
    int minuteout;
    double charge;

    int minutes;
    int hours;
    double rate_per_hour = 30.0;
    Banner();
    Menu(rate_per_hour);


    printf("Slot number            e.g. 7: ");
    slot = read_number();

    printf("Vehicle number      e.g. 120 : ");
    number = read_number();

    printf("-------------- Vehicle type -----------------\n");
    printf("  1. Car\n");
    printf("  2. Bike\n");
    printf("  3. Bicycle\n");
    printf("Vehicle type          e.g. 2 : ");
    type = read_number();

    printf("Minute in           e.g. 200  : ");
    minutein = read_number();

    printf("Minute out          e.g. 260  : ");
    minuteout = read_number();


    minutes = minuteout - minutein;
    hours = calc_hours(minutes);
    charge = calc_charge(hours, rate_per_hour);


    show_receipt(slot, number, type, minutein, minuteout, minutes, hours, charge);

    return 0;
}