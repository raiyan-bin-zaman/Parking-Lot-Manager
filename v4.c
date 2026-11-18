/* Parking Lot Manager - Version 4 */
#include <stdio.h>

#define TOTAL_SLOTS     10
#define MAX_PLATE       9999
#define MAX_MINUTE_IN   1439
#define MIDNIGHT        1440    /* minutes are counted from midnight of the arrival day */
#define MAX_MINUTE_OUT  2879

#define CAR_RATE        30.0
#define BIKE_RATE       15.0
#define BICYCLE_RATE     5.0

#define CAR_CAP        200.0
#define BIKE_CAP       100.0
#define BICYCLE_CAP     30.0

int    g_slot;
int    g_number;
int    g_type;
int    g_minutein;
int    g_minuteout;
double g_charge;

int    g_occupied = 0;
int    g_parked_count = 0;
int    g_released_count = 0;
double g_earnings = 0.0;
int    g_eof = 0;

void   Banner(void);
void   Menu(void);
int    read_number(void);
int    read_in_range(int low, int high);
double rate_for_type(int type);
double cap_for_type(int type);
int    is_overnight(int minuteout);
int    calc_hours(int minutes);
double calc_charge(int hours, double rate_per_hour);
double apply_cap(double charge, double cap, int overnight);
void   print_type_name(int type);
void   show_receipt(int minutes, int hours, double rate, double charge, int capped);
void   park_vehicle(void);
void   release_vehicle(void);
void   show_free_slots(void);
void   search_by_plate(void);
void   show_earnings(void);
void   save_and_load(void);
void   wait_for_enter(void);

int main(void)
{
    int choice;

    Banner();
    do {
        Menu();
        printf("Choose an option: ");
        choice = read_number();
        printf("\n");

        switch (choice) {
            case 1:  park_vehicle();    break;
            case 2:  release_vehicle(); break;
            case 3:  show_free_slots(); break;
            case 4:  search_by_plate(); break;
            case 5:  show_earnings();   break;
            case 6:  save_and_load();   break;
            case 0:
                show_earnings();
                if (g_occupied) {
                    printf("\nNote: vehicle %d is still in slot %d and was not charged.\n",
                           g_number, g_slot);
                }
                printf("\nGoodbye.\n");
                break;
            default:
                printf("That is not on the menu - choose a number from 0 to 6.\n");
                break;
        }
        printf("\n");
    } while (choice != 0);

    return 0;
}

void wait_for_enter(void)
{
    int ch;

    printf("\nPress Enter to continue...");
    ch = getchar();
    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }
}

void Banner(void)
{
    printf("========================================\n");
    printf("        PARKING LOT MANAGER\n");
    printf("   Cars in, cars out, fair charges\n");
    printf("========================================\n\n");
}

void Menu(void)
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
    printf("Rate per hour (part hour rounds up):\n");
    printf("  Car %.2f | Bike %.2f | Bicycle %.2f taka\n",
           rate_for_type(1), rate_for_type(2), rate_for_type(3));
    printf("Flat overnight cap (stay passes midnight):\n");
    printf("  Car %.2f | Bike %.2f | Bicycle %.2f taka\n\n",
           cap_for_type(1), cap_for_type(2), cap_for_type(3));
}

/* Returns the number typed, or -1 if the entry is not a clean whole number. */
int read_number(void)
{
    int value;
    int status;
    int ch;
    int junk = 0;

    status = scanf("%d", &value);
    if (status == EOF) {
        g_eof = 1;
        return 0;
    }
    if (status != 1) {
        junk = 1;
    }
    ch = getchar();
    while (ch != '\n' && ch != EOF) {
        if (ch != ' ' && ch != '\t') {
            junk = 1;
        }
        ch = getchar();
    }
    if (junk) {
        value = -1;
    }
    return value;
}

/* Asks again until the entry is from low to high; returns low if input ends. */
int read_in_range(int low, int high)
{
    int value;
    int ok = 0;

    do {
        value = read_number();
        if (g_eof) {
            return low;
        }
        if (value >= low && value <= high) {
            ok = 1;
        } else {
            printf("  Invalid - enter a whole number from %d to %d: ", low, high);
        }
    } while (!ok);

    return value;
}

double rate_for_type(int type)
{
    double rate;

    if (type == 1) {
        rate = CAR_RATE;
    } else if (type == 2) {
        rate = BIKE_RATE;
    } else if (type == 3) {
        rate = BICYCLE_RATE;
    } else {
        rate = 0.0;
    }
    return rate;
}

double cap_for_type(int type)
{
    double cap;

    if (type == 1) {
        cap = CAR_CAP;
    } else if (type == 2) {
        cap = BIKE_CAP;
    } else if (type == 3) {
        cap = BICYCLE_CAP;
    } else {
        cap = 0.0;
    }
    return cap;
}

/* A stay is overnight when the vehicle leaves at or after midnight. */
int is_overnight(int minuteout)
{
    if (minuteout >= MIDNIGHT) {
        return 1;
    }
    return 0;
}

/* Rounds up with integers only: 60 min -> 1 hour, 61 min -> 2 hours. */
int calc_hours(int minutes)
{
    return (minutes + 59) / 60;
}

double calc_charge(int hours, double rate_per_hour)
{
    return hours * rate_per_hour;
}

double apply_cap(double charge, double cap, int overnight)
{
    if (overnight && charge > cap) {
        return cap;
    }
    return charge;
}

