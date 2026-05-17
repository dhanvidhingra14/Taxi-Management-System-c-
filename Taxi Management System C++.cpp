#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <conio.h>
using namespace std;


int isalphaonly(char str[]) {
    for (int i = 0; str[i]!='\0';i++){
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z') ||
               str[i] == ' ')) {
                return 0;
               }
    }
    return 1;
}
int isdigitonly(char str[]) {
    int len = strlen(str);
    if (len != 10) return 0;
    for (int i = 0; i < len; i++) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0;
    }
    return 1;
}
float getRate() {
    FILE* f = fopen("rate.dat", "rb");
    float rate = 10.0; 
    if (f) {
        fread(&rate, sizeof(float), 1, f);
        fclose(f);
    }
    return rate;
}

void setRate(float rate) {
    FILE* f = fopen("rate.dat", "wb");
    if (f) {
        fwrite(&rate, sizeof(float), 1, f);
        fclose(f);
        cout << "Rate updated successfully to Rs " << rate << " per km.\n";
    }
}
class User {
public:
    char name[50];
    char phone[15];

    void registeruser() {
        while (true) {
            cout << "Enter Name (letters only): ";
            cin.ignore();
            cin.getline(name, 50);
            if (isalphaonly(name)) break;
            else cout << "Invalid name. Try again.\n";
        }
        while (true) {
        cout << "Enter Phone (10 digits only): ";
        cin.getline(phone, 15);
        if (!isdigitonly(phone)) {
        cout << "Invalid phone. Try again.\n";
    }
        else if (User::exists(phone)) {
        cout << "Phone number already registered. Try another.\n";
    }
        else {
        break;
    }
}
    }

     void save() {
        FILE *fp = fopen("users.dat", "ab");
        fwrite(this, sizeof(User), 1, fp);
        fclose(fp);
        cout << "User saved successfully.\n";
    }

    static int exists(char ph[]) {
        FILE *fp = fopen("users.dat", "rb");
        if (!fp) return 0;
        User u;
        while (fread(&u, sizeof(User), 1, fp)) {
            if (strcmp(u.phone, ph) == 0) {
                fclose(fp);
                return 1;
            }
        }
        fclose(fp);
        return 0;
    }

     static void showAll() {
        FILE *fp = fopen("users.dat", "rb");
        User u;
        cout << "\n--- Users ---\n";
        while (fread(&u, sizeof(User), 1, fp)) {
            cout << "Name: " << u.name << ", Phone: " << u.phone << "\n";
        }
        fclose(fp);
    }
    static void deleteUser(const char* phone) {
    FILE* in = fopen("users.dat", "rb");
    FILE* out = fopen("temp.dat", "wb");
    User u;
    bool found = false;

    while (fread(&u, sizeof(User), 1, in)) {
        if (strcmp(u.phone, phone) != 0)
            fwrite(&u, sizeof(User), 1, out);
        else
            found = true;
    }

    fclose(in); fclose(out);
    remove("users.dat");
    rename("temp.dat", "users.dat");

    if (found)
        cout << "User deleted successfully.\n";
    else
        cout << "User not found.\n";
}
};

class Taxi {
public:
    int id;
    char driver[50];
    int available;

    void addtaxi() {
        while (true) {
    cout << "Enter Taxi ID (max 4 digits): ";
    cin >> id;

    if (id < 0 || id > 9999) {
        cout << "Taxi ID must be up to 4 digits.\n";
    }
    else if (Taxi::idExists(id)) {
        cout << "Taxi ID already exists. Enter a different ID.\n";
    }
    else {
        break;
    }
}
        cin.ignore();
        cout << "Enter Driver Name: ";
        cin.getline(driver, 50);
        available = 1;
    }

    void save() {
        FILE *fp = fopen("taxis.dat", "ab");
        fwrite(this, sizeof(Taxi), 1, fp);
        fclose(fp);
        cout << "Taxi saved successfully.\n";
    }

