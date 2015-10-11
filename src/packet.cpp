/*
 * packet.cpp
 *
 *  Created on: 3 ��� 2015
 *      Author: pasvas
 */

#include "packet.h"
#include <bitset>
int packet::counter=0;

packet::packet() {
	counter++;
	id=counter;
	senderID=receiverID=0;
	cout<<"Empty packet with ID"<<id<<" created no sender or receiver defined"<<endl;
	// TODO Auto-generated constructor stub

}

packet::packet(int sID,int rID){
	counter++;
	id=counter;
	senderID=sID;
	receiverID=rID;
	cout<<"Empty packet with ID"<<id<<" created sender"<<senderID<<"receiver:"<<receiverID<<endl;
}

packet::packet(int sID,int rID,deque<unsigned char> &pLoad){
	counter++;
	id=counter;
	senderID=sID;
	receiverID=rID;
	payload=pLoad;
	cout<<"Packet with ID"<<id<<" created sender"<<senderID<<"receiver:"<<receiverID<<endl;
}

packet::packet(int segID,ffNumber *indexSegment,deque<unsigned char> &pLoad){
	//This constructor is used for packet after coding so the isLast info is not essential
	counter++;
	id=counter;
	segmentID=segID;
	indexInsideSegment=*indexSegment;
	payload=pLoad;
	isLast=false;
	cout<<"constructor of coded packet created"<<endl;
}

packet::packet(const packet &p) {
	// TODO Auto-generated constructor stub
	id=p.id;
	senderID=p.senderID;
	receiverID=p.receiverID;
	payload=p.payload;
	segmentID=p.segmentID;
	isLast=p.isLast;
	//cout<<"copy constructor for packet with id "<<id<<endl;
}

packet::~packet() {
	// TODO Auto-generated destructor stub
//	payload.clear();
}

void packet::showPayload(){
	for(unsigned int i=0;i<payload.size();i++){
		cout<<(int)payload[i]<<")"<<(bitset<8>)(payload[i])<<" ";
	}
	cout<<endl;
}

void packet::setSegmentID(int sID){
	segmentID=sID;
}

/*Overloaded Operators*/


packet operator * (const packet &a,ffNumber &x){
	deque<unsigned char > tempPayload;
	//1.multiply payload
	int z;
	for(unsigned int i=0;i<a.payload.size();i++){
		z=(int)a.payload[i];
		ffNumber c=z*x;
		tempPayload.push_back((unsigned char) c.number);
	}

	ffNumber tempIndexInsideSegment=a.indexInsideSegment*x;

	return packet(a.segmentID,&tempIndexInsideSegment,tempPayload);
}

packet operator * (ffNumber &x,const packet &a){
	return a*x;
}

/*packet operator * (const packet& a,int x){
	return a*ffNumber(x);
}

packet operator * (int x,const packet &a){
	return a*x;
}*/


packet operator + (const packet& a,const packet& b){

		deque<unsigned char > tempPayload;
		//1.multiply payload
		int z,w;
		for(unsigned int i=0;i<a.payload.size();i++){
			z=(int)a.payload[i];
			w=(int)b.payload[i];
			ffNumber c=ffNumber(z)+ffNumber(w);
			tempPayload.push_back((unsigned char) c.number);
		}
		//2.multiply sender and receiver ID
		ffNumber tempIndexInsideSegment=a.indexInsideSegment+b.indexInsideSegment;
		return packet(a.segmentID,&tempIndexInsideSegment,tempPayload);
}

