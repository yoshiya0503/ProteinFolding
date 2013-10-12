/******************************
 *縮退のない最低エネルギーを与える
 *ある構造に対してHPの割り振りを行う
 *****************************/

#include"Algorithm.hpp"
#include"DataStructure.hpp"
#include"HPModel2D.hpp"
#include"Parameter.hpp"
#include<fstream>

using namespace std;

//エネルギーの幅
const int E_size = 9;

void allSequence(int,int*,HPModel2D*,ofstream&);

int main(){
  ofstream ofile1("UniqueHP16_4x4.txt");
  
  int hp[Parameter::L] = {0};
  Algorithm* algorithm;
  HPModel2D* hpmodel = new HPModel2D(hp,algorithm);
  allSequence(0,hp,hpmodel,ofile1);
  delete hpmodel;
}

void allSequence(int n,int* data,HPModel2D* hpmodel,ofstream& ofile1){
  if(n==Parameter::L){
    ifstream ifile1("packing16_4x4.txt");
    int trinary[Parameter::L] = {0};
    hpmodel->setSequence(data);
	
	long Trinary=0;
    long temp =0;
    MyStack stack[E_size+1];
    
	//構造のファイルを読み込む
    while(ifile1!=0){
      ifile1>>Trinary;
      if(Trinary==0)
		break;
      temp = Trinary;
      for(int i=Parameter::L-1;i>=0;i--){
		trinary[i] = Trinary%10;
		Trinary/=10;
      }
      
      //HP配列と構造を作る
      for(int i=2;i<Parameter::L;i++)
		hpmodel->setSegment(trinary[i],i);
	  
      //stackを用いてユニークなものを探す
	  int e = -1*hpmodel->Energy();
	  stack[e].pushAllData(temp,hpmodel->Energy());
    }
    
    for(int e=E_size;e>=0;e--){
      if(stack[e].getTop()==0)
		continue;
      else if(stack[e].getTop()>1)
		break;
      else if(stack[e].getTop()==1){
		for(int i=0;i<Parameter::L;i++)
		  ofile1<<data[i];
		ofile1<<" ";
		stack[e].popData(ofile1);
		break;
      }
    }
  }else if(n<Parameter::L){
    for(int i=0;i<=1;i++){
      data[n] = i;
      allSequence(n+1,data,hpmodel,ofile1);
    }
  }
}
