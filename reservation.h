#ifndef RESERVATION_H
#define RESERVATION_H

void initializeSeats(int flightSeats[], int size);
int countAvailableSeats(int seats[], int totalSeats);
void reserveTicket(int flightSeats101[], int flightSeats202[], int flightSeats303[], int prices[]);
int getFlightNumber();
int getSeatSelection(int *row, int *col);
int isSeatAvailable(int flightNumber, int row, int col, int flightSeats101[], int flightSeats202[],
                    int flightSeats303[]);
void processSeatReservation(int flightNumber, int row, int col, int flightSeats101[],
                            int flightSeats202[], int flightSeats303[]);

#endif
