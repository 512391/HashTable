#include<iostream>
#include"Student.h"

/*
  author: Jay Williamson
  date: 12/2/2024
  this class represents a node in a linked list
 */

using namespace StudentTools;

namespace LinkedList
{
  class Node
  {
  public:
    //makes a new node and assigns the student to the data
      Node(Student* student);
    //deletes the data not the next node tho
      ~Node();
    //gets the next node it is connected to
      Node* getNext();
    //sets the next node it is connected to
      void setNext(Node* node);
    //this reutrn the data which is a student
      Student* getStudent();
    private:
    //the next node it is connected to
      Node* nextNode;
    //the data which is a student which contains nothing
      Student* data;
  };
}
