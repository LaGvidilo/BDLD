/*
 *  cidl.cpp
 *  CIDL
 *
 *  Created by Cyril Coelho on 30/06/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include "cidl.h"
#include "sha512.h"
#include <math.h>
#include <fstream>

const unsigned long hash(const char *str){
	unsigned long hash = 5381;
	int c;
	
	while ((c=*str++))
		hash = ((hash<<5)+hash)+c;
	return hash;
}

void KeyMat::init_hash(string key){
	HASHMINI = hash(key.c_str());
	MD5 = md5(HASHMINI);
	SHA512 = sha512(MD5);
	CHECKSUM64 = base64_encode((const unsigned char *)SHA512.c_str(),strlen(SHA512.c_str()));
	stringstream SS1;
	SS1 << MD5 << HASHMINI;
	COMBOSHA512 = sha512(SS1.str());
}

void KeyMat::init_seed(){
	srand( hash(COMBOSHA512.c_str()) );
	current=0;
}

bool XOR(bool a,bool b){
	return (a^b);
}

long int maybe_prime(long int x){
	return (x/sqrt(0.733))*log((cos(tan(0.267*x)))+x)+sin(tan(sqrt(sqrt((0.585*x)))));
}

void KeyMat::next_key(){
	stringstream S1;
	long int t=0;
	for (unsigned int it1=0; it1<8; ++it1){
		for (unsigned int it2=0; it2<8; ++it2){
			for (unsigned int it3=0; it3<8; ++it3){
				for (unsigned int it4=0; it4<8; ++it4){
					for (unsigned int it5=0; it5<8; ++it5){
						int R = rand() % 2;
						MAT[it1][it2][it3][it4][it5] = ((bool) (R));
						
						S1 << (char) MAT[it1][it2][it3][it4][it5];
						//cout << R;
						cout << "CREATION D'UNE NOUVELLE CLE: "<< t<<"/"<<8*8*8*8*8<<"(bits)"<<endl;
						t++;
					}
				}
			}
		}
	}
	string S2=S1.str();
}

void KeyMat::init_seed_RRB(){
	string TMP=S1.str();
	srand( hash(TMP.c_str()) );
	current_RRB=0;
}

void KeyMat::init_seed_BLOCK(){
	string TMP=S1.str();
	string shatmp = sha512(TMP.c_str());
	
	srand( hash(shatmp.c_str()) );
	NUMBERBLOCK = 2 + (2 * rand()) % 512;
}

bool KeyMat::open_read_file(const char filename[]){
	string line;
	TOTALOCT=0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			DATA.append(line +"\n");
			TOTALOCT += line.length()+1;
		}
		
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		fichier.close();
		return 1;
	}
	else {
		fichier.close();
		return 0;
	}
}

string open_detect_file_hash(const char filename[]){
	string line;
	string DATA;
	//TOTALOCT=0;
	int KARDE = 0;
	string sommedecontrol;
	ifstream fichier(filename);
	if (fichier.is_open()){
		bool HL = false;
		while (getline(fichier,line)){
			if (KARDE==0){
				string head = line;
			}
			if (KARDE==1){
				sommedecontrol=line;
			}
			if(KARDE>1){
				if (HL==true){
					DATA.append("\n");
				}
				DATA.append(line);
				HL = true;
				//TOTALOCT += line.length()+1;
			}
			KARDE++;
		}
		//TOTALOCT-=2;
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		fichier.close();
		return sommedecontrol;
	}
	else {
		fichier.close();
		return 0;
	}
}

string open_detect_file_type(const char filename[]){
	string line;
	//TOTALOCT=0;
	int KARDE = 0;
	string DATA;
	string head;
	ifstream fichier(filename);
	if (fichier.is_open()){
		bool HL = false;
		while (getline(fichier,line)){
			if (KARDE==0){
				head = line;
			}
			if (KARDE==1){
				string sommedecontrol=line;
			}
			if(KARDE>1){
				if (HL==true){
					DATA.append("\n");
				}
				DATA.append(line);
				HL = true;
				//TOTALOCT += line.length()+1;
			}
			KARDE++;
		}
		//TOTALOCT-=2;
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		fichier.close();
		return head;
	}
	else {
		fichier.close();
		return 0;
	}
}


bool KeyMat::open_read_file_dec(const char filename[]){
	string line;
	TOTALOCT=0;
	int KARDE = 0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		bool HL = false;
		while (getline(fichier,line)){
			if (KARDE==0){
				string head = line;
				if (head!="CK-CIDL-1-32768"){return 0;}
			}
			if (KARDE==1){
				string sommedecontrol=line;
				if (sommedecontrol!=CHECKSUM64){return 0;}
			}
			if(KARDE>1){
				if (HL==true){
					DATA.append("\n");
				}
				DATA.append(line);
				HL = true;
				TOTALOCT += line.length()+1;
			}
			KARDE++;
		}
		TOTALOCT-=2;
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		fichier.close();
		return 1;
	}
	else {
		fichier.close();
		return 0;
	}
}

void KeyMat::block(){
	//int taille = 16 + (2 * rand()) % 512;
	BLOCKD = DATA;
}


void KeyMat::encode(){
	DATA_ENC="";
	for (int temp = 0; temp < TOTALOCT; temp++){
		int csl = ((rand()*1) % 16);
		cout << "---+CRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_ENC += BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void KeyMat::write_file(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());
	
	//WRITE HEADER
	fichier << "CK-CIDL-1-32768\n";
	fichier << CHECKSUM64 << "\n";
	
	//WRITE DATA
	fichier << DATA_ENC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}

void KeyMat::decode(){
	DATA_DEC="";
	for (int temp = 0; temp < TOTALOCT; temp++){
		int csl = ((rand()*1) % 16);
		cout << "---+DECRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_DEC += BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void KeyMat::write_file_clear(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());

	//WRITE DATA
	fichier << DATA_DEC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}





/*
CIDL-2-32768bits

*/
void CIDL2::init_hash(string key){
	HASHMINI = hash(key.c_str());
	MD5 = md5(HASHMINI);
	SHA512 = sha512(MD5);
	CHECKSUM64 = base64_encode((const unsigned char *)SHA512.c_str(),strlen(SHA512.c_str()));
	stringstream SS1;
	SS1 << MD5 << HASHMINI;
	COMBOSHA512 = sha512(SS1.str());
}

