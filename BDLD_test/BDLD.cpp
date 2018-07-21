/*
 *  BDLD.cpp
 *  BDLD_test
 *
 *  Created by Cyril Coelho on 21/07/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include "BDLD.h"

const unsigned long hash(const char *str){
	unsigned long hash = 5381;
	int c;
	
	while ((c=*str++))
		hash = ((hash<<5)+hash)+c;
	return hash;
}

bool selectorIsGood(map<int,string> selected,string col){
	for (map<int,string>::iterator it = selected.begin(); it != selected.end(); ++it){
		if (it->second==col){return true;}
	}
	return false;
}

map <string, map<int, string> > getDataFromTable(string line, string selector){
	map < string, map < int,string > > data;
	string col;
	int id;
	string row;
	map<int,string> selected;
	int n=0;
	while (selector.find(";")!=string::npos){
		selected[n] = selector.substr(0,selector.find(";"));
		n+=1;
		selector = selector.substr(selector.find(";")+1);
	}
	while (line.find(",")!=string::npos){
		col = line.substr(0,line.find("%"));
		sscanf(line.substr(line.find("%")+1,line.find(":")).c_str(),"%d",&id);
		row = line.substr(line.find(":")+1,line.find(","));
		line = line.substr(line.find(",")+1);
		
		if ( selector == "*" || selectorIsGood(selected, col) ){
			data[col][id] = row.substr(0,row.find(","));
			cout << "COL: " << col << endl;
			cout << "---ID: " << id << endl;
			cout << "---ROW: " << data[col][id] << endl;
		}
		

		
	}
	return data;
}

void BDLD::setFile(string pathfile){
	ifstream fichier(pathfile.c_str());
	if (fichier.is_open()){
		fichier.close();
		exist = true;
		file = pathfile;
	}
	else{
		exist = false;
		file = pathfile;
	}
}

map <string, map<int, string> > BDLD::getTable(string nameTable,string selector){
	map <string, map<int, string> > data;
	ifstream fichier(file.c_str());
	string line;
	if (fichier.is_open()){
		while(getline(fichier,line)){
			if (line.find("$") != string::npos){
				if(line.substr(0,line.find("$"))==nameTable){
					data = getDataFromTable(line.substr(line.find("$")+1), selector);
				}
			}
		}
		fichier.close();
	}
	return data;
}

map <string, map<int, string> > BDLD::dropTable(string nameTable){
	map <string, map<int, string> > data;
	ifstream fichier(file.c_str());
	string line;
	if (fichier.is_open()){
		while(getline(fichier,line)){
			if (line.find("$") != string::npos){
				if(line.substr(0,line.find("$"))!=nameTable){
					data = getDataFromTable(line.substr(line.find("$")+1), selector);
				}
			}
		}
		fichier.close();
	}
	buffer = data;
	return data;
}


map <string, map<int, string> > BDLD::createTable(string nametable){
	map <string, map<int, string> > data;
	data = buffer;
	data[nametable] = map<int, string>;
	buffer = data;
	return data;
}
