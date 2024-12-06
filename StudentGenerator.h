#include<iostream>
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
      RandomStudents* makeStudents(int amount);
      int hashStudent(Student* student, int maxNumx);
  };
}
