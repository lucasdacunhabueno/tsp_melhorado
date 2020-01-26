#ifndef IMPORTDATA_H
#define IMPORTDATA_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>
#include <stdlib.h>
#include "City.h"

using std:: ifstream;
using std:: string;
using std:: cout;
using std:: regex;
using std:: vector;
using std:: ostringstream;
using std:: map;

enum { NAME = 0, COMMENT, TYPE, DIMENSION, EDGE_WEIGHT_TYPE, NODE_COORD_SECTION };

class ImportData{
    public:
        ImportData(string);
        vector<City> getCitiesCoord();
        string gettspName();
        string getType();
        string getedge_type();
        string getnode_comment();
        string getcomment();
        //void printInfos();
        //string getInfos();
		int get_population_size();
    private:
		
		vector<string> file_descriptions;

        /*string tspName="N/A";
        string type="N/A";
        string comment="";
        string edge_type="N/A";
        string node_comment="N/A";
        string flag;
        string flagaux;*/

        ifstream myfile;
        vector<City> citiescoord;

        //int dimension;
        //void regexManager(string);
        //bool findIgnoredWords(string);
        //void reader(string, string);

		void inputManager(string);

};

#endif
