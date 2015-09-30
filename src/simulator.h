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
	deque<node*> broadcastList;//list of nodes ready to broadcast
	node* broadcastNode;
	int numOfNodes;
	server *s;
	simulator(int nodesNum,server *srv);
	void createMeshTopology();
	void allocatePacketsOnChannels();
	void showChannelQueues();
	void checkNodesBroadcast();//iterates over nodelist to check if someone can broadcast checking {readyToBroadcast} variable
	void initReadyToBroadcastFlag();
	void showBroadcastList();
	void setBroadcastNode();//Decide which node among the candidates will be the broadcast node this check is done every second
	virtual ~simulator();
};

#endif /* SIMULATOR_H_ */
