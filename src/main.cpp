/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 			CSC 242
** Assignment: 		Assignment 5
** File: 			main.cpp
** Description: 	spell check and encrypt/decrypt file text. 
**
** Author: 			Cameron Beckwith , Isiah Dixon, Michael Bloom
** Date: 			09/04/2026
** -------------------------------------------------------------------------*/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <chrono>
#include <vector>


std::string title = R"raw(

 (   (       )            )         )  (         )  
 )\ ))\ ) ( /(   *   ) ( /(   (  ( /(  )\ )   ( /(  
(()/(()/( )\())` )  /( )\())  )\ )\())(()/(   )\()) 
 /(_))(_)|(_)\  ( )(_)|(_)\ (((_|(_)\  /(_)) ((_)\  
(_))(_))   ((_)(_(_())  ((_))\___ ((_)(_))   __((_) 
| _ \ _ \ / _ \|_   _| / _ ((/ __/ _ \| |    \ \/ / 
|  _/   /| (_) | | |  | (_) | (_| (_) | |__   >  <  
|_| |_|_\ \___/  |_|   \___/ \___\___/|____| /_/\_\ 
                                                    
)raw";


//Forward declarations

class Dummy{public:std::vector<std::string> m_wordList;}; 					//Cameron
void getWordList(std::string path, Dummy& dummy);							//Cameron
std::vector<std::string> compareLists(Dummy& dict, Dummy& words);			//Cameron
std::string getCypher(std::string key);										//Isiah
std::string encrypt(std::string cypher, std::string path);					//michael
std::string decrypt(std::string cypher, std::string path);					//Isiah
std::string reverseString(std::string input);								//michael
void writeToFile(const std::string& content, const std::string& path);		//michael


std::string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int main()
{

	//running bool
	bool running = true;
	//made these classes for a few reasons. It's easier to type and keep track of, 
	//I was worried about RAII at the beginning of the project
	//It's easier to keep track of what's what. 
	//It's a little easier to manage the memory
	//I also thought about allocating on the heap, but that was unnecessary. 
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
		std::cout << "--help, -h, or ? for help." << std::endl;
		std::getline(std::cin, input);
		std::istringstream iss(input);
		iss >> input >> arg1 >> arg2 >> arg3 >> arg4 >> arg5;
		//no empty inputs allowed!
		if(input == "--help" || input == "-h" || input == "?" || input.empty())
		{
			std::cout << "--help, -h, or ? for the help menu" << std::endl;
			std::cout << "--quit or -q to quit the program" << std::endl;
			std::cout << "Operations:" << std::endl;
			std::cout << "================================================" << std::endl;
			std::cout << "-a 			[path] [pathToCheck] or " << std::endl;
			std::cout << "--assignment 		[path] [pathToCheck]" << std::endl;
			std::cout << "-b 			[crypt/decrpyt] [key] [input path] [output path] or "<< std::endl;
			std::cout << "--bassignment 		[crypt/decrpyt] [key] [input path] [output path]" << std::endl;
		}
		else if(input == "--quit" || input == "-q")
		{
			std::cout << "Goodbye!:)" << std::endl;
			running = false;
		}
		//Magic
		else if(input == "-a" || input == "--assignment")
		{
			//get the word list for both objects. 
			getWordList(arg1, dict);
			getWordList(arg2, words);
			//compare the list for items that appear in words but not dict. 
			missedWords = compareLists(dict, words);
			//if missed words is greater than 0
			if(missedWords.size() > 0)
			{
				//then for each missed word we print it to the console. 
				for(size_t i = 0; i < missedWords.size(); i++)
				{
					std::cout << missedWords[i] << " " << std::endl;
				}
			}
			//no missed words found. 
			else if(missedWords.size() == 0)
			{
				std::cout << "No mispelled words were found!" << std::endl;
			}
			//Retroactively added words to dictionary!
			else if(missedWords.size() < 0)
			{
				std::cout << "Retroactively added words to dictionary!" << std::endl;
			}
		}
		else if(input == "-b" || input == "--bassignment")
		{
			//encryption
			if(arg1 == "crypt")
			{
				//key 			= arg2;
				//inputPath 	= arg3;
				//outputPath 	= arg4;
				writeToFile(encrypt(getCypher(arg2), arg3), arg4);
			}
			//decryption
			else if(arg1 == "decrypt")
			{
				//key 			= arg2;
				//inputPath 	= arg3;
				//outputPath 	= arg4;
				//overloading functions is fun!
				writeToFile(decrypt(getCypher(arg2), arg3), arg4);
			}
		}
		//catch all for invalid input
		else
		{
			std::cout << "You needn't continue on this path of foolery" << std::endl;
		}
	}
}

//pass the path and dummy reference
void getWordList(std::string path, Dummy& dummy)//Cameron
{
	//open word list
	std::ifstream fin(path);
	std::string word;
	//since we create dummy objects once at the beginning of the program
	//in order to prevent the list from growing forever we have to clear
	//after each use. 
	dummy.m_wordList.clear();
	while (getline(fin, word))
	{
		//std::cout << word << std::endl;
		//slow, but works. 
		dummy.m_wordList.push_back(word);
	}
	//close the file
	fin.close();
}


//pass two dummy obects and this function compares the right against the left. 
std::vector<std::string> compareLists(Dummy& dict, Dummy& words)//Cameron
{
	//grab the wordlist
	auto& D = dict.m_wordList;
	auto& W = words.m_wordList;
	//declare missed words list
	std::vector<std::string> missedWords;
	//for each word to be checked 
	for(size_t i = 0; i < W.size(); i++)
	{
		bool found = false;
		//for each word to be checked against. 
		for(size_t j = 0; j < D.size(); j++)
		{
			//if those words are the same
			if(W[i] == D[j])
			{
				//found == true and we escape second loop 
				found = true;
				break;
			}
		}
		//if found == false
		if(!found)
		{	
			//add the word to the missed word list. 
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
	cypher += reverseString(temp);
	std::cout << "cypher in getCypher: " << cypher << std::endl;
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
	fin.close();
	return output;
}


std::string decrypt(std::string cypher, std::string path)
{
	std::ifstream fin(path);
	std::string message;
	std::string output;
	while(getline(fin, message))
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
	fin.close();
	return output;
}


void writeToFile(const std::string& content, const std::string& path)
{
	std::ofstream fout(path);
	std::cout << content << std::endl;
	fout << content;
	fout.close();
}


std::string reverseString(std::string input)
{
	std::string output;
	for(size_t i = 0; i < input.length(); i++)
	{
		output += input[input.length()-i];
	}
	return output;
}