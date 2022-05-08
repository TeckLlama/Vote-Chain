// Author: Elliot Rihan
// Created: 12/02/22
// Last Modified Date: 05/05/22
// Description: VoteChain: A C++ program that receives Votes and stores data within a Blockchain.
// VoteChain.cpp: This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <mutex>
#include "Blockchain.h"
#include "Vote.h"
#include "sha256.h"

std::mutex voteVC_mutex;
Vote testVote = Vote();
bool stopVotingThread = false;
bool stopMiningThread = false;
HANDLE cFormat = GetStdHandle(STD_OUTPUT_HANDLE);

void generateTestHash()
{// Function to test accuracy of sha256.cpp
	std::cout << "\nTest Main.cpp: generateTestHash Started" << std::endl;
	std::stringstream ss;
	ss << "password";
	std::cout << "Test Hash: " << ss.str() << std::endl;
	std::cout << "SHA256 Hash: " << sha256(ss.str()) << std::endl;
	ss.str("");
	ss << "passWORD";
	std::cout << "Test Hash: " << ss.str() << std::endl;
	std::cout << "SHA256 Hash: " << sha256(ss.str()) << std::endl;
	ss.str("");
	ss << "9000password1000";
	std::cout << "Test Hash: " << ss.str() << std::endl;
	std::cout << "SHA256 Hash: " << sha256(ss.str()) << std::endl;
	ss.str("");
	ss << "--he//0w@r1d--";
	std::cout << "Test Hash: " << ss.str() << std::endl;
	std::cout << "SHA256 Hash: " << sha256(ss.str()) << std::endl;
	ss.str("");
	ss << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	std::cout << "Test Hash: " << ss.str() << std::endl;
	std::cout << "SHA256 Hash: " << sha256(ss.str()) << std::endl;
}

void colourTest()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	// 0 = Black	8 = Gray
	// 1 = Blue		9 = Light Blue
	// 2 = Green   10 = Light Green
	// 3 = Aqua	   11 = Light Aqua
	// 4 = Red	   13 = Light Red
	// 5 = Purple  14 = Light Purple
	// 6 = Yellow  15 = Light Yellow
	// 7 = White   
	std::cout << "\nHello World: Normal" << std::endl;
	SetConsoleTextAttribute(h, 0);
	std::cout << "\nHello World: 1" << std::endl;
	SetConsoleTextAttribute(h, 1);
	std::cout << "\nHello World: 1" << std::endl;
	SetConsoleTextAttribute(h, 2);
	std::cout << "\nHello World: 2" << std::endl;
	SetConsoleTextAttribute(h, 3);
	std::cout << "\nHello World: 3" << std::endl;
	SetConsoleTextAttribute(h, 4);
	std::cout << "\nHello World: 4" << std::endl;
	SetConsoleTextAttribute(h, 5);
	std::cout << "\nHello World: 5" << std::endl;
	SetConsoleTextAttribute(h, 6);
	std::cout << "\nHello World: 6" << std::endl;
	SetConsoleTextAttribute(h, 7);
	std::cout << "\nHello World: 7" << std::endl;
	SetConsoleTextAttribute(h, 8);
	std::cout << "\nHello World: 8" << std::endl;
	SetConsoleTextAttribute(h, 9);
	std::cout << "\nHello World: 9" << std::endl;
	SetConsoleTextAttribute(h, 11);
	std::cout << "\nHello World: 11" << std::endl;
	SetConsoleTextAttribute(h, 12);
	std::cout << "\nHello World: 12" << std::endl;
	SetConsoleTextAttribute(h, 13);
	std::cout << "\nHello World: 13" << std::endl;
	SetConsoleTextAttribute(h, 14);
	std::cout << "\nHello World: 14" << std::endl;
	SetConsoleTextAttribute(h, 15);
	std::cout << "\nHello World: 15" << std::endl;
	SetConsoleTextAttribute(h, 16);
	std::cout << "\nHello World: 16" << std::endl;
	SetConsoleTextAttribute(h, 17);
	std::cout << "\nHello World: 19" << std::endl;
	SetConsoleTextAttribute(h, 18);
	std::cout << "\nHello World: 18" << std::endl;
	SetConsoleTextAttribute(h, 19);
	std::cout << "\nHello World: 19" << std::endl;
	SetConsoleTextAttribute(h, 20);
	std::cout << "\nHello World: 20" << std::endl;
	SetConsoleTextAttribute(h, 15);
	std::cout << "\nHello World: White" << std::endl;
}

void voting()
{//	Voting Thread
	SetConsoleTextAttribute(cFormat, 13);
	std::cout << "Test Main.cpp: Vote Thread Initialized" << std::endl;
	SetConsoleTextAttribute(cFormat, 15);
	testVote.initializeVoteCandidates();
	std::unique_lock<std::mutex> ulVM(voteVC_mutex);
	testVote.initializeValidVoterIDs();
	ulVM.unlock();
	std::this_thread::sleep_for(std::chrono::seconds(6));
	while (!stopVotingThread) {
		std::unique_lock<std::mutex> ulVM(voteVC_mutex);
		SetConsoleTextAttribute(cFormat, 13);
		testVote.voterLogin();
		SetConsoleTextAttribute(cFormat, 15);
		ulVM.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(2));
		if (stopVotingThread == true) {
			stopMiningThread = true;
			SetConsoleTextAttribute(cFormat, 13);
			std::cout << "Test Main.cpp: stopMiningThread set to true" << std::endl;
			std::cout << "Test Main.cpp: Vote Thread Exited\n\n" << std::endl;
			SetConsoleTextAttribute(cFormat, 15);
			return;
		}
	}
}

