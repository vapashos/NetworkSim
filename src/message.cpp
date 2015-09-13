/*
 * message.cpp
 *
 *  Created on: 3 Σεπ 2015
 *      Author: pasvas
 */

#include "message.h"
int message::counter=0;

message::message() {
	// TODO Auto-generated constructor stub
	counter++;
	id=counter;
	senderID=receiverID=0;
	cout<<"this is message with id "<<id<<" sender and receiver are not defined"<<endl;
}

message::message(const message &m){
	id=m.id;
	senderID=m.senderID;
	receiverID=m.receiverID;
}




message::~message() {
	// TODO Auto-generated destructor stub
}

