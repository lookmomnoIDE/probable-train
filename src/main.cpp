/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 			CSC 242
** Assignment: 		Assignment 4
** File: 			main.cpp
** Description: 	Quantity Counter
**
** Author: 			Cameron Beckwith
** Date: 			08/24/2026
** -------------------------------------------------------------------------*/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <chrono>
#include <vector>


std::string title = R"raw(

)raw";


//Forward declarations

class Dummy
{
public:
	std::vector<std::string> m_wordList;
};
void getWordList(std::string path, Dummy& dummy);
std::vector<std::string> compareLists(Dummy& dict, Dummy& words);
std::string getCypher(std::string key);
std::string encrypt(std::string cypher, std::string path);
std::string decrypt(std::string cypher, std::string path);
void writeToFile(const std::string& content, const std::string& path);
std::string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
std::string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string cypherLower;
std::string cypherUpper;



int main()
{

	//running bool
	bool running = true;
	Dummy dict = Dummy();
	Dummy words = Dummy();

	//main loop
	while(running)
	{
		//setting up variables
		std::string input;
		std::string arg1, arg2, arg3, arg4, arg5;
		std::vector<std::string> missedWords;
		std::cout << title << std::endl;
		std::cout << " --help, -h, or ? for help." << std::endl;
		std::getline(std::cin, input);
		std::istringstream iss(input);
		iss >> input >> arg1 >> arg2 >> arg3 >> arg4 >> arg5;
		if(input == "--help" || input == "-h" || input == "?")
		{
			std::cout << "--help, -h, or ? for the help menu" << std::endl;
			std::cout << "--quit or -q to quit the program" << std::endl;
			std::cout << "-a [path] [pathToCheck]" << std::endl;
		}
		else if(input == "--quit" || input == "-q")
		{
			std::cout << "Goodbye!:)" << std::endl;
			running = false;
		}
		//no empty inputs allowed!
		else if(input.empty())
		{
			std::cout << "Please enter a valid input." << std::endl;
		}
		//Magic
		else if(input == "-a" || input == "--assignment")
		{
			getWordList(arg1, dict);
			getWordList(arg2, words);
			missedWords = compareLists(dict, words);
			if(missedWords.size() > 0)
			{
				for(size_t i = 0; i < missedWords.size(); i++)
				{
					std::cout << missedWords[i] << " " << std::endl;
				}
			}
		}
		else if(input == "-b" || input == "--bassignment")
		{
			if(arg1 == "crypt")
			{
				std::string key = arg2;
				std::string inputPath = arg3;
				std::string outputPath = arg4;
				cypherUpper = getCypher(key);
				writeToFile(encrypt(cypherUpper, inputPath), outputPath);

			}
			else if(arg1 == "decrypt")
			{
				std::string key = arg2;
				std::string inputPath = arg3;
				std::string outputPath = arg4;
				cypherUpper = getCypher(key);
				writeToFile(decrypt(cypherUpper, inputPath), outputPath);
			}
		}

	}
}



void getWordList(std::string path, Dummy& dummy)
{
	std::ifstream fin(path);
	std::string word;
	while (getline(fin, word))
	{
		//std::cout << word << std::endl;
		dummy.m_wordList.push_back(word);
	}
}

std::vector<std::string> compareLists(Dummy& dict, Dummy& words)
{
	auto D = dict.m_wordList;
	auto W = words.m_wordList;
	std::vector<std::string> missedWords;
	for(size_t i = 0; i < W.size(); i++)
	{
		bool found = false;
		for(size_t j = 0; j < D.size(); j++)
		{
			if(W[i] == D[j])
			{
				found = true;
				break;
			}
		}
		if(!found)
		{
			missedWords.push_back(W[i]);
		}
	}
	return missedWords;
}


std::string getCypher(std::string key)
{
	std::string cypher;
	std::string temp = alphabetUpper;
	for(size_t i = 0; i < key.length(); i++)
	{
		for(size_t j = 0; j < temp.length(); j++)
		{
			if(key[i] == temp[j])
			{
				temp.erase(j, 1);
				cypher += key[i];
			}
		}
	}
	cypher += temp;
	std::cout << "cyher in getCypher: " << cypher << std::endl;
	return cypher;
}


std::string encrypt(std::string cypher, std::string path)
{
	std::ifstream fin(path);
	std::string message;
	std::string output;
	std::cout << "cypher in encrypt " << cypher << std::endl;
	while (getline(fin, message))
	{
		std::cout << message << std::endl;
		for(size_t j = 0; j < message.length(); j++)
		{
			for(size_t i = 0; i < alphabetUpper.length(); i++)
			{
				if(message[j] == alphabetUpper[i])
				{
					std::cout << cypher[i] << std::endl;
					output += cypher[i];
				}
			}
		}
	}
	std::cout << output << std::endl;
	return output;
}


std::string decrypt(std::string cypher, std::string path)
{
	std::ifstream fin(path);
	std::string message;
	std::string output;
	while (getline(fin, message))
	{
		for(size_t j = 0; j < message.length(); j++)
		{
			for(size_t i = 0; i < cypher.length(); i++)
			{
				if(message[j] == cypher[i])
				{
					output += alphabetUpper[i];
				}
			}
		}
	}
	return output;
}

void writeToFile(const std::string& content, const std::string& path)
{
	std::ofstream fout(path);
	std::cout << content << std::endl;
	fout << content;
}