/*
 * node.cpp
 *
 *  Created on: 3 ��� 2015
 *      Author: pasvas
 */

#include "node.h"
int node::counter=0;

channel* node::wlan=new channel();

node::node() {
	// TODO Auto-generated constructor stub
	counter++;
	id=counter;
	ch3G=NULL;
	cout<<"Node "<<id<<" created"<<endl;
	segmentIDInitialPush=0;
}

node::~node() {
	// TODO Auto-generated destructor stub
}

void node::initChannelWlan(float lossProb){
	wlan=new channel(lossProb);
}

void node::showChannelWlan(){
	if(wlan->packetQueue.empty()){
		cout<<"wlan queue is empty"<<endl;
		return;
	}
	cout<<"----------------------------------------------"<<endl;
	cout<<"|                 wlan                     -"<<endl;
	cout<<"----------------------------------------------"<<endl;
	cout<<"|";
	for(unsigned int i=0;i<wlan->packetQueue.size();i++){
		cout<<"   p"<<wlan->packetQueue[i].id<<"   ";
	}
	cout<<"|"<<endl<<"|";

	for(unsigned int i=0;i<wlan->packetQueue.size();i++){
		cout<<" seg"<<wlan->packetQueue[i].segmentID<<"   ";
	}
	cout<<"|"<<endl<<"|";
	for(unsigned int i=0;i<wlan->packetQueue.size();i++){
		cout<<" (s"<<wlan->packetQueue[i].senderID<<"-r"<<wlan->packetQueue[i].receiverID<<") ";
	}
	cout<<"|"<<endl;
}

void node::broadcastPacket(){
	//Scans coded packet queue removes the packets from that queue and
	//inserts them inside packetQueue of wlan adding the receiver.

	if(segmentIDInitialPush==0){
		cout<<"segmentID for initial push is not set"<<endl;
		return;
	}
	cout<<"start adding coded packets on wlan"<<endl;
	for(unsigned int j=0;j<codedPacketsQueue[segmentIDInitialPush].size();j++){
		packet Temp=codedPacketsQueue[segmentIDInitialPush][j];
		for(unsigned int i=0;i<neighborList.size();i++){
			Temp.receiverID=neighborList[i]->id;
			Temp.senderID=id;
			//check Probability loss before putting it on wlan channel queue
			if(node::wlan->lossProb<getRandomNumber((float)1,(float)0))
				node::wlan->addPacket(Temp);
		}
	}
	//Clear node's list of coded packets
	codedPacketsQueue[segmentIDInitialPush].clear();
	cout<<"node"<<id<<" after broadcasting "<<segmentIDInitialPush<<" i shall release the flag"<<endl;
	cout<<"wlan queue"<<endl;
	showChannelWlan();
	cout<<"node coded packets queue"<<endl;
	showCodedPackets();
}


void node::downloadWlanPacket(){

	//Broadcast node should not enter this function
	cout<<"#### Node"<<this->id<<" Donwload Wlan Packet ######"<<endl;
	if(node::wlan->packetQueue.size()==0){
		return;
	}
	deque <packet> ::iterator iter=node::wlan->packetQueue.end();
	cout<<"node "<<this->id<<" check to download WLAN packet"<<endl;
	for(unsigned int i=0;i<node::wlan->packetQueue.size();i++){
		if(node::wlan->packetQueue[i].receiverID==this->id){
			cout<<"packet "<<node::wlan->packetQueue[i].id<<" ";
			node::wlan->packetQueue[i].showPayload();
			cout<<"with receiver id"<<node::wlan->packetQueue[i].receiverID<<"  was destined for me"<<endl;
			inComingCodedPackets[node::wlan->packetQueue[i].segmentID].push_back(node::wlan->packetQueue[i]);
			//Have to remove it from wlan channel queue
			iter=node::wlan->packetQueue.begin()+i;
			cout<<"before exiting iterator receiverid"<<iter->receiverID<<" and packetID"<<iter->id<<endl;
			break;
		}
	}

	if(iter!=node::wlan->packetQueue.end()){
		//erase
		cout<<"node "<<this->id<<" download packet function found element for me "<<iter->id<<" receiverid "<<iter->receiverID<<" remove it"<<endl;
		cout<<"size of queue before erasing"<<node::wlan->packetQueue.size()<<endl;
		showChannelWlan();
		node::wlan->packetQueue.erase(iter);
		cout<<"size of queue after erasing"<<node::wlan->packetQueue.size()<<endl;
		showChannelWlan();
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
		readyToBroadcast=false;
		return true;
	}

	//Add packet on in3GQueue and remove it then from channel3G
	in3GQueue.push_back(ch3G->packetQueue.front());
	ch3G->packetQueue.pop_front();
	cout<<"After downloading packet ";
	showQueue(in3GQueue);
	//check if the packet downloaded is the last packet of the segment so the user can broadcast
	if(in3GQueue.back().isLast){
		cout<<"node "<<id<<" can start the BROADCAST of segment "<<in3GQueue.back().segmentID<<endl;
		//set the flag readyToBroadcast equal to true to insert the node in broadcast list queue.
		readyToBroadcast=true;
		//Update segmentQueue Map
		in3GSegmentQueue[in3GQueue.back().segmentID]=in3GQueue;
		//Create coded packets
		//Supress for the time being the execution of created coded packets
		createCodedPackets(in3GQueue.back().segmentID);
		segmentIDInitialPush=in3GQueue.back().segmentID;
		//Clear the in3GQueue;
		in3GQueue.clear();
		//Make the initialpush
	}
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

void node::showSegmentQueue(){
	map<int, deque<packet> >::iterator it;
	for(it=in3GSegmentQueue.begin();it!=in3GSegmentQueue.end();it++){
		cout<<"segment"<<it->first;
		showQueue(it->second);
	}
}


void node::createCodedPackets(int segmentID){
	//first find the size of segment
	int segmentSize =in3GSegmentQueue[segmentID].size();
	if(segmentSize==0)
		return;
	//select random coefficients
	deque<ffNumber> coefficients;
	cout<<"create coded packets coefficients table:"<<endl;
	//The number of coded packets that are going to be prepared
	//are equal to the number of packets that belong to the segment
	//also to create a coded packet we have to create linear combination
	for(unsigned int i=0;i<in3GSegmentQueue[segmentID].size();i++){
		packet Temp;
		int randomCoeff;
		for(int j=0;j<segmentSize;j++){
			randomCoeff=getRandomNumber(255,0);
			coefficients.push_back(ffNumber(randomCoeff));
			Temp=Temp+coefficients[j]*in3GSegmentQueue[segmentID][j];
		}
		//add random coefficients on coded packet just created
		Temp.addCoefficients(coefficients);
		//For debugging
		//Temp.showRandCoefs();
		coefficients.clear();
		codedPacketsQueue[segmentID].push_back(Temp);
	}
}

void node::showCodedPackets(){
	cout<<"node"<<id<<"show coded Packets "<<endl;
	for(map<int, deque <packet> >::iterator it=codedPacketsQueue.begin();it!=codedPacketsQueue.end();it++){
		for(unsigned int i=0;i<it->second.size();i++){
			it->second[i].showRandCoefs();
			it->second[i].showPayload();
		}
	}
}


void node::showInCodedPackets(){
	cout<<"node"<<id<<"show incoming coded Packets "<<endl;
	for(map<int, deque <packet> >::iterator it=inComingCodedPackets.begin();it!=inComingCodedPackets.end();it++){
		cout<<"segID"<<it->first;
		for(unsigned int i=0;i<it->second.size();i++){
			cout<<it->second[i].id<<" ";
		}
		cout<<endl;
	}
}
