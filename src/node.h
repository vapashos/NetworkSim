/*
 * node.h
 *
 *  Created on: 3 ��� 2015
 *      Author: pasvas
 */

#ifndef NODE_H_
#define NODE_H_
#include "channel.h"
class node {
public:
	static int counter;
	static channel *wlan;/*This channel is shared between nodes to transmit packets over it*/
	channel *ch3G;/*channel to download data from the server*/
	deque<node*> neighborList;
	deque<packet> in3GQueue;//Queue with incoming packets of 3G
	int id;
	bool readyToBroadcast;//this variable is updated whenever the download of a segment is received.
	//functions
	static void initChannelWlan(float lossProb);
	static void showChannelWlan();
	void broadcastPacket();
	void addNeighbor(node *n);//Keep information of adjacent nodes
	void connectOn3GChannel(channel* c);//connect user on 3G channel (sets pointer x)
	bool download3GPacket();//if there is nothing else to download return true
	void showNeighborList();//show neighbors
	void showQueue(const deque<packet> &queue);//show any type of packet queue
	//void readyToBroadcast();//Each timeslot we run this check to know if one node is ready for broadcast after downloading all the packets of segment
	//constructors-destructor
	node();
	virtual ~node();
};

#endif /* NODE_H_ */
