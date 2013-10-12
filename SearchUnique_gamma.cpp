/******************************
 *縮退のない最低エネルギーを与える
 *HP配列をある構造に対して行う
 *各スタックは1024だけ構造を持てる
 *****************************/
#include"Algorithm.hpp"
#include"HPModel2D.hpp"
#include"Parametor.h"
#include<fstream>
#include<vector>

using namespace std;

//エネルギーの幅
const int E_size = 9;

void allSequence(int,int*,HPModel2D*,ofstream&,double);

int main(){
  
  int hp[Parametor::L] = {0};
  Algorithm* algorithm;
  HPModel2D* hpmodel = new HPModel2D(hp,algorithm);
  char s[256];
  
  //スレッド並列
  //double gamma =-1.0;
  //int z = 0;
  for(int z=-10;z<=-1;z++){
    sprintf(s,"UniqueHP4x4_+gamma%d.txt",z);
    ofstream ofile1(s);
    allSequence(0,hp,hpmodel,ofile1,gamma);
    cout<<"End One Gamma!"<<endl;
    gamma+=0.1;
  }
  delete hpmodel;
}

void allSequence(int n,int* data,HPModel2D* hpmodel,ofstream& ofile1,double gamma){
  if(n==Parametor::L){
    ifstream ifile1("packing4x4_+.txt");
    hpmodel->setSequence(data);
    int trinary[Parametor::L] = {0};
    long Trinary=0;
    long temp =0;
    int binNum = 2*E_size*10+200;
    Stack* stack = new Stack[binNum+1];
    //構造のファイルを読み込む
    while(ifile1!=0){
      ifile1>>Trinary;
      if(Trinary==0)
	break;
      temp = Trinary;
      for(int i=Parametor::L-1;i>=0;i--){
		trinary[i] = Trinary%10;
		Trinary/=10;
      }
      
      //HP配列と構造を作る
      for(int i=2;i<Parametor::L;i++)
		hpmodel->setSegment(trinary[i],i);
      
      //stackを用いてユニークなものを探す
      //エネルギーにgammaが入っている
      int e = -10*hpmodel->Energy(gamma);
      stack[e].pushData(temp,hpmodel->Energy(gamma));
    }
    
    for(int e=binNum;e>=0;e--){
      if(stack[e].getTop()==0)
	continue;
      else if(stack[e].getTop()>1)
	break;
      else if(stack[e].getTop()==1){
	for(int i=0;i<Parametor::L;i++)
	  ofile1<<data[i];
	ofile1<<" ";
	stack[e].popData(ofile1);
	break;
      }
    }
    
    delete[] stack;
  }else if(n<Parametor::L){
    for(int i=0;i<=1;i++){
      data[n] = i;
      allSequence(n+1,data,hpmodel,ofile1,gamma);
    }
  }
}
