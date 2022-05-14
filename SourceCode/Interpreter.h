/*
* Class: CS 4308 Section 03
* Term : Spring 2022
* Name : Hamza Khan
* Instructor : Sharon Perry
* Project : Deliverable P3 Interpreter
*/
#ifndef Interpreter_H
#define Interpreter_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctype.h>
#include "Parser.h"

using namespace std;

class Interpreter
{
private:
	vector<string> tkns;
	vector<string> idents;
	vector<string> exec;
	int cond1;
	int cond2;
	int newIdent;
	bool rningIF;
	bool rningWhile;
public:
	Interpreter();
	void updateIdents();
	void PullToken();
	void PullIdents();
	string execIF(int);
	string execWhile(int);
	string execRepeat(int);
	string Execute();
	string print(int);
	int ModIdent(int);
	int StringtoInt(string);
	string FindIdent(string);
	string execBlock(int);
	string printRes();
};
#endif // !Interpreter_H