    static bool isAvailable(int searchId) {
        FILE* f = fopen("taxis.dat", "rb");
        Taxi t;
        if (!f) return false;
        while (fread(&t, sizeof(Taxi), 1, f)) {
            if (t.id == searchId && t.available == 1) {
                fclose(f);
                return true;
            }
        }
        fclose(f);
        return false;
    }
    static void markUnavailable(int taxiID) {
        FILE* f = fopen("taxis.dat", "rb+");
        Taxi t;
        if (!f) return;
        while (fread(&t, sizeof(Taxi), 1, f)) {
            if (t.id == taxiID) {
                t.available = 0;
                fseek(f, -sizeof(Taxi), SEEK_CUR);
                fwrite(&t, sizeof(Taxi), 1, f);
                break;
            }
        }
        fclose(f);
    }
   static void showAll() {
        FILE *fp = fopen("taxis.dat", "rb");
        Taxi t;
        cout << "\n--- Taxis ---\n";
        while (fread(&t, sizeof(Taxi), 1, fp)) {
            cout << "ID: " << t.id << ", Driver: " << t.driver
                 << ", Available: " << (t.available ? "Yes" : "No") << "\n";
        }
        fclose(fp);
    }
    static void deleteTaxi(int delId) {
    FILE* in = fopen("taxis.dat", "rb");
    FILE* out = fopen("temp.dat", "wb");
    Taxi t;
    bool found = false;

    while (fread(&t, sizeof(Taxi), 1, in)) {
        if (t.id != delId)
            fwrite(&t, sizeof(Taxi), 1, out);
        else
            found = true;
    }

    fclose(in); fclose(out);
    remove("taxis.dat");
    rename("temp.dat", "taxis.dat");

    if (found)
        cout << "Taxi deleted successfully.\n";
    else

        cout << "Taxi not found.\n";
}
    static void updateTaxiIDOnly(int oldID) {
    FILE* f = fopen("taxis.dat", "rb+");
    Taxi t;
    int found = 0;

    while (fread(&t, sizeof(Taxi), 1, f)) {
        if (t.id == oldID) {
            cout << "Enter new Taxi ID: ";
            int newID;
            cin >> newID;

            t.id = newID;

            fseek(f, -sizeof(Taxi), SEEK_CUR);
            fwrite(&t, sizeof(Taxi), 1, f);
            found = 1;
            break;
        }
    }

    fclose(f);

    if (found)
        cout << "Taxi ID updated successfully.\n";
    else
        cout << "Taxi with ID " << oldID << " not found.\n";
}
static void showAvailableTaxis() {
    FILE* fp = fopen("taxis.dat", "rb");
    if (!fp) {
        cout << "No taxis found.\n";
        return;
    }

    Taxi t;
    int found = 0;
    cout << "\n--- Available Taxis ---\n";
    while (fread(&t, sizeof(Taxi), 1, fp)) {
        if (t.available == 1) {
            cout << "ID: " << t.id
                 << ", Driver: " << t.driver << "\n";
            found = 1;
        }
    }

    if (!found)
        cout << "No taxis are currently available.\n";

    fclose(fp);
}

