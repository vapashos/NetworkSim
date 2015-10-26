/*
 * node.h
 *
 *  Created on: 3 ��� 2015
 *      Author: pasvas
 */

#ifndef NODE_H_
#define NODE_H_
#include <map>
#include "channel.h"
#include "segment.h"
#include "ffNumber.h"
#include "generalFunctions.h"

class node {
public:
	static int counter;

	channel *ch3G;/*channel to download data from the server*/
	deque<node*> neighborList;
	static channel *wlan;/*This channel is shared between nodes to transmit packets over it*/
	deque<packet> in3GQueue;//Queue with incoming packets of 3G
	map<int,deque <packet> > in3GSegmentQueue;
	map<int,deque <packet> > codedPacketsQueue;
	map<int ,deque <packet> > inComingCodedPackets;//Map for incoming coded packets per segment
	deque<packet> outQueue;//Queue with coded packets to broadcast.
	int id,segmentIDInitialPush;//segmentIDInitialPush is the segment that has been received and node has to do thei initial push
	bool readyToBroadcast;//this variable is updated whenever the download of a segment is received.
	//functions
	static void initChannelWlan(float lossProb);
	static void showChannelWlan();
	void broadcastPacket();
	void downloadWlanPacket();
	void addNeighbor(node *n);//Keep information of adjacent nodes
	void connectOn3GChannel(channel* c);//connect user on 3G channel (sets pointer x)
	bool download3GPacket();//if there is nothing else to download return true
	void showNeighborList();//show neighbors
	void showQueue(const deque<packet> &queue);//show any type of packet queue
	void showSegmentQueue();
	//void readyToBroadcast();//Each timeslot we run this check to know if one node is ready for broadcast after downloading all the packets of segment
	void createCodedPackets(int segmentID);
	void showCodedPackets();
	void showInCodedPackets();
	//constructors-destructor
	node();
	virtual ~node();
};

#endif /* NODE_H_ */
