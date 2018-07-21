/*
 *  BDLD.cp
 *  BDLD
 *
 *  Created by Cyril Coelho on 20/07/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include "BDLD.h"
#include "BDLDPriv.h"

void BDLD::HelloWorld(const char * s)
{
	 BDLDPriv *theObj = new BDLDPriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void BDLDPriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

