//============================================================================
// Name        : NetworkSim.cpp
// Author      : S
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "node.h"
#include "message.h"
#include "server.h"




int main() {


	//node();
	//create set of 5 nodes
	int numOfNodes=5;
	deque<node*> nodeList;
	for(int i=0;i<numOfNodes;i++){
		nodeList.push_back(new node());
	}

	server s;
	s.createPacketList();
	s.showPacketList();
	s.showSegmentList();
	s.initChannels(numOfNodes,0.6,0.2);
	//Create neighbors of the nodes
	for(unsigned int i=0;i<nodeList.size();i++){
			for(unsigned int j=0;j<nodeList.size();j++){
				if(i!=j)
					nodeList[i]->addNeighbor(nodeList[j]);
			}
		//	nodeList[i]->showNeighborList();
			nodeList[i]->connectOn3GChannel(&s.channels3G[i]);// user with id=i is connected to channel with id=i
	}
	s.allocatePacketsOnChannels();
	s.showChannelQueues();

	//Simulate transmissions
	bool flag=false;//flag to check if there is nothing else to be downloaded from 3G for any node
	for(int i=0;!flag && i<100 ;i++){//100 timeslots
		cout<<"---------- this tis timeslot "<<i<<" ---------------------"<<endl;
		flag=true;
		for(unsigned int j=0;j<nodeList.size();j++){
			if(!nodeList[j]->ch3G->packetQueue.empty()){
				flag=false;
				if( getRandomNumber((float)1.0,0.0)>=nodeList[j]->ch3G->lossProb){
					flag=nodeList[j]->download3GPacket();
				}
			}
			nodeList[j]->ch3G->showChannel();
			//after each node downloads each packet it checks if it has downloaded a segment so it can start the broadcast

		}

	}



	return 0;
}
