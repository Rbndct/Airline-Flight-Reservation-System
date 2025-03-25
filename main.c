#include <stdio.h>
#include <string.h>

#define ROWS 5                     // Number of rows in each flight's seating arrangement
#define COLS 6                     // Number of columns in each flight's seating arrangement
#define TOTAL_SEATS (ROWS * COLS)  // Total number of seats per flight
#define FLIGHTS 3                  // Total number of flights

// Function Prototypes
void login();
void viewFlightSchedules(int seats[], int seats2[], int seats3[], int totalSeats);
void initializeSeats(int flightSeats[], int size);
int countAvailableSeats(int seats[], int totalSeats);
void displaySeats(int seats[]);
void processPayment(int price);
float applyDiscount(float totalPrice);
void transactionSummary(float totalSpent);
void reserveTicket(int flightSeats101[], int flightSeats202[], int flightSeats303[], int prices[]);
int getFlightNumber();
void displayAvailableSeats(int flightNumber, int flightSeats101[], int flightSeats202[],
                           int flightSeats303[]);
int getSeatSelection(int *row, int *col);
int isSeatAvailable(int flightNumber, int row, int col, int flightSeats101[], int flightSeats202[],
                    int flightSeats303[]);
float calculatePrice(int flightNumber, int prices[]);
int confirmPurchase();
void processSeatReservation(int flightNumber, int row, int col, int flightSeats101[],
                            int flightSeats202[], int flightSeats303[]);

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
            // Display X for taken seats and O for available seats
            printf("%c ", seats[index] ? 'X' : 'O');
            if (j == 2) printf("  ");
        }
        printf("\n");
    }
}
/**
 * Handles payment by prompting the user to enter payment amounts
 * until the total amount paid meets or exceeds the ticket price. If the payment
 * is insufficient, the user can add more money or cancel the transaction.
 */
void processPayment(int price)
{
    int totalPaid = 0, amount;
    char choice;
    int paymentComplete = 0;

    while (!paymentComplete)
    {
        printf(
            "\nTotal Due:      %-10d\nAmount Paid:    %-10d\nEnter payment "
            "amount: ",
            price, totalPaid);
        scanf("%d", &amount);

        if (amount <= 0)
        {
            printf("\nInvalid amount. Please enter a valid payment.\n");
        }
        else
        {
            totalPaid += amount;

            if (totalPaid < price)
            {
                printf(
                    "\nInsufficient payment. Add more cash or cancel (C to cancel, "
                    "any key to continue): ");
                scanf(" %c", &choice);

                if (choice == 'C' || choice == 'c')
                {
                    printf("\nTransaction Canceled. Returning to main menu...\n");
                    totalPaid = 0;
                    paymentComplete = 1;
                }
            }
            else
            {
                paymentComplete = 1;
            }
        }
    }

    if (totalPaid >= price)
    {
        printf("\nPayment Successful! Change: %d\n", totalPaid - price);
    }
}
/**
 * Applies a discount to the total price based on user selection.
 * - Senior Citizen/PWD Discount (20% Off)
 * - Manager's Discount (30% Off)
 * - No Discount
 */
float applyDiscount(float totalPrice)
{
    char discountType;
    float discount = 0.0;
    int validInput = 0;

    printf("\nAvailable Discounts:\n");
    printf("  %-2s %-25s %-5s\n", "S", "- Senior Citizen/PWD", "(20% Off)");
    printf("  %-2s %-25s %-5s\n", "M", "- Manager's Discount", "(30% Off)");
    printf("  %-2s %-25s\n", "N", "- No Discount");

    while (!validInput)
    {
        printf("\nEnter discount type (S/M/N): ");
        scanf(" %c", &discountType);

        while (getchar() != '\n');

        // Validate input
        if (discountType == 'S' || discountType == 's')
        {
            discount = totalPrice * 0.20;
            validInput = 1;
        }
        else if (discountType == 'M' || discountType == 'm')
        {
            discount = totalPrice * 0.30;
            validInput = 1;
        }
        else if (discountType == 'N' || discountType == 'n')
        {
            validInput = 1;
        }
        else
        {
            printf("Invalid choice! Please enter 'S', 'M', or 'N'.\n");
        }
    }

    printf("\nDiscount Applied: %.2f\n", discount);
    return totalPrice - discount;
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
                        col = (colChar >= 'A' && colChar <= 'F') ? colChar - 'A' : colChar - 'a';

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
 * Get the seat selection from the user.
 */
int isSeatAvailable(int flightNumber, int row, int col, int flightSeats101[], int flightSeats202[],
                    int flightSeats303[])
{
    int seatIndex = ((row - 1) * COLS) + col;
    if ((flightNumber == 101 && flightSeats101[seatIndex] == 1) ||
        (flightNumber == 202 && flightSeats202[seatIndex] == 1) ||
        (flightNumber == 303 && flightSeats303[seatIndex] == 1))
    {
        return 0;
    }
    return 1;
}

/**
 * Calculates the price of a ticket based on the flight number.
 */
float calculatePrice(int flightNumber, int prices[])
{
    return (flightNumber == 101) ? prices[0] : (flightNumber == 202) ? prices[1] : prices[2];
}

/**
 * Prompts the user to confirm the purchase.
 */
int confirmPurchase()
{
    char confirm;
    printf("Confirm purchase? (Y/N): ");
    if (scanf(" %c", &confirm) != 1 || (confirm != 'Y' && confirm != 'y'))
    {
        return 0;
    }
    return 1;
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

int main()
{
    int prices[] = {3500, 5000, 3200};
    int flightSeats101[TOTAL_SEATS], flightSeats202[TOTAL_SEATS], flightSeats303[TOTAL_SEATS];

    initializeSeats(flightSeats101, TOTAL_SEATS);
    initializeSeats(flightSeats202, TOTAL_SEATS);
    initializeSeats(flightSeats303, TOTAL_SEATS);

    login();

    int exitFlag = 0;
    while (exitFlag == 0)
    {
        int choice;
        printf(
            "\n1. View Flight Schedules\n2. Reserve Ticket\n3. Exit\nEnter "
            "choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            viewFlightSchedules(flightSeats101, flightSeats202, flightSeats303, TOTAL_SEATS);
        }
        else if (choice == 2)
        {
            reserveTicket(flightSeats101, flightSeats202, flightSeats303, prices);
        }
        else if (choice == 3)
        {
            exitFlag = 1;
        }
        else
        {
            printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}
