#include"Algorithm.hpp"
#include"DataStructure.hpp"
#include"HPModel2D.hpp"
#include"Parametor.h"
#include<fstream>
#include<vector>

using namespace std;

int main(){
  ifstream ifile1("UniqueHP16_5x5gamma13.txt");
  ifstream ifile2("packing4x4_+.txt");
  
  ofstream ofile1("NumOfHP_NumOf_Rgmin5x5_gamma13.txt");
  ofstream ofile2("MostDesigne16_4x4_gamma.txt");
  ofstream ofile3("MostDesigne16_+_gamma.txt");
  ofstream ofile4("AverageHPPlob_Rgmin_gamma.txt");
  
  long hp = 0;
  long trinary = 0;
  double E = 0;
  vector<long> flag;
  
  while(ifile2!=0){
    ifile2>>trinary;
    flag.push_back(trinary);
  }
  flag.pop_back();
  trinary=0;
  
  //スタックの中には構造毎のデータを格納する
  Stack* stack = new Stack[flag.size()];
  while(ifile1!=0){
    ifile1>>hp;
    ifile1>>trinary;
    ifile1>>E;
    if(trinary==0)
      break;
    for(int i=0;i<flag.size();i++){
      if(trinary==flag[i]){
		stack[i].pushData(hp,trinary,E);
      }
    }
  }

  double HP_ave[Parametor::L] = {0};
  double HP_ave1[Parametor::L] = {0};
  double HP_ave2[Parametor::L] = {0};
  double HP1[Parametor::L] = {0};
  double HP2[Parametor::L] = {0};
  double HP3[Parametor::L] = {0};
  double HP4[Parametor::L] = {0};
  int sum = 0;
  int sum1 = 0;
  int sum2 = 0;
  int designe1 = 0;
  int designe2 = 0;
  
  //4x4構造38個について、どのようなHP配列が選ばれるのかを考える
  for(int f=0;f<=37;f++){
    for(int t=0;t<stack[f].top;t++){
      long tmp = stack[f].hp[t];
      for(int i=Parametor::L-1;i>=0;i--){
	HP_ave1[i] += tmp%10;
	tmp/=10;
      }
      sum1++;
    }
  }
  
  //+構造について、どのようなHP配列が選ばれるのかを考える
  for(int f=38;f<flag.size();f++){
	for(int t=0;t<stack[f].top;t++){
	  long tmp = stack[f].hp[t];
	  for(int i=Parametor::L-1;i>=0;i--){
		HP_ave2[i] += tmp%10;
		tmp/=10;
	  }
	  sum2++;
	}
  }
  
  //全構造について、どのようなHP配列が選ばれるのかを考える
  for(int f=0;f<flag.size();f++){
	for(int t=0;t<stack[f].top;t++){
	  long tmp = stack[f].hp[t];
	  for(int i=Parametor::L-1;i>=0;i--){
		HP_ave[i] += tmp%10;
		tmp/=10;
	  }
	  sum++;
	}
  }
  
  //4x4構造で最もデザイン性の高い構造についてH確率を考える
  for(int i=0;i<stack[12].top;i++){
	long tmp = stack[12].hp[i];
	for(int i=Parametor::L-1;i>=0;i--){
	  HP1[i] += tmp%10;
	  tmp/=10;
	}
	designe1++;
  }
  
  //+構造で最もデザイン性の高い構造についてH確率を考える
  for(int i=0;i<stack[46].top;i++){
	long tmp = stack[46].hp[i];
	for(int i=Parametor::L-1;i>=0;i--){
	  HP2[i] += tmp%10;
	  tmp/=10;
	}
	designe2++;
  }
  
  //構造に対してのユニーク配列の数をヒストグラムにする
  for(int i=0;i<flag.size();i++){
    ofile1<<i+1<<" "<<stack[i].top<<" "<<flag[i]<<endl;
  }
  
  //4x4構造についてデザイン性の高い構造のH確率をプロット
  for(int i=0;i<Parametor::L;i++)
	ofile2<<i+1<<" "<<(HP1[i]/designe1)<<endl;
  //+構造についてデザイン性の高い構造のH確率をプロット
  for(int i=0;i<Parametor::L;i++)
	ofile3<<i+1<<" "<<(HP2[i]/designe2)<<endl;
  //慣性半径最低の構造についてデザイン性の高い構造のH確率をプロット
  for(int i=0;i<Parametor::L;i++)
	ofile4<<i+1<<" "<<HP_ave[i]/sum<<endl;
  
  delete []stack;
}
