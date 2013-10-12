//３進数のデータからPostScriptを生成
#include<fstream>
#include<iostream>

using namespace std;

//サイズを指定
const int L = 16;

void postscript(int*,ofstream&);

int main(){
  ifstream ifile1("packing16_4x4.txt");
  char s[256];
  int z = 0;
  long Trinary = 0;
  int trinary[L-2] = {0};
  while(ifile1!=0){
    ifile1>>Trinary;
    for(int i=L-3;i>=0;i--){
      trinary[i] = Trinary%10;
      Trinary/=10;
    }
    z+=1;
    sprintf(s,"fig%04d.ps",z);
    ofstream ofile1(s);
    postscript(trinary,ofile1);
  }
}

//postscriptでプロットする
void postscript(int* trinary,ofstream& ofile1){
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
  ofile1<<"segment"<<endl;
  ofile1<<"bond"<<endl;
  ofile1<<"segment"<<endl;
  
  for(int i=0;i<L-2;i++){
    if(trinary[i]==0){
      ofile1<<"bond"<<endl;
      ofile1<<"segment"<<endl;
    }else if(trinary[i]==1){
      ofile1<<"right rotate"<<endl;
      ofile1<<"bond"<<endl;
      ofile1<<"segment"<<endl;
    }else if(trinary[i]==2){
      ofile1<<"left rotate"<<endl;
      ofile1<<"bond"<<endl;
      ofile1<<"segment"<<endl;
    }else{
      cout<<"error"<<endl;
    }
  }
  
}
