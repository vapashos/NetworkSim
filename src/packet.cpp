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
	//cout<<"Empty packet with ID"<<id<<" created sender"<<senderID<<"receiver:"<<receiverID<<endl;
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