void CIDL2::init_seed(){
	srand( hash(COMBOSHA512.c_str()) );
	current=0;
}

void CIDL2::next_key(){
	stringstream S1;
	long int t=0;
	int R=0;
	int P=0;
	for (unsigned int it1=0; it1<8; ++it1){
		for (unsigned int it2=0; it2<8; ++it2){
			for (unsigned int it3=0; it3<8; ++it3){
				for (unsigned int it4=0; it4<8; ++it4){
					
					R = rand() % 2;
					MAT[it1][it2][it3][it4][0] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][1] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][2] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][3] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][4] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][5] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][6] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][7] = ((int) (R));

					P = (((pow(2,0)*MAT[it1][it2][it3][it4][0])+(pow(2,1)*MAT[it1][it2][it3][it4][1])+(pow(2,2)*MAT[it1][it2][it3][it4][2])+(pow(2,3)*MAT[it1][it2][it3][it4][3])+(pow(2,4)*MAT[it1][it2][it3][it4][4])+(pow(2,5)*MAT[it1][it2][it3][it4][5])+(pow(2,6)*MAT[it1][it2][it3][it4][6])+(pow(2,7)*MAT[it1][it2][it3][it4][7])));
					P = P % 256;
					S1 << (char) P;
					
					//cout << R;
					cout << "CREATION D'UNE NOUVELLE CLE: "<< 8*t<<"/"<<8*8*8*8*8<<"(bits)"<<endl;
					t++;
					
				}
			}
		}
	}
	string S2=S1.str();
}

void CIDL2::init_seed_RRB(){
	string TMP=S1.str();
	srand( hash(TMP.c_str()) );
	current_RRB=0;
}

void CIDL2::init_seed_BLOCK(){
	string TMP=S1.str();
	string shatmp = sha512(TMP.c_str());
	
	srand( hash(shatmp.c_str()) );
	NUMBERBLOCK = 2 + (2 * rand()) % 512;
}

