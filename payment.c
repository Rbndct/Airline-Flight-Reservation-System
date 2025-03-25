#include "payment.h"

#include <stdio.h>
#include <string.h>

/**
 * Calculates the price of a ticket based on the flight number.
 */
float calculatePrice(int flightNumber, int prices[])
{
    float price;

    if (flightNumber == 101)
    {
        price = prices[0];
    }
    else if (flightNumber == 202)
    {
        price = prices[1];
    }
    else
    {
        price = prices[2];
    }

    return price;
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
 * Prompts the user to confirm the purchase.
 */
int confirmPurchase()
{
    char confirm;
    int isConfirmed = 0;  // Assume the purchase is not confirmed

    printf("Confirm purchase? (Y/N): ");
    if (scanf(" %c", &confirm) == 1 && (confirm == 'Y' || confirm == 'y'))
    {
        isConfirmed = 1;  // Mark as confirmed
    }

    return isConfirmed;
}