/***************************
 *ターゲットとした構造探索
 *または全探索を行う
 **************************/
#include"Algorithm.hpp"
#include"HPModel2D.hpp"
#include"Parameter.hpp"
#include<iostream>
#include<fstream>

using namespace std;

int main(){
  
  //探索範囲と格子タンパクの長さを指定
  int N = 0;
  int M = 0;
  cout<<"Please input region of searching"<<endl;
  cout<<"N: "<<endl;
  cin>>N;
  cout<<"M: "<<endl;
  cin>>M;
  
  ofstream ofile1("NoMirror16_4x4.txt");
  int hp[Parameter::L] = {0};
  Algorithm* algorithm;
  HPModel2D* hpmodel = new HPModel2D(hp,algorithm);
  
  hpmodel->getAlgorithm()->searchNxM_NoMirrorPut(hpmodel,ofile1,N,M);
  ofile1.close();
  ifstream ifile1("NoMirror16_4x4.txt");
  ofstream ofile2("packing16_4x4.txt");
  hpmodel->getAlgorithm()->superScreaningTimeSymmetry(ifile1,ofile2);
  
  delete hpmodel;
}
