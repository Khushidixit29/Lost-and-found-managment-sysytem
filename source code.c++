#include <iostream>
#include<vector>
#include<iomanip>
#include<cstring>
#include<fstream>

using namespace std;
class ItemDetails {
public:
    int code;
    char item_name[30];
    char colour[10];
    char brand[10];
    char marks[30];
    char item_place[30];
    char student_name[30];
    char student_id[30];
    long int student_no;

    ItemDetails() : code(0), student_no(0) {}

    void addItem();
    void itemList();
    void removeItem();
    void findItem();
    void edit();
};

void ItemDetails::addItem() {
    ofstream outFile("items.txt",ios::app);

    cout << "Enter item code: ";
    cin >> code;

    cout << "Enter item name: ";
    cin.ignore();
    cin.getline(item_name, sizeof(item_name));

    cout << "Enter a short item description\n>>";
    cout << "Enter item color\n>>";
    cin.ignore();
    cin.getline(colour, sizeof(colour));

    cout << "Enter item brand\n>>";
    cin.ignore();
    cin.getline(brand, sizeof(brand));

    cout << "Identification mark (if any)\n>>";
    cin.ignore();
    cin.getline(marks, sizeof(marks));

    cout << "Enter the place where the item was found\n>>";
    cin.ignore();
    cin.getline(item_place, sizeof(item_place));

    cout << "Enter your name\n>>";
    cin.ignore();
    cin.getline(student_name, sizeof(student_name));

    cout << "Enter your student ID\n>>";
    cin.ignore();
    cin.getline(student_id, sizeof(student_id));

    cout << "Enter your contact number\n>>";
    cin>>student_no;
    cout << "Item added successfully\n";

    outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    outFile.close();
}

void ItemDetails::itemList() {
    ifstream inFile("items.txt",ios::binary);

    cout << "<== Items available ==>\n\n";
    cout <<left << setw(20) << "Item code" << setw(20) << "Item name" <<setw(20)
         << "Colour" <<setw(20) << "Brand" <<setw(20) << "Marks" << setw(20)
         << "Item place" <<setw(20) << "Student Name" <<setw(20) << "Student ID"
         <<setw(20) << "Student No." << "\n\n";

    while (inFile.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        cout << left <<setw(20) << code <<setw(20) << item_name <<setw(20)
             << colour <<setw(20) << brand <<setw(20) << marks <<setw(20)
             << item_place <<setw(20) << student_name <<setw(20) << student_id
             << setw(20) << student_no << "\n";
    }

    inFile.close();
}

