#ifndef PAYMENT_H
#define PAYMENT_H

void processPayment(int price);
float applyDiscount(float totalPrice);
float calculatePrice(int flightNumber, int prices[]);
int confirmPurchase();

#endif
