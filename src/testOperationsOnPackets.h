/*
 * testOperationsOnPackets.h
 *
 *  Created on: Oct 11, 2015
 *      Author: vapashos
 */

#ifndef SRC_TESTOPERATIONSONPACKETS_H_
#define SRC_TESTOPERATIONSONPACKETS_H_
#include "packet.h"
#include "generalFunctions.h"

class testOperationsOnPackets {
public:

	deque<packet> packetsForTesting;
	testOperationsOnPackets();
	virtual ~testOperationsOnPackets();
	void createPoolOfPackets(int packetsNum,int payloadSize);
	void showPoolOfPackets();
	void multiplyPacket(packet p,ffNumber x);
};

#endif /* SRC_TESTOPERATIONSONPACKETS_H_ */
