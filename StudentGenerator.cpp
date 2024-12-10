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

  
  if(firstNamesFile.is_open())
         {
	   int i = 0;
	   int j = 0;
	   cout << "file open \n";
           while(firstNamesFile.get(StudentGenerator::firstNames[i][j]))
	     {
	       cout << "char: " << StudentGenerator::firstNames[i][j] << '\n';
	       
	       if(StudentGenerator::firstNames[i][j] == '\n')
	         {
		   i++;
		   j = 0;
		   cout << StudentGenerator::firstNames[i-1] << '\n';
	         }
	       else
		 {
		   j++;
		 }
	     }
         }
       else
         {
           cout << "first names nor open";
         }
  if(lastNamesFile.is_open())
         {
           int i = 0;
           int j = 0;
           cout << "file open \n";
           while(lastNamesFile.get(StudentGenerator::lastNames[i][j]))
             {
               cout << "char: " << StudentGenerator::lastNames[i][j] << '\n';

               if(StudentGenerator::lastNames[i][j] == '\n')
                 {
                   i++;
                   j = 0;
                   cout << StudentGenerator::lastNames[i-1] << '\n';
                 }
               else
                 {
                   j++;
                 }
             }
         }
       else
         {
           cout << "first names nor open";
         }

}

RandomStudents* StudentGenerator::makeStudents(int amount)
{
  srand(time(0));

  ifstream firstNamesFile("FirstNames.txt");
    ifstream lastNamesFile("LastNames.txt");
  
  RandomStudents* randomStudents = new RandomStudents(amount);

  for(int i = 0; i < amount; i++)
    {
      int firstNameLength = rand() % 20 + 1;
      int secondNameLength = rand() % 20 + 1;
      cout << "before name assignement \n";
      char firstName[20] = {};
      strncpy(firstName, StudentGenerator::firstNames[firstNameLength-1], firstNameLength);
      char lastName[20] = {};
      strncpy(lastName, StudentGenerator::lastNames[secondNameLength-1], secondNameLength);
       float GPA = (float)(rand()%4);
       int id = StudentGenerator::currentId++;
       int randomSeed = rand() % 100 + 47;

       cout << "after name assignment \n";
       
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

       cout << "after all assignments \n";
       
       randomStudents->nodes[i] = new Node(newStudent);
       randomStudents->nodes[i]->setNext(nullptr);
    }
  return randomStudents;
}

int StudentGenerator::hashStudent(Student* student, int maxNum)
{
  int hash = static_cast<int>(student->id * student->randomSeed) % (maxNum+1);
  return hash;
}
