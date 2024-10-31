/*
=====================================================================
Author: Arjit Magar
Date: 2024/10/31
Description: A program to handle ticket sales for an auditorium 
    where the tickets are sold on Thursday, Friday and Saturday having three seating areas floor, balcony and upper balcony
    consisting of 20 seats with prices $30 , $20 & $10 respectively.
Input:Seat requests with a three or four character code
Output:Menu , Displayed seating chart , Sales summary .
Compilation instructions:
Usage:
Modifications:
Date Comment:
---- ------------------------------------------------
======================================================================
*/
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>

using namespace std;

const int DAYS = 3;
const int SECTIONS = 3;
const int SEATS = 20;
// Floor, Balcony, Upper Balcony
const int PRICES[SECTIONS] = {30, 20, 10};  

char seating[DAYS][SECTIONS][SEATS];

const string dayNames[DAYS] = {"Thursday", "Friday", "Saturday"};
const string sectionNames[SECTIONS] = {"Floor", "Balcony", "Upper Balcony"};

// Function declarations
char get_menu_choice();
void initialize_seating();
void print_chart();
bool sell_seat();
void print_day_list();
void print_section_list();

int main() {
    initialize_seating();
    char choice;

    do {
        choice = get_menu_choice();
        if (choice == 'S') {
            sell_seat();
        } else if (choice == 'C') {
            print_chart();
        } else if (choice == 'D') {
            print_day_list();
        } else if (choice == 'F') {
            print_section_list();
        } else if (choice == 'Q') {
            cout << "Bye" << endl;
        }
    } while (choice != 'Q');

    return 0;
}

// Menu choice function
char get_menu_choice() {
    char choice;
    cout << "\n     *** Main Menu ***\n"
         << "S - Sell a Ticket\n"
         << "C - Display Seating Chart\n"
         << "D - Display Sales Summary - Day Listing\n"
         << "F - Display Sales Summary - Floor Listing\n"
         << "Q - Quit\n"
         << "Your choice: ";
    cin >> choice;
    choice = toupper(choice);

    while (choice != 'S' && choice != 'C' && choice != 'D' && choice != 'F' && choice != 'Q') {
        cout << "\"" << choice << "\" is not a valid choice. Try again.\n";
        cout << "Your choice: ";
        cin >> choice;
        choice = toupper(choice);
    }
    return choice;
}

// Initializing seating with all seats available ('-')
void initialize_seating() {
    for (int day = 0; day < DAYS; day++) {
        for (int section = 0; section < SECTIONS; section++) {
            for (int seat = 0; seat < SEATS; seat++) {
                seating[day][section][seat] = '-';
            }
        }
    }
    cout << "All seats have been initialized.\n";
}

// Display seating chart function 
void print_chart() {
    for (int day = 0; day < DAYS; day++) {
        cout << dayNames[day] << endl;
        for (int section = 0; section < SECTIONS; section++) {
            cout << sectionNames[section] << ": ";
            for (int seat = 0; seat < SEATS; seat++) {
                cout << seating[day][section][seat] << " ";
            }
            cout << endl;
        }
    }
}

// Sell seat function
bool sell_seat() {
    char day, section;
    int seatNum;
    cout << "Enter seat request by Day (T)hursday, (F)riday, (S)aturday\n"
         << "followed by Section (F)loor, (B)alcony, (U)pper Balcony\n"
         << "followed by seat number (1 - 20).\n"
         << "Seat: ";
    string request;
    cin >> request;

    if (request.length() < 3 || request.length() > 4) {
        cout << "Invalid input length.\n";
        return false;
    }

    day = toupper(request[0]);
    section = toupper(request[1]);
    seatNum = stoi(request.substr(2)) - 1;

    int dayIndex;
    if (day == 'T') {
        dayIndex = 0;
    } else if (day == 'F') {
        dayIndex = 1;
    } else if (day == 'S') {
        dayIndex = 2;
    } else {
        cout << "Your day input is invalid. Please try again.\n";
        return false;
    }

    int sectionIndex;
    if (section == 'F') {
        sectionIndex = 0;
    } else if (section == 'B') {
        sectionIndex = 1;
    } else if (section == 'U') {
        sectionIndex = 2;
    } else {
        cout << "Invalid section.\n";
        return false;
    }

    if (seatNum < 0 || seatNum >= SEATS) {
        cout << "Invalid seat number.\n";
        return false;
    }

    if (seating[dayIndex][sectionIndex][seatNum] == '*') {
        cout << "That seat is taken, please select another.\n";
        return false;
    }

    seating[dayIndex][sectionIndex][seatNum] = '*';
    cout << "Congratulations! You got the seat.\n";
    return true;
}

// Sales summary by day
void print_day_list() {
    int totalSales = 0;
    int totalTickets = 0;

    for (int day = 0; day < DAYS; day++) {
        cout << dayNames[day] << endl;
        for (int section = 0; section < SECTIONS; section++) {
            int ticketsSold = 0;
            for (int seat = 0; seat < SEATS; seat++) {
                if (seating[day][section][seat] == '*') {
                    ticketsSold++;
                }
            }
            int revenue = ticketsSold * PRICES[section];
            cout << setw(14) << left << sectionNames[section] 
                 << "Tickets sold: " << setw(2) << ticketsSold 
                 << " $" << revenue << endl;
            totalSales += revenue;
            totalTickets += ticketsSold;
        }
    }
    cout << "Total ticket sales for all shows: " << totalTickets << " $" << totalSales << endl;
}

// Sales summary by section
void print_section_list() {
    int totalSales = 0;
    int totalTickets = 0;

    for (int section = 0; section < SECTIONS; section++) {
        cout << sectionNames[section] << endl;
        for (int day = 0; day < DAYS; day++) {
            int ticketsSold = 0;
            for (int seat = 0; seat < SEATS; seat++) {
                if (seating[day][section][seat] == '*') {
                    ticketsSold++;
                }
            }
            int revenue = ticketsSold * PRICES[section];
            cout << setw(10) << left << dayNames[day]
                 << "Tickets sold: " << setw(2) << ticketsSold 
                 << " $" << revenue << endl;
            totalSales += revenue;
            totalTickets += ticketsSold;
        }
    }
    cout << "Total ticket sales for all shows: " << totalTickets << " $" << totalSales << endl;
}