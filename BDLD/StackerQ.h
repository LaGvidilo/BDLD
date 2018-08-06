/*
 *  StackerQ.h
 *  StackerQ
 *
 *  Created by Cyril Coelho on 27/07/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef StackerQ_
#define StackerQ_
#include <map>
#include <string>
using namespace std;
/* The classes below are exported */
#pragma GCC visibility push(default)

class StackerQ{
	public:
	map<int, string> mapFile;
	string pop(){
		string tmp;
		tmp = "#";
		if (mapFile.begin()!=mapFile.end()){
			map<int, string>::iterator i = mapFile.begin();
			tmp = i->second;
			mapFile.erase(i);
		}
		return tmp;
	}
	void insert(string pathFile){
		mapFile[ID] = pathFile;
		ID++;
	}
		
	private:
	int ID;
};

#pragma GCC visibility pop
#endif
