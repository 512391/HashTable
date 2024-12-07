#include<iostream>
#include"StudentGenerator.h"
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

RandomStudents* StudentGenerator::makeStudents(int amount)
{
  srand(time(0));
  
  RandomStudents* randomStudents = new RandomStudents(amount);

  for(int i = 0; i < amount; i++)
    {
      int firstNameLength = rand() % 20 + 1;
      int secondNameLength = rand() % 20 + 1;
       char firstName[20] = {};
       char lastName[20] = {};
       float GPA = (float)(rand()%4);
       int id = rand() % 100 + 1;
       int randomSeed = rand() % 100 + 47;

       for(int j = 0; j < firstNameLength; j++)
	 {
	   firstName[j] = static_cast<char>(rand() % 26 + 65);
	 }

       for(int j = 0; j < secondNameLength; j++)
         {
           lastName[j] = static_cast<char>(rand() % 26 + 65);
         }
       
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
    }
  return randomStudents;
}

int StudentGenerator::hashStudent(Student* student, int maxNum)
{
  int hash = static_cast<int>(student->id * student->randomSeed * (student->lastNameLength*student->firstNameLength)) % (maxNum+1);
  return hash;
}
