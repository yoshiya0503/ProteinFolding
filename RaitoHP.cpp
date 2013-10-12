#include<iostream>
#include<fstream>

using namespace std;

int main(){

  ifstream ifile1("UniqueHP16_5x5");
  
  ifstream ifile("Designability16_4x4.txt");
  unsigned long hp = 0;
  unsigned long trinary = 0;
  double E = 0;
  double base = 0;
  double sum = 0;
  while(ifile1!=0){
	ifile1>>hp;
	ifile1>>trinary;
	ifile1>>E;
	sum++;
  }
    
  long SUM = 0;
  int num = 0;
  while(ifile!=0){
	ifile>>num;
	ifile>>base;
	ifile>>trinary;
	SUM += base;
  }
  cout<<SUM<<endl;
  cout<<SUM/sum<<endl;
}
