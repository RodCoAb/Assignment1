// ASU CSE310 Spring 2022 Assignment #1
// Name: Rodrigo Corrales
// ASU ID: 1216550582
// ASU Email Address: rcorral7@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

void printMenu();

int main()
 {
       // local variables, can be accessed anywhere from the main method
       char input1 = 'Z';
       string inputInfo;
       string firstName, lastName, newFullName;
       int id;
       double gpa;
       string line;
       bool success = false;

       // instantiate a Linked List object
       LinkedList* list1 = new LinkedList();

       printMenu();

       do  // will ask for user input
        {
           cout << "\nWhat action would you like to perform?\n";
           cin.get(input1);
           input1 = toupper(input1);    //change it to upper case
           cin.ignore(20, '\n');        //flush the buffer

           // matches one of the cases
           switch (input1)
           {
             case 'A':   //Add the student
               cout << "Please enter the student information:\n";
               cout << "Enter student first name:\n";
               getline(cin, firstName);
               cout << "Enter student last name:\n";
               getline(cin, lastName);
               cout << "Enter student id:\n";
               cin >> id;
               cin.ignore(20, '\n');
               cout << "Enter student gpa:\n";
               cin >> gpa;
               cin.ignore(20, '\n'); //flush the buffer

               success = list1->addStudent(firstName, lastName, id, gpa);

               if (success == true)
                cout << "Student \"" << firstName << " " << lastName << "\" is added\n";
               else
                cout << "Student \"" << firstName << " " << lastName << "\" is NOT added\n";
               break;

            case 'C':  //Change student name
                cout << "Please enter the student ID which you want to change the name:\n";
                cin >> id;
                cin.ignore(20, '\n'); //flush the buffer
                cout << "\nPlease enter student new full name: \n";
                getline(cin, newFullName);
                if(list1->findStudent(id) == true)
                {
                   list1->changeStudentName(id, newFullName);
                   cout << "Student ID #: " << id << " name was changed" << endl;
                }
                else
                {
                   cout << "Student is NOT inside the list, cannot change student name." << endl;
                   cout << "Student ID #: " << id <<" does not exist" << endl;
                }
                
                break;

             case 'D':   //Display all students
               list1->printStudentList();
               break;

             case 'E':   //Display students by last name
                cout << "\nPlease enter student last name which you want to display:\n";
                cin >> lastName;
                cin.ignore(20, '\n');
                list1->printStudentListByLastName(lastName);
               break;

              case 'F':   //Find a student
                cout << "\nPlease enter student id you want to search:\n";
                cin >> id;
                cin.ignore(20, '\n');   //flush the buffer
                if(list1->findStudent(id) == true)
                {
                   cout << "Student with ID #: " << id <<" was found" << endl;
                }
                else
                {
                   cout << "Student with ID #: " << id <<" was NOT found" << endl;
                }
                break;

             case 'P':  //Update a student gpa
                cout << "\nPlease enter the student id you want to update the gpa:\n";
                cin >> id;
                cin.ignore(20, '\n');

                if(list1->findStudent(id) == true)
                {
                   cout << "\nPlease enter the new gpa: " << endl;
                   cin >> gpa;
                   cin.ignore(20, '\n');
                   if(list1->updateStudentGpa(id, gpa))
                   {
                     cout << "Student with ID #: " << id  << " gpa was updated" << endl;
                   }
                }
                else
                {
                   cout << "Student with ID #: " << id  << " does NOT exist" << endl;
                   cin >> gpa;
                   cin.ignore(20, '\n');
                }
                break;

            case 'R':  //Remove a student from the list by ID
               cout << "\nPlease enter the student ID to remove:\n";
               cin >> id;
               cin.ignore(20, '\n');   //flush the buffer
               //Write your own code to finish this case
               success = list1->removeById(id);
               if(success)
               {
                  cout << "Student with ID #: " << id << " was removed\n";
               }
               else
                  cout << "Student with ID #: " << id << " does NOT exist\n";
               break;

            case 'S':  //Remove a student from the list by name
               cout << "Please enter student first name you want to remove:\n";
               getline(cin, firstName);
               cout << "Please enter student last name you want to remove:\n";
               getline(cin, lastName);

               //Write your own code to finish this case
               if (list1->removeByName(firstName, lastName) == true)
               {
                  cout << "Student with name: " << firstName << " " << lastName << " was removed";
               }
               else
               {
                  cout << "No such student name found." << endl;
                  cout << "Student with name: " << firstName << " " << lastName << " does NOT exist";
               }
               break;

             case 'Q':   //Quit
                 delete list1;
                 break;

             case '?':   //Display Menu
                 printMenu();
                 break;

             default:
               cout << "Unknown action\n";
               break;
            }
        } while (input1 != 'Q');
      return 0;
   }

  /** The method printMenu displays the menu to a user**/
  void printMenu()
   {
     cout << "Choice\t\tAction\n";
     cout << "------\t\t------\n";
     cout << "A\t\tAdd A Student\n";
     cout << "C\t\tChange A Student Name\n";
     cout << "D\t\tDisplay All Students\n";
     cout << "E\t\tDisplay Students by Last Name\n";
     cout << "F\t\tFind A Student\n";
     cout << "P\t\tUpdate Student GPA\n";
     cout << "R\t\tRemove Student by ID\n";
     cout << "S\t\tRemove Student by Name\n";
     cout << "Q\t\tQuit\n";
     cout << "?\t\tDisplay Help\n\n";
  }
