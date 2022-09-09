#include "emsHeaders.h"
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// vector Employee and map employee
std::vector<Employee *> employee;
std::map<std::string, Employee *> mp;

// constructor
Employee::Employee(std::string fN, std::string lN, int ag, std::string ID, std::string gen, std::string pos,
                   std::string dep, std::string sal) {
    firstName = std::move(fN);
    lastName = std::move(lN);
    age = ag;
    id = std::move(ID);
    gender = std::move(gen);
    position = std::move(pos);
    department = std::move(dep);
    salary = std::move(sal);
}

// function to add a new employee to the file
void Employee::add() {
    std::string fN, lN, ID, gen, pos, dep, sal, confirmation;
    int ag;

    cout << "Enter first name: ";
    cin >> fN;

    cout << "Enter Last name: ";
    cin >> lN;

    cout << "Enter age: ";
    std::string a;
    cin >> a;
    if (a.length() > 3) {
        cout << "Age Invalid." << endl;
        return;
    }

    for (auto it : a) {
        if ((it >= 'a' && it <= 'z') || (it >= 'A' && it <= 'Z')) {
            cout << "Age Invalid, age should be numeric" << endl;
            return;
        }
    }
    ag = stoi(a);

    cout << "Enter ID: ";
    cin >> ID;

    cout << "Enter gender: ";
    cin >> gen;

    cout << "Enter position: ";
    cin >> pos;

    cout << "Enter department: ";
    cin >> dep;

    cout << "Enter salary: ";
    cin >> sal;

    if (mp[ID] != nullptr) {
        cout << "Employee Exists." << endl;
        cout << endl;
        return;
    }

    cout << "Press 1 to save user details or any other key to abort: ";
    cin >> confirmation;
    if (confirmation == "1") {
        auto *tmp = new Employee(fN, lN, ag, ID, gen, pos, dep, sal);
        employee.push_back(tmp);
        mp[ID] = tmp;
        saveFile();
        cout << "Employee information saved." << endl << endl;
    } else {
        cout << "Employee information not saved." << endl << endl;
    }
}

// function to displayEmployeeInfo employee information
void Employee::displayEmployeeInfo(Employee *info) {
    cout << "Name: " << info->firstName << " " << info->lastName << endl;
    cout << "Age: " << info->age << endl;
    cout << "ID: " << info->id << endl;
    cout << "Gender: " << info->gender << endl;
    cout << "Position: " << info->position << endl;
    cout << "Department: " << info->department << endl;
    cout << "Salary: " << info->salary << endl << endl;
}

// function to search employee based on their IDs
void Employee::search(const std::string &a) {
    if (a == "1") {
        cout << "Enter Employee ID to find employee: ";
        string EmployeeID;
        cin >> EmployeeID;
        Employee *tmp = mp[EmployeeID];

        if (tmp == nullptr) {
            cout << "Employee does not exists with given ID" << endl << endl;
        } else {
            cout << endl;
            cout << "Details of the Employee" << endl;
            displayEmployeeInfo(tmp);
        }
    } else {
        if (employee.empty()) {
            cout << "No employee exists" << endl;
            return;
        }

        cout << endl;
        for (auto info : employee) {
            displayEmployeeInfo(info);
        }
    }
}

// function to update employee information based on given employee id
void Employee::update() {
    cout << "Enter employee ID: ";
    std::string EmployeeID;
    cin >> EmployeeID;
    cout << endl;

    Employee *tmp = mp[EmployeeID];
    if (tmp != nullptr) {
        cout << "Current information of employee" << endl;
        displayEmployeeInfo(tmp);

        std::string fN, lN, ID, gen, pos, dep, sal;
        int ag{};
        std::string confirmation;

        cout << "Enter updated first name: ";
        cin >> fN;

        cout << "Enter updated Last name: ";
        cin >> lN;

        cout << "Enter updated age: ";
        cin >> ag;

        //        cout << "Enter ID: ";
        //        cin >> ID;

        cout << "Enter updated gender: ";
        cin >> gen;

        cout << "Enter updated position: ";
        cin >> pos;

        cout << "Enter updated department: ";
        cin >> dep;

        cout << "Enter updated salary: ";
        cin >> sal;

        cout << "Press 1 to update employee information or any other key to discard: ";
        cin >> confirmation;
        if (confirmation == "1") {
            tmp->firstName = fN;
            tmp->lastName = lN;
            tmp->age = ag;
            tmp->gender = gen;
            tmp->position = pos;
            tmp->department = dep;
            tmp->salary = sal;
            saveFile();
            cout << "Employee information updated" << endl << endl;
        } else {
            cout << "Employee information not updated" << endl;
        }
    } else {
        cout << "No employee found with given ID" << endl;
    }
}

// function to delete employee based on given employee id
void Employee::remove() {
    cout << "Enter employee ID to find and delete: ";
    std::string EmployeeID;
    cin >> EmployeeID;

    Employee *tmp = mp[EmployeeID];
    if (tmp != nullptr) {
        cout << endl << "Details of employee to be deleted:" << endl;
        displayEmployeeInfo(tmp);

        string confirmation;
        cout << "Press 1 to confirm deletion: ";
        cin >> confirmation;
        if (confirmation == "1") {

            // delete from employee vector
            employee.erase(std::remove(employee.begin(), employee.end(), mp[EmployeeID]), employee.end());

            // delete from map
            mp[EmployeeID] = nullptr;
            cout << "Employee deleted successful" << endl << endl;
        } else {
            cout << "Deletion aborted" << endl << endl;
        }
    } else {
        cout << "No employee found with given ID" << endl;
        cout << endl;
    }
    saveFile();
}

