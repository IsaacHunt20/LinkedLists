#include <iostream>
#include <string.h>

using namespace std;

typedef struct employee
{
    char firstName[21];
    char lastName[21];
    int  age;
    int phoneNumber;
    struct employee* nextptr;
    struct employee* prevptr;
} employee_t;

void AddEmployee();
void DeleteEmployee();
void PrintForward(employee_t* headptr);
void PrintBackward(employee_t* tailptr);

employee_t* headptr = nullptr; //First node
employee_t* nodeptr = nullptr; //current node
employee_t* newptr = nullptr;  //newest node
employee_t* lastptr = nullptr; //ref to the last ptr
employee_t* tailptr = nullptr; //always last item 

int main(void)
{
    char option;
    bool quit = false;
    while (quit == false)
    {
        cout << "Linked List using Structures" << endl;
        cout << "1. Add New Employee" << endl;
        cout << "2. List Employees" << endl;
        cout << "3. Delete Employee" << endl;
        cout << "4. Print Backward" << endl;
        cout << "5. Quit" << endl << endl;
        cout << "Enter Choice: ";
        cin >> option;
        switch (option)
        {
        case '1': 
            AddEmployee(); // Add List
            break;
        case '2':  
            PrintForward(headptr); // List head to tail 
            break;
        case '3':  
            DeleteEmployee(); // Delete List Node
            break;
        case '4':
           PrintBackward(tailptr); //list tail to head
            break;
        case '5':
            quit = true;
            break;
        default:
            break;
        }
    }
}

void AddEmployee() 
{
    newptr = ( employee_t* )malloc( sizeof( employee_t ));

    if (newptr != nullptr) 
    {
        cout << "enter the first name for new employee: \n";
        cin >> newptr -> firstName;

        cout << "enter the lastname: \n";
        cin >> newptr->lastName;

        cout << "Enter the age for employee: \n";
        cin >> newptr->age;

        cout << "Enter phone # for employee: \n";
        cin >> newptr->phoneNumber;
        //insertion type was not specified in the assignemnt so I appended new entries to the end of the list. 
        newptr->nextptr = nullptr;

        if (headptr == nullptr)
        {
            //head is newptr bc its the only node in the list
            headptr = newptr;
            //Only one item in list so prev and next are null 
            newptr->prevptr = nullptr;
            newptr->nextptr = nullptr;
        }
        else 
        {
            //start nodeptr at the beginning of list and iterate until it finds a null
            nodeptr = headptr;
            while (nodeptr->nextptr != nullptr)
            {
                //moves nodeptr to end of list
                nodeptr = nodeptr->nextptr;
            }
            //sets the end of list equal to new item 
            nodeptr->nextptr = newptr;
            //the new item prevptr points to where the iteration stoped 
            newptr->prevptr = nodeptr;
            //the new items next ptr is null bc its the end of list
            newptr->nextptr = nullptr;
            //tail will be equal to all new items becasue appedning to the end
            tailptr = newptr;
        }
        cout << "Node (" << newptr->firstName << " " << newptr->lastName << ") Added " << endl;
    }
}

void DeleteEmployee()
{
    int phoneNumber;
    char lastName[21];
    bool found = false;

    PrintForward(headptr);
    
    cout << "Enter phone number of employee to delete: ";
    cin >> phoneNumber;

    cout << "last name of employee to delete: ";
    cin >> lastName;
    //Start at the beggining of the list iterate through until it finds the coresponding node to the entered data
    nodeptr = headptr;
    while ((nodeptr != nullptr) && (found == false))
    {
        if (phoneNumber == nodeptr->phoneNumber && (strcmp(lastName, nodeptr->lastName) == 0)) 
        {
            //if the first item make the next item the new head by making the headptr's nextptr the new headptr
            if (headptr == nodeptr)
                headptr = headptr->nextptr;

            //If the node is in the middle current, the nextptr pts to the prevptr of node && and the nodes prevptr becomes the new nextptr 
            if (nodeptr->nextptr != nullptr)
                nodeptr->nextptr->prevptr = nodeptr->prevptr;

            //if the prev ptr is not null but the nextptr is we are at the end of the list so make node to be deleted prevptr point to null
            if (nodeptr->prevptr != nullptr)
                nodeptr->prevptr->nextptr = nodeptr->nextptr;
            free(nodeptr);
            found = true;
        }

        //else advance through the list 
        else 
        {
            lastptr = nodeptr;
            nodeptr = nodeptr->nextptr;
        }
    }
}

void PrintForward(employee_t* headptr) 
{
    cout << "*****Current Employee List****\n";

    //start at head
    nodeptr = headptr;
    //iterate until null
    while (nodeptr != nullptr) 
    {
        cout << "Employee: " << nodeptr->lastName << ", " << nodeptr->firstName << " (" << nodeptr->age << ")" << " (" << nodeptr->phoneNumber << ")" << endl;
        //move the nodeptr to current nodes nextptr
        nodeptr = nodeptr->nextptr;
    }
    cout << endl;
}

void PrintBackward(employee_t* tailptr)
{
    cout << "*****Current Employee List****\n";
    nodeptr = tailptr;

    while (nodeptr != nullptr)
    {
        cout << "Employee: " << nodeptr->lastName << ", " << nodeptr->firstName << " (" << nodeptr->age << ")" << " (" << nodeptr->phoneNumber << ")" << endl;
        nodeptr = nodeptr->prevptr;
    }
    cout << endl;
}