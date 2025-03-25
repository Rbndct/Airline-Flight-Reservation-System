#include "reservation.h"

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "payment.h"
#include "user_interface.h"

/**
 * Initializes the seat array for a flight with all seats set to available.
 */
void initializeSeats(int flightSeats[], int size)
{
    for (int i = 0; i < size; i++)
    {
        // 0 indicates an available seat
        flightSeats[i] = 0;
    }
}

/**
 * Iterates through the seat array and counts the seats
 * that are available (marked as 0).
 */
int countAvailableSeats(int seats[], int totalSeats)
{
    int count = 0;
    for (int i = 0; i < totalSeats; i++)
    {
        // Count seats that are available
        if (seats[i] == 0) count++;
    }
    return count;
}

/**
 * Get the flight number from the user.
 */
int getFlightNumber()
{
    int flightNumber;
    int validInput = 0;

    while (!validInput)
    {
        printf("\nEnter Flight Number to Reserve (101, 202, 303): ");

        if (scanf("%d", &flightNumber) != 1)
        {
            printf("\nInvalid input. Please enter a valid flight number.\n");
            while (getchar() != '\n');  // Clear input buffer
        }
        else if (flightNumber == 101 || flightNumber == 202 || flightNumber == 303)
        {
            validInput = 1;
        }
        else
        {
            printf("\nInvalid Flight Number. Try again.\n");
        }
    }

    return flightNumber;
}

/**
 * Get the seat selection from the user.
 */
int isSeatAvailable(int flightNumber, int row, int col, int flightSeats101[], int flightSeats202[],
                    int flightSeats303[])
{
    int seatIndex = ((row - 1) * COLS) + col;
    int available = 1;  // Assume the seat is available

    if ((flightNumber == 101 && flightSeats101[seatIndex] == 1) ||
        (flightNumber == 202 && flightSeats202[seatIndex] == 1) ||
        (flightNumber == 303 && flightSeats303[seatIndex] == 1))
    {
        available = 0;  // Mark as unavailable
    }

    return available;
}

/**
 * Allows the user to select a flight, choose a seat, and confirm
 * the reservation. If the user wants to purchase multiple tickets, they can do so in a loop.
 */
void reserveTicket(int flightSeats101[], int flightSeats202[], int flightSeats303[], int prices[])
{
    int flightNumber, row, col;
    float totalSpent = 0.0;
    char buyMore;

    do
    {
        flightNumber = getFlightNumber();
        if (flightNumber != -1)
        {
            displayAvailableSeats(flightNumber, flightSeats101, flightSeats202, flightSeats303);

            int validSeat = 0;
            while (!validSeat)
            {
                printf("\nEnter seat row (1-%d): ", ROWS);
                if (scanf("%d", &row) != 1 || row < 1 || row > ROWS)
                {
                    printf("\nInvalid row selection. Try again.\n");
                    while (getchar() != '\n');
                }
                else
                {
                    char colChar;
                    printf("Enter seat column (A-F): ");
                    if (scanf(" %c", &colChar) != 1 ||
                        !((colChar >= 'A' && colChar <= 'F') || (colChar >= 'a' && colChar <= 'f')))
                    {
                        printf("\nInvalid column selection. Try again.\n");
                        while (getchar() != '\n');
                    }
                    else
                    {
                        if (colChar >= 'A' && colChar <= 'F')
                        {
                            col = colChar - 'A';
                        }
                        else if (colChar >= 'a' && colChar <= 'f')
                        {
                            col = colChar - 'a';
                        }

                        if (isSeatAvailable(flightNumber, row, col, flightSeats101, flightSeats202,
                                            flightSeats303))
                        {
                            validSeat = 1;
                        }
                        else
                        {
                            printf("\nSeat already taken. Please choose another.\n");
                        }
                    }
                }
            }

            float totalPrice = calculatePrice(flightNumber, prices);
            totalPrice = applyDiscount(totalPrice);

            printf("\nTotal price for Seat %d%c on Flight %d after discount: %.2f\n", row,
                   col + 'A', flightNumber, totalPrice);

            if (confirmPurchase())
            {
                totalSpent += totalPrice;
                processSeatReservation(flightNumber, row, col, flightSeats101, flightSeats202,
                                       flightSeats303);
                printf("\nSeat %d%c for Flight %d reserved successfully!\n", row, col + 'A',
                       flightNumber);
            }
            else
            {
                printf("\nTransaction Canceled.\n");
            }
        }

        printf("\nWould you like to buy more tickets? (Y/N): ");
        scanf(" %c", &buyMore);

    } while (buyMore == 'Y' || buyMore == 'y');

    if (totalSpent > 0)
    {
        processPayment(totalSpent);
        transactionSummary(totalSpent);
    }
}

/**
 * Processes the seat reservation by marking the selected seat as taken.
 */
void processSeatReservation(int flightNumber, int row, int col, int flightSeats101[],
                            int flightSeats202[], int flightSeats303[])
{
    int seatIndex = ((row - 1) * COLS) + col;
    if (flightNumber == 101)
    {
        flightSeats101[seatIndex] = 1;
    }
    else if (flightNumber == 202)
    {
        flightSeats202[seatIndex] = 1;
    }
    else if (flightNumber == 303)
    {
        flightSeats303[seatIndex] = 1;
    }
}
