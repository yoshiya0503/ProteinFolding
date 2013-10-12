/*************************
 *よく使うデータ構造を生成
 *リンクリストを使わない
 *スタックの実装
 ************************/
#ifndef DATASTRUCTURE
#define DATASTRUCTURE
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class MyStack{
private:
  int top;
  double energy;
  vector<unsigned long> sequence;
  vector<unsigned long> trinary;
public:
  MyStack();
  ~MyStack();
  void pushSequence(unsigned long);
  void pushTrinary(unsigned long);
  void pushEnergy(double);
  void pushAllData(unsigned long,unsigned long,double);
  void pushAllData(unsigned long,double);
  void popAllData(std::ofstream&);
  void popData(std::ofstream&);
  unsigned long getSequence(int);
  unsigned long getTrinary(int);
  double getEnergy();
  int getTop();
  void clearData();
};

#endif
