#include<fstream>
#include<iostream>

using namespace std;

int main(){
  
  ifstream ifile1("MostDesigne4x4_+.txt");
  ifstream ifile2("UniqueHP4x4_+.txt");
  ofstream ofile3("MostDesigne4x4_+Prob.txt");
  ofstream ofile4("temp.txt");
  ofstream ofile5("Histgram.txt");
  
  long HP=0;
  long trinary=0;
  int E=0;
    
  double hp3[16] = {0};  
  double temp[16] = {0};
  double histgram[10] = {0};

  int sum1 = 0;
  int sum2 = 0;
  int sum3 = 0;
  
  while(ifile1!=0){
    ifile1>>HP;
    ifile1>>trinary;
    ifile1>>E;
    if(HP==0)
      break;
    for(int i=16-1;i>=0;i--){
      hp3[i] += HP%10;
      HP/=10;
    }
    for(int i=16-1;i>=0;i--){
      temp[i] += trinary%10;
      trinary/=10;
    }
    int n = -E;
    histgram[n]++;
    sum3++;
  }
  
  while(ifile2!=0){
    ifile2>>HP;
    ifile2>>trinary;
    ifile2>>E;
  }
  
  for(int i=0;i<16;i++){
    ofile3<<i+1<<" "<<hp3[i]/sum3<<" "<<endl;
  }
  for(int i=0;i<9;i++)
    ofile5<<-(i+1)<<" "<<histgram[i]<<endl;
}
