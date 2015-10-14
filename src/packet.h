/*
 * packet.h
 *
 *  Created on: 3 ��� 2015
 *      Author: pasvas
 */

#ifndef packet_H_
#define packet_H_
#include <deque>
#include <iostream>
#include "ffNumber.h"

using namespace std;

class packet {
public:
	static int counter;
	int id,senderID,receiverID;
	int segmentID;
	ffNumber indexInsideSegment;
	deque<ffNumber> randCoefficients;
	bool isLast;//flag that shows us tha this is the last packet of the segment
	deque<unsigned char> payload;
	//All the coded information shall be less tha 256 and shall be formulated as ffnumber
	//ffNumber header[8];//0:index inside segment,1:size in bytes,2:Rtp packet ID,3:lid,4:tid,5:qid,6:NalUnitID(similar to the number of line of file),7:NALUnitIDMultiplier(used for values >255)
	void showPayload() const;
	void setSegmentID(int sID);
	void addCoefficients(deque<ffNumber> coeff);
	void showRandCoefs();
	packet();
	packet(int sID,int rID);
	packet(int sID,int rID,deque<unsigned char> &pLoad);
	packet(int segID,ffNumber *indexSegment,deque<unsigned char> &pLoad);
	packet(const packet &p);
	virtual ~packet();
};

packet operator * (const packet& a,int x);
packet operator * (int x,const packet &a);
packet operator * (ffNumber &x,const packet &a);
packet operator * (const packet &a,ffNumber &x);
packet operator + (const packet& a,const packet& b);

#endif /* packet_H_ */
