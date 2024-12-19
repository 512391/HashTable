#include<iostream>
#include <fstream>
#include"Node.h"


/*
  author: Jay Williamson
  date: 12/19/2024
  this file contains the info about the student generator
 */

using namespace LinkedList;

namespace StudentTools
{
//random students struct
  struct RandomStudents
  {
    Node** nodes;
    RandomStudents(int amount);
  };

//Student generator class
  class StudentGenerator
  {
    public:
    StudentGenerator();
      RandomStudents* makeStudents(int amount);
      int hashStudent(Student* student, int maxNumx);
  private:
    int currentId;
    char **firstNames = new char*[21];
    char **lastNames = new char*[21];
  };
}
