/*
 * Class:       CS 4308 Section 03
 * Term:        Spring 2022
 * Name:        Hamza Khan
 * Instructor:  Sharon Perry
 * Project:     Deliverable P2 Parser
 */
#include "Parser.h"

using namespace std;

Parser::Parser()
{
}

void Parser::PullToken() //pulls tokens from token.txt file which was made by scanner
{
	string line;

	fstream File("Tokens.txt");

	if (File.is_open()) //If file exists then....
	{
		while (getline(File, line)) //Obtain individual lines from file
		{
			tkns.push_back(line);
		}
	}
	else //If file doesnt exist or is invalid file type output message to console and end program
	{
		cout << "Cant find tokens file" << endl;

		system("pause");
		exit(0);
	}
}

void Parser::PullIdents() //pulls identifiers from Identifiers.txt file which was made by Scanner
{
	string line;

	fstream File("Identifiers.txt");

	if (File.is_open()) //If file exists then....
	{
		while (getline(File, line)) //Obtain individual lines from file
		{
			idents.push_back(line);
		}
	}
	else //If file doesnt exist or is invalid file type output message to console and end program
	{
		cout << "Cant find Identifier File" << endl;

		system("pause");
		exit(0);
	}
}

bool Parser::isNum(string in) //Checks if given string is numerical
{
	bool num = true;//iniatilzes boolean value as true by default
	for (int i = 0; i < in.length(); i++)//iterates through string charactacters
	{
		if (!isdigit(in[i])) //if a single character in string is not a digit then....
			num = false; //set boolean value to false
	}

	return num; //return boolean value
}

bool Parser::FindIdent(string id)//Looks for specified identifer in identifiers vector
{
	bool found = false;

	for (int i = 0; i < idents.size(); i++)//iterates through identifier vector
	{
		if (id.find(idents.at(i).substr(2,1)) != std::string::npos)//if found then
			found = true;//boolean value = true
	}

	return found;//return boolean value
}

bool Parser::BuildTree()//method for building parse tree
{
	if(tkns.at(0).substr(0,3) == "500")//if first token is function statement then....
	{
		bool pEnd = false;
		string temp = "<program> -> function ";
		gTree.push_back(temp);//push above string to tree vector

		if(tkns.at(1).substr(0,3) == "102")//if second token is function name then....
		{
			gTree.at(0) += "id()"; //add this string to first string in tree vector
			bool foundArith = false; //initializes boolean value

			for(int i = 2; i < tkns.size(); i++) //iterates through token vector
			{
				if(isStatement(tkns.at(i)) != "" || FindIdent(tkns.at(i)) == true) //If token is statement or identifier then...
				{
					if(i == 2) //at start of loop
					{
						gTree.at(0) += (" <block> ");//add block statement to first string in tree vector
						temp = {"<block> -> "};
						gTree.push_back(temp);//push temp string to vector
					}

					if(isStatement(tkns.at(i)) == "<if_statement>")//if token is if statement then...
					{
						if(checkIf(i+1) == true)//check whether if statement is valid, then....
						{
							gTree[1] += " <if_statement> ";//add following string to block string
							gTree.push_back(buildIf(i+1));//build If statement and push to tree vector
							foundArith = false;
						}
						else//If not valid then...
						{
							gTree[1] += " <if_statement> ";
							gTree.push_back("Error: Check IF statement syntax");//throw error and....
							return false;//return false to BuildTree method
						}
					}
					else if(isStatement(tkns.at(i)) == "<while_statement>")//if token is while statement then...
					{
						if(checkWhile(i+1) == "Valid")//If while statement is valid then...
						{
							gTree[1] += " <while_statement> ";//add following string to block string
							gTree.push_back(buildWhile(i+1));//build while statement and push to tree vector
							foundArith = false;
						}
						else//if not valid then....
						{
							gTree[1] += " <while_statement> ";
							gTree.push_back("Error: Check WHILE statement syntax" + checkWhile(i+1));//throw error and....
							return false;//return false to BuildTree method
						}
					}
					else if(isStatement(tkns.at(i)) == "<repeat_statement>")//if token is repeat statement then...
					{
						if(checkRep(i+1) == true)//If repeat statement is valid then....
						{
							gTree[1] += " <repeat_statement> ";//add following string to block string
							gTree.push_back(buildRep(i+1));//build repeat statement and push to tree vector
							foundArith = false;
						}
						else//if not valid then....
						{
							gTree[1] += " <repeat_statement> ";
							gTree.push_back("Error: Check REPEAT statement syntax");//Throw error and....
							return false;//return false to BuildTree method
						}
					}
					else if(isStatement(tkns.at(i)) == "<print_statement>")//if print statement then....
					{
						if(checkPrint(i) == true)//if print statement is valid then...
						{
							gTree[1] += " <print_statement> ";//add following string to block string
							gTree.push_back(buildP(i));//build print statement and push to tree vector
							foundArith = false;
						}
						else//if not valid then.....
						{
							gTree[1] += " <print_statement> ";
							gTree.push_back("Error: Check PRINT statement syntax");//Throw error and.....
							return false;//return false to BuildTree method
						}
					}
					else if(tkns.at(i).substr(0,3) == "100")//if token is assignment statement then
					{
						if(checkAssign(i+1) == true)//if assignment statement is valid then...
						{
							gTree[1] += " <assignment_statement> ";//add following string to block string
							gTree.push_back("<assignment_statement> -> id <assignment_operator> <arithmetic_expression> ");//push following string to vector
							foundArith = false;
						}
						/*else//if not valid then.....
						{
							gTree[1] += " <assignment_statement> ";
							gTree.push_back("Error: Check assignment statement syntax");//Throw error and.....
							return false;//return false to BuildTree method
						}*/
					}
					else if(isRel(tkns.at(i)) != "" && isBoolExp(i+1) == true)//if token is boolean expression then....
					{
						gTree.push_back("<boolean_expression> -> <relative_op> <arithmetic_expression> <arithmetic_expression> ");//push following string to vector
						foundArith = false;
					}
					else if(isArithExp(tkns.at(i)) && foundArith == false)//if token is arithmetic expression then...
					{
						gTree.push_back(buildArith(i));//build arithmetic expression and push to vector
						foundArith = true;
					}
				}
				else if(tkns.at(i).substr(0,3) == "600")//if token is end statement then....
					{
						gTree.at(0) += " <end_statement>";//add following string to function string
						gTree.push_back("<end_statement>");//push following string to vector and....
						return true;//return true
					}
			}
		}
	}
	else//If first token is not function statement then...
	{
		cout << "Error: function statement expected";
	}
}

