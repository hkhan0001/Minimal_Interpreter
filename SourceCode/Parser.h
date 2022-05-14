#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctype.h>
#include "Scanner.h"

using namespace std;

class Parser
{
private:
	vector<string> tkns;
	vector<string> idents;
	vector<string> gTree;
public:
	Parser();
	void PullToken();
	void PullIdents();
	bool FindIdent(string);
	string isStatement(string);
	string isRel(string);
	string buildIf(int);
	string buildWhile(int);
	string buildRep(int);
	string buildP(int);
	string buildArith(int);
	bool isArithExp(string);
	bool isBoolExp(int);
	bool checkIf(int);
	string checkWhile(int);
	bool checkRep(int);
	bool checkPrint(int);
	bool checkAssign(int);
	bool isNum(string);
	bool BuildTree();
	void Print();
};
#endif // !PARSER_H

