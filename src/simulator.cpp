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
	broadcastNode=NULL;
}

simulator::~simulator() {
	// TODO Auto-generated destructor stub
}

void simulator::createMeshTopology(){
cout<<"Inside create mesh Topology"<<endl;
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
	cout<<"allocate Packets on Channels"<<endl;
	s->allocatePacketsOnChannels();
}

//A different approach
void simulator::allocateSegmentsOnChannels(){
	cout<<"allocate segments on Packets"<<endl;
	s->allocateSegmentsOnChannels();
}

void simulator::showChannelQueues(){
	s->showChannelQueues();
}

void simulator::checkForBroadcastNodes(){
	cout<<"candidates for Broadcast nodes:";
	for(unsigned int i=0;i<nodeList.size();i++){
		if(nodeList[i]->readyToBroadcast){
			//Node is candidate for broadcast
			nodeList[i]->readyToBroadcast=false;
			broadcastList.push_back(nodeList[i]);
			//Set flag that indiacates that user is ready to broadcast to false
			cout<<"n"<<nodeList[i]->id<<" ";
		}
	}
	cout<<endl;
}


void simulator::selectBroadcastNode(){

	if(broadcastNode!=NULL){
			cout<<"there exists broadcast node"<<endl;
			return;
		}

		if (broadcastList.empty())
			return;
		else if(broadcastList.size()==1){
				broadcastNode=broadcastList.front();
				broadcastList.pop_front();
				cout<<"broadcast node among 1 candidate was set to "<<broadcastNode->id<<endl;
				return;
		}
		else {
			cout<<"there are more than one candidates for broadcasting from 0 to "<<broadcastList.size()-1;
			int x=getRandomNumber(0,broadcastList.size()-1);
			cout<<" select randomly "<<x<<endl;
			broadcastNode=broadcastList[x];
			cout<<"before removing node"<<endl;
			showBroadcastList();
			//Remove the respective node from broadcast candidate list;
			broadcastList.erase(broadcastList.begin()+x);
			cout<<"after erasing "<<endl;
			showBroadcastList();
		}
}

void simulator::showBroadcastList(){
	cout<<"Broadcast list:";
	if(broadcastList.empty()){
		cout<<"is empty"<<endl;
		return;
	}
	for(unsigned int i=0;i<broadcastList.size();i++){
		cout<<"n"<<broadcastList[i]->id<<" ";
	}
	cout<<endl;
}


void simulator::updateDownloadedSegmentInfo(node *nodePtr){

	for(unsigned int i=0;nodePtr->downloadedSegmentIDs.size();i++){
		/*for()
		if(nodePtr->downloadedSegmentIDs[i]==)*/
	}
}