string Parser::buildIf(int index)//Method for building if statement
{
	string temp = "<if_statement> -> if ";
	bool s = false;

	for(int i = index; i < tkns.size(); i++)
	{
		if(isRel(tkns.at(i)) != "" && isBoolExp(i+1) == true)
			temp += "<boolean_expression>";
		else if(tkns.at(i).substr(0,3) == "507")
			temp += "<then_statement>";
		else if (tkns.at(i).substr(0, 3) == "506")
			temp += " <do_statement> ";
		else if (s == false && isStatement(tkns.at(i)) != "")
		{
			temp += isStatement(tkns.at(i));
		}
		else if (FindIdent(tkns.at(i)) == true && tkns.at(i + 1).substr(0, 3) != "507" && tkns.at(i + 2).substr(0, 3) != "507")
		{
			temp += " id ";
			s = true;
		}
		else if (tkns.at(i).substr(0, 3) == "101" && tkns.at(i + 1).substr(0, 3) != "507" && tkns.at(i + 2).substr(0, 3) != "507")
		{
			temp += " <literal_integer> ";
		}
		else if (tkns.at(i).substr(0, 1) == "3")
		{
			temp += " <relative_operator> ";
		}
		else if (tkns.at(i).substr(0, 1) == "4")
		{
			temp += " <arithmetic_operator> ";
		}
		else if(tkns.at(i).substr(0,3) == "508")
		{
			temp += "<else_statement>";
			s = false;
		}
		else if(tkns.at(i).substr(0,3) == "600")
		{
			temp += "<end_statement>";
			return temp;
		}
	}

	return temp;
}

string Parser::buildWhile(int index)//method for building while statement
{
	string temp = "<while_statement> -> while ";
	bool s = false;

	for(int i = index; i < tkns.size(); i++)
	{
		if(isRel(tkns.at(i)) != "" && isBoolExp(i+1) == true)
			temp += " <boolean_expression> ";
		else if(tkns.at(i).substr(0,3) == "506")
			temp += " <do_statement> ";
		else if (s == false && isStatement(tkns.at(i)) != "")
		{
			temp += isStatement(tkns.at(i));
		}
		else if(FindIdent(tkns.at(i)) == true && tkns.at(i+1).substr(0, 3) != "506" &&  tkns.at(i + 2).substr(0, 3) != "506")
		{
			temp += " id ";
			s = true;
		}
		else if (tkns.at(i).substr(0, 3) == "101" && tkns.at(i + 1).substr(0, 3) != "506" && tkns.at(i + 2).substr(0, 3) != "506")
		{
			temp += " <literal_integer> ";
		}
		else if (tkns.at(i).substr(0, 1) == "3")
		{
			temp += " <relative_operator> ";
		}
		else if (tkns.at(i).substr(0, 1) == "4")
		{
			temp += " <arithmetic_operator> ";
		}
		else if(tkns.at(i).substr(0,3) == "600")
		{
			temp += " <end_statement> ";
			return temp;
		}
	}

	return temp;
}