void ItemDetails::removeItem() {
    int code;
    bool found = false;

    cout << "Enter the item code to remove: ";
    cin >> code;

    ifstream inFile("items.txt",ios::binary);
    ofstream outFile("temp1.txt",ios::binary);

    while (inFile.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        if (code != this->code) {
            outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("items.txt");
    rename("temp1.txt", "items.txt");

    if (found)
        cout << "\nDeleted successfully\n";
    else
        cout << "\nRecord not found!\n";
}

void ItemDetails::findItem() {
    int found = 0;
    char name[10];

    cout << "Enter name of the item: ";
    cin >> name;

    ifstream inFile("items.txt",ios::binary);

    while (inFile.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        if (strcmp(name, item_name) == 0) {
            cout <<left <<setw(20) << "Item code" <<setw(20) << "Item name" <<setw(20)
                 << "Colour" <<setw(20) << "Brand" <<setw(20) << "Marks" <<setw(20)
                 << "Item place" << setw(20) << "Student Name" <<setw(20) << "Student ID"
                 <<setw(20) << "Student No." << "\n\n";

            cout <<left <<setw(20) << code <<setw(20) << item_name <<setw(20)
                 << colour << setw(20) << brand << setw(20) << marks <<setw(20)
                 << item_place <<setw(20) << student_name << setw(20) << student_id
                 << setw(20) << student_no << "\n";

            found++;
        }
    }

    if (found == 0)
        cout << "Item not found!!\n";

    inFile.close();
}

void ItemDetails::edit() {
    int code;
    char ch;
    bool found = false;

    cout << "Enter the item code to edit: ";
    cin >> code;

    ifstream inFile("items.txt",ios::binary);
    ofstream outFile("temp1.txt",ios::binary);

    while (inFile.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        if (code == this->code) {
            found = true;
            cout << "\nDo you want to change the item name? (y/n)\n";
            cin >> ch;
            if (ch == 'y') {
                cout << "Enter new item name: ";
                cin.ignore();
                cin.getline(item_name, sizeof(item_name));
            }

            cout << "\nDo you want to change the item colour? (y/n)\n";
            std::cin >> ch;
            if(ch == 'y')
            {
                cout << "Enter new item colour: ";
                cin >> colour;
            }

            cout << "\nDo you want to change the brand? (y/n)\n";
            cin >> ch;
            if(ch == 'y')
            {
                cout << "Enter new brand: ";
                cin >> brand;
            }

            cout << "\nDo you want to change the mark? (y/n)\n";
            cin >> ch;
            if(ch == 'y')
            {
                cout << "Enter new mark: ";
                cin >> marks;
            }

            cout << "\nDo you want to change the place? (y/n)\n";
            cin >> ch;
            if(ch == 'y')
            {
                cout << "Enter new place: ";
                cin.ignore();
                cin.getline(item_place, sizeof(item_place));
            }

            cout << "\nDo you want to change the student name? (y/n)\n";
            cin >> ch;
            if(ch == 'y')
            {
                cout << "Enter new student name: ";
                cin.ignore();
                cin.getline(student_name, sizeof(student_name));
            }

            cout << "\nDo you want to change the contact number? (y/n)\n";
            cin >> ch;
            if(ch == 'y')
            {
                cout << "Enter new contact number: ";
                cin >> student_no;
            }
        }

        outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }

    inFile.close();
    outFile.close();

    remove("items.txt");
    rename("temp1.txt", "items.txt");

    if (found)
        cout << "\nModified successfully\n";
    else
        cout << "\nRecord not found!\n";
}

int main() {
    int ch, login_type;
    ItemDetails item;
    cout<<"                 _                              \n"
          "                | |                             \n"
          " _          _ _ | |  _  _   _ _ __    _ \n"
          " \\ \\ /\\ / // _ \\| | / _|/ _ \\ | ' ` _ \\  / _ \\\n"
          "  \\ V  V / |  _/| || (| () || | | | | ||  __/\n"
          "   \\/\\/  \\_||| \\_|\\_/ || || || \\_|\n"
          "                                                \n"
          "                                                \n";
    user:
    cout << "How would you like to login\n1. Student\n2. Admin\n0. To exit the program\n";
    cin >> login_type;

    if (login_type == 0) {
        exit(0);
    } else if (login_type == 1) {
        while (1) {
            cout << "<== Lost and Found ==>\n";
            cout << "1. Add a lost item\n";
            cout << "2. Lost items List\n";
            cout << "3. Search an item\n";
            cout << "0. To change user\n";
            cin >> ch;

            switch (ch) {
                case 0:
                    goto user;
                case 1:
                    item.addItem();
                    break;
                case 2:
                    item.itemList();
                    break;
                case 3:
                    item.findItem();
                    break;
                default:
                    cout << "Invalid choice....\n";
            }
            char choice;
            cout << "Do you want to continue? (y/n): ";
            cin >> choice;

            if (choice != 'y') {
                break;
            }
        }
    } else if (login_type == 2) {
        int pass;
        cout << "Please enter the password\n";
        cin >> pass;

        while (pass != 1234) {
            cout << "Wrong password!!\nplease enter the password again\n";
            cin >> pass;
        }

        if (pass == 1234) {
            while (1) {
                cout << "<== Lost and Found ==>\n";
                cout << "1. Add a lost item\n";
                cout << "2. Lost items List\n";
                cout << "3. Remove a lost item\n";
                cout << "4. Edit information about a lost item\n";
                cout << "5. Search an item\n";
                cout << "0. Change user\n\n";
                cout << "Enter your choice: ";
                cin >> ch;

                switch (ch) {
                    case 0:
                        goto user;
                    case 1:
                        item.addItem();
                        break;
                    case 2:
                        item.itemList();
                        break;
                    case 3:
                        item.removeItem();
                        break;
                    case 4:
                        item.edit();
                        break;
                    case 5:
                        item.findItem();
                        break;
                    default:
                        cout << "Invalid choice....\n\n";
                }
                char choice;
                cout << "Do you want to continue? (y/n): ";
                cin >> choice;

                if (choice != 'y') {
                    break;
                }
            }
        }
    }

    return 0;
}