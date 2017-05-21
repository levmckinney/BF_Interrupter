#include <iostream>
#include <vector>
#include <fstream>
#include <string>

const int bfMemSize = 300000;
const int braketDepth = 5000;
const int memToDump = 10;
//loops.reserve(10000);

std::vector<char>* getBF()
{
	std::cout << "Give path" << std::endl;
	std::string path = "";
	std::cin >> path;
	std::ifstream bfText = std::ifstream(path);
	std::vector<char> *output = new std::vector<char>();
	if(bfText.good())
	{
		char input;
		while(bfText.peek() != -1)
		{
			input = bfText.get();
			if(input == '>'||
				input == '<'||
				input == '+'||
				input == '-'||
				input == '.'||
				input == '.'||
				input == '['||
				input == ']'||
				input == '#')
			{
				output->push_back(input);
			}
		}
	}
	else
	{
		std::cout << "Not a good file" << std::endl;
	}
	for (int i = 0; i < output->size(); i++)
	{
		std::cout << output->at(i);
	}
	std::cout << std::endl;
	return output;
}

void movePointerRight(int *memIndex)
{
	(*memIndex)++;
}
void movePointerLeft(int *memIndex)
{
	if(*memIndex > 0)
  {
 	 *memIndex = *memIndex - 1;
  }
}
void incrementMem(int *memIndex, std::vector<int> *bfMem)
{
	if(254 < bfMem->at(*memIndex))
	{
		bfMem->at(*memIndex) = 0;
	}
	else
	{
		bfMem->at(*memIndex)++;
	}
}
void decrementMem(int *memIndex, std::vector<int> *bfMem)
{
	if(1 > bfMem->at(*memIndex))
	{
		bfMem->at(*memIndex) = 255;
	}
	else
	{
		bfMem->at(*memIndex)--;
	}
}
void printMem(int *memIndex, std::vector<int> *bfMem)
{
	std::cout << (char)bfMem->at(*memIndex);
}
void inputToMem(int *memIndex, std::vector<int> *bfMem)
{
	std::cin >> bfMem->at(*memIndex);
}
int startLoop(int *memIndex, std::vector<int> *bfMem, std::vector<int> *loops, int i, std::vector<char> *bfSource)
{
	if(bfMem->at(*memIndex) == 0)
	{
		int braketCount = 1;
		for(int k = i; k > bfSource->size(); ++k)
		{
			if (braketCount == 0)
			{
				i = k + 1;
				break;
			}
			if(bfSource->at(k) = '[')
			{
				braketCount++;
			}
			else if (bfSource->at(k) = '[')
			{
				braketCount--;
			}
		}
	}
	else
	{
		loops->push_back(i);
	}
	return i;
}

int endLoop(int *memIndex, std::vector<int> *bfMem, std::vector<int> *loops, int i)
{
	if(loops->size() > 0)
	{
		if(bfMem->at(*memIndex) == 0)
		{
			loops->pop_back();
		}
		else
		{
			i = loops->back();
		}
	}
	else
	{
		std::cout << "Unexpected ']";
	}
	return i;
}

void dumpMem(std::vector<int> *bfMem, int *memIndex)
{
	for (int i = 0; i < memToDump; i++)
	{
		std::cout << i << ':' << bfMem->at(i) << ' ';
	}
	std::cout << " mem index at:" << *memIndex << std::endl;
}

void inturpret()
{
	std::vector<int> *bfMem = new std::vector<int>(bfMemSize);
	std::vector<int> *loops = new std::vector<int>();
	loops->reserve(braketDepth);
	std::vector<char> *bfSource = new std::vector<char>();
	bfSource = getBF();
	int *memIndex = new int;
	*memIndex = 0;
	for (int i = 0; i < bfSource->size(); i++)
	{
			switch (bfSource->at(i)) {
				case '>':
					movePointerRight(memIndex);
				break;
				case '<':
					movePointerLeft(memIndex);
				break;
				case '+':
					incrementMem(memIndex, bfMem);
				break;
				case '-':
					decrementMem(memIndex, bfMem);
				break;
				case '.':
				 printMem(memIndex, bfMem);
				break;
				case ',':
					inputToMem(memIndex, bfMem);
				break;
				case '[':
					i = startLoop(memIndex, bfMem, loops, i, bfSource);
				break;
				case ']':
					i = endLoop(memIndex, bfMem, loops, i);
				break;
				case'#':
					dumpMem(bfMem, memIndex);
				break;
			}
	}
	delete bfMem;
	delete loops;
	delete memIndex;
	delete bfSource;
}

int main()
{
	inturpret();
	return 0;
}
