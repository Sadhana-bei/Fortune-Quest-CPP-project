#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

template <typename T>
class Adventure {
private:
    string name;
    string password;
    T health;
    T treasure;

public:
    Adventure() : health(100), treasure(0) {}

    void setName(const string& name) {
        this->name = name;
    }

    string getName() const {
        return name;
    }

    void setPassword(const string& password) {
        this->password = password;
    }

    string getPassword() const {
        return password;
    }

    T getHealth() const {
        return health;
    }

    void setHealth(T health) {
        this->health = health;
    }

    T getTreasure() const {
        return treasure;
    }

    void setTreasure(T treasure) {
        this->treasure = treasure;
    }

    void saveToFile() {
        ofstream file("players.txt", ios::app);
        if (file.is_open()) {
            file << name << " " << password << " " << health << " " << treasure << endl;
            file.close();
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    bool loadFromFile(const string& name, const string& password) {
        ifstream file("players.txt");
        if (file.is_open()) {
            string storedName, storedPassword;
            T health, treasure;
            while (file >> storedName >> storedPassword >> health >> treasure) {
                if (storedName == name && storedPassword == password) {
                    this->name = storedName;
                    this->password = storedPassword;
                    this->health = health;
                    this->treasure = treasure;
                    file.close();
                    return true;
                }
            }
            file.close();
        } else {
            cout << "Unable to open file for reading." << endl;
        }
        return false;
    }

    void playGame();
};

template <typename T>
void registerPlayer() {
    Adventure<T> player;
    string name, password;

    cout << "Enter your name: ";
    cin >> name;
    player.setName(name);

    cout << "Enter your password: ";
    cin >> password;
    player.setPassword(password);

    player.saveToFile();
    cout << "Registration successful!" << endl;
}

template <typename T>
void loginPlayer() {
    string name, password;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your password: ";
    cin >> password;

    Adventure<T> player;
    if (player.loadFromFile(name, password)) {
        cout << "Login successful!" << endl;
        try {
            player.playGame();
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    } else {
        cout << "Invalid credentials. Try again." << endl;
    }
}

template <typename T>
void Adventure<T>::playGame() {
    cout << "\n" << endl;
    cout << "************************************************" << endl;
    cout << "*                                              *" << endl;
    cout << "*            WELCOME TO THE ADVENTURE          *" << endl;
    cout << "************************************************" << endl;
    cout << "\n" << endl;
    
    // Initialize random seed
    srand(static_cast<unsigned int>(time(0))); 
    
    while (health > 0) {
        int encounter = rand() % 6; // Adjusted range to match the number of cases (0-5)

        switch (encounter) {
        case 0: {
            // Wild animal attack
            cout << "\n" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "You encounter a wild animal. It attacks you!" << endl;
            cout << "Do you: " << endl;
            cout << "1. Run away" << endl;
            cout << "2. Fight back" << endl;
            int choice;
            cin >> choice;
            if (choice == 1) {
                health -= 20;
                cout << "You run away, but the animal bites you. You lose 20 health." << endl;
            } else if (choice == 2) {
                health -= 10;
                cout << "You fight back, but the animal is too strong. You lose 10 health." << endl;
            }
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\n" << endl;
            break;
        }

        case 1: {
            // Treasure chest
            cout << "\n" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "You find a treasure chest!" << endl;
            cout << "Do you: " << endl;
            cout << "1. Open it" << endl;
            cout << "2. Leave it" << endl;

            int choice;
            cin >> choice;
            if (choice == 1) {
                treasure += 10;
                cout << "You open the chest and find 10 gold coins!" << endl;
            } else if (choice == 2) {
                cout << "You leave the chest. Maybe it's trapped?" << endl;
            }
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\n" << endl;
            break;
        }

        case 2: {
            // River crossing
            cout << "\n" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "You come across a river. Do you: " << endl;
            cout << "1. Swim across" << endl;
            cout << "2. Look for a bridge" << endl;
            int choice;
            cin >> choice;
            if (choice == 1) {
                health -= 15;
                cout << "You swim across, but the current is strong. You lose 15 health." << endl;
            } else if (choice == 2) {
                cout << "You find a bridge and cross safely." << endl;
            }
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\n" << endl;
            break;
        }

        case 3:  {
            // Treasure map
            cout << "\n" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "You find a treasure map! It leads to hidden treasure." << endl;
            cout << "Do you: " << endl;
            cout << "1. Follow the map to find the treasure" << endl;
            cout << "2. Leave the map and move on" << endl;

            int choice;
            cin >> choice;
            if (choice == 1) {
                treasure += 20;
                cout << "You follow the map and find 20 gold coins!" << endl;
            } else if (choice == 2) {
                cout << "You leave the map behind and continue on your adventure." << endl;
            }

            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\n" << endl;
            break;
        }
           
        case 4: {
            // Potion
            cout << "\n" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "You discover a potion on the ground. Do you: " << endl;
            cout << "1. Drink it" << endl;
            cout << "2. Ignore it" << endl;
            int choice;
            cin >> choice;
            if (choice == 1) {
                health += 10;
                cout << "The potion restores 10 health. You feel good!" << endl;
            } else if (choice == 2) {
                cout << "You leave the potion behind. It might have been useful." << endl;
            }
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\n" << endl;
            break;
        }

        case 5: {
            // Merchant
            cout << "\n" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "You encounter a merchant who offers you a deal." << endl;
            cout << "Do you: " << endl;
            cout << "1. Trade 10 gold coins for 20 health" << endl;
            cout << "2. Trade 20 health for 15 gold coins" << endl;
            cout << "3. Decline the offer" << endl;
            int choice;
            cin >> choice;
            if (choice == 1 && treasure >= 10) {
                treasure -= 10;
                health += 20;
                cout << "You trade 10 gold coins for 20 health." << endl;
            } else if (choice == 2 && health >= 20) {
                health -= 20;
                treasure += 15;
                cout << "You trade 20 health for 15 gold coins." << endl;
            } else if (choice == 3) {
                cout << "You decline the merchant's offer and move on." << endl;
            } else {
                cout << "You don't have enough resources for this trade." << endl;
            }
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\n" << endl;
            break;
        }
        }

        cout << "Your current health: " << health << endl;
        cout << "Your current treasure: " << treasure << endl;

        if (treasure >= 250) {
            cout << "\t\t.............." << endl;
            cout << "\t\t *********** " << endl;
            cout << "\t\t   ********  " << endl;
            cout << "\t\t    *****  " << endl;
            cout << "\t\t     ****  " << endl;
            cout << "\t\t      **   " << endl;
            cout << "\t\t      #1  " << endl;
            cout << "\t\t      ** " << endl;
            cout << "\t\t      ** " << endl;
            cout << "\t\t      ** " << endl;
            cout << "\t\t     **** " << endl;
            cout << "\t\tCongratulations, you have won the game!" << endl;
            break;
        } else if (health <= 0) {
            throw runtime_error("Game Over. You died!");
        }
    }
}

int main() {
    int choice;
    system("clear");
    cout << "\n" << endl;
    cout << "********************************************************" << endl;
    cout << "*                                                      *" << endl;
    cout << "*              WELCOME TO THE ADVENTURE                *" << endl;
    cout << "*                                                      *" << endl;
    cout << "*           Welcome to an epic journey full of         *" << endl;
    cout << "*           challenges and rewards. Are you            *" << endl;
    cout << "*              ready to test your skills?              *" << endl;
    cout << "*                                                      *" << endl;
    cout << "*      1. Register - Create a new character            *" << endl;
    cout << "*    2. Login - Access your existing character         *" << endl;
    cout << "*           3. Quit - Exit the game                    *" << endl;
    cout << "*                                                      *" << endl;
    cout << "********************************************************" << endl;
    cout << "\n" << endl;

    while (true) {
        cout << "\t\tWelcome to the game! " << endl;
        cout << " ____________________________________________ " << endl;
        cout << "\n\t1. Register" << endl;
        cout << "\n\t2. Login" << endl;
        cout << "\n\t3. Quit" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            registerPlayer<int>();
            break;
        case 2:
            loginPlayer<int>();
            break;
        case 3:
            cout << "Thanks for playing! Goodbye." << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
    return 0;
}