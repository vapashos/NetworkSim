/*
 * message.h
 *
 *  Created on: 3 Σεπ 2015
 *      Author: pasvas
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>
using namespace std;

class message {
public:
	static int counter;
	int id,senderID,receiverID;
	message();
	message(const message &m);
	virtual ~message();
};

#endif /* MESSAGE_H_ */