string Parser::buildRep(int index)//method for building repeat statement
{
	string temp = "<repeat_statement> -> repeat ";
	bool s = false;

	for(int i = index; i < tkns.size(); i++)
	{
		if(isStatement(tkns.at(i)) != "" && s == false)
		{
			temp += "<block> ";
			s = true;
		}
		else if(tkns.at(i).substr(0,3) == "509")
		{
			temp += "<until_statement> ";
			s = false;
		}
		else if(isRel(tkns.at(i)) != "" && isBoolExp(i+1) == true)
			temp += "<boolean_expression>";
	}

	return temp;
}

string Parser::buildP(int index)//method for building print statement
{
	int begin = 0;
	int end = 0;

	bool validP = false;

	string temp = "<print> -> print ( ";

	for(int i = 0; i < tkns.at(index).length(); i++)
	{
		if(tkns.at(index)[i] == '(')
			begin = i+1;
		else if(tkns.at(index)[i] == '(')
			end = i;
	}

	string t = "";
	for(int i = begin; i < end; i++)
	{
		t += tkns.at(index)[i];
	}

	if(FindIdent(t) == true)
	{
		temp += "<arithmetic_expression>  ) ";
	}
	else if (isNum(t) == true)
	{
		temp += "<literal_integer> )";
	}
	return temp;
}

string Parser::buildArith(int index)//method for building arithmetic expression
{
	string temp = "<arithmetic_expression> -> ";

	for(int i = index; i < tkns.size(); i++)
	{
		if(isArithExp(tkns.at(i)) == true)
		{
			if(tkns.at(i).substr(0,3) == "100")
				temp += "id ";
			else if(tkns.at(i).substr(0,3) == "101")
				temp += "<literal_integer> ";
			else if(tkns.at(i).substr(0,3) == "400")
				temp += "<add_operator>";
			else if(tkns.at(i).substr(0,3) == "401")
				temp += "<sub_operator>";
			else if(tkns.at(i).substr(0,3) == "402")
				temp += "<mul_operator>";
			else if(tkns.at(i).substr(0,3) == "403")
				temp += "<div_operator>";
			else if(tkns.at(i).substr(0,3) == "404")
				temp += "<pe_operator>";
			else if(tkns.at(i).substr(0,3) == "405")
				temp += "<me_operator>";
			else
				return temp;
		}
	}

	return temp;
}

bool Parser::checkAssign(int index)//check if assignment statement is valid
{
	bool aStmt = false;

	if(tkns.at(index).substr(0,3) == "200" && isArithExp(tkns.at(index+1)))
		aStmt = true;

	return aStmt;
}

bool Parser::checkPrint(int index)//check if print statement is valid 
{
	int begin = 0;
	int end = 0;

	bool validP = false;

	for(int i = 0; i < tkns.at(index).length(); i++)
	{
		if(tkns.at(index)[i] == '(')
			begin = i+1;
		else if(tkns.at(index)[i] == ')')
			end = i;
	}

	string temp = "";
	for(int i = begin; i < end; i++)
	{
		temp += tkns.at(index)[i];
	}

	if(isNum(temp) == true || FindIdent(temp) == true)
	{
		return true;
	}

	return false;
}

bool Parser::checkRep(int index)//check if repeat statement is valid
{
	bool validW = false;

	for(int i = index; i < tkns.size(); i++)
	{
		if(isStatement(tkns.at(i)) != "")
		{
			validW = true;
		}
		else if (tkns.at(i).substr(0, 1) == "0")
		{
			return false;
		}
		else if(tkns.at(i) == "509")
		{
			validW = true;
		}
		else if(isRel(tkns.at(i)) != "" && tkns.at(i-1) == "509")
			return true;
	}
	return validW;
}