bool CIDL2::open_read_file(const char filename[]){
	string line;
	TOTALOCT=0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			DATA.append(line +"\n");
			TOTALOCT += line.length()+1;
		}
		
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

bool CIDL2::open_read_file_dec(const char filename[]){
	string line;
	TOTALOCT=0;
	int KARDE = 0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			if (KARDE==0){
				string head = line;
				if (head!="CK-CIDL-2-32768"){return 0;}
			}
			if (KARDE==1){
				string sommedecontrol=line;
				if (sommedecontrol!=CHECKSUM64){return 0;}
			}
			if(KARDE>1){
				DATA.append(line +"\n");
				TOTALOCT += line.length()+1;
			}
			KARDE++;
		}
		TOTALOCT-=2;
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

void CIDL2::block(){
	//int taille = 16 + (2 * rand()) % 512;
	BLOCKD = DATA;
}


void CIDL2::encode(){
	DATA_ENC="";
	for (int temp = 0; temp < TOTALOCT; temp++){
		int csl = ((rand()*1) % 16);
		cout << "---+CRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_ENC += BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL2::write_file(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());
	
	//WRITE HEADER
	fichier << "CK-CIDL-2-32768\n";
	fichier << CHECKSUM64 << "\n";
	
	//WRITE DATA
	fichier << DATA_ENC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}

void CIDL2::decode(){
	DATA_DEC="";
	for (int temp = 0; temp < TOTALOCT; temp++){
		int csl = ((rand()*1) % 16);
		cout << "---+DECRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_DEC += BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL2::write_file_clear(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());

	//WRITE DATA
	fichier << DATA_DEC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}






/*
CIDL-3-32768bits

*/
void CIDL3::init_hash(string key){
	HASHMINI = hash(key.c_str());
	MD5 = md5(HASHMINI);
	SHA512 = sha512(MD5);
	CHECKSUM64 = base64_encode((const unsigned char *)SHA512.c_str(),strlen(SHA512.c_str()));
	stringstream SS1;
	SS1 << MD5 << HASHMINI;
	COMBOSHA512 = sha512(SS1.str());
}

void CIDL3::init_seed(){
	srand( hash(COMBOSHA512.c_str()) );
	current=0;
}

void CIDL3::next_key(int mode){
	stringstream S1;
	long int t=0;
	int R=0;
	int P=0;
	for (unsigned int it1=0; it1<8; ++it1){
		for (unsigned int it2=0; it2<8; ++it2){
			for (unsigned int it3=0; it3<8; ++it3){
				for (unsigned int it4=0; it4<8; ++it4){
					
					R = rand() % 2;
					MAT[it1][it2][it3][it4][0] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][1] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][2] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][3] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][4] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][5] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][6] = ((int) (R));
					R = rand() % 2;
					MAT[it1][it2][it3][it4][7] = ((int) (R));

					P = (((pow(2,0)*MAT[it1][it2][it3][it4][0])+(pow(2,1)*MAT[it1][it2][it3][it4][1])+(pow(2,2)*MAT[it1][it2][it3][it4][2])+(pow(2,3)*MAT[it1][it2][it3][it4][3])+(pow(2,4)*MAT[it1][it2][it3][it4][4])+(pow(2,5)*MAT[it1][it2][it3][it4][5])+(pow(2,6)*MAT[it1][it2][it3][it4][6])+(pow(2,7)*MAT[it1][it2][it3][it4][7])));
					P = P % 256;
					if (mode == 0){
						P = P << abs(1+rand() % 128);
					}
					if (mode == 1){
						P = P >> abs(1+rand() % 128);
					}
					S1 << (char) P;
					
					//cout << R;
					cout << "CREATION D'UNE NOUVELLE CLE: "<< 8*t<<"/"<<8*8*8*8*8<<"(bits)"<<endl;
					t++;
					
				}
			}
		}
	}
	string S2=S1.str();
}

void CIDL3::init_seed_RRB(){
	string TMP=S1.str();
	srand( hash(TMP.c_str()) );
	current_RRB=0;
}

