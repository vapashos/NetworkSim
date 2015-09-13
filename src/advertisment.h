/*
 * advertisment.h
 *
 *  Created on: 3 Σεπ 2015
 *      Author: pasvas
 */

#ifndef ADVERTISMENT_H_
#define ADVERTISMENT_H_

#include "message.h"

class advertisment: public virtual message {
public:
	advertisment();
	virtual ~advertisment();
};

#endif /* ADVERTISMENT_H_ */
