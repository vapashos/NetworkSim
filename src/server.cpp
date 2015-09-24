/*
 * server.cpp
 *
 *  Created on: Sep 9, 2015
 *      Author: vapashos
 */

#include "server.h"

server::server() {
	// TODO Auto-generated constructor stub

}

server::~server() {
	// TODO Auto-generated destructor stub
}


void server::createPacketList(){

	//int numberofPackets this is in case of testing the functionality of simulator
	int numOFPackets=20;
	int generationSize=2;//number of packets that belong on a segment
	deque<unsigned char > temp;
	//each packet created will have payload 1 byte equal to its id
	for(unsigned int i=0;i<numOFPackets;i++){
		temp.push_back(i+1);
		packetsToDownload.push_back(packet(0,0,temp));
		temp.clear();
	}
	//allocate packets to segments
	int counter=0;
	for(unsigned int i=0;i<packetsToDownload.size();i++){
		if(i%generationSize==0){
			counter=0;
//			if(!segmentList.empty())
//				segmentList.back().showSegmentPackets();
			segmentList.push_back(segment());
		}
		packetsToDownload[i].segmentID=segmentList.back().id;
		segmentList.back().addPacketOnSegment(&packetsToDownload[i]);
	}
}

void server::showPacketList(){
	for(unsigned int i=0;i<packetsToDownload.size();i++){
		cout<<"p"<<packetsToDownload[i].id<<":";
		packetsToDownload[i].showPayload();
	}
}

void server::initChannels(int channelsNumber,float maxlossProb,float minlossProb){
	//channels Number is equal to the number of users
	//each user uses one channel to download data from server
	numberOf3GChannels=channelsNumber;
	for(int i=0;i<channelsNumber;i++){
		channels3G.push_back(channel(getRandomNumber(maxlossProb,minlossProb)));
	}
}

void server::allocatePacketsOnChannels(){

	//for each user we allocate segments not packets in round robin
	cout<<"inside allocatePacketsOnChannels segmentList size="<<segmentList.size()<<endl;
	for(unsigned int i=0;i<segmentList.size();i++){
		cout<<"seg:"<<segmentList[i].id<<"=";
		for(unsigned int j=0;j<segmentList[i].packetList.size();j++){
			cout<<"pID"<<segmentList[i].packetList[j]->id<<" ";
			packet temp=packet(*segmentList[i].packetList[j]);
			channels3G[i%channels3G.size()].packetQueue.push_back(temp);
		}
		cout<<endl;
	}
}


void server::showChannelQueues(){
	for(unsigned int i=0;i<channels3G.size();i++){
		channels3G[i].showChannel();
	}
}

void server::showSegmentList(){

	for(unsigned int i=0;i<segmentList.size();i++){
		cout<<"----------------------------------------------"<<endl;
		cout<<"seg"<<segmentList[i].id<<"size"<<segmentList[i].packetList.size()<<endl;
		for(unsigned int j=0;j<segmentList[i].packetList.size();j++){
			cout<<"p"<<segmentList[i].packetList[j]->id<<":"<<segmentList[i].packetList[j]->isLast<<"| ";
			segmentList[i].packetList[j]->showPayload();
		}
		cout<<endl;
		segmentList[i].showLastPacket();
	}

}

