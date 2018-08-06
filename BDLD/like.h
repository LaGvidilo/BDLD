/*
 *  like.h
 *  BDLD_tool
 *
 *  Created by Myria Joao on 01/08/18.
 *  Copyright 2018 INFORMABOX TECH. All rights reserved.
 *
 */
 #include <iostream>
 #include <string>
 #include <map>
 
 using namespace std;
 
 bool is_like(string A, string B){
	map <string, int> counting1;
	map <string, int> counting2;
	string key;
	//compter les caractères de A
	for(string::iterator it1=A.begin(); it1!=A.end(); ++it1)
	{
		key = *it1;
		if (counting1.find(key) != counting1.end()){
			counting1[key] = counting1[key] + 1; 
		}
		else{
			counting1[key] = 1;
		}
	}

	//compter les caractères de B
	for(string::iterator it2=B.begin(); it2!=B.end(); ++it2)
	{
		key = *it2;
		if (counting2.find(key) != counting2.end()){
			counting2[key] = counting2[key] + 1; 
		}
		else{
			counting2[key] = 1;
		}
	}
 
	//int tailleA = sizeof(A);
	//int tailleB = sizeof(B);
	unsigned int occ1 = 0;
	unsigned int occ2 = 0;
	 
	for (map<string,int>::iterator it=counting1.begin(); it!=counting1.end(); ++it)
	{
		occ1=occ1+it->second;
		if (counting2.find(it->first) != counting2.end()){
			occ2=occ2+counting2[it->first];
		}
	}
	
	
	if (((float)occ2 / (float)occ1)>0.57){
		return true;
	}
	else{
		return false;
	}
 
 }

 bool is_equal_like(string A, string B){
	map <string, int> counting1;
	map <string, int> counting2;
	string key;
	//compter les caractères de A
	for(string::iterator it1=A.begin(); it1!=A.end(); ++it1)
	{
		key = *it1;
		if (counting1.find(key) != counting1.end()){
			counting1[key] = counting1[key] + 1; 
		}
		else{
			counting1[key] = 1;
		}
	}

	//compter les caractères de B
	for(string::iterator it2=B.begin(); it2!=B.end(); ++it2)
	{
		key = *it2;
		if (counting2.find(key) != counting2.end()){
			counting2[key] = counting2[key] + 1; 
		}
		else{
			counting2[key] = 1;
		}
	}
 
	//int tailleA = sizeof(A);
	//int tailleB = sizeof(B);
	unsigned int occ1 = 0;
	unsigned int occ2 = 0;
	 
	for (map<string,int>::iterator it=counting1.begin(); it!=counting1.end(); ++it)
	{
		occ1=occ1+it->second;
		if (counting2.find(it->first) != counting2.end()){
			occ2=occ2+counting2[it->first];
		}
	}
	
	
	if (((float)occ2 / (float)occ1)>0.99){
		return true;
	}
	else{
		return false;
	}
 
 }

