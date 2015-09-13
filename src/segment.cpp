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
}


segment::segment(int size){
	counter++;
	id=counter;
	size=0;//undefined size
}

segment::segment(const segment &s){
	id=s.id;
	size=s.size;
	packetList=s.packetList;
}

segment::~segment() {
	// TODO Auto-generated destructor stub
}

void segment::addPacketOnSegment(packet *p){
	packetList.push_back(p);
	size++;
	//cout<<"segment"<<id<<" add packet"<<packetList.back()->id<<" new size="<<size<<endl;
}
