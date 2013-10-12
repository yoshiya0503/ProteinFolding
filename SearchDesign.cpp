/**************************
 *デザイン性の分布やH確率を得る
 *(任意の構造群について)
 *エネルギーヒストグラムも
 *プロットできる
 *************************/
#include"Algorithm.hpp"
#include"Datastructure.hpp"
#include"HPModel2D.hpp"
#include"Parameter.hpp"
#include<fstream>
#include<vector>

using namespace std;

int main(){
  ifstream ifile1("UniqueHP16_5x5.txt");
  ifstream ifile2("packing16_4x4_+.txt");
  
  ofstream ofile1("Designability16_5x5.txt");
  ofstream ofile2("Histgram_EConformation4x4_+.txt");
  
  ofstream ofile3("AverageHPPlob16_4x4.txt");
  ofstream ofile4("AverageHPPlob16_+.txt");
  ofstream ofile5("AverageHPPlob16_4x4Ratio.txt");
  ofstream ofile6("AverageHPPlob16_+Ratio.txt");
  
  ofstream ofile7("MostDesigne16_4x4.txt");
  ofstream ofile8("MostDesigne16_+.txt");
  ofstream ofile9("MostDesigne16_4x4Ratio.txt");
  ofstream ofile10("MostDesigne16_+Ratio.txt");
  
  ofstream ofile11("AverageHPPlob_Rgmin.txt");
  
  long hp = 0;
  long trinary = 0;
  int E = 0;
  vector<long> flag;
  int HistgramE[Parameter::L+1] = {0};
  while(ifile2!=0){
    ifile2>>trinary;
    flag.push_back(trinary);
  }
  flag.pop_back();
  trinary=0;
  
  //スタックの中には構造毎のデータを格納する
  MyStack* stack = new MyStack[flag.size()];
  while(ifile1!=0){
    ifile1>>hp;
    ifile1>>trinary;
    ifile1>>E;
    if(trinary==0)
      break;
    for(unsigned int i=0;i<flag.size();i++){
      if(trinary==flag[i]){
		stack[i].pushAllData(hp,trinary,E);
      }
    }
    HistgramE[-E]++;
  }

  double HP_ave[Parameter::L] = {0};
  double HP_ave1[Parameter::L] = {0};
  double HP_ave2[Parameter::L] = {0};
  double HP1[Parameter::L] = {0};
  double HP2[Parameter::L] = {0};
  int sum = 0;
  int sum1 = 0;
  int sum2 = 0;
  int designe1 = 0;
  int designe2 = 0;
  //4x4構造38個について、どのようなHP配列が選ばれるのかを考える
  for(int f=0;f<=37;f++){
    for(int t=0;t<stack[f].getTop();t++){
      if(stack[f].getTop()==0)
		break;
	  long tmp = stack[f].getSequence(t);
      for(int i=Parameter::L-1;i>=0;i--){
		HP_ave1[i] += tmp%10;
		tmp/=10;
      }
      sum1++;
    }
  }
  
  //+構造について、どのようなHP配列が選ばれるのかを考える
  for(unsigned int f=38;f<flag.size();f++){
    for(int t=0;t<stack[f].getTop();t++){
      if(stack[f].getTop()==0)
		break;
	  long tmp = stack[f].getSequence(t);
      for(int i=Parameter::L-1;i>=0;i--){
		HP_ave2[i] += tmp%10;
		tmp/=10;
      }
      sum2++;
    }
  }
  
  //全構造について、どのようなHP配列が選ばれるのかを考える
  for(unsigned int f=0;f<flag.size();f++){
    for(int t=0;t<stack[f].getTop();t++){
      if(stack[f].getTop()==0)
		break;
	  long tmp = stack[f].getSequence(t);
      for(int i=Parameter::L-1;i>=0;i--){
		HP_ave[i] += tmp%10;
		tmp/=10;
      }
      sum++;
    }
  }
  
  //4x4で最もデザイン性の高い構造について、H確率を考える
  for(int i=0;i<stack[12].getTop();i++){
    long tmp = stack[12].getSequence(i);
    for(int i=Parameter::L-1;i>=0;i--){
      HP1[i] += tmp%10;
      tmp/=10;
    }
    designe1++;
  }
  
  //+構造で最もデザイン性の高い構造についてH確率を考える
  for(int i=0;i<stack[46].getTop();i++){
    long tmp = stack[46].getSequence(i);
    for(int i=Parameter::L-1;i>=0;i--){
      HP2[i] += tmp%10;
      tmp/=10;
    }
    designe2++;
  }
  
  //--------------------ヒストグラムの出力--------------------
  //構造に対してのユニーク配列の数をヒストグラムにする
  for(unsigned int i=0;i<flag.size();i++)
	ofile1<<i+1<<" "<<stack[i].getTop()<<" "<<endl;
  //どのような配列が選ばれるのかをエネルギーについてのヒストグラムにする
  for(int i=9;i>=0;i--)
	ofile2<<-i<<" "<<HistgramE[i]<<endl;
  //----------------------------------------------------------
  
  //--------------------各残基のHP確率をプロット--------------
  
  //4x4構造38個について、HP配列の平均H確率をプロット
  for(int i=0;i<Parameter::L;i++)
    ofile3<<i+1<<" "<<(HP_ave1[i]/sum1)<<endl;  
  //+構造について、HP配列の平均H確率をプロット
  for(int i=0;i<Parameter::L;i++)
    ofile4<<i+1<<" "<<(HP_ave2[i]/sum2)<<endl;
  
  //4x4構造38個について、HP配列の平均H確率の比をプロット
  for(int i=0;i<Parameter::L;i++)
    ofile5<<i+1<<" "<<(HP_ave1[i]/sum1)/(HP_ave[i]/sum)<<endl;
  //+構造について、HP配列の平均H確率の比をプロット
  for(int i=0;i<Parameter::L;i++)
    ofile6<<i+1<<" "<<(HP_ave2[i]/sum2)/(HP_ave[i]/sum)<<endl;
  
  //4x4でデザイン性の高い構造についてH確率をプロット
  for(int i=0;i<Parameter::L;i++)
    ofile7<<i+1<<" "<<(HP1[i]/designe1)<<endl;
  //+構造でデザイン性の高い構造についてH確率をプロット
  for(int i=0;i<Parameter::L;i++)
    ofile8<<i+1<<" "<<(HP2[i]/designe2)<<endl;
  
  //4x4でデザイン性の高い構造についてH確率の比をプロット
  for(int i=0;i<Parameter::L;i++)
    ofile9<<i+1<<" "<<(HP1[i]/designe1)/(HP_ave1[i]/sum1)<<endl;
  //+構造でデザイン性の高い構造についてH確率の比をプロット
  for(int i=0;i<Parameter::L;i++)
    ofile10<<i+1<<" "<<(HP2[i]/designe2)/(HP_ave2[i]/sum2)<<endl;
  //慣性半径最低の構造が選ばれるHP確率
  for(int i=0;i<Parameter::L;i++)
	ofile11<<i+1<<" "<<HP_ave[i]/sum<<endl;
  //-----------------------------------------------------------
  delete []stack;
}
