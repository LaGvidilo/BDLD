/*
 *  BDLD.h
 *  BDLD_test
 *
 *  Created by Cyril Coelho on 21/07/18.
 *  Copyright 2018 INFORMABOX TECH. All rights reserved.
 *
 *	Version 0.1.0 prototype
 */
#ifndef BDLD_H
#define BDLD_H
#include "base64.h"
#include "md5.h"
#include "sha512.h"
#include <stdio.h>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <algorithm>

//is_like("Nicolas", "nicole"); //SOURCE , VALUECUR
using namespace std;

map <string, map<int, string> > getDataFromTable(string line, string selector);

class BDLD{
	public:
	void setFile(string pathfile);
	void createTable(string nametable);
	void dropTable(string nametable);
	map < string, map < int,string > > getTable(string nameTable,string selector);
	void saveFile(string pathfile);
	void createStruct(string nametable,string structure);
	void insertData(string nametable, string info[]);
	void deleteData(string nametable, int codeid);
	map <string, map<int, string> > getDataFromTable(string line, string selector);
	map <string, map<int, string> > getAllTable(string selector);
	
	map <string, map<int, string> > BUFF;
	
	private:
	bool exist;
	string file;
	map <string, map<int, string> > buffer;
	int ID_STRUCT;
	

};





#endif