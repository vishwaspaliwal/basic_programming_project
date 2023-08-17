#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Train {
public:
    int trainNumber;
    std::string trainName;
    int totalSeats;

    Train(int number, const std::string& name, int seats)
        : trainNumber(number), trainName(name), totalSeats(seats) {}
};

class Reservation {
public:
    int trainNumber;
    int numSeats;
    std::string passengerName;

    Reservation(int train, int seats, const std::string& name)
        : trainNumber(train), numSeats(seats), passengerName(name) {}
};

class RailwayReservationSystem {
private:
    std::vector<Train> trains;
    std::vector<Reservation> reservations;

public:
    void addTrain(int number, const std::string& name, int seats) {
        trains.emplace_back(number, name, seats);
    }

    void bookTicket(int trainNumber, int numSeats, const std::string& passengerName) {
        for (Train& train : trains) {
            if (train.trainNumber == trainNumber) {
                if (numSeats <= train.totalSeats) {
                    train.totalSeats -= numSeats;
                    reservations.emplace_back(trainNumber, numSeats, passengerName);
                    std::cout << "Ticket booked successfully!\n";
                    saveBookingToFile(trainNumber, numSeats, passengerName);
                    return;
                } else {
                    std::cout << "Not enough seats available on this train.\n";
                    return;
                }
            }
        }
        std::cout << "Train not found.\n";
    }

    void saveBookingToFile(int trainNumber, int numSeats, const std::string& passengerName) {
        std::ofstream bookingFile("C:\\Users\\mahim\\OneDrive\\Desktop\\New folder\\railway reservation\\bookings", std::ios::app);
        if (bookingFile.is_open()) {
            bookingFile << "Train Number: " << trainNumber << "\tSeats: " << numSeats << "\tPassenger: " << passengerName << "\n";
            bookingFile.close();
            std::cout << "Booking information saved to bookings.txt.\n";
        } else {
            std::cout << "Unable to open bookings.txt for writing.\n";
        }
    }

    void displayTrains() {
        std::cout << "Train Number\tTrain Name\tAvailable Seats\n";
        for (const Train& train : trains) {
            std::cout << train.trainNumber << "\t\t" << train.trainName << "\t\t" << train.totalSeats << "\n";
        }
    }
};

int main() {
    RailwayReservationSystem system;

    system.addTrain(1, "Express", 50);
    system.addTrain(2, "Superfast", 40);
    system.addTrain(3, "Local", 100);

    int choice;
    do {
        std::cout << "1. Display Trains\n";
        std::cout << "2. Book Ticket\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.displayTrains();
                break;
            case 2: {
                int trainNumber, numSeats;
                std::string passengerName;

                std::cout << "Enter Train Number: ";
                std::cin >> trainNumber;
                std::cout << "Enter Number of Seats: ";
                std::cin >> numSeats;
                std::cout << "Enter Passenger Name: ";
                std::cin.ignore(); // Clear newline from previous input
                std::getline(std::cin, passengerName);

                system.bookTicket(trainNumber, numSeats, passengerName);
                break;
            }
            case 3:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
