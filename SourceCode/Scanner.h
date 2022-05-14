#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <direct.h>
#include <ctype.h>

using namespace std;

class Scanner
{
	private:
		vector<string> lexemes; //Initializes vector for incoming lexemes
		vector<int> code; //Initializes vector for code for corresponding lexeme
		vector<string> identifiers; //Initializes vector for any incoming identifiers
		vector<int> val; //Initializes vector for any incoming values
		vector<int> lineNums;
	public:
		Scanner();
		int lineNum;
		void initialize(string);
		void getToken(string);
		bool isNum(string);
		bool isAlpha(string);
		void assignCode();
		void writeFile();
};
#endif // !SCANNER_H
