/*
 *  cidl.h
 *  CIDL
 *
 *  Created by Cyril Coelho on 30/06/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */
#include <string.h>
#include "md5.h"
#include "base64.h"
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
using namespace std;
string open_detect_file_hash(const char filename[]);
string open_detect_file_type(const char filename[]);

class KeyMat{
	public:
	string hash1;
	string MD5;
	string SHA512;
	string HASHMINI;	
	int taille;
	int TOTALOCT;
	int current;
	bool MAT[8][8][8][8][8];
	string CHECKSUM64;
	string COMBOSHA512;
	void init_hash(string key);
	void init_seed();
	void next_key();
	stringstream S1;
	void init_seed_RRB();
	int current_RRB;
	string SHA512_RRB;
	int NUMBERBLOCK;
	void init_seed_BLOCK();
	string DATA;
	bool open_read_file(const char filename[]);
	void block();
	string BLOCKD;
	string S2;
	void encode();
	int BLOCKD_MAX;
	int MAX_LAST_CHAR;
	int LAST_CHAR;
	string DATA_ENC;
	string DATA_DEC;
	void decode();
	void write_file_clear(string filename);
	void write_file(string filename);
	bool open_read_file_dec(const char filename[]);
};


class CIDL2{
	public:
	string hash1;
	string MD5;
	string SHA512;
	string HASHMINI;	
	int taille;
	int TOTALOCT;
	int current;
	int MAT[8][8][8][8][8];
	string CHECKSUM64;
	string COMBOSHA512;
	void init_hash(string key);
	void init_seed();
	void next_key();
	stringstream S1;
	void init_seed_RRB();
	int current_RRB;
	string SHA512_RRB;
	int NUMBERBLOCK;
	void init_seed_BLOCK();
	string DATA;
	bool open_read_file(const char filename[]);
	void block();
	string BLOCKD;
	string S2;
	void encode();
	int BLOCKD_MAX;
	int MAX_LAST_CHAR;
	int LAST_CHAR;
	string DATA_ENC;
	string DATA_DEC;
	void decode();
	void write_file_clear(string filename);
	void write_file(string filename);
	bool open_read_file_dec(const char filename[]);
};

class CIDL3{
	public:
	string hash1;
	string MD5;
	string SHA512;
	string HASHMINI;	
	int taille;
	int TOTALOCT;
	int current;
	int MAT[8][8][8][8][8];
	string CHECKSUM64;
	string COMBOSHA512;
	void init_hash(string key);
	void init_seed();
	void next_key(int mode);
	stringstream S1;
	void init_seed_RRB();
	int current_RRB;
	string SHA512_RRB;
	int NUMBERBLOCK;
	void init_seed_BLOCK();
	string DATA;
	bool open_read_file(const char filename[]);
	void block();
	string BLOCKD;
	string S2;
	void encode();
	int BLOCKD_MAX;
	int MAX_LAST_CHAR;
	int LAST_CHAR;
	string DATA_ENC;
	string DATA_DEC;
	void decode();
	void write_file_clear(string filename);
	void write_file(string filename);
	bool open_read_file_dec(const char filename[]);
};


class CIDL3_4096{
	public:
	string hash1;
	string MD5;
	string SHA512;
	string HASHMINI;	
	int taille;
	int TOTALOCT;
	int current;
	int MAT[8][8][8][8];
	string CHECKSUM64;
	string COMBOSHA512;
	void init_hash(string key);
	void init_seed();
	void next_key(int mode);
	stringstream S1;
	void init_seed_RRB();
	int current_RRB;
	string SHA512_RRB;
	int NUMBERBLOCK;
	void init_seed_BLOCK();
	string DATA;
	bool open_read_file(const char filename[]);
	void block();
	string BLOCKD;
	string S2;
	void encode();
	int BLOCKD_MAX;
	int MAX_LAST_CHAR;
	int LAST_CHAR;
	string DATA_ENC;
	string DATA_DEC;
	void decode();
	void write_file_clear(string filename);
	void write_file(string filename);
	bool open_read_file_dec(const char filename[]);
};

class CIDL4_4096{
	public:
	string hash1;
	string MD5;
	string SHA512;
	string HASHMINI;	
	int taille;
	int TOTALOCT;
	int current;
	int MAT[8][8][8][8];
	string CHECKSUM64;
	string COMBOSHA512;
	void init_hash(string key);
	void init_seed();
	void next_key(int mode);
	stringstream S1;
	void init_seed_RRB();
	int current_RRB;
	string SHA512_RRB;
	int NUMBERBLOCK;
	void init_seed_BLOCK();
	string DATA;
	bool open_read_file(const char filename[]);
	void block();
	string BLOCKD;
	string S2;
	void encode();
	int BLOCKD_MAX;
	int MAX_LAST_CHAR;
	int LAST_CHAR;
	string DATA_ENC;
	string DATA_DEC;
	void decode();
	void write_file_clear(string filename);
	void write_file(string filename);
	bool open_read_file_dec(const char filename[]);
};


class CIDL4_512{
	public:
	string hash1;
	string MD5;
	string SHA512;
	string HASHMINI;	
	int taille;
	int TOTALOCT;
	int current;
	int MAT[8][8][8];
	string CHECKSUM64;
	string COMBOSHA512;
	void init_hash(string key);
	void init_seed();
	void next_key(int mode);
	stringstream S1;
	void init_seed_RRB();
	int current_RRB;
	string SHA512_RRB;
	int NUMBERBLOCK;
	void init_seed_BLOCK();
	string DATA;
	bool open_read_file(const char filename[]);
	void block();
	string BLOCKD;
	string S2;
	void encode();
	int BLOCKD_MAX;
	int MAX_LAST_CHAR;
	int LAST_CHAR;
	string DATA_ENC;
	string DATA_DEC;
	void decode();
	void write_file_clear(string filename);
	void write_file(string filename);
	bool open_read_file_dec(const char filename[]);
};

class CIDL5_512{
	public:
	string hash1;
	string MD5;
	string SHA512;
	string HASHMINI;	
	int taille;
	int TOTALOCT;
	int current;
	int MAT[8][8][8];
	string CHECKSUM64;
	string COMBOSHA512;
	void init_hash(string key);
	void init_seed();
	void next_key(int mode);
	stringstream S1;
	void init_seed_RRB();
	int current_RRB;
	string SHA512_RRB;
	int NUMBERBLOCK;
	void init_seed_BLOCK();
	string DATA;
	bool open_read_file(const char filename[]);
	void block();
	string BLOCKD;
	string S2;
	void encode();
	int BLOCKD_MAX;
	int MAX_LAST_CHAR;
	int LAST_CHAR;
	string DATA_ENC;
	string DATA_DEC;
	void decode();
	void write_file_clear(string filename);
	void write_file(string filename);
	bool open_read_file_dec(const char filename[]);
};