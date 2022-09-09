#ifndef EMS_HEADERS_H
#define EMS_HEADERS_H

#pragma once
#include <string>

class Employee {
 private:
  int age;
  std::string id;
  std::string firstName;
  std::string lastName;
  std::string gender;
  std::string position;
  std::string department;
  std::string salary;

 public:
  Employee(std::string fN, std::string lN, int ag, std::string ID, std::string gen,
           std::string pos, std::string dep, std::string sal);

  static void add();
  static void displayEmployeeInfo(Employee *info);
  static void update();
  static void search(const std::string &);
  static void remove();
  static void retrieveFile();
  static void saveFile();
  static void separator(std::string);
  static void sortFile(int);
  static bool compareID(Employee *a, Employee *b);
  static bool compareName(Employee *a, Employee *b);
  static void loop();

};

#endif //EMS_HEADERS_H
