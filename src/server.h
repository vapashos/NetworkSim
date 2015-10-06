/*
 * server.h
 *
 *  Created on: Sep 9, 2015
 *      Author: vapashos
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "segment.h"
#include "generalFunctions.h"
#include "channel.h"
class server {
public:
	deque<packet> packetsToDownload;//list of packets that users have to download
	deque<channel> channels3G;
	deque<segment> segmentList;
	int numberOf3GChannels;
	server();
	server(const server &x);
	void createPacketList();//creates packets for trasmition and assigns packets to segments
	void showPacketList();//Show packet list with data that users are going to download
	void initChannels(int channelsNumber,float maxlossProb,float minlossProb);//Initialise parameters of channels for 3G
	void allocatePacketsOnChannels();//this function allocate packets among channels - users in round robin
	void allocateSegmentsOnChannels();
	void showChannelQueues();
	void showChannelSegQueues();
	void showSegmentList();
	virtual ~server();
};

#endif /* SERVER_H_ */
