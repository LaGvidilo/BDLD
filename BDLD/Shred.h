/*
 *  Shred.h
 *  Destroyer
 *
 *  Created by Cyril Coelho on 27/07/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
void shredder(string filePath){
	fstream is(filePath.c_str(), ios::out | ios::in | ios::binary);
	
	is.seekg(0, is.end);
	int length = is.tellg();
	is.seekg(0, is.beg);
	stringstream SS1;
	for (int i = 0; i<length; i++){
		for (int j = 0; j < 200; j++){
			SS1.str("");
			SS1 << (char) (rand()*(int)(256));
			is.seekg(i);
			is << SS1.str();
		}
		is.seekg(i);
		is << "#";
	}
	is.close();
	remove(filePath.c_str());
}