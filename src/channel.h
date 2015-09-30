/*
 * channel.h
 *
 *  Created on: 3 Σεπ 2015
 *      Author: pasvas
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_
#include "packet.h"

class channel {
public:
	static int counter;
	int id;
	deque<packet> packetQueue;
	float lossProb;
	channel();
	channel(float prob);
	void addPacket(const packet &p);
	void removePacket();
	void showChannel();
	virtual ~channel();

};

#endif /* CHANNEL_H_ */