//function to separate different employee information
void Employee::separator(std::string s) {
    int len = s.length();
    int prv = 0;

    std::string fN, lN, ID, gen, pos, dep, sal;
    int ag{};
    int count = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == ',') {
            if (count == 0) {
                int lth = i - 1 - prv + 1;
                fN = s.substr(prv, lth);
                count++;
                prv = i + 1;
            } else if (count == 1) {
                int lth = i - 1 - prv + 1;
                lN = s.substr(prv, lth);
                count++;
                prv = i + 1;
            } else if (count == 2) {
                int lth = i - 1 - prv + 1;
                ag = stoi(s.substr(prv, lth));
                count++;
                prv = i + 1;
            } else if (count == 3) {
                int lth = i - 1 - prv + 1;
                ID = s.substr(prv, lth);
                count++;
                prv = i + 1;
            } else if (count == 4) {
                int lth = i - 1 - prv + 1;
                gen = s.substr(prv, lth);
                count++;
                prv = i + 1;
            } else if (count == 5) {
                int lth = i - 1 - prv + 1;
                pos = s.substr(prv, lth);
                count++;
                prv = i + 1;
            } else if (count == 6) {
                int lth = i - 1 - prv + 1;
                dep = s.substr(prv, lth);
                count++;
                prv = i + 1;
            } else if (count == 7) {
                int lth = i - 1 - prv + 1;
                sal = s.substr(prv, lth);
                count++;
                prv = i + 1;
            }
        }
    }

    auto *tmp = new Employee(fN, lN, ag, ID, gen, pos, dep, sal);
    employee.push_back(tmp);
    mp[ID] = tmp;
}

//function to retrieve employee.txt file
void Employee::retrieveFile() {
    std::ifstream infile("employee.txt", std::ifstream::binary);
    std::string line;
    while (getline(infile, line)) {
        separator(line);
    }
}

//function to save employee.txt file
void Employee::saveFile() {
    ofstream outfile;
    outfile.open("employee.txt", ios::out | ios::trunc);
    for (auto info : employee) {
        outfile << info->firstName << "," << info->lastName << "," << info->age << "," << info->id << ","
                << info->gender << "," << info->position << "," << info->department << "," << info->salary << ","
                << endl;
    }
    outfile.close();
}

// function to sort employee information based on IDs or names
void Employee::sortFile(int a) {
    if (a == 1) {
        vector<Employee *> tmp = employee;
        sort(tmp.begin(), tmp.end(), compareID);
        for (auto info : tmp) {
            displayEmployeeInfo(info);
        }
    } else {
        vector<Employee *> tmp = employee;
        sort(tmp.begin(), tmp.end(), compareName);
        for (auto info : tmp) {
            displayEmployeeInfo(info);
        }
    }
}

//function to compare IDs
bool Employee::compareID(Employee *a, Employee *b) {
    std::string employee1 = a->id;
    std::string employee2 = b->id;
    if (employee1 <= employee2) {
        return true;
    } else {
        return false;
    }
}

// function to compare names
bool Employee::compareName(Employee *a, Employee *b) {
    std::string employee1 = a->firstName;
    std::string employee2 = b->firstName;
    if (employee1 <= employee2) {
        return true;
    } else {
        return false;
    }
}

// function to display options to perform
void Employee::loop() {

    while (true) {
        std::string option;
        cout << "*****************Menu*****************" << endl;
        cout << "Choose one of the options below:" << endl;
        cout << "1 => Display employee or all employees" << endl;
        cout << "2 => Add a new record" << endl;
        cout << "3 => Sort all employee" << endl;
        cout << "4 => Update record of an employee" << endl;
        cout << "5 => Delete record of an employee" << endl;
        cout << "6 => Exit from the program" << endl;
        cout << "**************************************" << endl;
        cout << "Choose an option: ";
        cin >> option;

        if (option == "1") {
            std::string a = "1";
            cout << "Enter 1 to find single employee or any other number to see all of the employees: ";
            cin >> a;
            search(a);
        } else if (option == "2") {
            add();
        } else if (option == "3") {
            cout << "Press 1 to to sort employees by IDs or press any other number to sort by names: ";
            std::string sortOption;
            cin >> sortOption;
            if (sortOption == "1") {
                cout << endl;
                sortFile(1);
            } else {
                cout << endl;
                sortFile(100);
            }
        } else if (option == "4") {
            update();
        } else if (option == "5") {
            remove();
        } else if (option == "6") {
            char confirmation;
            cout << "(Y/y) to confirm: ";
            cin >> confirmation;

            if (confirmation == 'Y' || confirmation == 'y')
                cout << "Exited Successful." << endl << endl;
            break;
        } else {
            cout << "Invalid Input" << endl;
        }
    }
    saveFile();
}

