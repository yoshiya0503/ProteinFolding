/*********************************
 *HPモデルを扱うクラス
 *セグメントは格子上しか動かない
 *探索の方法を抱える
 ********************************/
#ifndef HPMODEL2D
#define HPMODEL2D
#include"Parameter.hpp"
#include"Algorithm.hpp"
#include<iostream>
#include<fstream>
#include<math.h>

class Algorithm;

class HPSequence{
private: 
  int x;
  int y;
  int base;
public:
  HPSequence(int x,int y,int base);
  HPSequence(){}
  int getX();
  int getY();
  int getBase();
  friend class HPModel2D;
};

class HPModel2D{
private:
  HPSequence* sequence;
  Algorithm* algorithm;
public:
  HPModel2D(int* hp,Algorithm* algorithm);
  ~HPModel2D();
  HPSequence getSequence(int i);
  Algorithm* getAlgorithm();
  void setSequence(int[]);
  void setSegment(int,int);
  bool contactUpper(int,int);
  bool contactDown(int,int);
  bool contactRight(int,int);
  bool contactLeft(int,int);
  bool overlap(int);
  //物理量
  int Energy();
  int contact();
  double Energy(double);
  double splitEnergy(int,int,double);
  double Rg();
  double distance_end_end();
};

#endif
