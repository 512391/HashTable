#include<iostream>


/*
  author: Jay Williamson
  date: 12/19/2024
  this class holds the data for the student
 */

namespace StudentTools
{
  class Student
  {
    public:
//info
    char firstName[20];
    char lastName[20];
    float GPA;
    int id;
    int lastNameLength;
    int firstNameLength;
//seed for hashing
    int randomSeed;
    Student();
  };
}
