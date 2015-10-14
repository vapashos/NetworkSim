//============================================================================
// Name        : NetworkSim.cpp
// Author      : S
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "simulator.h"
#include "testOperationsOnPackets.h"



int main() {


	//node();
	//create set of 5 nodes
	int numOfNodes=5;

	server *s=new server();
	s->createPacketList();
	s->showPacketList();
	s->showSegmentList();
	s->initChannels(numOfNodes,0.6,0.2);


	simulator mySim(5,s);
	s->showPacketList();
	mySim.s->showPacketList();
	mySim.createMeshTopology();
	mySim.allocatePacketsOnChannels();
	mySim.showChannelQueues();

	bool flag=false;//flag to check if there is nothing else to be downloaded from 3G for any node
		for(int i=0;!flag && i<100 ;i++){//100 timeslots
			cout<<"---------- this tis timeslot "<<i<<" ---------------------"<<endl;
			flag=true;
			mySim.setBroadcastNode();
			for(unsigned int j=0;j<mySim.nodeList.size();j++){
				if(!mySim.nodeList[j]->ch3G->packetQueue.empty()){
					flag=false;
					if( getRandomNumber((float)1.0,0.0)>=mySim.nodeList[j]->ch3G->lossProb){
						flag=mySim.nodeList[j]->download3GPacket();
						mySim.checkNodesBroadcast();
					}
				}
				mySim.nodeList[j]->ch3G->showChannel();
				//after each node downloads each packet it checks if it has downloaded a segment so it can start the broadcast
			}
		}


		for(unsigned int i=0;i<mySim.nodeList.size();i++){
			mySim.nodeList[i]->showSegmentQueue();
			mySim.nodeList[i]->showCodedPackets();
		}

		//Check operations on packets permanently

/*
  Use testOperationOnPackets class to test operations over packets
		testOperationsOnPackets x;
		x.createPoolOfPackets(3,3);
		x.showPoolOfPackets();
		//x.multiplyPacket(x.packetsForTesting[0],ffNumber(5));
		x.addPackets(&x.packetsForTesting[0],&x.packetsForTesting[1]);

*/
	return 0;
}
