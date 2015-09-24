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
	simulator(int nodesNum,server *srv);
	void createMeshTopology();
	void allocatePacketsOnChannels();
	void showChannelQueues();

	virtual ~simulator();
};

#endif /* SIMULATOR_H_ */
