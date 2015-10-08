/*
 * simulator.cpp
 *
 *  Created on: Sep 24, 2015
 *      Author: vapashos
 */

#include "simulator.h"
#include <algorithm>


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
	s->showChannelQueues();//2 is the size of segment
}

void simulator::checkNodesBroadcast(){

	for(unsigned int i=0;i<nodeList.size();i++){
		if(nodeList[i]->readyToBroadcast){
			//if(find(broadcastList.begin(),broadcastList.end(),nodeList[i])!=broadcastList.end()){
		//		cout<<"node "<<nodeList[i]->id<<" already in broadcast list"<<endl;
		//	}
			//else{
			//Sthn ousia h broadcast list tha periexei aithseis apo ton antistoixo kombo gia broadcast
			//opote de mas peirazei na iparxoun parapanw apo 1 aithseis apo idio node
				broadcastList.push_back(nodeList[i]);
				cout<<"node "<<nodeList[i]->id<<" added in the broadcasting list";
				nodeList[i]->readyToBroadcast=false;
			//}
		}
	}
	showBroadcastList();
}
void simulator::initReadyToBroadcastFlag(){
	//Executed on each timeslot to inititalize readyToBroadcastFlag;
	for(unsigned int i=0;i<nodeList.size();i++){
		nodeList[i]->readyToBroadcast=false;
	}
}

void simulator::showBroadcastList(){
	cout<<"broadcast list :";
	if(broadcastList.empty()){
		cout<<"is empty"<<endl;
		return;
	}

	for(unsigned int i=0;i<broadcastList.size();i++){
		cout<<"n"<<broadcastList[i]->id<<" ";
	}
	cout<<endl;
}

void simulator::setBroadcastNode(){

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
		cout<<"there are more than one candidates for broadcasting ";
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



