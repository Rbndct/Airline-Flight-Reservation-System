#include <stdio.h>
#include <string.h>

#include "config.h"
#include "payment.h"
#include "reservation.h"
#include "user_interface.h"

int main()
{
    int prices[] = {3500, 5000, 3200};
    int flightSeats101[TOTAL_SEATS], flightSeats202[TOTAL_SEATS], flightSeats303[TOTAL_SEATS];

    initializeSeats(flightSeats101, TOTAL_SEATS);
    initializeSeats(flightSeats202, TOTAL_SEATS);
    initializeSeats(flightSeats303, TOTAL_SEATS);

    login();

    int exitFlag = 0;
    while (!exitFlag)
    {
        int choice;
        printf("\n1. View Flight Schedules\n2. Reserve Ticket\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                viewFlightSchedules(flightSeats101, flightSeats202, flightSeats303, TOTAL_SEATS);
                break;
            case 2:
                reserveTicket(flightSeats101, flightSeats202, flightSeats303, prices);
                break;
            case 3:
                exitFlag = 1;
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}
