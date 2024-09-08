//
// Created by Rahul on 9/8/2024.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Room class
class Room {
public:
    int roomNumber;
    string roomType;
    bool isBooked;

    Room(int number, string type) : roomNumber(number), roomType(type), isBooked(false) {}
};

// Guest class
class Guest {
public:
    string name;
    int roomNumber;

    Guest(string guestName, int room) : name(guestName), roomNumber(room) {}
};

// Hotel class
class Hotel {
private:
    vector<Room> rooms;
    vector<Guest> guests;

public:
    Hotel() {

        rooms.emplace_back(101, "Single");
        rooms.emplace_back(102, "Double");
        rooms.emplace_back(103, "Suite");
        rooms.emplace_back(104, "Single");
        rooms.emplace_back(105, "Double");
    }

    // Display rooms
    void displayRooms() {
        cout << "Room Number\tRoom Type\tStatus" << endl;
        for (const auto& room : rooms) {
            cout << room.roomNumber << "\t\t" << room.roomType << "\t\t" << (room.isBooked ? "Booked" : "Available") << endl;
        }
    }

    // Display all booked rooms
    void displayBookedRooms() {
        cout << "Booked Rooms:" << endl;
        for (const auto& room : rooms) {
            if (room.isBooked) {
                cout << "Room Number: " << room.roomNumber << ", Room Type: " << room.roomType << endl;
            }
        }
    }

    // Book a room
    void bookRoom(int roomNumber, string guestName) {
        for (auto& room : rooms) {
            if (room.roomNumber == roomNumber) {
                if (room.isBooked) {
                    cout << "Room " << roomNumber << " is already booked." << endl;
                    return;
                }
                room.isBooked = true;
                guests.emplace_back(guestName, roomNumber);
                cout << "Room " << roomNumber << " booked for " << guestName << "." << endl;
                return;
            }
        }
        cout << "Room " << roomNumber << " not found." << endl;
    }

    // Check-in a guest
    void checkInGuest(int roomNumber) {
        for (const auto& guest : guests) {
            if (guest.roomNumber == roomNumber) {
                cout << "Guest " << guest.name << " is already checked in to room " << roomNumber << "." << endl;
                return;
            }
        }
        cout << "No guest found for room " << roomNumber << "." << endl;
    }

    // Check-out a guest
    void checkOutGuest(int roomNumber) {
        for (auto& room : rooms) {
            if (room.roomNumber == roomNumber) {
                if (!room.isBooked) {
                    cout << "Room " << roomNumber << " is not booked." << endl;
                    return;
                }
                room.isBooked = false;
                guests.erase(remove_if(guests.begin(), guests.end(), [roomNumber](const Guest& guest) {
                    return guest.roomNumber == roomNumber;
                }), guests.end());
                cout << "Checked out of room " << roomNumber << "." << endl;
                return;
            }
        }
        cout << "Room " << roomNumber << " not found." << endl;
    }

    // View guest information
    void viewGuestInfo(int roomNumber) {
        for (const auto& guest : guests) {
            if (guest.roomNumber == roomNumber) {
                cout << "Guest Name: " << guest.name << ", Room Number: " << roomNumber << endl;
                return;
            }
        }
        cout << "No guest found for room " << roomNumber << "." << endl;
    }

    // Cancel a booking
    void cancelBooking(int roomNumber) {
        for (auto& room : rooms) {
            if (room.roomNumber == roomNumber) {
                if (!room.isBooked) {
                    cout << "Room " << roomNumber << " is not booked." << endl;
                    return;
                }
                room.isBooked = false;
                guests.erase(remove_if(guests.begin(), guests.end(), [roomNumber](const Guest& guest) {
                    return guest.roomNumber == roomNumber;
                }), guests.end());
                cout << "Booking for room " << roomNumber << " has been canceled." << endl;
                return;
            }
        }
        cout << "Room " << roomNumber << " not found." << endl;
    }
};

int main() {
    Hotel hotel;
    int choice, roomNumber;
    string guestName;

    while (true) {
        cout << "\nHotel Management System" << endl;
        cout << "1. Display Rooms" << endl;
        cout << "2. Display Booked Rooms" << endl;
        cout << "3. Book Room" << endl;
        cout << "4. Check-in Guest" << endl;
        cout << "5. Check-out Guest" << endl;
        cout << "6. View Guest Information" << endl;
        cout << "7. Cancel Booking" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.displayRooms();
                break;
            case 2:
                hotel.displayBookedRooms();
                break;
            case 3:
                cout << "Enter room number to book: ";
                cin >> roomNumber;
                cout << "Enter guest name: ";
                cin.ignore();  // Ignore leftover newline character
                getline(cin, guestName);
                hotel.bookRoom(roomNumber, guestName);
                break;
            case 4:
                cout << "Enter room number for check-in: ";
                cin >> roomNumber;
                hotel.checkInGuest(roomNumber);
                break;
            case 5:
                cout << "Enter room number for check-out: ";
                cin >> roomNumber;
                hotel.checkOutGuest(roomNumber);
                break;
            case 6:
                cout << "Enter room number to view guest information: ";
                cin >> roomNumber;
                hotel.viewGuestInfo(roomNumber);
                break;
            case 7:
                cout << "Enter room number to cancel booking: ";
                cin >> roomNumber;
                hotel.cancelBooking(roomNumber);
                break;
            case 8:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

