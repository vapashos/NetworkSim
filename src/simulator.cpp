/*
 * simulator.cpp
 *
 *  Created on: Sep 24, 2015
 *      Author: vapashos
 */

#include "simulator.h"



simulator::simulator(int nodesNum,server *srv){
	numOfNodes=nodesNum;
	for(int i=0;i<numOfNodes;i++){
		nodeList.push_back(new node());
	}
	s=srv;
}

simulator::~simulator() {
	// TODO Auto-generated destructor stub
}

void simulator::createMeshTopology(){

	for(unsigned int i=0;i<nodeList.size();i++){
		for(unsigned int j=0;j<nodeList.size();j++){
			if(i!=j)
				nodeList[i]->addNeighbor(nodeList[j]);
		}
			//	nodeList[i]->showNeighborList();
		nodeList[i]->connectOn3GChannel(&s->channels3G[i]);// user with id=i is connected to channel with id=i
	}
}
void simulator::allocatePacketsOnChannels(){
	s->allocatePacketsOnChannels();
}
void simulator::showChannelQueues(){
	s->showChannelQueues();
}