void mining()
{//	Mines the number of blocks allocated in the for loop at end of loop Voting Thread 
 // Set to close after any inprogress votes are made then one additional block is mined 
	SetConsoleTextAttribute(cFormat, 11);
	std::cout << "Test Main.cpp: Mining Thread Initialized" << std::endl;
	SetConsoleTextAttribute(cFormat, 15);
	Blockchain bChain = Blockchain();
	std::unique_lock<std::mutex> ulVM(voteVC_mutex);
	bChain.generateGenesisBlock(Block(0, testVote.voterInitialStatus), testVote.voterInitialStatus);
	ulVM.unlock();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	int blockIndex;
	for (blockIndex = 1; blockIndex < 6; blockIndex++) {
		//std::cout << "\nTest Main.cpp: blockIndex " << blockIndex << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));
		std::unique_lock<std::mutex> ulVM(voteVC_mutex);
		SetConsoleTextAttribute(cFormat, 11);
		std::cout << "\nTest Main.cpp: Mining Block: " << blockIndex << std::endl;
		SetConsoleTextAttribute(cFormat, 15);
		bChain.addNewBlock(Block(blockIndex, testVote.unverifiedVotes), testVote.unverifiedVotes);
		if (testVote.unverifiedVotes != "")
		{
			testVote.verifiedVotes += testVote.unverifiedVotes + "\n";
		}
		testVote.unverifiedVotes = "";
		SetConsoleTextAttribute(cFormat, 11);
		std::cout << "Test Main.cpp: Block " << blockIndex << " successfully mined\n" << std::endl;
		SetConsoleTextAttribute(cFormat, 15);
		ulVM.unlock();
		//std::cout << "Test Main.cpp: VerifiedVotes\n" << testVote.verifiedVotes << std::endl;
	}
	stopVotingThread = true;
	SetConsoleTextAttribute(cFormat, 11);
	std::cout << "\nTest Main.cpp: stopVotingThread set to true" << std::endl;
	SetConsoleTextAttribute(cFormat, 15);
	while (stopMiningThread == false) {
		std::this_thread::sleep_for(std::chrono::seconds(15));
		if (stopMiningThread == true) {
			std::unique_lock<std::mutex> ulVM(voteVC_mutex);
			bChain.addNewBlock(Block(blockIndex, testVote.unverifiedVotes), testVote.unverifiedVotes);
			if (testVote.unverifiedVotes != "")
			{
				testVote.verifiedVotes += testVote.unverifiedVotes + "\n";
				testVote.unverifiedVotes = "";
			}
			ulVM.unlock();
			if (stopVotingThread && stopMiningThread == true) {
				SetConsoleTextAttribute(cFormat, 11);
				testVote.totalVerifiedVotes();
				SetConsoleTextAttribute(cFormat, 15);
				bChain.addNewBlock(Block(blockIndex + 1, testVote.voteBreakdown), testVote.voteBreakdown);
			}
			SetConsoleTextAttribute(cFormat, 11);
			std::cout << "\n\n\nTest Main.cpp: VerifiedVotes\n" << testVote.verifiedVotes << std::endl;;
			std::cout << "Test Main.cpp: Mining Thread Exited" << std::endl;
			SetConsoleTextAttribute(cFormat, 15);
			return;
		}
	}
}

int main()
{
	SetConsoleTitleA("Vote Chain");	
	char menuChar = 0;
	
	do {// changed from cin to _getch to force input of one char 
		menuChar = (char)0;
		SetConsoleTextAttribute(cFormat, 2);
		std::cout << "[A] Start Voting [A]" << std::endl;
		std::cout << "[B] Test Hash    [B]" << std::endl;
		std::cout << "[C] Test Colours [C]" << std::endl; 
		std::cout << "[D] Exit         [D]" << std::endl;
		// std::cout << "[D] New Option   [D]" << std::endl;
		std::cout << "Press A to Initilize Vote or [A/B/C/D] --> ";
		SetConsoleTextAttribute(cFormat, 15);
		menuChar = _getch();
		std::cout << menuChar << std::endl;
		menuChar = toupper(menuChar);		
	} while (menuChar != 'A' && menuChar != 'B' && menuChar != 'C' && menuChar != 'D');
	//std::cout << "Test Main.cpp: Accepted User input Char " << menuChar << std::endl;
	if (menuChar == 'A') {
		std::thread voteingThread(voting);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::thread miningThread(mining);
		voteingThread.join();
		miningThread.join();
	}
	if (menuChar == 'B') {		
		generateTestHash();
		std::this_thread::sleep_for(std::chrono::seconds(10));
		return 2;
	}
	if (menuChar == 'C') {
		colourTest();
		std::this_thread::sleep_for(std::chrono::seconds(10));
		return 2;
	}
	if (menuChar == 'D') {
		return 2;
	}
	return 0;
}