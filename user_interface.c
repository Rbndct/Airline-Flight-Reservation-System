#include "user_interface.h"

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "payment.h"
#include "reservation.h"


/**
 * Handles user login before accessing the system.
 * Ensures only authorized users can proceed.
 */
void login()
{
    char username[20], password[20];
    int loggedIn = 0;

    while (loggedIn == 0)
    {
        printf("\nEnter Username: ");
        scanf("%s", username);
        printf("Enter Password: ");
        scanf("%s", password);

        if (strcmp(username, "STUDENT") == 0 && strcmp(password, "TAFT2401") == 0)
        {
            printf("\nLogin Successful!\n");
            loggedIn = 1;
        }
        else
        {
            printf("\nInvalid username or password. Please try again.\n");
        }
    }
}

/**
 * Displays the flight schedules, including departure and arrival details.
 */
void viewFlightSchedules(int seats[], int seats2[], int seats3[], int totalSeats)
{
    int flightNumbers[] = {101, 202, 303};                       // Flight numbers
    char departures[][15] = {"Manila", "Manila", "Cebu"};        // Departure cities
    char arrivals[][15] = {"Cebu", "Davao", "Manila"};           // Arrival cities
    char depTimes[][10] = {"08:00 AM", "01:00 PM", "06:00 PM"};  // Departure times
    char arrTimes[][10] = {"10:00 AM", "03:00 PM", "08:00 PM"};  // Arrival times
    int prices[] = {3500, 5000, 3200};                           // Ticket prices

    // Calculate the actual number of available seats for each flight
    int seatCounts[] = {countAvailableSeats(seats, totalSeats),
                        countAvailableSeats(seats2, totalSeats),
                        countAvailableSeats(seats3, totalSeats)};

    printf("\nFlight Schedules:\n");
    printf(
        "---------------------------------------------------------------------"
        "----------------------\n");
    printf("| %-12s | %-12s | %-12s | %-10s | %-10s | %-7s | %-8s |\n", "Flight No", "Departure",
           "Arrival", "Dep Time", "Arr Time", "Seats", "Price");
    printf(
        "---------------------------------------------------------------------"
        "-----------------------\n");

    for (int i = 0; i < 3; i++)
    {
        printf("| %-12d | %-12s | %-12s | %-10s | %-10s | %-7d | %-8d |\n", flightNumbers[i],
               departures[i], arrivals[i], depTimes[i], arrTimes[i], seatCounts[i], prices[i]);
    }
    printf(
        "---------------------------------------------------------------------"
        "-----------------------\n");
}

/**
 * Displays the seating arrangement of a flight.
 */
void displaySeats(int seats[])
{
    printf("\nSeat Map (X = Taken, O = Available)\n");
    // The Rows are numbered from 1 to 5 and the Columns are labeled from A to F
    printf("   A B C   D E F\n");

    for (int i = 0; i < ROWS; i++)
    {
        printf("%d  ", i + 1);
        for (int j = 0; j < COLS; j++)
        {
            int index = (i * COLS) + j;

            char seatSymbol = 'O';  // Default to available seat
            if (seats[index] == 1)
            {
                seatSymbol = 'X';  // Mark as taken seat
            }

            printf("%c ", seatSymbol);
            if (j == 2)
            {
                printf("  ");
            }
        }
        printf("\n");
    }
}

/**
 * Displays the available seats for a given flight.
 */
void displayAvailableSeats(int flightNumber, int flightSeats101[], int flightSeats202[],
                           int flightSeats303[])
{
    if (flightNumber == 101)
    {
        displaySeats(flightSeats101);
    }
    else if (flightNumber == 202)
    {
        displaySeats(flightSeats202);
    }
    else if (flightNumber == 303)
    {
        displaySeats(flightSeats303);
    }
}

/**
 * Displays a summary of the completed transaction.
 */
void transactionSummary(float totalSpent)
{
    printf("\n================ TRANSACTION SUMMARY ================\n");
    printf("Total Amount Spent: %.2f\n", totalSpent);
    printf("Thank you for booking with us!\n");
    printf("=====================================================\n");
}