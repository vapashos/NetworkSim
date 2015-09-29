/*
 * channel.cpp
 *
 *  Created on: 3 ��� 2015
 *      Author: pasvas
 */

#include "channel.h"

int channel::counter=0;
channel::channel() {
	// TODO Auto-generated constructor stub
	counter++;
	id=counter;
	cout<<"channel id"<<id<<endl;
}

channel::channel(float prob){
	counter++;
	id=counter;
	lossProb=prob;//Set the loss probability
	cout<<"channel"<<id<<" with "<<lossProb<<" just created"<<endl;
}


channel::~channel() {
//	cout<<"channel destructor"<<endl;
	// TODO Auto-generated destructor stub
}

void channel::addPacket(const packet &p){
	cout<<"packet with id "<<p.id<<" is going to be transmitted "<<endl;
	packetQueue.push_back(p);
}

void channel::showChannel(int segmentSize){
	if(packetQueue.empty()){
		cout<<"packet Queue is empty"<<endl;
		return;
	}
	cout<<"*** ch"<<id<<" ***"<<endl;
	for(unsigned int i=0;i<packetQueue.size();i++){
		cout<<"========";
	}
	cout<<endl;
	for(unsigned int i=0;i<packetQueue.size();i++){
		if(i%segmentSize==0){
			if(i!=0)
				cout<<"}";
			cout<<"seg("<<packetQueue[i].segmentID<<"){ ";
		}
		cout<<"P"<<packetQueue[i].id<<" ";
	}
	cout<<"}"<<endl;
	for(unsigned int i=0;i<packetQueue.size();i++){
		cout<<"========";
	}
	cout<<endl<<endl;



}
