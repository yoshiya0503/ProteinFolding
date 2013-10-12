#include"HPModel2D.hpp"
#include<iostream>

using namespace std;

HPSequence::HPSequence(int x,int y,int base){
  this->x = x;
  this->y = y;
  this->base = base;
}

int HPSequence::getX(){
  return this->x;
}

int HPSequence::getY(){
  return this->y;
}

int HPSequence::getBase(){
  return this->base;
}

HPModel2D::HPModel2D(int* hp,Algorithm* algorithm){
  this->sequence = new HPSequence[Parameter::L];
  for(int i=0;i<Parameter::L;i++){
    this->sequence[i] = HPSequence(0,i,hp[i]);
  }
  this->algorithm = algorithm;
}

HPModel2D::~HPModel2D(){
  delete[] sequence;
}

HPSequence HPModel2D::getSequence(int i){
  return this->sequence[i];
}

Algorithm* HPModel2D::getAlgorithm(){
  return this->algorithm;
}

void HPModel2D::setSequence(int sequence[]){
  for(int i=0;i<Parameter::L;i++)
    this->sequence[i].base = sequence[i];
}

bool HPModel2D::contactUpper(int i,int j){
  if((sequence[j].x==sequence[i].x)&&(sequence[j].y==(sequence[i].y+1)))
    return true;
  else
    return false;
}

bool HPModel2D::contactDown(int i,int j){
  if((sequence[j].x==sequence[i].x)&&(sequence[j].y==(sequence[i].y-1)))
    return true;
  else
    return false;
}

bool HPModel2D::contactLeft(int i,int j){
  if((sequence[j].x==(sequence[i].x-1))&&(sequence[j].y==sequence[i].y))
    return true;
  else
    return false;
}

bool HPModel2D::contactRight(int i,int j){
  if((sequence[j].x==(sequence[i].x+1))&&(sequence[j].y==sequence[i].y))
    return true;
  else
    return false;
}

//0=まっすぐ 1=右に曲がる 2=左に曲がる
void HPModel2D::setSegment(int i,int n){
  if(i==0){
    if((this->sequence[n-1].x) == (this->sequence[n-2].x+1)){
      this->sequence[n].x = this->sequence[n-1].x+1;
      this->sequence[n].y = this->sequence[n-1].y;
    }else if((this->sequence[n-1].x) == (this->sequence[n-2].x-1)){
      this->sequence[n].x = this->sequence[n-1].x-1;
      this->sequence[n].y = this->sequence[n-1].y;
    }else if((this->sequence[n-1].y) == (this->sequence[n-2].y+1)){
      this->sequence[n].x = this->sequence[n-1].x;
      this->sequence[n].y = this->sequence[n-1].y+1;
    }else if((this->sequence[n-1].y) == (this->sequence[n-2].y-1)){
      this->sequence[n].x = this->sequence[n-1].x;
      this->sequence[n].y = this->sequence[n-1].y-1;
    }
  }else if(i==1){
    if((this->sequence[n-1].x) == (this->sequence[n-2].x+1)){
      this->sequence[n].x = this->sequence[n-1].x;
      this->sequence[n].y = this->sequence[n-1].y-1;
    }else if((this->sequence[n-1].x) == (this->sequence[n-2].x-1)){
      this->sequence[n].x = this->sequence[n-1].x;
      this->sequence[n].y = this->sequence[n-1].y+1;
    }else if((this->sequence[n-1].y) == (this->sequence[n-2].y+1)){
      this->sequence[n].x = this->sequence[n-1].x+1;
      this->sequence[n].y = this->sequence[n-1].y;
    }else if((this->sequence[n-1].y) == (this->sequence[n-2].y-1)){
      this->sequence[n].x = this->sequence[n-1].x-1;
      this->sequence[n].y = this->sequence[n-1].y;
    }
  }else if(i==2){
    if((this->sequence[n-1].x) == (this->sequence[n-2].x+1)){
      this->sequence[n].x = this->sequence[n-1].x;
      this->sequence[n].y = this->sequence[n-1].y+1;
    }else if((this->sequence[n-1].x) == (this->sequence[n-2].x-1)){
      this->sequence[n].x = this->sequence[n-1].x;
      this->sequence[n].y = this->sequence[n-1].y-1;
    }else if((this->sequence[n-1].y) == (this->sequence[n-2].y+1)){
      this->sequence[n].x = this->sequence[n-1].x-1;
      this->sequence[n].y = this->sequence[n-1].y;
    }else if((this->sequence[n-1].y) == (this->sequence[n-2].y-1)){
      this->sequence[n].x = this->sequence[n-1].x+1;
      this->sequence[n].y = this->sequence[n-1].y;
    }
  }
}