void CIDL3::init_seed_BLOCK(){
	string TMP=S1.str();
	string shatmp = sha512(TMP.c_str());
	
	srand( hash(shatmp.c_str()) );
	NUMBERBLOCK = 2 + (2 * rand()) % 512;
}

bool CIDL3::open_read_file(const char filename[]){
	string line;
	TOTALOCT=0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			DATA.append(line +"\n");
			TOTALOCT += line.length()+1;
		}
		
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

bool CIDL3::open_read_file_dec(const char filename[]){
	string line;
	TOTALOCT=0;
	int KARDE = 0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			if (KARDE==0){
				string head = line;
				if (head!="CK-CIDL-3-32768"){return 0;}
			}
			if (KARDE==1){
				string sommedecontrol=line;
				if (sommedecontrol!=CHECKSUM64){return 0;}
			}
			if(KARDE>1){
				DATA.append(line +"\n");
				TOTALOCT += line.length()+1;
			}
			KARDE++;
		}
		TOTALOCT-=2;
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

void CIDL3::block(){
	//int taille = 16 + (2 * rand()) % 512;
	BLOCKD = DATA;
}


void CIDL3::encode(){
	DATA_ENC="";
	for (int temp = 0; temp < TOTALOCT; temp++){
		int csl = ((rand()*1) % 16);
		cout << "---+CRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_ENC += BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL3::write_file(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());
	
	//WRITE HEADER
	fichier << "CK-CIDL-3-32768\n";
	fichier << CHECKSUM64 << "\n";
	
	//WRITE DATA
	fichier << DATA_ENC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}

void CIDL3::decode(){
	DATA_DEC="";
	for (int temp = 0; temp < TOTALOCT; temp++){
		int csl = ((rand()*1) % 16);
		cout << "---+DECRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_DEC += BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL3::write_file_clear(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());

	//WRITE DATA
	fichier << DATA_DEC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}






/*
CIDL-3-4096bits

*/
void CIDL3_4096::init_hash(string key){
	HASHMINI = hash(key.c_str());
	MD5 = md5(HASHMINI);
	SHA512 = sha512(MD5);
	CHECKSUM64 = base64_encode((const unsigned char *)SHA512.c_str(),strlen(SHA512.c_str()));
	stringstream SS1;
	SS1 << MD5 << HASHMINI;
	COMBOSHA512 = sha512(SS1.str());
}

void CIDL3_4096::init_seed(){
	srand( hash(COMBOSHA512.c_str()) );
	current=0;
}

void CIDL3_4096::next_key(int mode){
	stringstream S1;
	long int t=0;
	int R=0;
	int P=0;
	for (unsigned int it1=0; it1<8; ++it1){
		for (unsigned int it2=0; it2<8; ++it2){
			for (unsigned int it3=0; it3<8; ++it3){
					
				R = rand() % 2;
				MAT[it1][it2][it3][0] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][1] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][2] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][3] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][4] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][5] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][6] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][7] = ((int) (R));
				P = (((pow(2,0)*MAT[it1][it2][it3][0])+(pow(2,1)*MAT[it1][it2][it3][1])+(pow(2,2)*MAT[it1][it2][it3][2])+(pow(2,3)*MAT[it1][it2][it3][3])+(pow(2,4)*MAT[it1][it2][it3][4])+(pow(2,5)*MAT[it1][it2][it3][5])+(pow(2,6)*MAT[it1][it2][it3][6])+(pow(2,7)*MAT[it1][it2][it3][7])));
				P = P % 256;
				if (mode == 0){
					P = P << abs(1+rand() % 128);
				}
				if (mode == 1){
					P = P >> abs(1+rand() % 128);
				}
				S1 << (char) P;
					
				//cout << R;
				cout << "CREATION D'UNE NOUVELLE CLE: "<< 8*t<<"/"<<8*8*8*8<<"(bits)"<<endl;
				t++;
					
			}
		}
	}
	string S2=S1.str();
}

void CIDL3_4096::init_seed_RRB(){
	string TMP=S1.str();
	srand( hash(TMP.c_str()) );
	current_RRB=0;
}

