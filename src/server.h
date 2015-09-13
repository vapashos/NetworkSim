/*
 * server.h
 *
 *  Created on: Sep 9, 2015
 *      Author: vapashos
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "packet.h"
#include "generalFunctions.h"
#include "channel.h"
class server {
public:
	deque<packet> packetsToDownload;
	deque<channel> channels3G;
	int numberOf3GChannels;
	server();
	void createPacketList();
	void showPacketList();//Show packet list with data that users are going to download
	void initChannels(int channelsNumber,float maxlossProb,float minlossProb);//Initialise parameters of channels for 3G
	void allocatePacketsOnChannels();//this function allocate packets among channels - users in round robin
	void showChannelQueues();
	virtual ~server();
};

#endif /* SERVER_H_ */
