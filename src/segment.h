/*
 * segment.h
 *
 *  Created on: Sep 13, 2015
 *      Author: vapashos
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_
#include "packet.h"

class segment {
public:
	static int counter;
	int id,size;
	deque<packet*> packetList;//The list of packets that belong to the segment
	packet* lastPacket;//This pointer always points on the last packet
	void addPacketOnSegment(packet *p);
	void showLastPacket();
	packet* getLastPacket();//function that returns a handler to the last packet of the segment
	segment();
	segment(int size);
	segment(const segment &s);
	virtual ~segment();
};

#endif /* SEGMENT_H_ */
