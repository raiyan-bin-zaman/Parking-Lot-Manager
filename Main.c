#include <stdio.h>

int main(void) {
    int slot_no;
    char vehicle_plate[50];
    int vehicle_type;
    int minute_in;
    int minute_out;
    double charge;

//welcome screen and main menu
    printf("=========================================\n");
    printf("             PARKING LOT MANAGER            \n");
    printf("=========================================\n");

    printf("• Main Menu:\n");
    printf("============\n");

    printf("1. Park a vehicle\n");
    printf("2. Release and charge\n");
    printf("3. Show free slots\n");
    printf("4. Search by plate\n");
    printf("5. Day's earnings\n");
    printf("6. Save & load\n");
    printf("7. Exit\n\n");

   //reading with scanf
    printf("• RECORD DETAILS:\n");
    printf("Enter Slot Number: ");
    scanf("%d", &slot_no);

    printf("Enter Vehicle Plate: ");
    scanf("%49s", vehicle_plate);

    printf("Enter Vehicle Type: ");
    scanf("%d", &vehicle_type);

    printf("Enter Minute In: ");
    scanf("%d", &minute_in);

    printf("Enter Minute Out: ");
    scanf("%d", &minute_out);



    int duration = minute_out - minute_in;
    int billed_hours = (duration + 59) / 60;
    charge = billed_hours * 30.0;            // 30 Taka/h

    //displaying output
    printf("\n=========================================\n");
    printf("             RECORDED DETAILS              \n");
    printf("=========================================\n");
    printf("Slot No.     : %d\n", slot_no);
    printf("Vehicle Plate: %s\n", vehicle_plate);
    printf("Vehicle Type : %d\n", vehicle_type);
    printf("Minute In    : %d\n", minute_in);
    printf("Minute Out   : %d\n", minute_out);
    printf("Charge       : %.2f Taka\n", charge);
    printf("=========================================\n");

    return 0;
}