void print_type_name(int type)
{
    switch (type) {
        case 1:  printf("Car");     break;
        case 2:  printf("Bike");    break;
        case 3:  printf("Bicycle"); break;
        default: printf("Unknown"); break;
    }
}

void show_receipt(int minutes, int hours, double rate, double charge, int capped)
{
    printf("\n--------------- RECEIPT ----------------\n");
    printf("  Slot no.       : %d\n", g_slot);
    printf("  Vehicle number : %d\n", g_number);
    printf("  Vehicle type   : ");
    print_type_name(g_type);
    printf("\n");
    printf("  Minute in      : %d\n", g_minutein);
    printf("  Minute out     : %d\n", g_minuteout);
    printf("  Time parked    : %d min\n", minutes);
    printf("  Billed hours   : %d at %.2f taka\n", hours, rate);
    if (capped) {
        printf("  Overnight cap applied\n");
    }
    printf("  Charge         : %.2f taka\n", charge);
    printf("----------------------------------------\n");
}

void park_vehicle(void)
{
    printf("========================================\n");
    printf("            PARK A VEHICLE\n");
    printf("========================================\n");

    if (g_occupied) {
        printf("Slot %d is already in use by vehicle %d.\n", g_slot, g_number);
        printf("Version 4 can hold one vehicle at a time - release it first.\n");
        return;
    }

    printf("Slot number (1-%d)          e.g. 7   : ", TOTAL_SLOTS);
    g_slot = read_in_range(1, TOTAL_SLOTS);

    printf("Vehicle number (1-%d)     e.g. 120 : ", MAX_PLATE);
    g_number = read_in_range(1, MAX_PLATE);

    printf("-------------- Vehicle type -----------------\n");
    printf("  1. Car\n");
    printf("  2. Bike\n");
    printf("  3. Bicycle\n");
    printf("Vehicle type (1-3)         e.g. 2   : ");
    g_type = read_in_range(1, 3);

    printf("Minute in (0-%d)         e.g. 200 : ", MAX_MINUTE_IN);
    g_minutein = read_in_range(0, MAX_MINUTE_IN);

    if (g_eof) {
        return;
    }

    g_occupied = 1;
    g_parked_count++;
    printf("\nParked: vehicle %d (", g_number);
    print_type_name(g_type);
    printf(") in slot %d at minute %d.\n", g_slot, g_minutein);
}

void release_vehicle(void)
{
    int minutes;
    int hours;
    int capped;
    double rate;
    double raw;

    printf("========================================\n");
    printf("        RELEASE AND CHARGE\n");
    printf("========================================\n");

    if (!g_occupied) {
        printf("No vehicle is parked - there is nothing to release.\n");
        return;
    }

    printf("Releasing vehicle %d from slot %d (came in at minute %d).\n",
           g_number, g_slot, g_minutein);
    printf("Minute out (%d-%d; 1440 = midnight) : ", g_minutein + 1, MAX_MINUTE_OUT);
    g_minuteout = read_in_range(g_minutein + 1, MAX_MINUTE_OUT);
    if (g_eof) {
        return;
    }

    minutes = g_minuteout - g_minutein;
    hours = calc_hours(minutes);
    rate = rate_for_type(g_type);
    raw = calc_charge(hours, rate);
    g_charge = apply_cap(raw, cap_for_type(g_type), is_overnight(g_minuteout));
    capped = (g_charge < raw);

    show_receipt(minutes, hours, rate, g_charge, capped);

    g_earnings += g_charge;
    g_released_count++;
    g_occupied = 0;

    wait_for_enter();
}

void show_free_slots(void)
{
    int s;

    printf("========================================\n");
    printf("            FREE SLOTS\n");
    printf("========================================\n");
    printf("[nn] = free, [XX] = taken\n\n");

    for (s = 1; s <= TOTAL_SLOTS; s++) {
        if (g_occupied && s == g_slot) {
            printf("[XX] ");
        } else {
            printf("[%2d] ", s);
        }
        if (s % 5 == 0) {
            printf("\n");
        }
    }
    printf("\nFree slots: %d of %d\n", TOTAL_SLOTS - g_occupied, TOTAL_SLOTS);
}

void search_by_plate(void)
{
    int key;

    printf("========================================\n");
    printf("          SEARCH BY PLATE\n");
    printf("========================================\n");
    printf("Vehicle number (1-%d) : ", MAX_PLATE);
    key = read_in_range(1, MAX_PLATE);
    if (g_eof) {
        return;
    }

    if (g_occupied && key == g_number) {
        printf("\nFound: vehicle %d is in slot %d (", g_number, g_slot);
        print_type_name(g_type);
        printf("), came in at minute %d.\n", g_minutein);
    } else {
        printf("\nVehicle %d is not in the lot.\n", key);
    }
}

void show_earnings(void)
{
    printf("========================================\n");
    printf("            DAY'S EARNINGS\n");
    printf("========================================\n");
    printf("  Vehicles parked   : %d\n", g_parked_count);
    printf("  Vehicles released : %d\n", g_released_count);
    printf("  Still in the lot  : %d\n", g_occupied);
    printf("  Total earnings    : %.2f taka\n", g_earnings);
    if (g_released_count > 0) {
        printf("  Average per exit  : %.2f taka\n", g_earnings / g_released_count);
    }
}

void save_and_load(void)
{
    printf("========================================\n");
    printf("            SAVE & LOAD\n");
    printf("========================================\n");
    printf("Saving needs text files, which arrive in Version 5.\n");
    printf("For now the day's figures last only until you choose Exit.\n");
}
