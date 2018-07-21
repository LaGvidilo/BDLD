/*
 *  BDLD.h
 *  BDLD_test
 *
 *  Created by Cyril Coelho on 21/07/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef BDLD_H
#define BDLD_H
#include "base64.h"
#include "md5.h"
#include "sha512.h"
#include "cidl.h"
#include <stdio.h>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <istream>

using namespace std;

map <string, map<int, string> > getDataFromTable(string line, string selector);

class BDLD{
	public:
	void setFile(string pathfile);
	map <string, map<int, string> > createTable(string nametable);
	map <string, map<int, string> > dropTable(string nametable);
	map < string, map < int,string > > getTable(string nameTable,string selector);
	void saveFile(string pathfile);
	
	private:
	bool exist;
	string file;
	map <string, map<int, string> > buffer;
	

};





#endif