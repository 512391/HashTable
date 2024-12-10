#include<iostream>
#include <fstream>
#include"Node.h"

using namespace LinkedList;

namespace StudentTools
{
  struct RandomStudents
  {
    Node** nodes;
    RandomStudents(int amount);
  };
    
  class StudentGenerator
  {
    public:
    StudentGenerator();
      RandomStudents* makeStudents(int amount);
      int hashStudent(Student* student, int maxNumx);
  private:
    int currentId;
    char firstNames[20][20];
    char lastNames[20][20];
  };
}
