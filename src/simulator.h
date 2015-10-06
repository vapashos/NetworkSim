/*
 * simulator.h
 *
 *  Created on: Sep 24, 2015
 *      Author: vapashos
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_
#include "node.h"
#include "message.h"
#include "server.h"


class simulator {
public:
	deque<node*> nodeList;
	int numOfNodes;
	server *s;
	node* broadcastNode;//points anytime on broadcastingNode
	deque<node*> broadcastList;//requests of nodes for broadcast
	simulator(int nodesNum,server *srv);
	void createMeshTopology();
	void allocatePacketsOnChannels();
	void allocateSegmentsOnChannels();
	void showChannelQueues();
	void showBroadcastList();
	void checkForBroadcastNodes();
	void selectBroadcastNode();
	void updateDownloadedSegmentInfo(node *nodePtr);

	virtual ~simulator();
};

#endif /* SIMULATOR_H_ */

//Notes
//########### 1.function checkForBroadcastNodes ####################
//each time simulator runs a function that scans the node list to check if a node
//has readyToBroadcast flag true.which means that the node is ready to broadcast
//if there is a node ready for broadcast simulator will add him on broadcastCandidates queue
//after this simulator shall select a broadcastNode from the candidates.