string Parser::checkWhile(int index)//check if while statement is valid
{
	string out = "";

	if(isRel(tkns.at(index)) != "")
	{
		if (isBoolExp(index + 1) == false)
		{
			out = " boolean expression at line: " + tkns.at(index + 1).substr(tkns.at(index + 1).length() - 1, 1);
			return out;
		}
		else if (tkns.at(index + 3).substr(0, 3) != "506")
		{
			out = " do statement at line: " + tkns.at(index + 3).substr(tkns.at(index + 3).length() - 1, 1);
			return out;
		}
		for(int i = index+4; i < tkns.size();i++)
		{
			if (isStatement(tkns.at(i)) == "" && FindIdent(tkns.at(i)) == false && tkns.at(i).substr(0,1) == "0" && tkns.at(i).substr(0,1) != "4" && tkns.at(i).substr(0,3) != "101" && tkns.at(i).substr(0, 3) != "200")
			{
				out  = " block error at line: " + tkns.at(i).substr(tkns.at(i).length()-1, 1);
				return out;
			}
			if (tkns.at(i).substr(0, 3) == "600")
			{
				return "Valid";
			}
		}
	}
	else
	{
		out = " boolean expression at line: " + tkns.at(index).substr(tkns.at(index).length() - 1, 1);
		return out;
	}

	return out;
}

bool Parser::checkIf(int index)//check if "if" statement is valid
{
	bool validIf = false;

	if(isRel(tkns.at(index)) != "")
	{
		validIf = true;
		if (isBoolExp(index + 1) == false)
		{
			validIf = false;
			cout << "Boolean Expression expected at line: " << tkns.at(index).substr(tkns.at(index).length() - 1, 1) << endl;
		}
		else if (tkns.at(index + 3).substr(0, 3) != "507")
		{
			validIf = false;
			cout << "Then_statement expected at line: "<< tkns.at(index).substr(tkns.at(index).length() - 1, 1) << endl;
		}
		else
		{
			for (int i = index + 3; i < tkns.size(); i++)
			{
				if (isStatement(tkns.at(i)) == "" && FindIdent(tkns.at(i)) == false && tkns.at(i).substr(0, 1) != "0" && tkns.at(i).substr(0, 1) != "4" && tkns.at(i).substr(0, 3) != "101" && tkns.at(i).substr(0, 3) != "507" && tkns.at(i).substr(0, 3) != "508" && tkns.at(i).substr(0, 3) != "600")
				{
					validIf = false;
					cout << "IF block error at line: " << tkns.at(index).substr(tkns.at(index).length() - 1, 1) << endl;
				}
				if (tkns.at(i).substr(0, 3) == "600")
				{
					return true;
				}
			}
		}
	}

	return validIf;
}

bool Parser::isBoolExp(int index)//checks whether boolean expression is valid
{
	bool isBool = false;

	for(int i = index; i < index+2; i++)
	{
		if(isArithExp(tkns.at(i)) == true)
			isBool = true;
	}

	return isBool;
}

string Parser::isRel(string in)//checks if token is a relative operator
{
	if(in.substr(0,3) == "300")
		return "<le_operator>";
	else if(in.substr(0,3) == "301")
		return "<lt_operator>";
	else if(in.substr(0,3) == "302")
		return "<ge_operator>";
	else if(in.substr(0,3) == "303")
		return "<gt_operator>";
	else if(in.substr(0,3) == "304")
		return "<eq_operator>";
	else if(in.substr(0,3) == "305")
		return "<ne_operator>";
	else
		return "";
}

string Parser::isStatement(string in)//checks if token is a statement
{
	if(in.substr(0,3) == "501")
		return "<print_statement>";
	else if(in.substr(0,3) == "504")
		return "<while_statement>";
	else if(in.substr(0,3) == "502")
		return "<if_statement>";
	else if(in.substr(0,3) == "503")
		return "<repeat_statement>";
	else
		return "";
}

bool Parser::isArithExp(string in)//checks if arithemetic expression is valid
{
	bool found = false;
	if (in.substr(0, 3) == "100" || in.substr(0, 3) == "101" || in[0] == '4')
	{
		found = true;
	}

	return found;
}

void Parser::Print()//prints parse tree and writes to .txt file
{
	
	fstream parsed("Parsed.txt", ios::out); //Creates a parsed.txt file and initializes it for output

	for (int i = 0; i < gTree.size(); i++) //iterates through lexemes and code vectors
	{
			parsed << gTree.at(i) << endl;
			cout << gTree.at(i) << endl;
	}
	parsed << '\n';
	cout << '\n';

	parsed.close(); //closes parsed.txt file
}