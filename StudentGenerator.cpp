#include<iostream>
#include"StudentGenerator.h"
#include <fstream>
#include<cstdlib>
#include<cstring>
#include<ctime>


/*
  author: Jay Williamson
  date: 12/19/2024
  this class generates students randomly and returns them
 */

using namespace std;
using namespace LinkedList;
using namespace StudentTools;

//constructor for random students struct to return the students
RandomStudents::RandomStudents(int amount)
{
  RandomStudents::nodes = new Node*[amount];
}

//constructor for the student generator
StudentGenerator::StudentGenerator()
{
//gets teh first and last names
  ifstream firstNamesFile("FirstNames.txt");
    ifstream lastNamesFile("LastNames.txt");
    StudentGenerator::currentId = 0;

    cout << endl;

//makes new arrays for the names
    for(int i = 0; i < 20; i++)
      {
	StudentGenerator::firstNames[i] = new char[21];
	StudentGenerator::lastNames[i] = new char[21];
      }

//this reads all of the first names
  if(firstNamesFile.is_open())
         {
	   int i = 0;
	   int j = 0;
	//gets the current letter
           while(firstNamesFile.get(StudentGenerator::firstNames[i][j]))
	     { 
		//checks if it should move to the next name
	       if(StudentGenerator::firstNames[i][j] == '\n')
	         {
		   i++;
		   j = 0;
	         }
	       else
		 {
		   j++;
		 }
	     }
         }
//this reads all of the last names
  if(lastNamesFile.is_open())
         {
           int i = 0;
           int j = 0;
           //gets current letter
           while(lastNamesFile.get(StudentGenerator::lastNames[i][j]))
             {
		//checks if it should move to next name
               if(StudentGenerator::lastNames[i][j] == '\n')
                 {
                   i++;
                   j = 0;
                 }
               else
                 {
                   j++;
                 }
             }
	 }
}

//this makes random students
RandomStudents* StudentGenerator::makeStudents(int amount)
{
//seeds the random
  srand(time(0));
//makes the return object of students
  RandomStudents* randomStudents = new RandomStudents(amount);
//makes the amount fo students needed
  for(int i = 0; i < amount; i++)
    {
//gets index and length of names
      int firstNameLength = rand() % 20 + 1;
      int secondNameLength = rand() % 20 + 1;

//this inputs the names to the student
      char firstName[20] = {};
      strncpy(firstName, StudentGenerator::firstNames[firstNameLength-1], firstNameLength);
      char lastName[20] = {};
      strncpy(lastName, StudentGenerator::lastNames[secondNameLength-1], secondNameLength);
//randomizes other aspects about the student
       float GPA = (float)(rand()%4);
       int id = StudentGenerator::currentId;
       int randomSeed = rand() % 100 + 47;

//increases the id
       StudentGenerator::currentId++;
       
       //creates the new students
       Student* newStudent = new Student();

       //copies all of the info into the student
       strcpy(newStudent->firstName, firstName);
       strcpy(newStudent->lastName, lastName);
       newStudent->GPA = GPA;
       newStudent->id = id;
       newStudent->lastNameLength = secondNameLength;
       newStudent->firstNameLength = firstNameLength;
       newStudent->randomSeed = randomSeed;
       
       randomStudents->nodes[i] = new Node(newStudent);
       randomStudents->nodes[i]->setNext(nullptr);
    }
  return randomStudents;
}

//gets the hash value for the student
int StudentGenerator::hashStudent(Student* student, int maxNum)
{
  int hash = (student->id * student->randomSeed) % (maxNum+1);
 
  return hash;
}
