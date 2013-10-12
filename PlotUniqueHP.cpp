//３進数のデータからPostScriptを生成
#include<fstream>
#include<iostream>
#include"Parametor.h"

using namespace std;

void postscript(int*,int*,ofstream&);

int main(){
  ifstream ifile1("UniqueHP4x3.txt");
  char s[256];
  int z = 0;
  long Trinary = 0;
  long HP=0;
  int E = 0;
  double Rg =0;
  int hp[Parametor::L] = {0};
  int trinary[Parametor::L] = {0};
  while(ifile1!=0){
    ifile1>>HP;
    ifile1>>Trinary;
    ifile1>>E;
    ifile1>>Rg;
    
    for(int i=Parametor::L-1;i>=0;i--){
      trinary[i] = Trinary%10;
      Trinary/=10;
    }
    for(int i=Parametor::L-1;i>=0;i--){
      hp[i] = HP%10;
      HP/=10;
    }
    
    z+=1;
    sprintf(s,"fig%03d.ps",z);
    ofstream ofile1(s);
    postscript(trinary,hp,ofile1);
  }
}

//postscriptでプロットする
void postscript(int* trinary,int* hp,ofstream& ofile1){
  ofile1<<"/x0{300} def"<<endl;
  ofile1<<"/y0{300} def"<<endl;
  ofile1<<"/bondlength{60} def"<<endl;
  ofile1<<"/right{-90} def"<<endl;
  ofile1<<"/left{90} def"<<endl;
  
  ofile1<<"/segment"<<endl;
  ofile1<<"{newpath"<<endl;
  ofile1<<"0 0 15 0 360 arc"<<endl;
  ofile1<<"8 setlinewidth"<<endl;
  ofile1<<"stroke"<<endl;
  ofile1<<"0 0 15 0 360 arc"<<endl;
  ofile1<<"0.0 0.7 0.0 setrgbcolor"<<endl;
  ofile1<<"fill"<<endl;
  ofile1<<"} def"<<endl;

  ofile1<<"/H"<<endl;
  ofile1<<"{newpath"<<endl;
  ofile1<<"0 0 15 0 360 arc"<<endl;
  ofile1<<"8 setlinewidth"<<endl;
  ofile1<<"stroke"<<endl;
  ofile1<<"0 0 15 0 360 arc"<<endl;
  ofile1<<"0.0 0.0 0.7 setrgbcolor"<<endl;
  ofile1<<"fill"<<endl;
  ofile1<<"} def"<<endl;
  
  ofile1<<"/P"<<endl;
  ofile1<<"{newpath"<<endl;
  ofile1<<"0 0 15 0 360 arc"<<endl;
  ofile1<<"8 setlinewidth"<<endl;
  ofile1<<"stroke"<<endl;
  ofile1<<"0 0 15 0 360 arc"<<endl;
  ofile1<<"0.7 0.0 0.0 setrgbcolor"<<endl;
  ofile1<<"fill"<<endl;
  ofile1<<"} def"<<endl;
  
  ofile1<<"/bond"<<endl;
  ofile1<<"{newpath"<<endl;
  ofile1<<"0 15 moveto"<<endl;
  ofile1<<"0 bondlength rlineto"<<endl;
  ofile1<<"12 setlinewidth"<<endl;
  ofile1<<"0 setgray"<<endl;
  ofile1<<"stroke"<<endl;
  ofile1<<"0 bondlength translate"<<endl;
  ofile1<<"} def"<<endl;
  
  ofile1<<"newpath"<<endl;
  ofile1<<"x0 y0 translate"<<endl;
  
  if(hp[0]==1){
    ofile1<<"H"<<endl;
  }else if(hp[0]==0){
    ofile1<<"P"<<endl;
  }
  
  for(int i=1;i<Parametor::L;i++){
    if(hp[i]==1){
      if(trinary[i]==0){
	ofile1<<"bond"<<endl;
	ofile1<<"H"<<endl;
      }else if(trinary[i]==1){
	ofile1<<"right rotate"<<endl;
	ofile1<<"bond"<<endl;
	ofile1<<"H"<<endl;
      }else if(trinary[i]==2){
	ofile1<<"left rotate"<<endl;
	ofile1<<"bond"<<endl;
	ofile1<<"H"<<endl;
      }else{
	cout<<"error"<<endl;
      }
    }else if(hp[i]==0){
      if(trinary[i]==0){
	ofile1<<"bond"<<endl;
	ofile1<<"P"<<endl;
      }else if(trinary[i]==1){
	ofile1<<"right rotate"<<endl;
	ofile1<<"bond"<<endl;
	ofile1<<"P"<<endl;
      }else if(trinary[i]==2){
	ofile1<<"left rotate"<<endl;
	ofile1<<"bond"<<endl;
	ofile1<<"P"<<endl;
      }else{
	cout<<"error"<<endl;
      }
    }
  }  
}
