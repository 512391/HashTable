#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include "StudentGenerator.h"
/*
  Author: Jay Williamson
  Date: 12/19/2024
  This program maintains a hash table of students which can be added to or deleted from
  you can also print the students and type QUIT to exit
 */

using namespace std;
using namespace LinkedList;
using namespace StudentTools;

Student* makeStudent()
{
  //variables for the student
  char* firstName = new char[21];
  char* lastName = new char[21];
  float GPA = 0;
  int id = 0;

  //gets the students info
          cout << "Enter Student First Name\n";
          cin >> firstName;
	  cout << "Enter Student Last Name\n";
          cin >> lastName;
          cout << "Enter GPA\n";
          cin >> GPA;
          cout << "Enter ID\n";
          cin >> id;

	  //creates the new students
          Student* newStudent = new Student();

	  newStudent->firstNameLength = strlen(firstName);
	  
	  //copies all of the info into the student
          strcpy(newStudent->firstName, firstName);
	  strcpy(newStudent->lastName, lastName);
	  
          newStudent->GPA = GPA;
          newStudent->id = id;
	  
	  return newStudent;
}

//this prints all of the students in the list
void printNames(Node* head)
{
  //checks if there is a list at all
  if(head == nullptr)
    {
      return;
    }

  //gets the student once to reuse
  Student* currentStudent = head->getStudent();

  //outputs the stuff
  cout << "ID: " << currentStudent->id << endl;
  
  cout << "GPA: " << currentStudent->GPA << endl;
  
  cout << "First Name: ";
  for(int i = 0; i < currentStudent->firstNameLength; i++)
    {
      cout << currentStudent->firstName[i];
    }

  cout << endl;
  
  cout << "Last name: " << currentStudent->lastName << endl;

  //checks if it should get the next student if there is one
  if(head->getNext() != nullptr)
    {
      cout << endl;
      cout << "COLLISION" << endl;
      cout << endl;
      //if there is one it prints the next persons stuff
      printNames(head->getNext());
    }
  else
    {
      //outherwise it just exits the recursion
      cout << endl;
      return;
    }
}

//this deletes a node based on an id number
Node* deleteName(Node* newHead, Node* head, Node* previous, int toDelete)
{
  //checks if ther is a list at all
  if(newHead == nullptr)
    {
      //gets out if there is no list
      return newHead;
    }

  //this accesses the next node to use
  Node* next = head->getNext();

  //this checks if the node it the one to delete
  if(head->getStudent()->id == toDelete)
    {
      //this checks whether it is in the middle of the list
      if(previous != nullptr && next != nullptr)
        {
	  //this corrects the list
          previous->setNext(next);
	  //this deleted the node it is on
          delete head;
	  //continues the search
          deleteName(newHead, next, previous, toDelete);
        }//this checks if it is the end of the list
      else if(previous != nullptr)
        {
	  //sets the previous one to the new end of the list
          previous->setNext(nullptr);
	  //deletes current node
          delete head;
	  //returns out
          return newHead;
        }
      else//this case is for the beginning
        {
	  //deletes the current node
          delete head;
	  //checks if it is the beginning and end
          if(next == nullptr)
            {
	      //if it is the only element it returns a nullptr as there is no list
              return nullptr;
            }
	  //otherwise it continues searching with the next element as the new head
          deleteName(next, next, nullptr, toDelete);
        }
    }//if it is not the one to delete and there are more elements it continues searching
  else if(head->getNext() != nullptr)
    {
      deleteName(newHead, next, head, toDelete);
    }
  else//if it is the end of the list and it is not the one to delete it returns the new head in case the first element was deleted
    {
      return newHead;
    }
}

//this adds a node to the linked list
void addNode(Node* head, Node* toAdd)
{
  if(head == nullptr)
    {
      cout << "head null";
    }
  //if it is at the end of the list it sets the toAdd to the end of the list
  if(head->getNext() == nullptr)
    {
      //sets the toAdd tot he end of the list
      head->setNext(toAdd);
      return;
    }
  else//if it is not at the end of the list it keeps traversing to the end
    {
      addNode(head->getNext(), toAdd);
    }
}

//this gets the amount of elements in a certain linked list
int checkAmountOfElementsInLinkedList(Node* node, int amountSoFar)
{
//checks if the start if null if so it is 0 lone
  if(node == nullptr)
    {
      return 0;
    }//if the next is null just return the amouns so far plus the current
  if(node->getNext() == nullptr)
    {
      return amountSoFar+1;
    }
  else //if there are more call recursively
    {
      checkAmountOfElementsInLinkedList(node->getNext(), amountSoFar+1);
    }
}

