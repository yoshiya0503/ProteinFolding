/************************
 *ある構造群についてRgを
 *プロットする。
 *Rgの小さいものから順に
 *ソートしておく
 ***********************/
#include<vector>
#include<stdlib.h>
#include<math.h>
#include"Algorithm.hpp"
#include"HPModel2D.hpp"
#include"Parametor.h"

using namespace std;

void QuickSort(int,int,double data[][2]);

int main(){
  ifstream ifile1("packing16_5x5.txt");
  ofstream ofile1("Conformation_Rg.txt");
  ofile1.precision(10);
  
  int hp[Parametor::L] = {0};
  Algorithm* algorithm;
  HPModel2D* hpmodel = new HPModel2D(hp,algorithm);
  long Trinary = 0;
  long tmp = 0;
  int trinary[Parametor::L] = {0};
  vector<long> trinary_vec;
  vector<double> Rg;
    
  while(ifile1!=0){
    ifile1>>Trinary;
    if(Trinary==0)
      break;
    tmp = Trinary;
    for(int i=Parametor::L-1;i>=0;i--){
      trinary[i] = Trinary%10;
      Trinary/=10;
    }
    
    //構造を復元する
    for(int i=2;i<Parametor::L;i++)
      hpmodel->setSegment(trinary[i],i);
    
    //構造と慣性半径をベクトルに保存
    trinary_vec.push_back(tmp);
    Rg.push_back(hpmodel->Rg());
  }
  
  double sortedRg[Rg.size()][2];
  for(int i=0;i<Rg.size();i++){
    sortedRg[i][0] = Rg[i];
    sortedRg[i][1] = trinary_vec[i];
  }
  
  QuickSort(0,Rg.size()-1,sortedRg);
  
  for(int i=0;i<Rg.size();i++){
    ofile1<<i+1<<" ";
    //ofile1<<sortedRg[i][1]<<" ";
    ofile1<<sortedRg[i][0]<<endl;
  }
  
  
  delete hpmodel;
}


//２次元のクイックそーと
void QuickSort(int bottom,int top,double data[][2]){
  int lower;
  int upper;
  double div;
  double temp1;
  double temp2;
  if(bottom>=top){
    return;
  }
  div = data[bottom][0];
  for(lower = bottom,upper = top;lower < upper;){
    while(lower <=upper && data[lower][0]<=div){
      lower++;
    }
    while(lower <= upper && data[upper][0]>div){
      upper--;
    }
    if(lower < upper){
      temp1 = data[lower][0];
      temp2 = data[lower][1];
      data[lower][0] = data[upper][0];
      data[lower][1] = data[upper][1];
      data[upper][0] = temp1;
      data[upper][1] = temp2;
    }
  }
  temp1 = data[bottom][0];
  temp2 = data[bottom][1];
  data[bottom][0] = data[upper][0];
  data[bottom][1] = data[upper][1];
  data[upper][0] = temp1;
  data[upper][1] = temp2;
  
  QuickSort(bottom,upper-1,data);
  QuickSort(upper+1,top,data);
}
