#include <iostream>
#include "BDLD.h"
#include <stdio.h>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int main (int argc, char * const argv[]) {
    // insert code here...
    BDLD bdd;
	map < string, map < int,string > > data;
	bdd.setFile("test.bdld");
	data = bdd.getTable("auth","code;");
    return 0;
}
