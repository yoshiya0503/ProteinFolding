#include"Algorithm.hpp"
#include<math.h>

using namespace std;

//全探索
void Algorithm::searchNoMirrorPut(HPModel2D* hpmodel,ofstream& ofile1){
  int data[Parameter::L] = {0};
  searchNoMirror(hpmodel,2,data,ofile1);
}

void Algorithm::searchNoMirror(HPModel2D* hpmodel,int n,int* data,
                               ofstream& ofile1){
  if(n==Parameter::L){
      for(int i=2;i<Parameter::L;i++)
		ofile1<<data[i];
      ofile1<<" ";
      ofile1<<getMagicNumber(data);
      ofile1<<endl;
  }else if(n<Parameter::L){
    for(int i=0;i<=2;i++){
      hpmodel->setSegment(i,n);
      if(hpmodel->overlap(n) || noMirror(data,n))
        continue;
      data[n] = i;
      searchNoMirror(hpmodel,n+1,data,ofile1);
    }
  }
}

//可能なNxM構造を全探索
void Algorithm::searchNxM_NoMirrorPut(HPModel2D* hpmodel,ofstream& ofile1,
                                      int N,int M){
  int data[Parameter::L] = {0};
  searchNxM_NoMirror(hpmodel,2,data,ofile1,N,M);
}

void Algorithm::searchNxM_NoMirror(HPModel2D* hpmodel,int n,int* data,
                                   ofstream& ofile1,int N,int M){
  if(n==Parameter::L){
    if(isNxM(hpmodel,n,N,M)){
      for(int i=2;i<Parameter::L;i++){
		ofile1<<data[i];
      }
      ofile1<<" ";
      ofile1<<getMagicNumber(data);
      ofile1<<endl;
    }
  }else if(n<Parameter::L){
    for(int i=0;i<=2;i++){
      hpmodel->setSegment(i,n);
      if(hpmodel->overlap(n) ||noMirror(data,n)||!isNxM(hpmodel,n,N,M))
        continue;
      data[n] = i;
      searchNxM_NoMirror(hpmodel,n+1,data,ofile1,N,M);
    }
  }
}

//時間反転対称性を除く高速なスクリーニング
void Algorithm::superScreaningTimeSymmetry(ifstream& ifile1,ofstream& ofile1){
  unsigned long magic_number = 0;
  unsigned long trinary = 0;
  vector<unsigned long> vec;
  while(ifile1!=0){
    ifile1>>trinary;
    ifile1>>magic_number;
    vec.push_back(magic_number);
  }
  vec.pop_back();
  std::sort(vec.begin(),vec.end());
  vector<unsigned long>::iterator it 
    = unique(vec.begin(),vec.end());
  vec.erase(it,vec.end());
  
  int data[Parameter::L] = {0};
  cout<<"NumOfSAW:"<<vec.size()<<endl;
  for(unsigned int n=0;n<vec.size();n++){
    for(int i=Parameter::L-1;i>=2;i--){
      data[i] = vec[n]/pow(3,i);
      ldiv_t d = ldiv(vec[n],pow(3,i));
      vec[n] = d.rem;
    }
    for(int i=Parameter::L-1,j=0;i>=2;i--,j++){
      ofile1<<data[i];
      if(j==19)
		ofile1<<" ";
    }
    ofile1<<endl;
  }
}

//NxM構造の判定
bool Algorithm::isNxM(HPModel2D* hpmodel,int L,int N,int M){
  int x_max=0;
  int y_max=0;
  int x_min=0;
  int y_min=0;
  for(int i=0;i<L;i++){
    if(hpmodel->getSequence(i).getX() >= x_max)
      x_max = hpmodel->getSequence(i).getX();
    if(hpmodel->getSequence(i).getY() >= y_max)
      y_max = hpmodel->getSequence(i).getY();  
    if(hpmodel->getSequence(i).getX() < x_min)
      x_min = hpmodel->getSequence(i).getX();
    if(hpmodel->getSequence(i).getY() < y_min)
      y_min = hpmodel->getSequence(i).getY();
  }
  if((x_max-x_min<=N-1) && (y_max-y_min<=M-1))
    return true;
  else
    return false;
}

//鏡面対称の判定
bool Algorithm::noMirror(int* data,int n){
  for(int i=2;i<n;i++){
    if(data[i]!=0 && data[i]==1){
      return false;
    }else if(data[i]!=0 && data[i]==2){
      return true;
    }else if(data[i]==0){
      continue;
    }
  }
  return false;
}

//時間反転鏡面対称の判定
bool Algorithm::backMirror(long vec1,long vec2){
  int tmp1[Parameter::L-2] = {0};
  int tmp2[Parameter::L-2] = {0};
  for(int i=Parameter::L-3;i>=0;i--){
    tmp1[i] = vec1%10;
    tmp2[i] = vec2%10;
    vec1/=10;
    vec2/=10;
  }
  for(int i=0;i<Parameter::L-2;i++){
    if(tmp1[i]==1 && tmp2[i]==2)
      continue;
    else if(tmp1[i]==2 && tmp2[i]==1)
      continue;
    else if(tmp1[i]==0 && tmp2[i]==0)
      continue;
    else
      return false;
  }
  return true;
}

//構造特有の数値
unsigned long Algorithm::getMagicNumber(int* trinary){
  unsigned long num1=0;
  unsigned long num2=0;
  unsigned long num3=0;
  unsigned long num4=0;
  unsigned long num_min=0;
  int i=0;
  int j=0;
  
  //準方向のインデックス生成
  for(i=2;i<Parameter::L;i++){
    num1 += trinary[i]*pow(3,i);
  }
  //逆方向のインデックス生成
  for(i=Parameter::L-1,j=2;i>=2;i--,j++){
    num2 += trinary[i]*pow(3,j);
  }
  //逆方向鏡映インデックス 生成
  for(i=Parameter::L-1,j=2;i>=2;i--,j++){
    if(trinary[i]==1)
      num3 += 2*pow(3,j);
    else if(trinary[i]==2)
      num3 += 1*pow(3,j);
    else if(trinary[i]==0)
      num3 += 0;
  }
  //鏡映方向のインデックス　生成
  for(i=2;i<Parameter::L;i++){
    if(trinary[i]==1)
      num4 += 2*pow(3,i);
    else if(trinary[i]==2)
      num4 += 1*pow(3,i);
    else if(trinary[i]==0)
      num4 += 0;
  }
    
  //最小値を決定
  num_min = num1;
  if(num_min>=num2)
    num_min = num2;
  if(num_min>=num3)
    num_min = num3;
  if(num_min>=num4)
    num_min = num4;

  return num_min;
}
