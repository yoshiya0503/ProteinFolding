/*******************
 *DataStructureの実装
 *Stackの実装
 ******************/
#include"DataStructure.hpp"

MyStack::MyStack(){
  this->top = 0;
  this->energy = 0;
}

MyStack::~MyStack(){
  this->trinary.clear();
  this->sequence.clear();
  this->energy = 0;
  this->top = 0;
}

void MyStack::pushSequence(unsigned long sequence){
  this->sequence.push_back(sequence);
}

void MyStack::pushTrinary(unsigned long trinary){
  this->trinary.push_back(trinary);
}

void MyStack::pushEnergy(double energy){
  this->energy = energy;
}

void MyStack::pushAllData(unsigned long sequence,unsigned long trinary,
                          double energy){
  this->sequence.push_back(sequence);
  this->trinary.push_back(trinary);
  this->energy = energy;
  this->top++;
}

void MyStack::pushAllData(unsigned long trinary,double energy){
  this->trinary.push_back(trinary);
  this->energy = energy;
  this->top++;
}

unsigned long MyStack::getSequence(int i){
  return this->sequence[i];
}

unsigned long MyStack::getTrinary(int i){
  return this->trinary[i];
}

double MyStack::getEnergy(){
  return this->energy;
}

void MyStack::popAllData(std::ofstream& ofile){
  ofile<<this->sequence[0]<<" ";
  ofile<<this->trinary[0]<<" ";
  ofile<<this->energy<<endl;
}

void MyStack::popData(std::ofstream& ofile){
  ofile<<this->trinary[0]<<" ";
  ofile<<this->energy<<endl;
}

int MyStack::getTop(){
  return this->top;
}

void MyStack::clearData(){
  this->trinary.clear();
  this->sequence.clear();
  this->energy = 0;
  this->top = 0;
}
