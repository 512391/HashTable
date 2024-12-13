#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include "StudentGenerator.h"
/*
  Author: Jay Williamson
  Date: 10/24/2024
  This program maintains a list of students which can be added to or deleted from
  you can also print the students and type QUIT to exit
 */

using namespace std;
using namespace LinkedList;
using namespace StudentTools;

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

int checkAmountOfElementsInLinkedList(Node* node, int amountSoFar)
{
  if(node == nullptr)
    {
      return 0;
    }
  if(node->getNext() == nullptr)
    {
      return amountSoFar+1;
    }
  else
    {
      checkAmountOfElementsInLinkedList(node->getNext(), amountSoFar+1);
    }
}

bool checkIfShouldReorganize(Node** hashTable, int hashTableMax)
{
  int amountOfNodes = 0;
  
  for(int i = 0; i < hashTableMax; i++)
          {
            if(checkAmountOfElementsInLinkedList(hashTable[i], 0) >= 3)
              {
                return true;
              }
	    else
	      {
		amountOfNodes += checkAmountOfElementsInLinkedList(hashTable[i], 0);
	      }
          }
  if(amountOfNodes >= (hashTableMax/2))
    {
      return true;
    }
return false;
}

Node** reorganizeHashTable(Node** hashTable, StudentGenerator sg, int oldSize, int newSize)
{
  Node** tempHashTable = new Node*[newSize];

  for(int i = 0; i < newSize; i++)
    {
      tempHashTable[i] = nullptr;
    }

  int amountOfStudents = 0;
  
  for(int i = 0; i < oldSize; i++)
    {
	  Node* st = hashTable[i];
  
	  while(st != nullptr)
	    {
	      amountOfStudents++;
	      int hash = sg.hashStudent(st->getStudent(), newSize);
   
              if(tempHashTable[hash] == nullptr)
                {
                  tempHashTable[hash] = st;
                }
              else
                {
                  addNode(tempHashTable[hash], st);
		}
 
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

	  
	  while(checkIfShouldReorganize(hashTable, hashTableMax))
	    {
	      hashTable = reorganizeHashTable(hashTable, sg, hashTableMax, hashTableMax*2);
	      hashTableMax = hashTableMax*2;
	    }
	}//Checks if it should print the students
      else if(strncmp(input, "PRINT", 5) == 0)
	{
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
