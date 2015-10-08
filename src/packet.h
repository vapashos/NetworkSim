/*
 * packet.h
 *
 *  Created on: 3 ��� 2015
 *      Author: pasvas
 */

#ifndef PACKET_H_
#define PACKET_H_
#include <deque>
#include <iostream>

using namespace std;

class packet {
public:
	static int counter;
	int id,senderID,receiverID;
	int segmentID;

	bool isLast;//flag that shows us tha this is the last packet of the segment
	deque<unsigned char> payload;
	void showPayload();
	void setSegmentID(int sID);
	packet();
	packet(int sID,int rID);
	packet(int sID,int rID,deque<unsigned char> &pLoad);
	packet(const packet &p);
	virtual ~packet();
};

#endif /* PACKET_H_ */
