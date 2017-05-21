#include <iostream>
#include <vector>
#include <fstream>
#include <string>

//settings
//how big the tape starts it can grow
const int tapeStartSize = 300000;
//how long the dump for the debug char # should be
const int memToDump = 10;
//line ends its a bit inconsistent so here you can set it
const int eof = 0;
const bool eofSet = true;

//ask for a input from the user
std::string askFor(std::string qestion)
{
	std::string output;
	std::cout << qestion << std::endl;
	std::cin >> output;
	return output;
}

bool isBF(char input)
{
	if(input == '>'||
		input == '<'||
		input == '+'||
		input == '-'||
		input == '.'||
		input == ','||
		input == '['||
		input == ']'||
		input == '#')
	{
		return true;
	}
	else
	{
		return false;
	}
}

//takes in the text if text and parses it into a vector
//converts the []s to jump points
std::vector<int>* prossesText(std::ifstream *bfText)
{
	std::vector<int> *output = new std::vector<int>();
	std::vector<int> loopStack;
	char input;
	//run untile it reaches end of file
	while(bfText->peek() != -1)
	{
		input = bfText->get();
		if(isBF(input))
		{
			//this is were we convert the loops to jumps in the code program
			//might look like ++[(10)>++<-](3)
			if (input == '[')
			{
				output->push_back('[');
				loopStack.push_back(output->size());
				output->push_back(0);
			}else
			if(input == ']')
			{
				if (loopStack.size() <= 0)
				{
					std::cout << "Unnexpected ']'" << std::endl;
				}else
				{
					output->push_back(']');
					output->at(loopStack.back()) = (output->size());
					output->push_back((loopStack.back()));
					loopStack.pop_back();
				}
			}else
			{
				output->push_back(input);
			}
		}
	}
	if (loopStack.size() != 0)
	{
		std::cout << "Unnexpected '['" << std::endl;
	}
	return output;
}

//this gets brain F*k from a file
std::vector<int>* getProgramFromFile()
{
	std::string path = askFor("Give path");
	std::ifstream bfText = std::ifstream(path);
	std::vector<int> *output;
	if(bfText.good())
	{
		output = prossesText(&bfText);
		return output;
	}
	else
	{
		std::cout << "Not a good file" << std::endl;
		return new std::vector<int>();
	}
	bfText.close();
}

//interrupts the Brain F*k after the program.
void interrupt(std::vector<int> *program)
{
	std::vector<int> tape = std::vector<int>(tapeStartSize);
	std::vector<char> input;
	int tapeP = 0;
	for (int prCount = 0; prCount < program->size(); prCount++)
	{
		//adds one to this poin on the tape
		if (program->at(prCount) == '+')
		{
			tape.at(tapeP)++;
		}else
		//subtracts one this point on the tape
		if (program->at(prCount) == '-')
		{
			tape.at(tapeP)--;
		}else
		//moves pointer one to the right along the tape
		//dose this as long as the Ram will allow
		if (program->at(prCount) == '>')
		{
			if(tapeP + 1 >= tape.size())
			{
				tape.push_back(0);
				tapeP++;
				std::cout << "Warning: resized tape to a length of :" << tape.size() << '\n';
			}
			else
			{
				tapeP++;
			}
		}else
		//moves pointer one to the left
		//stop you from going below zero
		if (program->at(prCount) == '<')
		{
			if (0 < tapeP)
			{
				tapeP--;
			}
		}else
		//print the curent tape cell to the console
		if (program->at(prCount) == (int)'.')
		{
			std::cout << (char)tape.at(tapeP);
		}else
		//takes the last this in the stdin buffer and adds it to curent cell
		if (program->at(prCount) == ',')
		{
			if(std::cin.peek() == 10)
			{
				if(eofSet)
				{
					tape.at(tapeP) = eof;
				}
				getchar();
			}
			else
			{
				tape.at(tapeP) = getchar();
			}
		}else
		//uses jumps we set up earlier to exicute loops
		//for the open loop we jump only if the curent cell is at zero
		if (program->at(prCount) == '[')
		{
			if (tape.at(tapeP) == 0)
			{
				prCount = program->at(prCount + 1);
			}
			else
			{
				prCount++;
			}
		}else
		//for the close loop on the other hand we only jump if the curent cell is not zero
		if (program->at(prCount) == ']')
		{
			if (tape.at(tapeP) == 0)
			{
				prCount++;
			}
			else
			{
				prCount = program->at(prCount + 1);
			}
		}else
		//dubuging operator just nice to have :-D
		if (program->at(prCount) == '#')
		{
			for (int i = 0; i < memToDump; i++)
			{
				if(i == tapeP)
				{
					std::cout << '\e' << "[1m" << i << ':' << tape.at(i) << '\e' << "[0m" <<' ';
				}
				else
				{
					std::cout << i << ':' << tape.at(i) << ' ';
				}
			}
			std::cout << std::endl;
		}
	}
	return;
}

int main()
{
	std::vector<int> *program = getProgramFromFile();
	std::cout << std::endl;
	//clearing the buffer
	std::cin.ignore();
	interrupt(program);
	delete program;
	return 0;
}