//重なりの判定
bool HPModel2D::overlap(int n){
  for(int i=n-4;i>=0;i--,i--){
    if(sequence[i].x!=sequence[n].x)
      continue;
    else if(sequence[i].y!=sequence[n].y)
      continue;
    else
      return true;
  }
  return false;
}

//エネルギーを整数で計算
int HPModel2D::Energy(){
  int E0 = 0;
  int E = 0;
  for(int i=0;i<Parameter::L-1;i++){
    E0 += this->sequence[i].getBase()*this->sequence[i+1].getBase();
  }
  for(int i=0;i<Parameter::L;i++){
    for(int j=i+1;j<Parameter::L;j++){
	  if(contactUpper(i,j)){
		E -= this->sequence[i].getBase()*this->sequence[j].getBase();
      }
      if(contactDown(i,j)){
		E -= this->sequence[i].getBase()*this->sequence[j].getBase();
      }
      if(contactRight(i,j)){
		E -= this->sequence[i].getBase()*this->sequence[j].getBase();
      }
      if(contactLeft(i,j)){
		E -= this->sequence[i].getBase()*this->sequence[j].getBase();
      }
    }
  }
  return E+E0;
}

//エネルギーを実数で計算
double HPModel2D::Energy(double gamma){
  double E0 = 0;
  double E = 0;
  for(int i=0;i<Parameter::L-1;i++){
    E0 += this->splitEnergy(i,i+1,gamma);
  }
  for(int i=0;i<Parameter::L;i++){
    for(int j=i+1;j<Parameter::L;j++){
	  if(contactUpper(i,j)){
		E += splitEnergy(i,j,gamma); 
      }
      if(contactDown(i,j)){
		E += splitEnergy(i,j,gamma); 
      }
      if(contactRight(i,j)){
		E += splitEnergy(i,j,gamma); 
      }
      if(contactLeft(i,j)){
		E += splitEnergy(i,j,gamma); 
      }
    }
  }
  return E-E0;
}

double HPModel2D::splitEnergy(int i,int j,double gamma){
  double split = 0;
  if(this->sequence[i].getBase() == 0){
    if(this->sequence[j].getBase() == 0)
      split -= 0;
    else if(this->sequence[j].getBase() == 1)
      split -= 1;
  }else if(this->sequence[i].getBase() == 1){
    if(this->sequence[j].getBase() == 0)
      split -= 1;
    else if(this->sequence[j].getBase() == 1)
      split -= 2+gamma;
  }
  return split;
}

//コンタクトの数を計算
int HPModel2D::contact(){
  int C0 = 0;
  int C = 0;
  for(int i=0;i<Parameter::L-1;i++)
    C0++;
  for(int i=0;i<Parameter::L;i++){
    for(int j=i+1;j<Parameter::L;j++){
	  if(contactUpper(i,j))
		C++;
      if(contactDown(i,j))
		C++;
      if(contactRight(i,j))
		C++;
      if(contactLeft(i,j))
		C++;
    }
  }
  return C-C0;
}

//慣性半径を計算
double HPModel2D::Rg(){
  double sum=0;
  double dx = 0;
  double dy = 0;
  for(int i=0;i<Parameter::L;i++)
    for(int j=0;j<Parameter::L;j++){
      dx = sequence[i].x-sequence[j].x;
      dy = sequence[i].y-sequence[j].y;
      sum += dx*dx+dy*dy;
    }
  double tmp = (Parameter::L+1)*(Parameter::L+1)*2;
  return sqrt(sum/tmp);
}

//末端間距離を計算
double HPModel2D::distance_end_end(){
  int dx = this->sequence[Parameter::L-1].x - this->sequence[0].x;
  int dy = this->sequence[Parameter::L-1].y - this->sequence[0].y;
  return sqrt(dx*dx+dy*dy);
}
