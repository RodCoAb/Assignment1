// ASU CSE310 Spring 2022 Assignment #1
// Name: Rodrigo Corrales
// ASU ID: 1216550582
// ASU Email address: rcorral7@asu.edu
// Description: Header file contaiining functions for a linked list.

#include <iostream>
#include <iomanip>          //used to control the format of the output
#include <string>

using namespace std; 

//Student represents a student information
struct Student
{
    string firstName, lastName;
    int id;
    double gpa;
    struct Student* next;
};

//class LinkedList will contains a linked list of Students. This is class definition
class LinkedList
{
    private:
        struct Student* head;
        
    public:
        LinkedList(); // DONE. I think it is right.
        ~LinkedList(); // DONE. I think it is right.
        bool findStudent(int studentId); // DONE. I think it is right.
        bool addStudent(string firstName, string lastName, int studentId, double gpa); // DONE. I think it is right.
        bool removeById(int studentId); // DONE. I think it is right.
        bool removeByName(string firstName, string lastName); // DONE. I think it is right.
        bool changeStudentName(int studentId, string newFullName); // DONE. I think it is right.
        bool updateStudentGpa(int studentId, double newGpa); // DONE. I think it is right.
        void printStudentListByLastName(string oneLastName); // I think it needs more work.
        void printStudentList(); // DONE. I think it is right.
        void alphabeticalOrder(); // DONE. To be used to facilitate other methods.
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList() 
{
    head = NULL; // Initializes the head of the linked list to null.
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
	int nodeCounter = 0; // Variable that is used to keep track of the deleted nodes.
    Student* temp = head; // Creating a temporary pointer to help traverse the linked list.
    while(head != NULL) // While the head is not null, iterates through the list.
    {
        temp = head->next; 
        delete temp; // Deletes the node to which the head pointer points to.
        head = temp; // Head pointer now points to temp node (i.e the next item in the linked list.)
        nodeCounter++; // Increments the counter that keeps track of how many items are deleted at the very end.
    }
    cout<< "The number of deleted student is: " << nodeCounter <<"\n"; // Print statement that keeps track of how many students were removed at the end.
}

void LinkedList::alphabeticalOrder() // Method made by me that sorts the Students by the criteria specified, Last name first, then first name and then by id if they happen to have the exact name.
{
    Student* temp1; // Initializes temp pointer.
    Student* temp2; // Initializes temp pointer.

   if(head == NULL || head->next == NULL) //checking if there are 0 or 1 entries in list, doesnt need to be sorted
    {
        return; 
    }
    temp1 = head; // Sets temp pointer equal to the head.
    while(temp1->next != NULL) // Iterates through the first pointer.
    {
        string student1Compare = temp1->lastName + temp1->firstName + to_string(temp1->id); // Saves the string criteria in order for temp1 pointer.
        temp2 = temp1->next; // Gives temp2 a value.
        while (temp2 != NULL) // Iterates through the second pointer.
        {
            string student2Compare = temp2->lastName + temp2->firstName + to_string(temp2->id); // Saves the string criteria in order for temp2 pointer.
            if(student1Compare.compare(student2Compare) > 0) // If string 1 is after string 2, we must swap
            {
                Student* temp3 = new Student(); // temp student to use in the swap. Below, we copy the details from string 1 to the temp student.
                temp3->firstName = temp1->firstName; 
                temp3->lastName = temp1->lastName;
                temp3->id = temp1->id;
                temp3->gpa = temp1->gpa;

                temp1->firstName = temp2->firstName; // Temp1 now holds the details/values of temp2.
                temp1->lastName = temp2->lastName;
                temp1->id = temp2->id;
                temp1->gpa = temp2->gpa;

                temp2->firstName = temp3->firstName; // Temp2 will now hold the details/values of temp3.
                temp2->lastName = temp3->lastName;
                temp2->id = temp3->id;
                temp2->gpa = temp3->gpa;
                delete temp3;
            }
            temp2 = temp2->next; // Iterates through the temp2 pointer.
        }
        temp1 = temp1->next; // Iterates through the temp1 pointer.
    }
}
 
//A function to identify if the parameterized Student is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::findStudent(int studentId)
{
    Student* temp = head; // temp pointer referencing the head.
    if (head == NULL) // If the list is empty.
    {
        return false;
    }
    while(temp != NULL) // Approach. Needs to be worked on further. Need to find a way to specify that it is the specific object id.
    {
        if (temp->id == studentId) // If the id of that student is found.
        {
            return true;
        }
        temp = temp->next; // May not be needed since we are not traversing the list.
    }
    return false; // Returns false if the id is not found at all (i.e list is empty.)
}

//This function creates a new node and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of Students by their names, i.e.
//first by last name, then by first name. Note: each Student has a unique id, but
//may have the same first and last name with another Student. In case two Students have same names
//they should be inserted according to the increasing order of their IDs.
//Return true if it is successfully inserted and false in case of failures.
bool LinkedList::addStudent(string firstName, string lastName, int studentId, double gpa)
{
    Student* newStudent = new Student(); // Allocates memory space for the new node in the list.
    newStudent->firstName = firstName; // Sets the first name of student.
    newStudent->lastName = lastName; // Sets the last name of student.
    newStudent->id = studentId; // Sets the student id.
    newStudent->gpa = gpa; // Sets the student gps.
    newStudent->next = NULL;
    Student* tempNode = head;
///////////////////////////////////////////////////////////////////////////// Creates the new student above.
    if (head == NULL) // If the list is empty, we will add newStudent to the head of the list.     
    {
        head = newStudent; // Head of the list becomes newStudent.
        return true; 
    }
    while (tempNode->next != NULL) // Helps iterate through the list.
    {  
        if(tempNode->id == studentId) // Checks to see if the Student is already in the list. Avoids duplicates.
        {
            return false;
        }
        tempNode = tempNode->next; // Moves onto the next tempNode.
    }
    tempNode->next = newStudent; // sets tempNode->next to the newStudent.
    alphabeticalOrder(); // Method to sort all added students in the specified criteria. 
   return true;
}

//Removes the specified student from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeById(int studentId) 
 {
	Student* tempStudent1 = head; // Temp pointer references the head.
    if (head == NULL) // Boundary checking; In case the list is empty.
    {
        return false; // If the list is empty nothing happens
    }
    if(head->id == studentId) // If the id matches.
    {
        tempStudent1 = head->next; 
        delete head; // deletes the head.
        head = tempStudent1;
        alphabeticalOrder(); // Sorts everything again.
        return true;
    }
    while (tempStudent1->next != NULL) // Helps iterate through the list.
    {
        if (tempStudent1->next->id == studentId) // If the id matches at this position.
        {
            Student *tempNode = tempStudent1->next->next;
            delete tempStudent1->next;
            tempStudent1->next = tempNode;
            alphabeticalOrder();
            return true;
        }
        tempStudent1 = tempStudent1->next; // Moves onto the next node.
    }    
    return false;
 }

//Removes the given Student from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all Students with
//the same first and last name should be removed from the list.
bool LinkedList::removeByName(string firstName, string lastName)
{
    Student* temp = head; // Temp pointer referencing the head.
    bool remove = false;
    if (head->firstName == firstName && head->lastName == lastName) // Checks to see if we remove at the head.
    {
        if (head->next != NULL) 
        {
            if (head->next->firstName == firstName && head->next->lastName == lastName)
            {
                head = head->next;
            }
            head = head->next;
        }
        remove = true;
    }
    while (temp->next != NULL) // Helps iterate through the list.
    {
        if (temp->next->firstName == firstName && temp->next->lastName == lastName) // Checks to see if the name matches at a different position.
        {
            temp->next = temp->next->next;
            remove = true;
        }
        else
        {
            temp = temp->next;
        }
    }
    return remove; 
}

//Modifies the data of the given Student. Return true if it modifies successfully and
//false otherwise. Note: after changing a Student name, the linked list must still be
//in correct alphabetical order.
bool LinkedList::changeStudentName(int studentId, string newFullName)
{
    Student* temp = head; // Temporary pointer referencing the head.
    
    string delimiter = " "; // Sets the delimiter.
    size_t spaceIndex = newFullName.find(delimiter); // Gets the index at the delimiter.
    string firstName = newFullName.substr(0,spaceIndex); // Scores the first half into first name.
    string lastName = newFullName.substr(spaceIndex + 1, newFullName.back()); // Scores the second half into the last name.
    if (head == NULL) // Checks if the list is null.
    {
        return false;
    }
    while (temp != NULL) // Helps iterate through the list.
    {
        if (temp->id == studentId) // Looks for an id match.
        {
            temp->firstName = firstName; 
            temp->lastName = lastName;
            alphabeticalOrder(); // Reorganizes the list.
            return true;
        }
        temp = temp->next; // Moves onto the next nodes.
    }
    return false;
}
bool LinkedList::updateStudentGpa(int studentId, double newGpa)
{
    Student* update = head; // Temp pointer referencing head.
    if (head == NULL) // Checks if list is empty.
    {
        return false;
    }
    while(update != NULL) // Helps iterate through the list.
    {
        if (update->id == studentId) // Checks if the id match.
        {
            update->gpa = newGpa; // updates gpa.
            return true;
        }
        update = update->next;
    }
    return false;
}
//Prints all students in the list with the same last name.
void LinkedList::printStudentListByLastName(string oneLastName) // THIS METHOD WORKS.
{
    bool found = false; // Boolean to be used later.
    Student* theStudent = head; // Pointer referencing the head.
    if(theStudent == NULL) // checks if the list is empty.
    {
		cout << "The list is empty\n";
		return;
	}
    else
    {
        while (theStudent != NULL) // Helps iterate through the list.
        {
            if(theStudent->lastName == oneLastName) // If the last name is a match.
            {
                cout << left << setw(12) << theStudent->firstName
                    << left << setw(12) << theStudent->lastName
                    << right << setw(8) << theStudent->id
                    << setw(10) << fixed << setprecision(2) << theStudent->gpa << "\n";
                    found = true;
            }
                theStudent = theStudent->next;
        }
        if (!found)
        {
            cout << "No students with the specified last name found.";
        }
    }
}

//Prints all students in the linked list starting from the head node.
void LinkedList::printStudentList() // THIS METHOD WORKS.
{
    Student* temp = head; // Temp pointer referencing the head.
 	if(temp == NULL) // If list is empty.
    {
		cout << "The list is empty\n";
		return;
	}
    else
    {
        while (temp != NULL) // Helps iterate through the list.
        {
            cout << left    << setw(12) << temp->firstName
             << left    << setw(12) << temp->lastName
             << right   << setw(8) << temp->id
             << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";
             temp = temp->next; // Moves onto the next student in the list.
        }   
    }
}