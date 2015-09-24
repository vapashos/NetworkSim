/*
 * segment.cpp
 *
 *  Created on: Sep 13, 2015
 *      Author: vapashos
 */

#include "segment.h"


int segment::counter=0;


segment::segment() {
	// TODO Auto-generated constructor stub
	counter++;
	id=counter;
	size=0;//undefined size
	lastPacket=NULL;
}


segment::segment(int size){
	counter++;
	id=counter;
	size=0;//undefined size
	lastPacket=NULL;
}

segment::segment(const segment &s){
	id=s.id;
	size=s.size;
	packetList=s.packetList;
	lastPacket=s.lastPacket;
}

segment::~segment() {
	// TODO Auto-generated destructor stub
}

void segment::addPacketOnSegment(packet *p){
	packetList.push_back(p);
	if(lastPacket!=NULL)//there was no packet in the segment
		lastPacket->isLast=false;

	lastPacket=p;//always point to the last received packet.
	lastPacket->isLast=true;
	size++;
	//cout<<"segment"<<id<<" add packet"<<packetList.back()->id<<" new size="<<size<<endl;
}

void segment::showLastPacket(){
	if(lastPacket==NULL){
		cout<<"there is no last packet on this segment "<<endl;
		return;
	}
	cout<<"segment"<<id<<"last packet is p"<<lastPacket->id<<endl;
	lastPacket->showPayload();
}

packet* segment::getLastPacket(){
	return lastPacket;
}