//THis checks if it shoudl reorganize the hashtable
bool checkIfShouldReorganize(Node** hashTable, int hashTableMax)
{
  int amountOfNodes = 0;

//goes through the hashtable
  for(int i = 0; i < hashTableMax; i++)
          {
	//checks if any of the lists are longer than three
            if(checkAmountOfElementsInLinkedList(hashTable[i], 0) >= 3)
              {
                return true;
              }
	    else
	      {
		amountOfNodes += checkAmountOfElementsInLinkedList(hashTable[i], 0);
	      }
          }
	//checks if over half the table is filled
  if(amountOfNodes >= (hashTableMax/2))
    {
      return true;
    }
return false;
}

//this doubles and reorganizes the hash table
Node** reorganizeHashTable(Node** hashTable, StudentGenerator sg, int oldSize, int newSize)
{
//makes a temp hash table to hold the new data
  Node** tempHashTable = new Node*[newSize];

//resets the new hash table
  for(int i = 0; i < newSize; i++)
    {
      tempHashTable[i] = nullptr;
    }
//checks the amount of students to make sure there are as much as started
  int amountOfStudents = 0;

//goes through the old hashtable
  for(int i = 0; i < oldSize; i++)
    {
	  Node* st = hashTable[i];
  //puts the students into the new hashtable by rehashing them with the new size
	  while(st != nullptr)
	    {
	      amountOfStudents++;
		    //hashes the student
	      int hash = sg.hashStudent(st->getStudent(), newSize);

	//this adds it to the new table
              if(tempHashTable[hash] == nullptr)
                {
                  tempHashTable[hash] = st;
                }
              else
                {
                  addNode(tempHashTable[hash], st);
		}
 //moves to the next node
	      Node* tempSt = st;
	      st = st->getNext();
	      tempSt->setNext(nullptr);
	    }
    }

  delete hashTable;

  return tempHashTable;
}

int main()
{
  StudentGenerator sg;
  Node** hashTable = nullptr;

  hashTable = new Node*[100];
  int hashTableMax = 100;

//clears hashtable
  for(int i = 0; i < hashTableMax; i++)
    {
      hashTable[i] = nullptr;
    }
  
  //the input
  char input[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};
  const char emptyInput[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};

  //gets initial input
  cout << "Enter one of the following inputs, PRINT. ADD, DELETE, or QUIT \n";
  cin >> input;

//checks if it should quit and end
  while(strncmp(input, "QUIT", 4) != 0)
    {
      //Checks if it is adding a student
      if(strncmp(input, "ADD", 3) == 0)
	{
	  int addingInput = 0;
	  cout << "Press 1 for adding random or 2 for adding specific" << endl;
	  cin >> addingInput;
	  if(addingInput == 1)
	    {
	      int amountOfStudents = 0;

	      cout << "How many would you like to add: \n";
	      cin >> amountOfStudents;
	  
	      RandomStudents* rs = sg.makeStudents(amountOfStudents);
	      for(int i = 0; i < amountOfStudents; i++)
		{
		  Node* st = rs->nodes[i];

		  //adds the student that was made to the linkedList
		  int hash = sg.hashStudent(st->getStudent(), hashTableMax);
		  if(hashTable[hash] == nullptr)
		    {
		      hashTable[hash] = st;
		    }
		  else
		    {
		      addNode(hashTable[hash], st);
		    }
		}
	    }
	  else
	    {
	      Node* st = new Node(makeStudent());
	      int hash = sg.hashStudent(st->getStudent(), hashTableMax);

	      if(hashTable[hash] == nullptr)
                {
                  hashTable[hash] = st;
                }
              else
                {
                  addNode(hashTable[hash], st);
                }

	    }
	  //checks if should reorganize
	  while(checkIfShouldReorganize(hashTable, hashTableMax))
	    {
	      hashTable = reorganizeHashTable(hashTable, sg, hashTableMax, hashTableMax*2);
	      hashTableMax = hashTableMax*2;
	    }
	}//Checks if it should print the students
      else if(strncmp(input, "PRINT", 5) == 0)
	{
		//goes through all hashes and prints
	  for(int i = 0; i < hashTableMax; i++)
	    {
	      cout << "hash: " << i << endl;
	      
	      printNames(hashTable[i]);
	    }
	}//Checks if it should delete a student
      else if(strncmp(input, "DELETE", 6) == 0)
	{
	  int id = 0;
	  //gets an id to check for
	  cout << "Enter an ID to delete \n";
	  cin >> id;

	  for(int i = 0; i < hashTableMax; i++)
	    {
	      hashTable[i] = deleteName(hashTable[i], hashTable[i], nullptr, id);
	    }
	}

      //clears the input array
      for(int i = 0; i < 7; i++)
	{
	  input[i] = emptyInput[i]; 
	}

      //gets next input
      cout << "Enter one of the following inputs, PRINT. ADD, DELETE, or QUIT \n";
      cin >> input;
    }
  
  cout << "bye bye";

  return 0;
}
