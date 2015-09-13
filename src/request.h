/*
 * request.h
 *
 *  Created on: 3 Σεπ 2015
 *      Author: pasvas
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include "message.h"

class request: public virtual message {
public:
	request();
	virtual ~request();
};

#endif /* REQUEST_H_ */