void CIDL3_4096::init_seed_BLOCK(){
	string TMP=S1.str();
	string shatmp = sha512(TMP.c_str());
	
	srand( hash(shatmp.c_str()) );
	NUMBERBLOCK = 2 + (2 * rand()) % 512;
}

bool CIDL3_4096::open_read_file(const char filename[]){
	string line;
	TOTALOCT=0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			DATA.append(line +"\n");
			TOTALOCT += line.length()+1;
		}
		
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

bool CIDL3_4096::open_read_file_dec(const char filename[]){
	string line;
	TOTALOCT=0;
	int KARDE = 0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			if (KARDE==0){
				string head = line;
				if (head!="CK-CIDL-3-4096"){return 0;}
			}
			if (KARDE==1){
				string sommedecontrol=line;
				if (sommedecontrol!=CHECKSUM64){return 0;}
			}
			if(KARDE>1){
				DATA.append(line +"\n");
				TOTALOCT += line.length()+1;
			}
			KARDE++;
		}
		TOTALOCT-=2;
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

void CIDL3_4096::block(){
	//int taille = 16 + (2 * rand()) % 512;
	BLOCKD = DATA;
}


void CIDL3_4096::encode(){
	DATA_ENC="";
	for (int temp = 0; temp < TOTALOCT; temp++){
		int csl = ((rand()*1) % 16);
		cout << "---+CRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_ENC += BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL3_4096::write_file(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());
	
	//WRITE HEADER
	fichier << "CK-CIDL-3-4096\n";
	fichier << CHECKSUM64 << "\n";
	
	//WRITE DATA
	fichier << DATA_ENC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}

void CIDL3_4096::decode(){
	DATA_DEC="";
	for (int temp = 0; temp < TOTALOCT; temp++){
		int csl = ((rand()*1) % 16);
		cout << "---+DECRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_DEC += BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL3_4096::write_file_clear(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());

	//WRITE DATA
	fichier << DATA_DEC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}





/*
CIDL-4-4096bits

*/
void CIDL4_4096::init_hash(string key){
	HASHMINI = hash(key.c_str());
	MD5 = md5(HASHMINI);
	SHA512 = sha512(MD5);
	CHECKSUM64 = base64_encode((const unsigned char *)SHA512.c_str(),strlen(SHA512.c_str()));
	stringstream SS1;
	SS1 << MD5 << HASHMINI;
	COMBOSHA512 = sha512(SS1.str());
}

void CIDL4_4096::init_seed(){
	srand( hash(COMBOSHA512.c_str()) );
	current=0;
}

void CIDL4_4096::next_key(int mode){
	stringstream S1;
	long int t=0;
	int R=0;
	int P=0;
	for (unsigned int it1=0; it1<8; ++it1){
		for (unsigned int it2=0; it2<8; ++it2){
			for (unsigned int it3=0; it3<8; ++it3){
					
				R = rand() % 2;
				MAT[it1][it2][it3][0] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][1] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][2] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][3] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][4] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][5] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][6] = ((int) (R));
				R = rand() % 2;
				MAT[it1][it2][it3][7] = ((int) (R));
				P = (((pow(2,0)*MAT[it1][it2][it3][0])+(pow(2,1)*MAT[it1][it2][it3][1])+(pow(2,2)*MAT[it1][it2][it3][2])+(pow(2,3)*MAT[it1][it2][it3][3])+(pow(2,4)*MAT[it1][it2][it3][4])+(pow(2,5)*MAT[it1][it2][it3][5])+(pow(2,6)*MAT[it1][it2][it3][6])+(pow(2,7)*MAT[it1][it2][it3][7])));
				P = P % 256;
				if (mode == 0){
					P = P << abs(1+rand() % 128);
				}
				if (mode == 1){
					P = P >> abs(1+rand() % 128);
				}
				S1 << (char) P;
					
				//cout << R;
				cout << "CREATION D'UNE NOUVELLE CLE: "<< 8*t<<"/"<<8*8*8*8<<"(bits)"<<endl;
				t++;
					
			}
		}
	}
	string S2=S1.str();
}

