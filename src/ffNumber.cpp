/*
 * ffNumber.cpp
 *
 *  Created on: 9 ��� 2015
 *      Author: pasvas
 */

#include "ffNumber.h"

ffNumber::ffNumber(){
	//char c;
	//cout<<"call of default constuctor ffNumber";
	number=0;
	ff=new finiteField(2,8);
	//cin>>c;
}

ffNumber::ffNumber(int x){
	number=x;
	ff=new finiteField(2,8);
}


ffNumber::ffNumber(int n,finiteField *x) {
	number=n;
	ff=x;

}

ffNumber::ffNumber(const ffNumber &x){
	number=x.number;
	ff=x.ff;
}



ffNumber::~ffNumber() {
	//delete ff;
}


ffNumber operator *(const ffNumber &a,int x){
	return ffNumber(a.ff->mul[a.number][x],a.ff);
}

ffNumber operator *(int x,const ffNumber &a){
	return ffNumber(a.ff->mul[a.number][x],a.ff);
}

ffNumber operator *(const ffNumber &a,const ffNumber &b){
	char c;
	if(a.number>255 || b.number>255){
		cout<<"Error in finite numbers"<<a.number<<" and "<<b.number<<endl;
		cin>>c;
	}

	return(ffNumber(a.ff->mul[a.number][b.number],a.ff));
}

ffNumber operator +(const ffNumber &a,const ffNumber &b){
	//cout<<"inside operator + overloading a.number="<<a.number<<" and b.number="<<b.number<<endl;
	return(ffNumber(a.ff->sum[a.number][b.number],a.ff));
}

ffNumber operator /(const ffNumber &a,const ffNumber &b){
	return(ffNumber(a.ff->div[a.number][b.number],a.ff));
}


ffNumber operator /(int x,const ffNumber &a){
	return(ffNumber(a.ff->div[x][a.number],a.ff));
}

ostream& operator <<(ostream &os,const ffNumber &a){
	os<<a.number;
	return os;
}
