/******************************
 *探索アルゴリズムのクラス
 *探索範囲を指定可能
 *****************************/
#ifndef ALGORITHM
#define ALGORITHM
#include<fstream>
#include"Parameter.hpp"
#include"HPModel2D.hpp"
#include<vector>

class HPModel2D;

class Algorithm{
public:
  void trinaryPut(HPModel2D*,std::ofstream&);
  void trinary(HPModel2D*,int,int*,std::ofstream&);
  void searchNoMirrorPut(HPModel2D*,std::ofstream&);
  void searchNxM_NoMirrorPut(HPModel2D*,std::ofstream&,int,int);
  void searchNxM_NoMirror(HPModel2D*,int,int*,std::ofstream&,int,int);
  void searchNoMirror(HPModel2D*,int,int*,std::ofstream&);
  void superScreaningTimeSymmetry(std::ifstream&,std::ofstream&);
  bool isNxM(HPModel2D*,int,int,int);
  bool noMirror(int*,int);
  bool backMirror(long,long);
  unsigned long getMagicNumber(int*);
};

#endif
