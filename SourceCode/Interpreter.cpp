/*
* Class: CS 4308 Section 03
* Term : Spring 2022
* Name : Hamza Khan
* Instructor : Sharon Perry
* Project : Deliverable P3 Interpreter
*/

#include "Interpreter.h"

using namespace std;

Interpreter::Interpreter()//constructor
{
	//Initializes values that are used for comparison in boolean expressions
	cond1 = 0; 
	cond2 = 0;
	//Initalizes the new value for specified identifer"
	newIdent = 0;
}

void Interpreter::PullToken()//pulls tokens from tokens.txt
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
		cout << "Cant find Tokens File" << endl;

		system("pause");
		exit(0);
	}
}

void Interpreter::PullIdents()//pulls identifiers from Identifiers.txt
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

string Interpreter::FindIdent(string id)//Method for finding identifiers
{
	for (int i = 0; i < idents.size(); i++)
	{
		if (id.find(idents.at(i).substr(2, 1)) != std::string::npos)
			return idents.at(i);
	}

	return "";
}

string Interpreter::Execute()//execution method
{
	string res = "Result: ";
	for (int i = 0; i < tkns.size(); i++)
	{
		if (tkns.at(i).substr(0,3) == "502" && rningWhile == false)
		{
			res += execIF(i + 1);
			return res;
		}
		else if (tkns.at(i).substr(0, 3) == "504" && rningIF == false)
		{
			res += execWhile(i + 1);
			return res;
		}
		else if (tkns.at(i).substr(0, 3) == "503" && rningWhile == false && rningIF == false)
		{
			res += execRepeat(i + 1);
			return res;
		}
		else if (tkns.at(i).substr(0, 3) == "501" && rningWhile == false && rningIF == false)
		{
			res += print(i);
			return res;
		}
	}
}

void Interpreter::updateIdents()//method for updating identifiers.txt file
{
	fstream ident("Identifiers.txt", ios::out); //finds identifiers.txt file and initializes it for output

	for (int i = 0; i < idents.size(); i++) //iterates through identifiers and val vectors
	{
		ident  << idents.at(i) << '\n'; //writes identifier and corresponding value into file
		//cout << "I:" << identifiers.at(i) << " V:" << val.at(i) << '\n';
	}

	ident.close();
}

string Interpreter::execRepeat(int index) //method for executing repeat statement
{
	string out = "";
	for (int i = 0; i < tkns.size(); i++)
	{
		if (tkns.at(i).substr(0, 3) == "509")
		{
			index = i + 1;
			break;
		}
	}

	if (tkns.at(index + 1).substr(0, 3) == "100")
	{
		string temp = FindIdent(tkns.at(index + 1));
		temp = temp.substr(temp.length() - 1, 1);
		cond1 = StringtoInt(temp);
	}
	if (tkns.at(index + 2).substr(0, 3) == "100")
	{
		string temp = FindIdent(tkns.at(index + 2));
		temp = temp.substr(temp.length() - 1, 1);
		cond2 = StringtoInt(temp);
	}
	if (tkns.at(index + 1).substr(0, 3) == "101")
	{
		string temp = tkns.at(index + 1).substr(6, 1);
		cond1 = StringtoInt(temp);
	}
	if (tkns.at(index + 2).substr(0, 3) == "101")
	{
		string temp = tkns.at(index + 2).substr(6, 1);
		cond2 = StringtoInt(temp);
	}
	if (tkns.at(index).substr(0, 3) == "300")
	{
		while (cond1 <= cond2)
		{
			out = execBlock(index + 4);
		}
	}
	else if (tkns.at(index).substr(0, 3) == "301")
	{
		while (cond1 < cond2)
		{
			out = execBlock(index + 4);
		}
	}
	else if (tkns.at(index).substr(0, 3) == "302")
	{
		while (cond1 >= cond2)
		{
			out = execBlock(index + 4);
		}
	}
	else if (tkns.at(index).substr(0, 3) == "303")
	{
		while (cond1 > cond2)
		{
			out = execBlock(index + 4);
		}
	}
	else if (tkns.at(index).substr(0, 3) == "304")
	{
		while (cond1 == cond2)
		{
			out = execBlock(index + 4);
		}
	}
	else if (tkns.at(index).substr(0, 3) == "305")
	{
		while (cond1 != cond2)
		{
			out = execBlock(index + 4);
		}
	}

	return out;
}

int Interpreter::StringtoInt(string in)//method for converting string to int
{
	int num = std::stoi(in);

	return num;
}