    static void updateDriverOnly(int id) {
    FILE* f = fopen("taxis.dat", "rb+");
    Taxi t;
    int found = 0;

    while (fread(&t, sizeof(Taxi), 1, f)) {
        if (t.id == id) {
            cin.ignore();
            cout << "Enter new Driver Name: ";
            char newDriver[50];
            cin.getline(newDriver, 50);

            strcpy(t.driver, newDriver);

            fseek(f, -sizeof(Taxi), SEEK_CUR);
            fwrite(&t, sizeof(Taxi), 1, f);
            found = 1;
            break;
        }
    }

    fclose(f);

    if (found)
        cout << "Driver name updated successfully.\n";
    else
        cout << "Taxi with ID " << id << " not found.\n";
}
    static int idExists(int searchId) {
    FILE* f = fopen("taxis.dat", "rb");
    if (!f) return 0;

    Taxi t;
    while (fread(&t, sizeof(Taxi), 1, f)) {
        if (t.id == searchId) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

};

class Booking {
public:
    char phone[15];
    int taxiID;
    float distance;
    float fare;
    char paymentMethod[20];
    char date[30];
    time_t bookingTime; 

    void input() {
        cout << "Enter your phone number: ";
        cin.ignore();
        cin.getline(phone, 15);

        if (!User::exists(phone)) {
            cout << "User not registered.\n";
            return;
        }

        Taxi::showAvailableTaxis();
        cout << "Enter Taxi ID to book: ";
        cin >> taxiID;

        if (!Taxi::isAvailable(taxiID)) {
            cout << "Taxi not available.\n";
            return;
        }

        cout << "Enter distance (km): ";
        cin >> distance;
       fare = distance * getRate();
        time_t now = time(0);
        bookingTime = now;

        cout << "Select payment method: 1. Cash 2. UPI 3. Card: ";
        int pm;
        cin >> pm;
        switch (pm) {
            case 1: strcpy(paymentMethod, "Cash"); break;
            case 2: strcpy(paymentMethod, "UPI"); break;
            case 3: strcpy(paymentMethod, "Card"); break;
            default: strcpy(paymentMethod, "Unknown");
        }
        strcpy(date, ctime(&now));
        date[strlen(date) - 1] = '\0';

        FILE* f = fopen("bookings.dat", "ab");
        fwrite(this, sizeof(Booking), 1, f);
        fclose(f);

        Taxi::markUnavailable(taxiID);
        cout << "Booking successful. Fare: RS" << fare << ", Date: " << date << "\n";
    }

    static void showAll() {
        FILE* f = fopen("bookings.dat", "rb");
        Booking b;
        if (!f) {
            cout << "No bookings found.\n";
            return;
        }
        cout << "\n--- Bookings ---\n";
        while (fread(&b, sizeof(Booking), 1, f)) {
            cout << "Phone: " << b.phone << ", TaxiID: " << b.taxiID
                 << ", Distance: " << b.distance << " km, Fare: RS" << b.fare
                 << ", Payment: " << b.paymentMethod << ", Date: " << b.date << "\n";
        }
        fclose(f);
    }

    static void showUserBookings(const char* ph) {
        FILE* f = fopen("bookings.dat", "rb");
        Booking b;
        if (!f) {
            cout << "No bookings found.\n";
            return;
        }
        cout << "\n--- Your Bookings ---\n";
        while (fread(&b, sizeof(Booking), 1, f)) {
            if (strcmp(b.phone, ph) == 0) {
                cout << "TaxiID: " << b.taxiID << ", Distance: " << b.distance
                     << ", Fare: RS" << b.fare << ", Payment: " << b.paymentMethod
                     << ", Date: " << b.date << "\n";
            }
        }
        fclose(f);
    }
   
    static void removeBooking() {
    FILE *in = fopen("bookings.dat", "rb");
    FILE *out = fopen("temp.dat", "wb");
    int taxiIDtodelete;
    cout<<"Enter taxi ID to delete booking:";
    cin>>taxiIDtodelete;

    Booking b;
    int found = 0;

    while (fread(&b, sizeof(Booking), 1, in)) {
        if (b.taxiID!=taxiIDtodelete) {
            fwrite(&b, sizeof(Booking), 1, out);
        } else {
            found = 1;

        
            Taxi t;
            FILE *ftaxi = fopen("taxis.dat", "rb+");
            while (fread(&t, sizeof(Taxi), 1, ftaxi)) {
                if (t.id == taxiIDtodelete) {
                    t.available = 1;
                    fseek(ftaxi, -sizeof(Taxi), SEEK_CUR);
                    fwrite(&t, sizeof(Taxi), 1, ftaxi);
                    break;
                }
            }
            fclose(ftaxi);
        }
    }

    fclose(in);
    fclose(out);
    remove("bookings.dat");
    rename("temp.dat", "bookings.dat");

    if (found)
        cout << "Your booking has been deleted, and the taxi is now available again.\n";
    else
        cout << "No booking found on this taxi number.\n";
}

    static void generateReport() {
        FILE* f = fopen("bookings.dat", "rb");
        Booking b;
        int count = 0;
        float totalFare = 0;
        char lastDate[30] = "";
        int taxiCount[10000] = {0};
      

      while (fread(&b, sizeof(Booking), 1, f))  {
            count++;
            totalFare += b.fare;
            strcpy(lastDate, b.date);
            if (b.taxiID >= 0 && b.taxiID < 10000)
                taxiCount[b.taxiID]++;
        }
        fclose(f);
  
        cout << "\n===== BOOKING REPORT =====\n";
        cout << "Total Bookings: " << count << "\n";
        cout << "Total Fare Collected: RS" << totalFare << "\n";
        cout << "Last Booking Date: " << lastDate << "\n";
        
    }
    static void generateReportByTaxiID() {
    int taxiId;
    cout << "Enter Taxi ID to generate report: ";
    cin >> taxiId;

    FILE* f = fopen("bookings.dat", "rb");
    if (!f) {
        cout << "No bookings found.\n";
        return;
    }

    Booking b;
    int count = 0;
    float totalFare = 0;
    char lastDate[30] = "";

    cout << "\n--- Bookings for Taxi ID: " << taxiId << " ---\n";
    while (fread(&b, sizeof(Booking), 1, f)) {
        if (b.taxiID == taxiId) {
            count++;
            totalFare += b.fare;
            strcpy(lastDate, b.date);
            cout << "Phone: " << b.phone
                 << ", Distance: " << b.distance
                 << ", Fare: RS" << b.fare
                 << ", Payment: " << b.paymentMethod
                 << ", Date: " << b.date << "\n";
        }
    }

    fclose(f);

    if (count == 0)
        cout << "No bookings found for Taxi ID " << taxiId << ".\n";
    else {
        cout << "\n===== REPORT =====\n";
        cout << "Total Bookings: " << count << "\n";
        cout << "Total Fare: RS" << totalFare << "\n";
        cout << "Last Booking Date: " << lastDate << "\n";
    }
}
    static void cancelbooking() {
    char phone[15];
    int taxiId;
    cout << "Enter your registered phone number: ";
    cin.ignore();
    cin.getline(phone, 15);
    cout << "Enter taxi ID of the booking to cancel: ";
    cin >> taxiId;

    FILE *in = fopen("bookings.dat", "rb");
    FILE *out = fopen("temp.dat", "wb");
    Booking b;
    int found = 0;
    time_t now = time(0); // Current time

    while (fread(&b, sizeof(Booking), 1, in)) {
        if (!(strcmp(b.phone, phone) == 0 && b.taxiID == taxiId)) {
            fwrite(&b, sizeof(Booking), 1, out);
        } else {
           
            double secondsPassed = difftime(now, b.bookingTime);
            if (secondsPassed > 120) {
                cout << " Cancellation period expired (more than 2 minutes). Cannot cancel this booking.\n";
                fwrite(&b, sizeof(Booking), 1, out); // Keep the booking
                continue;
            }

            
            found = 1;
            Taxi t;
            FILE *ftaxi = fopen("taxis.dat", "rb+");
            while (fread(&t, sizeof(Taxi), 1, ftaxi)) {
                if (t.id == taxiId) {
                    t.available = 1;
                    fseek(ftaxi, -sizeof(Taxi), SEEK_CUR);
                    fwrite(&t, sizeof(Taxi), 1, ftaxi);
                    break;
                }
            }
            fclose(ftaxi);
        }
    }

    fclose(in);
    fclose(out);
    remove("bookings.dat");
    rename("temp.dat", "bookings.dat");

    if (found)
        cout << " Booking canceled successfully within time. Taxi is now available.\n";
    else
        cout << "No booking found with this phone and taxi ID.\n";
}
};
void adminMenu() {
    int ch;
    do {
        cout << "\n--- ADMIN MENU ---\n";
        cout<<"1. Add Taxi";
        cout<<"\n2. Show Users";
        cout<<"\n3. Show Taxis";
        cout<<"\n4. Show Bookings";
        cout <<"\n5. Generate Overall Report";
        cout <<"\n6. Generate Report by Taxi ID";
        cout<<"\n7. Delete User";
        cout<<"\n8. Delete Taxi";
        cout<<"\n9. Delete Booking";
        cout <<"\n10. Update Taxi ID";
        cout <<"\n11. Update Driver Name";
        cout << "\n12. Change Rate Per KM";
        cout << "\n13. Logout\nChoice: ";

        cin >> ch;
        switch (ch) {
            case 1: { Taxi t; 
                t.addtaxi();
                 t.save(); 
                 break; 
                }
            case 2: User::showAll(); 
                break;
            case 3: Taxi::showAll(); 
                 break;
            case 4: Booking::showAll(); 
                break;
            case 5:
                Booking::generateReport();
            break;
            case 6:
                Booking::generateReportByTaxiID();
                break;
            case 7: {
                char ph[15];
                cout << "Enter phone to delete: ";
                cin.ignore();
                cin.getline(ph, 15);
                User::deleteUser(ph);
                break;
            }
            case 8: {
                int id;
                cout << "Enter taxi ID to delete: ";
                cin >> id;
                Taxi::deleteTaxi(id);
                break;
            }
            case 9: {
                Booking::removeBooking();
                break;
            }
            case 10: {
                 int oldID;
                 cout << "Enter current Taxi ID to update ID: ";
                 cin >> oldID;
                 Taxi::updateTaxiIDOnly(oldID);
                 break;
                }
            case 11: {
                 int id;
                cout << "Enter Taxi ID to update driver name: ";
                cin >> id;
                Taxi::updateDriverOnly(id);
                break;
                }
                case 12: {
                    float newRate;
                    cout << "Enter new rate per KM: ";
                    cin >> newRate;
                    setRate(newRate);
                    break;
                }
        }
    } while (ch != 13);
}
void userMenu(const char* phone) {
    int ch;
    do {
        cout << "\n--- USER MENU ---\n";
        cout << "1. Book Taxi\n2. View My Bookings\n3. Cancel bookings\n4. Logout\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: { Booking b;
                 b.input();
                 break; }
            case 2: Booking::showUserBookings(phone);
            break;
            case 3:
            Booking :: cancelbooking();
                break;
        }
    } while (ch != 4);
}

void userLogin() {
    char ph[15];
    cout << "Enter registered phone number: ";
    cin.ignore();
    cin.getline(ph, 15);

    if (User::exists(ph)) {
        userMenu(ph);
    } else {
        cout << "User not found.\n";
    }
}
void mainMenu() {
    int ch;
    do {
        cout << "\n=== TAXI BOOKING SYSTEM ===\n";
        cout << "1. Register User\n2. User Login\n3. Admin Login\n4. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: { User u;
                 u.registeruser();
                 u.save(); 
                 break; }
            case 2: userLogin(); 
            break;
            case 3: {
                char pwd[20], c;
                int i = 0;
                cout << "Enter Admin Password: ";
                while ((c = getch()) != '\r') {
                    if (c == '\b' && i > 0) {
                        cout << "\b \b"; i--;
                    } else {
                        pwd[i++] = c; cout << '*';
                    }
                }
                pwd[i] = '\0';
                cout << "\n";
                if (strcmp(pwd, "1428") == 0)
                    adminMenu();
                else
                    cout << "Incorrect password.\n";
                break;
            }
        }
    } while (ch != 4);
}

int main() {
    mainMenu();
    return 0;
}