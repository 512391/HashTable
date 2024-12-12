#include<iostream>
#include"StudentGenerator.h"
#include <fstream>
#include<cstdlib>
#include<cstring>
#include<ctime>

using namespace std;
using namespace LinkedList;
using namespace StudentTools;

RandomStudents::RandomStudents(int amount)
{
  RandomStudents::nodes = new Node*[amount];
}

StudentGenerator::StudentGenerator()
{
  ifstream firstNamesFile("FirstNames.txt");
    ifstream lastNamesFile("LastNames.txt");
    StudentGenerator::currentId = 0;

    cout << endl;
    
    for(int i = 0; i < 20; i++)
      {
	StudentGenerator::firstNames[i] = new char[21];
	StudentGenerator::lastNames[i] = new char[21];
      }
    
  if(firstNamesFile.is_open())
         {
	   int i = 0;
	   int j = 0;
           while(firstNamesFile.get(StudentGenerator::firstNames[i][j]))
	     { 
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

  if(lastNamesFile.is_open())
         {
           int i = 0;
           int j = 0;
           
           while(lastNamesFile.get(StudentGenerator::lastNames[i][j]))
             {
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
  for(int i = 0; i < 20; i++)
      {
        for(int j = 0; j < 20; j++)
          {
            cout << StudentGenerator::firstNames[i][j];
          }
        cout << endl;
      }
for(int i = 0; i < 20; i++)
      {
        for(int j = 0; j < 20; j++)
          {
            cout << StudentGenerator::lastNames[i][j];
          }
        cout << endl;
      }

}

RandomStudents* StudentGenerator::makeStudents(int amount)
{
  srand(time(0));
  
  RandomStudents* randomStudents = new RandomStudents(amount);

  for(int i = 0; i < amount; i++)
    {
      int firstNameLength = rand() % 20 + 1;
      int secondNameLength = rand() % 20 + 1;
      
      char firstName[20] = {};
      strncpy(firstName, StudentGenerator::firstNames[firstNameLength-1], firstNameLength);
      char lastName[20] = {};
      strncpy(lastName, StudentGenerator::lastNames[secondNameLength-1], secondNameLength);
       float GPA = (float)(rand()%4);
       int id = StudentGenerator::currentId;
       int randomSeed = rand() % 100 + 47;

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

int StudentGenerator::hashStudent(Student* student, int maxNum)
{
  int hash = (student->id * student->randomSeed) % (maxNum+1);
 
  return hash;
}