void CIDL4_4096::init_seed_RRB(){
	string TMP=S1.str();
	srand( hash(TMP.c_str()) );
	current_RRB=0;
}

void CIDL4_4096::init_seed_BLOCK(){
	string TMP=S1.str();
	string shatmp = sha512(TMP.c_str());
	
	srand( hash(shatmp.c_str()) );
	NUMBERBLOCK = 2 + (2 * rand()) % 512;
}

bool CIDL4_4096::open_read_file(const char filename[]){
	string line;
	TOTALOCT=0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			DATA.append(line +"\n");
			TOTALOCT += line.length()+1;
		}
		
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

bool CIDL4_4096::open_read_file_dec(const char filename[]){
	string line;
	TOTALOCT=0;
	int KARDE = 0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			if (KARDE==0){
				string head = line;
				if (head!="CK-CIDL-4-4096"){return 0;}
			}
			if (KARDE==1){
				string sommedecontrol=line;
				if (sommedecontrol!=CHECKSUM64){return 0;}
			}
			if(KARDE>1){
				DATA.append(line +"\n");
				TOTALOCT += line.length()+1;
			}
			KARDE++;
		}
		TOTALOCT-=2;
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

void CIDL4_4096::block(){
	//int taille = 16 + (2 * rand()) % 512;
	BLOCKD = DATA;
}


void CIDL4_4096::encode(){
	DATA_ENC="";
	char ENCBYTE;
	
	for (int temp = 0; temp < TOTALOCT; temp++){
		ENCBYTE = BLOCKD.at(temp);
		for (int temp2 = 0; temp2 < TOTALOCT; temp2++){
			ENCBYTE = ENCBYTE ^ S2[temp2%(sizeof(S2) / sizeof(char))];
		}
		//int csl = ((rand()*1) % 16);
		cout << "---+CRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_ENC += ENCBYTE; //^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL4_4096::write_file(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());
	
	//WRITE HEADER
	fichier << "CK-CIDL-4-4096\n";
	fichier << CHECKSUM64 << "\n";
	
	//WRITE DATA
	fichier << DATA_ENC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}

void CIDL4_4096::decode(){
	DATA_DEC="";
	char ENCBYTE;
	for (int temp = 0; temp < TOTALOCT; temp++){
		ENCBYTE = BLOCKD.at(temp);
		for (int temp2 = 0; temp2 < TOTALOCT; temp2++){
			ENCBYTE = ENCBYTE ^ S2[temp2%(sizeof(S2) / sizeof(char))];
		}
		
		cout << "---+DECRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_DEC += ENCBYTE;//BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL4_4096::write_file_clear(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());

	//WRITE DATA
	fichier << DATA_DEC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}



/*
CIDL-4-512bits

*/
void CIDL4_512::init_hash(string key){
	HASHMINI = hash(key.c_str());
	MD5 = md5(HASHMINI);
	SHA512 = sha512(MD5);
	CHECKSUM64 = base64_encode((const unsigned char *)SHA512.c_str(),strlen(SHA512.c_str()));
	stringstream SS1;
	SS1 << MD5 << HASHMINI;
	COMBOSHA512 = sha512(SS1.str());
}

void CIDL4_512::init_seed(){
	srand( hash(COMBOSHA512.c_str()) );
	current=0;
}

void CIDL4_512::next_key(int mode){
	stringstream S1;
	long int t=0;
	int R=0;
	int P=0;
	for (unsigned int it1=0; it1<8; ++it1){
		for (unsigned int it2=0; it2<8; ++it2){
					
			R = rand() % 2;
			MAT[it1][it2][0] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][1] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][2] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][3] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][4] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][5] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][6] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][7] = ((int) (R));
			P = (((pow(2,0)*MAT[it1][it2][0])+(pow(2,1)*MAT[it1][it2][1])+(pow(2,2)*MAT[it1][it2][2])+(pow(2,3)*MAT[it1][it2][3])+(pow(2,4)*MAT[it1][it2][4])+(pow(2,5)*MAT[it1][it2][5])+(pow(2,6)*MAT[it1][it2][6])+(pow(2,7)*MAT[it1][it2][7])));
			P = P % 256;
			if (mode == 0){
				P = P << abs(1+rand() % 128);
			}
			if (mode == 1){
				P = P >> abs(1+rand() % 128);
			}
			S1 << (char) P;
					
			//cout << R;
			cout << "CREATION D'UNE NOUVELLE CLE: "<< 8*t<<"/"<<8*8*8*8<<"(bits)"<<endl;
			t++;
					
			
		}
	}
	string S2=S1.str();
}

