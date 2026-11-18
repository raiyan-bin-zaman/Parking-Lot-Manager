#include <stdio.h>

/* Function Prototypes */
void Banner(void);
void Menu(double rate);
int read_number(void);
int calc_hours(int minutes);
double get_rate(int type);
double calc_charge(int hours, double rate);
void show_receipt(int slot, int number, int type,
                  int minutein, int minuteout,
                  int minutes, int hours, double charge);

int main(void)
{
    int choice;
    int slot = 0, number = 0, type = 0;
    int minutein = 0, minuteout;
    int minutes, hours;
    int occupied = 0;
    int count = 0;
    int overnight;

    int search;
    double rate;
    double charge;
    double earnings = 0.0;

    Banner();

    do
    {
        Menu(30.0);

        printf("Choose an option: ");
        choice = read_number();

        switch(choice)
        {
            case 1:
                if(occupied == 1)
                {
                    printf("Parking slot is occupied!\n");
                    break;
                }

                printf("Slot number (1-10): ");
                slot = read_number();

                if(slot < 1 || slot > 10)
                {
                    printf("Invalid slot number!\n");
                    break;
                }

                printf("Vehicle number: ");
                number = read_number();

                if(number <= 0)
                {
                    printf("Invalid vehicle number!\n");
                    break;
                }

                printf("\n1. Car\n");
                printf("2. Bike\n");
                printf("3. Bicycle\n");

                printf("Vehicle type: ");
                type = read_number();

                if(type < 1 || type > 3)
                {
                    printf("Invalid vehicle type!\n");
                    break;
                }

                printf("Minute in (0-1439): ");
                minutein = read_number();

                if(minutein < 0 || minutein > 1439)
                {
                    printf("Invalid entry time!\n");
                    break;
                }

                rate = get_rate(type);

                occupied = 1;
                count++;

                printf("\nVehicle parked successfully!\n");
                printf("Rate: %.2f taka per hour\n", rate);

                break;

            case 2:
                if(occupied == 0)
                {
                    printf("No vehicle is parked!\n");
                    break;
                }

                printf("Minute out (0-1439): ");
                minuteout = read_number();

                if(minuteout < 0 || minuteout > 1439)
                {
                    printf("Invalid exit time!\n");
                    break;
                }

                if(minuteout == minutein)
                {
                    printf("Invalid parking duration!\n");
                    break;
                }

                if(minuteout < minutein)
                {
                    minutes = (1440 - minutein) + minuteout;
                    overnight = 1;
                }
                else
                {
                    minutes = minuteout - minutein;
                    overnight = 0;
                }

                hours = calc_hours(minutes);
                rate = get_rate(type);

                charge = calc_charge(hours, rate);

                if(overnight == 1 && charge > 300.0)
                {
                    charge = 300.0;
                }

                earnings = earnings + charge;

                show_receipt(slot, number, type,
                             minutein, minuteout,
                             minutes, hours, charge);

                occupied = 0;

                break;

            case 3:
                if(occupied == 1)
                    printf("Free slots: 9\n");
                else
                    printf("Free slots: 10\n");

                break;

            case 4:
                printf("Enter vehicle number: ");
                search = read_number();

                if(occupied == 1 && search == number)
                {
                    printf("Vehicle found!\n");
                    printf("Slot number: %d\n", slot);
                    printf("Vehicle number: %d\n", number);
                }
                else
                {
                    printf("Vehicle not found!\n");
                }

                break;

            case 5:
                printf("Vehicles parked: %d\n", count);
                printf("Day's earnings: %.2f taka\n", earnings);

                break;

            case 0:
                printf("Thank you! Goodbye.\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while(choice != 0);

    return 0;
}

/* Banner Function */
void Banner(void)
{
    printf("========================================\n");
    printf("        PARKING LOT MANAGER\n");
    printf("   Cars in, cars out, fair charges\n");
    printf("========================================\n");
}

/* Menu Function */
void Menu(double rate)
{
    printf("\n---------------- MENU ------------------\n");
    printf("1. Park a vehicle\n");
    printf("2. Release and charge\n");
    printf("3. Show free slots\n");
    printf("4. Search by vehicle number\n");
    printf("5. Day's earnings\n");
    printf("0. Exit\n");
    printf("----------------------------------------\n");
    printf("Standard car rate: %.2f taka/hour\n", rate);
}

/* Input Function */
int read_number(void)
{
    int value;
    scanf("%d", &value);
    return value;
}

/* Calculate Hours */
int calc_hours(int minutes)
{
    return (minutes + 59) / 60;
}

/* Vehicle Rate Function */
double get_rate(int type)
{
    if(type == 1)
        return 30.0;

    else if(type == 2)
        return 20.0;

    else
        return 10.0;
}

/* Calculate Charge */
double calc_charge(int hours, double rate)
{
    return hours * rate;
}

/* Receipt Function */
void show_receipt(int slot, int number, int type,
                  int minutein, int minuteout,
                  int minutes, int hours, double charge)
{
    printf("\n--------------- RECEIPT ----------------\n");
    printf("Slot no.       : %d\n", slot);
    printf("Vehicle number : %d\n", number);
    printf("Vehicle type   : %d\n", type);
    printf("Minute in      : %d\n", minutein);
    printf("Minute out     : %d\n", minuteout);
    printf("Time parked    : %d min\n", minutes);
    printf("Billed hours   : %d\n", hours);
    printf("Charge         : %.2f taka\n", charge);
    printf("----------------------------------------\n");
}