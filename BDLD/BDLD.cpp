/*
 *  BDLD.cpp
 *  BDLD_test
 *
 *  Created by Cyril Coelho on 21/07/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include "BDLD.h"
#include "like.h"
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

int idget=0;

void reset_idget(){
	idget = 0;
} 

map <string, map<int, string> > BDLD::getDataFromTable(string line, string selector){
	map < string, map < int,string > > data;
	string col;
	//int id;
	string row;
	map<int,string> selected;
	int n=0;
	while (selector.find(";")!=string::npos){
		selected[n] = selector.substr(0,selector.find(";"));
		n+=1;
		selector = selector.substr(selector.find(";")+1);
	}
	idget++;
	//cout << "l: " << line << endl;
	while (line.find(",")!=string::npos){
		col = line.substr(0,line.find(":"));
		row = line.substr(line.find(":")+1,line.find(","));
		line = line.substr(line.find(",")+1);
		
		if ( selector == "*" || selectorIsGood(selected, col) ){
			data[col][idget] = row.substr(0,row.find(","));
			cout << "COL: " << col << endl;
			cout << "---ID: " << idget << endl;
			cout << "---ROW: " << data[col][idget] << endl;
			BUFF[col][idget] = data[col][idget];
		}
		

		
	}
	return data;
}

void BDLD::setFile(string pathfile){
	ID_STRUCT=0;
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
	reset_idget();
	map <string, map<int, string> > data;
	ifstream fichier(file.c_str());
	string line;
	//map <string, map<int, string> > afp;
	if (fichier.is_open()){
		//cout << "fichier ouvert: " << file << endl;
		while(getline(fichier,line)){
			line = base64_decode(line);
			//cout << "line: " << line << endl;
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

map <string, map<int, string> > BDLD::getAllTable(string selector){
	//reset_idget();
	map <string, map<int, string> > data;
	ifstream fichier(file.c_str());
	string line;
	//map <string, map<int, string> > afp;
	if (fichier.is_open()){
		//cout << "fichier ouvert: " << file << endl;
		while(getline(fichier,line)){
			line = base64_decode(line);
			//cout << "line: " << line << endl;
			if (line.find("$") != string::npos){
				data = getDataFromTable(line.substr(line.find("$")+1), selector);	
			}
			if (line.find("&") != string::npos){
				data = getDataFromTable(line.substr(line.find("&")+1), selector);	
			}
		}
		fichier.close();
	}
	return data;
}


void BDLD::dropTable(string nameTable){
	map <string, map<int, string> > data;
	data = buffer;
	ifstream fichier(file.c_str());
	string line;
	if (fichier.is_open()){
		while(getline(fichier,line)){
			line = base64_decode(line);
			if (line.find("$") != string::npos){
				if(line.substr(0,line.find("$"))!=nameTable){
					data = getDataFromTable(line.substr(line.find("$")+1), "*");
				}
			}
		}
		fichier.close();
	}
	buffer = data;

}

void BDLD::createTable(string nametable){
	map <string, map<int, string> > data;
	data = buffer;
	map<int, string> tmp;
	data[nametable] = tmp;
	buffer = data;
}

void BDLD::createStruct(string nametable,string structure){
	ID_STRUCT++;
	buffer[nametable][-(ID_STRUCT)] = structure;
}

void BDLD::insertData(string nametable, string info[]){
	int fpuff;
	string temp;
	string namecol;
	string typecol;
	string dtatmp;
	for (int it=0; it<sizeof(info)-1; it++){
		fpuff = buffer[nametable].end()->first;
		for (map<int, string>::iterator it2 = buffer[nametable].begin(); it2!=buffer[nametable].end(); ++it2){
			if (it2->first<0){
				temp = it2->second;
				namecol = temp.substr(0, temp.find(":"));
				typecol = temp.substr(temp.find(":")+1);
				
				if (is_equal_like(namecol,info[it].substr(0,info[it].find(":")))){
					cout << namecol << " , " << it2->first << "  <--" << endl;
					dtatmp = dtatmp + info[it]; 
					if (it<sizeof(info)-1){dtatmp=dtatmp+",";}
				}
				
			}
		}
	}
	buffer[nametable][fpuff] = dtatmp;
}

void BDLD::deleteData(string nametable, int codeid)
{
	//cout << "===" << buffer[nametable][codeid] << endl;
	buffer[nametable].erase(codeid);
	//cout << "===" << buffer[nametable][codeid] << endl;	
}

void BDLD::saveFile(string filepath){
	ifstream fichier(filepath.c_str());
	string line;
	map <int, string> afp;
	int sid = 0;
	if (fichier.is_open()){
		while(getline(fichier,line)){
			line = base64_decode(line);
			sid++;
			afp[sid] = line;
		}
	}
	fichier.close();
				

	ofstream fichier2(filepath.c_str());
	map <int, string> tarte;
	stringstream SS1;
	stringstream SS2;
	string dt;
	//buffer = getAllTable("*");
	for (map <string, map <int, string> >::iterator it=buffer.begin(); it!=buffer.end(); ++it){
		tarte = it->second;
		for (map <int , string>::iterator it2=tarte.begin(); it2!=tarte.end(); ++it2){
			if (it2->first < 0){
				SS1 << it->first << "&" << it2->second << endl;
				dt = SS1.str();
				fichier2 << base64_encode((unsigned char*)dt.c_str(),strlen(dt.c_str())) << endl;
				SS1.str("");
			}
			else{
				SS2 << it->first << "$" << it2->second << endl;
				dt = SS2.str();
				fichier2 << base64_encode((unsigned char*)dt.c_str(),strlen(dt.c_str())) << endl;
				SS2.str("");
			}
		}
	}

	//fichier << SS1.str() << endl;//base64_encode((unsigned char*)dt.c_str(),strlen(dt.c_str())) << endl;
	//fichier << SS2.str() << endl;
	fichier2.close();

	ifstream fichier3(filepath.c_str());
	line="";
	map <int, string> afp2;
	sid = 0;
	if (fichier3.is_open()){
		while(getline(fichier3,line)){
			line = base64_decode(line);
			sid++;
			afp2[sid] = line;
		}
	}
	fichier3.close();
	
	
	ofstream fichier4(filepath.c_str());
	for (map<int, string>::iterator it=afp.begin(); it!=afp.end(); ++it)
	{
		dt = it->second;
		for (map<int, string>::iterator uu=afp2.begin(); uu!=afp2.end(); ++uu)
		{
		
			if (dt == uu->second){
				afp2.erase(uu->first);
			}
		
		}
		fichier4 << base64_encode((unsigned char*)dt.c_str(),strlen(dt.c_str())) << endl;
	}
	for (map<int, string>::iterator it=afp2.begin(); it!=afp2.end(); ++it)
	{
		dt = it->second;
		fichier4 << base64_encode((unsigned char*)dt.c_str(),strlen(dt.c_str())) << endl;
	}	
	fichier4.close();
}