void CIDL4_512::init_seed_RRB(){
	string TMP=S1.str();
	srand( hash(TMP.c_str()) );
	current_RRB=0;
}

void CIDL4_512::init_seed_BLOCK(){
	string TMP=S1.str();
	string shatmp = sha512(TMP.c_str());
	
	srand( hash(shatmp.c_str()) );
	NUMBERBLOCK = 2 + (2 * rand()) % 512;
}

bool CIDL4_512::open_read_file(const char filename[]){
	string line;
	TOTALOCT=0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			DATA.append(line +"\n");
			TOTALOCT += line.length()+1;
		}
		
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

bool CIDL4_512::open_read_file_dec(const char filename[]){
	string line;
	TOTALOCT=0;
	int KARDE = 0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			if (KARDE==0){
				string head = line;
				if (head!="CK-CIDL-4-512"){return 0;}
			}
			if (KARDE==1){
				string sommedecontrol=line;
				if (sommedecontrol!=CHECKSUM64){return 0;}
			}
			if(KARDE>1){
				DATA.append(line +"\n");
				TOTALOCT += line.length()+1;
			}
			KARDE++;
		}
		TOTALOCT-=2;
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

void CIDL4_512::block(){
	//int taille = 16 + (2 * rand()) % 512;
	BLOCKD = DATA;
}


void CIDL4_512::encode(){
	DATA_ENC="";
	char ENCBYTE;
	
	for (int temp = 0; temp < TOTALOCT; temp++){
		ENCBYTE = BLOCKD.at(temp);
		for (int temp2 = 0; temp2 < TOTALOCT; temp2++){
			ENCBYTE = ENCBYTE ^ S2[temp2%(sizeof(S2) / sizeof(char))];
		}
		//int csl = ((rand()*1) % 16);
		cout << "---+CRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_ENC += ENCBYTE; //^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL4_512::write_file(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());
	
	//WRITE HEADER
	fichier << "CK-CIDL-4-512\n";
	fichier << CHECKSUM64 << "\n";
	
	//WRITE DATA
	fichier << DATA_ENC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}

void CIDL4_512::decode(){
	DATA_DEC="";
	char ENCBYTE;
	for (int temp = 0; temp < TOTALOCT; temp++){
		ENCBYTE = BLOCKD.at(temp);
		for (int temp2 = 0; temp2 < TOTALOCT; temp2++){
			ENCBYTE = ENCBYTE ^ S2[temp2%(sizeof(S2) / sizeof(char))];
		}
		
		cout << "---+DECRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_DEC += ENCBYTE;//BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL4_512::write_file_clear(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());

	//WRITE DATA
	fichier << DATA_DEC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}



/*
CIDL-5-512bits

*/
void CIDL5_512::init_hash(string key){
	HASHMINI = hash(key.c_str());
	MD5 = md5(HASHMINI);
	SHA512 = sha512(MD5);
	CHECKSUM64 = base64_encode((const unsigned char *)SHA512.c_str(),strlen(SHA512.c_str()));
	stringstream SS1;
	SS1 << MD5 << HASHMINI;
	COMBOSHA512 = sha512(SS1.str());
}

void CIDL5_512::init_seed(){
	srand( hash(COMBOSHA512.c_str()) );
	current=0;
}

void CIDL5_512::next_key(int mode){
	stringstream S1;
	long int t=0;
	int R=0;
	int P=0;
	for (unsigned int it1=0; it1<8; ++it1){
		for (unsigned int it2=0; it2<8; ++it2){
					
			R = rand() % 2;
			MAT[it1][it2][0] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][1] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][2] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][3] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][4] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][5] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][6] = ((int) (R));
			R = rand() % 2;
			MAT[it1][it2][7] = ((int) (R));
			P = (((pow(2,0)*MAT[it1][it2][0])+(pow(2,1)*MAT[it1][it2][1])+(pow(2,2)*MAT[it1][it2][2])+(pow(2,3)*MAT[it1][it2][3])+(pow(2,4)*MAT[it1][it2][4])+(pow(2,5)*MAT[it1][it2][5])+(pow(2,6)*MAT[it1][it2][6])+(pow(2,7)*MAT[it1][it2][7])));
			P = P % 256;
			if (mode == 0){
				P = P << abs(1+rand() % 128);
			}
			if (mode == 1){
				P = P >> abs(1+rand() % 128);
			}
			S1 << (char) P;
					
			//cout << R;
			cout << "CREATION D'UNE NOUVELLE CLE: "<< 8*t<<"/"<<8*8*8*8<<"(bits)"<<endl;
			t++;
					
			
		}
	}
	string S2=S1.str();
}