string Interpreter::execWhile(int index)//method for executing while statment
{
	string out = "";

	if (tkns.at(index + 1).substr(0, 3) == "100")
	{
		string temp = FindIdent(tkns.at(index + 1));
		temp = temp.substr(temp.length() - 1, 1);
		cond1 = StringtoInt(temp);
	}
	if (tkns.at(index + 2).substr(0, 3) == "100")
	{
		string temp = FindIdent(tkns.at(index + 2));
		temp = temp.substr(temp.length() - 1, 1);
		cond2 = StringtoInt(temp);
	}
	if (tkns.at(index + 1).substr(0, 3) == "101")
	{
		string temp = tkns.at(index + 1).substr(6, 1);
		cond1 = StringtoInt(temp);
	}
	if (tkns.at(index + 2).substr(0, 3) == "101")
	{
		string temp = tkns.at(index + 2).substr(6, 1);
		cond2 = StringtoInt(temp);
	}
	if (tkns.at(index).substr(0, 3) == "300")
	{
		while (cond1 <= cond2)
		{
			out = execBlock(index + 4);
		}
	}
	else if (tkns.at(index).substr(0, 3) == "301")
	{
		while (cond1 < cond2)
		{
			out = execBlock(index + 4);
		}
	}
	else if (tkns.at(index).substr(0, 3) == "302")
	{
		while (cond1 >= cond2)
		{
			out = execBlock(index + 4);
		}
	}
	else if (tkns.at(index).substr(0, 3) == "303")
	{
		while (cond1 > cond2)
		{
			out = execBlock(index + 4);
		}
	}
	else if (tkns.at(index).substr(0, 3) == "304")
	{
		while (cond1 == cond2)
		{
			out = execBlock(index + 4);
		}
	}
	else if (tkns.at(index).substr(0, 3) == "305")
	{
		while (cond1 != cond2)
		{
			out = execBlock(index + 4);
		}
	}
	return out;
}

string Interpreter::execIF(int index)//method for executing if statement
{
	int cond1 = 0;
	int cond2 = 0;

	if (tkns.at(index + 1).substr(0, 3) == "100")
	{
		string temp = FindIdent(tkns.at(index + 1));
		temp = temp.substr(temp.length() - 1, 1);
		cond1 = StringtoInt(temp);
	}
	if (tkns.at(index + 2).substr(0, 3) == "100")
	{
		string temp = FindIdent(tkns.at(index + 2));
		temp = temp.substr(temp.length() - 1, 1);
		cond2 = StringtoInt(temp);
	}
	if (tkns.at(index + 1).substr(0, 3) == "101")
	{
		string temp = tkns.at(index + 1).substr(6, 1);
		cond1 = StringtoInt(temp);
	}
	if (tkns.at(index + 2).substr(0, 3) == "101")
	{
		string temp = tkns.at(index + 2).substr(6, 1);
		cond2 = StringtoInt(temp);
	}
	if (tkns.at(index).substr(0, 3) == "300")
	{
		if (cond1 <= cond2)
			return execBlock(index + 3);
		else
		{
			for (int i = index; i < tkns.size(); i++)
			{
				if (tkns.at(i).substr(0, 3) == "508")
				{
					return execBlock(i + 1);
				}
			}
		}
	}
	else if (tkns.at(index).substr(0, 3) == "301")
	{
		if (cond1 < cond2)
			return execBlock(index+3);
		else
		{
			for (int i = index; i < tkns.size(); i++)
			{
				if (tkns.at(i).substr(0, 3) == "508")
				{
					return execBlock(i + 1);
				}
			}
		}
	}
	else if (tkns.at(index).substr(0, 3) == "302")
	{
		if (cond1 >= cond2)
			return execBlock(index+3);
		else
		{
			for (int i = index; i < tkns.size(); i++)
			{
				if (tkns.at(i).substr(0, 3) == "508")
				{
					return execBlock(i + 1);
				}
			}
		}
	}
	else if (tkns.at(index).substr(0, 3) == "303")
	{
		if (cond1 > cond2)
			return execBlock(index+3);
		else
		{
			for (int i = index; i < tkns.size(); i++)
			{
				if (tkns.at(i).substr(0, 3) == "508")
				{
					return execBlock(i + 1);
				}
			}
		}
	}
	else if (tkns.at(index).substr(0, 3) == "304")
	{
		if (cond1 == cond2)
			return execBlock(index+3);
		else
		{
			for (int i = index; i < tkns.size(); i++)
			{
				if (tkns.at(i).substr(0, 3) == "508")
				{
					return execBlock(i + 1);
				}
			}
		}
	}
	else if (tkns.at(index).substr(0, 3) == "305")
	{
		if (cond1 != cond2)
		{
			return execBlock(index + 4);
		}
		else
		{
			for (int i = index; i < tkns.size(); i++)
			{
				if (tkns.at(i).substr(0, 3) == "508")
				{
					return execBlock(i + 1);
				}
			}
		}
	}
	return "";
}

