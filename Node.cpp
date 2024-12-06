#include<iostream>
#include "Node.h"
/*
  author: Jay Williamson
  date: 12/2/2024
  this class gives functionality to the node
 */
using namespace LinkedList;
using namespace std;
using namespace StudentTools;

Node::Node(Student* student)
{
  //sets the data
  Node::data = student;
  Node::nextNode = nullptr;
}

Node* Node::getNext()
{
  //returns the next node
  return Node::nextNode;
}

void Node::setNext(Node* node)
{
  //sets the next node
  Node::nextNode = node;
}

Student* Node::getStudent()
{
  //return the data as a student
  return Node::data;
}

Node::~Node()
{
  //deletes the data
  delete Node::data;
}