void CIDL5_512::init_seed_RRB(){
	string TMP=S1.str();
	srand( hash(TMP.c_str()) );
	current_RRB=0;
}

void CIDL5_512::init_seed_BLOCK(){
	string TMP=S1.str();
	string shatmp = sha512(TMP.c_str());
	
	srand( hash(shatmp.c_str()) );
	NUMBERBLOCK = 2 + (2 * rand()) % 512;
}

bool CIDL5_512::open_read_file(const char filename[]){
	string line;
	TOTALOCT=0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			DATA.append(line +"\n");
			TOTALOCT += line.length()+1;
		}
		
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

bool CIDL5_512::open_read_file_dec(const char filename[]){
	string line;
	TOTALOCT=0;
	int KARDE = 0;
	ifstream fichier(filename);
	if (fichier.is_open()){
		while (getline(fichier,line)){
			if (KARDE==0){
				string head = line;
				if (head!="CK-CIDL-5-512"){return 0;}
			}
			if (KARDE==1){
				string sommedecontrol=line;
				if (sommedecontrol!=CHECKSUM64){return 0;}
			}
			if(KARDE>1){
				DATA.append(line +"\n");
				TOTALOCT += line.length()+1;
			}
			KARDE++;
		}
		TOTALOCT-=2;
		//DATA = base64_encode((const unsigned char *)DATA.c_str(), strlen(DATA.c_str()) );
		return 1;
	}
	else {
		return 0;
	}
}

void CIDL5_512::block(){
	//int taille = 16 + (2 * rand()) % 512;
	BLOCKD = DATA;
}


void CIDL5_512::encode(){
	DATA_ENC="";
	
	for (int temp = 0; temp < TOTALOCT; temp++){
		int csl = ((rand()*1) % 16);
		cout << "---+CRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_ENC += BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL5_512::write_file(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());
	
	//WRITE HEADER
	fichier << "CK-CIDL-5-512\n";
	fichier << CHECKSUM64 << "\n";
	
	//WRITE DATA
	fichier << DATA_ENC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}

void CIDL5_512::decode(){
	DATA_DEC="";
	char ENCBYTE;
	for (int temp = 0; temp < TOTALOCT; temp++){
		ENCBYTE = BLOCKD.at(temp);
		for (int temp2 = 0; temp2 < TOTALOCT; temp2++){
			ENCBYTE = ENCBYTE ^ S2[temp2%(sizeof(S2) / sizeof(char))];
		}
		
		cout << "---+DECRYPTAGE "<< temp+1<<"/"<<TOTALOCT<<endl;
		DATA_DEC += ENCBYTE;//BLOCKD.at(temp) ^ ( S2[temp%(sizeof(S2) / sizeof(char))]^(COMBOSHA512.at(csl) ) );
	}
	cout << endl;
}

void CIDL5_512::write_file_clear(string filename){
	ofstream fichier;
	fichier.open(filename.c_str());

	//WRITE DATA
	fichier << DATA_DEC;

	fichier.close();
	cout << "FICHIER FERMER"<<endl;
}

