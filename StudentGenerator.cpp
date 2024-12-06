#include<iostream>
#include"StudentGenerator.h"
#include<cstdlib>
#include<cstring>

using namespace std;
using namespace LinkedList;
using namespace StudentTools;

RandomStudents::RandomStudents(int amount)
{
  RandomStudents::nodes = new Node*[amount];
}

RandomStudents* StudentGenerator::makeStudents(int amount)
{
  RandomStudents* randomStudents = new RandomStudents(amount);

  for(int i = 0; i < amount; i++)
    {
      int firstNameLength = rand() % 21;
      int secondNameLength = rand() % 21;
       char firstName[20] = {};
       char lastName[20] = {};
       float GPA = static_cast<float>((rand() % 401)/100);
       int id = rand() % 101;

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

       randomStudents->nodes[i] = new Node(newStudent);
    }
  return randomStudents;
}

int StudentGenerator::hashStudent(Student* student, int maxNum)
{
  int hash = static_cast<int>(student->id * (student->GPA*100) * (student->lastNameLength+student->firstNameLength)) % (maxNum+1);
  return hash;
}
