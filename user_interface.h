#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

void login();
void viewFlightSchedules(int seats[], int seats2[], int seats3[], int totalSeats);
void displaySeats(int seats[]);
void displayAvailableSeats(int flightNumber, int flightSeats101[], int flightSeats202[],
                           int flightSeats303[]);
void transactionSummary(float totalSpent);

#endif
