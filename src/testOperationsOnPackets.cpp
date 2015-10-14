/*
 * testOperationsOnPackets.cpp
 *
 *  Created on: Oct 11, 2015
 *      Author: vapashos
 */

#include "testOperationsOnPackets.h"

testOperationsOnPackets::testOperationsOnPackets() {
	// TODO Auto-generated constructor stub

}

testOperationsOnPackets::~testOperationsOnPackets() {
	// TODO Auto-generated destructor stub
}

void testOperationsOnPackets::createPoolOfPackets(int packetsNum,int payloadSize){

	deque<unsigned char> pLoad;
	for(unsigned int i=0;i<packetsNum;i++){
		for(int j=0;j<payloadSize;j++){
			pLoad.push_back((unsigned char)getRandomNumber(255,0));
		}
		packetsForTesting.push_back(packet(0,new ffNumber(i+1),pLoad));
		pLoad.clear();
	}
}


void testOperationsOnPackets::showPoolOfPackets(){

	for(unsigned int i=0;i<packetsForTesting.size();i++){
		cout<<"testPkt"<<i+1<<" ";
		packetsForTesting[i].showPayload();
	}
}


void testOperationsOnPackets::multiplyPacket(packet p,ffNumber x){
	cout<<"before multiplication"<<endl;
	p.showPayload();
	packet temp=p*x;
	cout<<"after multiplication "<<endl;
	temp.showPayload();

}


void testOperationsOnPackets::addPackets(packet *p1,packet *p2){
	cout<<"before packet Addition"<<endl;
	cout<<"p1 payload:"<<endl;
	p1->showPayload();
	cout<<"p2 payload"<<endl;
	p2->showPayload();
	cout<<"after packets addition"<<endl;
	packet temp=*p1+*p2;
	temp.showPayload();
}

