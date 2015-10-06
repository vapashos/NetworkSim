/*
 * channel.h
 *
 *  Created on: 3 Σεπ 2015
 *      Author: pasvas
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_
#include "packet.h"
#include "segment.h"
class channel {
public:
	static int counter;
	int id;
	deque<packet> packetQueue;
	deque<segment*> segQueue;
	float lossProb;
	channel();
	channel(float prob);
	void addPacket(const packet &p);
	void removePacket();
	void showChannel();
	void showChannelSegments();
	virtual ~channel();

};

#endif /* CHANNEL_H_ */