int Interpreter::ModIdent(int index)//Method for modifying identifer
{
	int val1 = 0;
	int val2 = 0;
	int out = 0;

	if (tkns.at(index - 1).substr(0, 3) == "101")
	{
		string temp = tkns.at(index - 1).substr(6, 1);
		val1 = StringtoInt(temp);
	}
	else if (tkns.at(index - 1).substr(0, 3) == "100")
	{
		string temp = FindIdent(tkns.at(index - 1));
		temp = temp.substr(temp.length() - 1, 1);
		val1 = StringtoInt(temp);
	}
	if (tkns.at(index + 1).substr(0, 3) == "101")
	{
		string temp = tkns.at(index + 1).substr(6, 1);
		val2 = StringtoInt(temp);
	}
	else if (tkns.at(index + 1).substr(0, 3) == "100")
	{
		string temp = FindIdent(tkns.at(index + 1));
		temp = temp.substr(temp.length() - 1, 1);
		val2 = StringtoInt(temp);
	}
	if (tkns.at(index).substr(0, 3) == "400")
	{
		out = val1 + val2;
	}
	else if (tkns.at(index).substr(0, 3) == "401")
	{
		out = val1 - val2;
	}
	else if (tkns.at(index).substr(0, 3) == "402")
	{
		out = val1 * val2;
	}
	else if (tkns.at(index).substr(0, 3) == "403")
	{
		out = val1 / val2;
	}

	return out;
}

string Interpreter::print(int index)//method for executing print statement
{
	int begin = 0;
	int end = 0;

	for (int i = 0; i < tkns.at(index).length(); i++)
	{
		if (tkns.at(index)[i] == '(')
			begin = i + 1;
		else if (tkns.at(index)[i] == ')')
			end = i;
	}

	string temp = "";
	for (int i = begin; i < end; i++)
	{
		temp += tkns.at(index)[i];
	}
	if (FindIdent(temp) != "")
	{
		for (int i = 0; i < idents.size(); i++)
		{
			if (FindIdent(tkns.at(index)) == idents.at(i))
			{
				string t = idents.at(i).substr(idents.at(i).length() - 1, 1);
				return t;
			}
		}
	}

	return temp;
}

string Interpreter::execBlock(int index)//method for executing a block of code of a statement
{
	int val = 0;
	while (tkns.at(index).substr(0, 3) != "600")
	{
		if (tkns.at(index).substr(0, 3) == "200")
		{
			string temp = FindIdent(tkns.at(index - 1));
			temp = temp.substr(temp.length() - 1, 1);
			val = StringtoInt(temp);

			if (tkns.at(index + 2).substr(0, 1) == "4")
			{
				newIdent = ModIdent(index + 2);
				if (val == cond1)
				{
					cond1 = newIdent;
				}
				if (val == cond2)
				{
					cond2 = newIdent;
				}
			}
			for (int i = 0; i < idents.size(); i++)
			{
				if (FindIdent(tkns.at(index - 1)) == idents.at(i))
				{
					idents.at(i).erase(idents.at(i).length() - 1, 1);
					idents.at(i) += to_string(newIdent);
					updateIdents();
					return to_string(newIdent);
				}
			}
		}
		else if (tkns.at(index).substr(0, 3) == "501")
		{
			int i = index;
			return print(i);
		}
		index++;
	}
}

string Interpreter::printRes()
{
	fstream result("Result.txt", ios::out); //Creates a result.txt file and initializes it for output

	cout << "Interpreter Output: " << endl;
	cout << Execute();

	result << "Interpreter Output: " << endl;
	result << Execute();

	cout << '\n';

	result.close(); //closes result.txt file
}
int main()
{
	Interpreter i;
	Parser test;
	Scanner s;

	string in;
	cout << "Enter File name (including file type)"; //Takes in file name from user
	cin >> in;

	s.initialize(in); //initializes scanner class and sends file name

	s.assignCode(); //runs assign code method

	cout << "\nScanner Output: " << endl;
	s.writeFile(); //writes outputs to .txt files

	test.PullToken();
	test.PullIdents();
	bool build = test.BuildTree();
	cout << "\nParser Output: " << endl;
	test.Print();
	if (build == true)
	{
		i.PullToken();
		i.PullIdents();
		i.printRes();
	}

	system("pause");
}