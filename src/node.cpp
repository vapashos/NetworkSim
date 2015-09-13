/*
 * node.cpp
 *
 *  Created on: 3 ��� 2015
 *      Author: pasvas
 */

#include "node.h"
int node::counter=0;
channel *node::wlan;
node::node() {
	// TODO Auto-generated constructor stub
	counter++;
	id=counter;
	ch3G=NULL;
	cout<<"Node "<<id<<" created"<<endl;
}

node::~node() {
	// TODO Auto-generated destructor stub
}

void node::initChannelWlan(float lossProb){
	node::wlan=new channel(lossProb);
}

void node::showChannelWlan(){
	if(node::wlan->packetQueue.empty()){
		cout<<"wlan queue is empty"<<endl;
		return;
	}
	cout<<"----------------------------------------------"<<endl;
	cout<<"|                 wlan                     -"<<endl;
	cout<<"----------------------------------------------"<<endl;
	for(unsigned int i=0;i<node::wlan->packetQueue.size();i++){
		cout<<"   p"<<node::wlan->packetQueue[i].id<<"    ";
	}
	cout<<endl;
	for(unsigned int i=0;i<node::wlan->packetQueue.size();i++){
		cout<<"(s"<<node::wlan->packetQueue[i].senderID<<"-r"<<node::wlan->packetQueue[i].receiverID<<") ";
	}
}

void node::broadcastPacket(){
	for(unsigned int i=0;i<5;i++){
		node::wlan->packetQueue.push_back(packet(1,i+1));
	}
}

void node::addNeighbor(node *n){
	neighborList.push_back(n);
	//cout<<"Node"<<id<<" add node in"<<neighborList.back()->id<<endl;
}


void node::connectOn3GChannel(channel* c){
	ch3G=c;
	cout<<"User "<<id<<" is now connected on channel "<<ch3G->id<<" with loss probability "<<ch3G->lossProb<<endl;
}


bool node::download3GPacket(){
	//Check if the channel is empty first
	if(ch3G->packetQueue.empty()){
		cout<<"channel3G is empty"<<endl;
		return true;
	}

	//Add packet on in3GQueue and remove it then from channel3G
	in3GQueue.push_back(ch3G->packetQueue.front());
	ch3G->packetQueue.pop_front();
	cout<<"After downloading packet ";
	showQueue(in3GQueue);
	return false;
}


void node::showNeighborList(){
	cout<<"Node"<<id<<" neighborList:";
	if(neighborList.empty()){
		cout<<"-";
		return;
	}
	cout<<endl;
	for(unsigned int i=0;i<neighborList.size();i++){
		cout<<"n"<<neighborList[i]->id<<" ";
	}
	cout<<endl;
}


void node::showQueue(const deque<packet> &queue){
	cout<<"node"<<id<<" queue:";
	if(!queue.empty()){
		for(unsigned int i=0;i<queue.size();i++){
			cout<<"p"<<queue[i].id<<" ";
		}
		cout<<endl;
		return;
	}
	cout<<"-";

}


