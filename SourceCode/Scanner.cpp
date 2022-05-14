/*
 * Class:       CS 4308 Section 03
 * Term:        Spring 2022
 * Name:        Hamza Khan
 * Instructor:  Sharon Perry
 * Project:     Deliverable P1 Scanner
 */
#include "Scanner.h"

using namespace std;
int opCode[] = {100, 101, 102, //Operation codes that correspond to keyword table provided in word doc
					200, 300, 301,
					302, 303, 304,
					305, 400, 401,
					402, 403, 404,
					405, 500, 501,
					600, 502, 503,
					504, 506, 507,
					508, 509};

Scanner::Scanner()
{
	lineNum = 0;
}

	void Scanner::initialize(string in) //Starts of by reading in file that is provided by user
	{
		string line;

		fstream File(in);

		if (File.is_open() && in.find(".jl") != std::string::npos) //If file exists and is .jl file then....
		{
			while (getline(File, line)) //Obtain individual lines from file
			{
				getToken(line); //run getToken method
			}
		}
		else //If file doesnt exist or is invalid file type output message to console and end program
		{
			cout << "Cant find file or invalid file" << endl;

			system("pause");
			exit(0);
		}
	}

	void Scanner::getToken(string line) //take in line from file
	{
		lineNum++;
		if(line.find("//") != std::string::npos) //if line contains comment markers....
			line = " "; //set line equal to blank space causing rest of method to ignore it

		string temp = ""; //initialize temp string
		
		std::stringstream iss(line); //use string stream for line

		while(iss >> temp) //stream line into temp string
		{
			if (temp.find(" ") == std::string::npos) //if temp string is not a blank space....
			{
				lexemes.push_back(temp); //push into lexeme vector
				lineNums.push_back(lineNum);
			}
		}
	}

	bool Scanner::isNum(string in) //Checks if given string is numerical
	{
		bool num = true;//iniatilzes boolean value as true by default
		for(int i = 0; i < in.length(); i++)//iterates through string charactacters
		{
			if(!isdigit(in[i])) //if a single character in string is not a digit then....
				num = false; //set boolean value to false
		}

		return num; //return boolean value
	}

	bool Scanner::isAlpha(string in) //Checks if given string is alphabetical
	{
		bool alpha = true; //iniatilzes boolean value as true by default
		for (int i = 0; i < in.length(); i++) //iterates through string charactacters
		{
			if (!isalpha(in[i])) //if a single character in string is not a digit then...
				alpha = false; //set boolean value to false
		}

		return alpha; //return boolean value
	}

	void Scanner::assignCode() //Assigns opCode to corresponding lexeme
	{
		for(int i = 0; i < lexemes.size(); i++) //Iterates through given lexemes
		{
			//If given lexeme satisfies the conditions the corresponding opCode is pushed into the code vector
			if(lexemes.at(i).length() == 1 && isAlpha(lexemes.at(i)))
			{
				code.push_back(opCode[0]);
				bool found = false;
				for (int j = 0; j < identifiers.size(); j++) //checks if identifiers exists or not
				{
					if (identifiers.at(j) == lexemes.at(i))
						found = true;
				}
				if (!found) //if identifier does not exist then.....
					identifiers.push_back(lexemes.at(i)); //push new identifier into identifier vector

			}
			else if (isNum(lexemes.at(i)))
			{
				code.push_back(opCode[1]);
				if (lexemes.at(i-1) == "=") //if value is being assigned then....
				{
					val.push_back(std::stoi(lexemes.at(i))); //push value into val vector
				}
			}
			else if(lexemes.at(i) == "=")
			{
				code.push_back(opCode[3]);
			}
			else if (lexemes.at(i).length() == 3 && lexemes.at(i).find("()") != std::string::npos)
			{
				code.push_back(opCode[2]);
			}
			else if(lexemes.at(i) == "<=")
			{
				code.push_back(opCode[4]);
			}
			else if(lexemes.at(i) == "<")
			{
				code.push_back(opCode[5]);
			}
			else if(lexemes.at(i) == ">=")
			{
				code.push_back(opCode[6]);
			}
			else if(lexemes.at(i) == ">")
			{
				code.push_back(opCode[7]);
			}
			else if(lexemes.at(i) == "==")
			{
				code.push_back(opCode[8]);
			}
			else if(lexemes.at(i) == "~=")
			{
				code.push_back(opCode[9]);
			}
			else if(lexemes.at(i) == "+")
			{
				code.push_back(opCode[10]);
			}
			else if(lexemes.at(i) == "-")
			{
				code.push_back(opCode[11]);
			}
			else if(lexemes.at(i) == "*")
			{
				code.push_back(opCode[12]);
			}
			else if(lexemes.at(i) == "/")
			{
				code.push_back(opCode[13]);
			}
			else if (lexemes.at(i) == "end")
			{
				code.push_back(opCode[18]);
			}
			else if (lexemes.at(i) == "until")
			{
				code.push_back(opCode[25]);
			}
			else if (lexemes.at(i) == "function")
			{
				code.push_back(opCode[16]);
			}
			else if (lexemes.at(i).find("print") != std::string::npos)
			{
				code.push_back(opCode[17]);
			}
			else if (lexemes.at(i) == "if")
			{
				code.push_back(opCode[19]);
			}
			else if (lexemes.at(i) == "repeat")
			{
				code.push_back(opCode[20]);
			}
			else if (lexemes.at(i) == "while")
			{
				code.push_back(opCode[21]);
			}
			else if (lexemes.at(i) == "do")
			{
				code.push_back(opCode[22]);
			}
			else if (lexemes.at(i) == "then")
			{
				code.push_back(opCode[23]);
			}
			else if (lexemes.at(i) == "else")
			{
				code.push_back(opCode[24]);
			}
			//If lexeme satisfies none of the condition then it is invalid token and is given -1 opCode
			else
			{
				code.push_back(0); 
			}
		}
	}

	void Scanner::writeFile() //Writes obtained vectors into txt files
	{
		fstream tokens("Tokens.txt", ios::out); //Creates a Tokens.txt file and initializes it for output

		for (int i = 0; i < lexemes.size(); i++) //iterates through lexemes and code vectors
		{
			tokens << code.at(i)<< " : " << lexemes.at(i) << " : " << lineNums.at(i) << endl; //writes corresponding lexeme and opCode into file
			cout << code.at(i) << " : " << lexemes.at(i) << " : " << lineNums.at(i) << endl;
		}

		tokens.close(); //closes Tokens.txt file

		cout << "\nIdentifiers:\n";
		fstream ident("Identifiers.txt", ios::out); //Creates a identifiers.txt file and initializes it for output

		for (int i = 0; i < identifiers.size(); i++) //iterates through identifiers and val vectors
		{
			ident << "I:" << identifiers.at(i) << " V:" << val.at(i) << '\n'; //writes identifier and corresponding value into file
			cout << "I:" << identifiers.at(i) << " V:" << val.at(i) << '\n';
		}

		ident.close(); //closes identifiers.txt file;
	}