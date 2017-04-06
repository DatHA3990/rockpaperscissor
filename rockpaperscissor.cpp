/*

Code written by Dat HA
Copyrights 2017/03/30

This code used to be in multiple folders, but do to compiler problems and many more,
I've decided to pack them all in to this one.

I used multiple - if - else if - else - because it is reliable and clean.

*/

#include <iostream> // I/O library
#include <string>   // string library
#include <vector>   // vector library

#define VERSION_NUM 1.21 // version number

#define ROCK 1
#define PAPER 2
#define SCISSOR 3

#define TIE 0

#define LOSS 1
#define WIN 2

#define HUMAN 1
#define CPU 2

// CALL	UPDATE EACH TIME!!!!!
class CpuPlayer { // cpu player class
private:
	int m_move = 0; // cpu's move

	bool m_firstMove = 1; // true = this is the first move : false = we've past the first move
	static const int m_cpuFirstMove = PAPER; // cpu's first move will be paper

	int m_totalGames = 0; // total games

	std::vector<int> m_gameResult{ 0 }; // the game results - 0 - tie or error - 1 = human player win - 2 = cpu win
	std::vector<int> m_ennemiMove{ 0 }; // ennemi's moves are logged here
	std::vector<int> m_cpuMove{ 0 };    // cpu's moves are lagged here

	void FirstMove();

	void Loss();    // we previously loss
	void Win();     // we previously won
	void Tie();     // we previously tied

	void Double();  // the opponent played the same move 2 times
	void Spam();    // the opponent is spaming a move (because they are trying to crack the algo!!!!)
	void Reverse(); // opponent is going in reverse order, let's fix them!
	void Streak();  // opponent is on a streak

public:
	CpuPlayer();
	~CpuPlayer();

	int GetMove(); // the AI will generate a smart move using my algorithm
	void Update(int previousOpponentMove, int gameResult); // uptade the AI with the latest info - ennemi's move and victor
};


class HumanPlayer {
public:
	HumanPlayer();
	~HumanPlayer();

	int GetMove();
};

class Referee {
public:
	Referee();
	~Referee();

	// return 0 = tie, 1 = human win, 2 = cpu win
	int GetScore(int humanPlayerScore, int cpuPlayerScore);
};

class Translate
{
public:
	Translate();
	~Translate();

	std::string TieLossWin(int val);       // translate winner value
	std::string RockPaperScissor(int val); // translate move
};

CpuPlayer CpuPlayer_;     // cpu player
HumanPlayer HumanPlayer_; // human player
Referee Referee_;         // referee - the one that decides the winner
Translate Translate_;     // translate value, becaue we wan't to print it

int main() {
	std::cout << "Version : " << VERSION_NUM << std::endl << std::endl;

	while (1) {
		std::cout <<
			"Enter move : " << std::endl;

		int cpuMove = CpuPlayer_.GetMove();     // cpu player makes its move - move generated BEFORE the human player
		int humanMove = HumanPlayer_.GetMove(); // human player makes its move

		int victory = Referee_.GetScore(humanMove, cpuMove); // compare the results to get the match's victor

		std::cout << // print
			Translate_.RockPaperScissor(humanMove) << // human move
			"  vs  " << // vs
			Translate_.RockPaperScissor(cpuMove) << // cpu move
			"  :  " << // :
			Translate_.TieLossWin(victory) << // winner
			std::endl << std::endl; // skip a line

		CpuPlayer_.Update(humanMove, victory); // update the cpu player with its new info
	}
	return 0;
}

CpuPlayer::CpuPlayer() {}
CpuPlayer::~CpuPlayer() {}

// The code is written the way it is because this method is flexible

void CpuPlayer::FirstMove() {
	m_move = m_cpuFirstMove;
	m_firstMove = 0;
}

void CpuPlayer::Loss() {
	if (m_ennemiMove[m_totalGames] == ROCK)
		m_move = PAPER;
	else if (m_ennemiMove[m_totalGames] == PAPER)
		m_move = SCISSOR;
	else if (m_ennemiMove[m_totalGames] == SCISSOR)
		m_move = ROCK;
}

void CpuPlayer::Win() {
	if (m_move == ROCK)
		m_move = PAPER;
	else if (m_move == PAPER)
		m_move = SCISSOR;
	else if (m_move == SCISSOR)
		m_move = ROCK;
}

void CpuPlayer::Tie() {
	if (m_move == ROCK)
		m_move = SCISSOR;
	else if (m_move == PAPER)
		m_move = ROCK;
	else if (m_move == SCISSOR)
		m_move = PAPER;
}

void CpuPlayer::Double() {
	if (m_ennemiMove[m_totalGames] == ROCK)
		m_move = SCISSOR;
	else if (m_ennemiMove[m_totalGames] == PAPER)
		m_move = ROCK;
	else if (m_ennemiMove[m_totalGames] == SCISSOR)
		m_move = PAPER;
}

void CpuPlayer::Spam() {
	if (m_ennemiMove[m_totalGames] == ROCK)
		m_move = PAPER;
	else if (m_ennemiMove[m_totalGames] == PAPER)
		m_move = SCISSOR;
	else if (m_ennemiMove[m_totalGames] == SCISSOR)
		m_move = ROCK;
}

void CpuPlayer::Reverse() {
	if (m_ennemiMove[m_totalGames] == ROCK)
		m_move = ROCK;
	else if (m_ennemiMove[m_totalGames] == PAPER)
		m_move = PAPER;
	else if (m_ennemiMove[m_totalGames] == SCISSOR)
		m_move = SCISSOR;
}

void CpuPlayer::Streak() {
	if (m_ennemiMove[m_totalGames] == ROCK)
		m_move = ROCK;
	else if (m_ennemiMove[m_totalGames] == PAPER)
		m_move = PAPER;
	else if (m_ennemiMove[m_totalGames] == SCISSOR)
		m_move = SCISSOR;
}

int CpuPlayer::GetMove() {
	if (m_firstMove) // first move
		this->FirstMove();
	else if ((m_totalGames > 3) && (m_ennemiMove[m_totalGames] == m_ennemiMove[m_totalGames - 1]) &&
		(m_ennemiMove[m_totalGames] == m_ennemiMove[m_totalGames - 2])) // if the ennemi is spamming
		this->Spam();

	else if (m_totalGames >= 1 && (
		(m_ennemiMove[m_totalGames] == ROCK && m_ennemiMove[m_totalGames - 1] == PAPER) ||
		(m_ennemiMove[m_totalGames] == PAPER && m_ennemiMove[m_totalGames - 1] == SCISSOR) ||
		(m_ennemiMove[m_totalGames] == SCISSOR && m_ennemiMove[m_totalGames - 1] == ROCK)))
		this->Reverse();

	else if (m_totalGames >= 3 && (
		m_gameResult[m_totalGames] == LOSS &&
		m_gameResult[m_totalGames - 1] == LOSS &&
		m_gameResult[m_totalGames - 2] == LOSS))
		this->Streak();

	else if (m_gameResult[m_totalGames] == LOSS) // if we loss the previous game
		this->Loss();
	else if (m_gameResult[m_totalGames] == TIE) // if the game is a tie
		this->Tie();
	else if (m_totalGames > 2 && m_ennemiMove[m_totalGames] == m_ennemiMove[m_totalGames - 1]) // if he did 2 times the same move
		this->Double();
	else if (m_gameResult[m_totalGames] == WIN) // if we won the previous game
		this->Win();

	return m_move;
}

void CpuPlayer::Update(int previousOpponentMove, int gameResult) {
	m_totalGames++; // add a game to the total count

					// resize the vectors for game results, ennemi's moves and cpu's moves
	m_gameResult.resize(m_totalGames + 1);
	m_ennemiMove.resize(m_totalGames + 1);
	m_cpuMove.resize(m_totalGames + 1);

	// update the information and log some info
	m_gameResult[m_totalGames] = gameResult;           // log the game result
	m_ennemiMove[m_totalGames] = previousOpponentMove; // log the ennemi's move
	m_cpuMove[m_totalGames] = m_move;                  // log the cpu's move
}

HumanPlayer::HumanPlayer() {}
HumanPlayer::~HumanPlayer() {}

int HumanPlayer::GetMove() {
	std::cout << ">>>";

	std::string string;
	std::cin >> string;
	
	if (string == "1")
		return ROCK;
	else if (string == "2")
		return PAPER;
	else if (string == "3")
		return SCISSOR;
	else this->GetMove();
}

Referee::Referee() {}
Referee::~Referee() {}

int Referee::GetScore(int humanPlayerScore, int cpuPlayerScore) {
	if ((humanPlayerScore == ROCK    && cpuPlayerScore == SCISSOR) ||
		(humanPlayerScore == PAPER   && cpuPlayerScore == ROCK) ||
		(humanPlayerScore == SCISSOR && cpuPlayerScore == PAPER))
		return HUMAN;

	else if ((humanPlayerScore == ROCK    && cpuPlayerScore == PAPER) ||
		(humanPlayerScore == SCISSOR && cpuPlayerScore == ROCK) ||
		(humanPlayerScore == PAPER   && cpuPlayerScore == SCISSOR))
		return CPU;

	else return TIE;
}

Translate::Translate() {}
Translate::~Translate() {}

std::string Translate::TieLossWin(int val) {
	if (val == 0)
		return "TIE";
	else if (val == 1)
		return "HUMAN WIN";
	else if (val == 2)
		return "CPU WIN";
	else
		return "SYSTEM ERROR";
}

std::string Translate::RockPaperScissor(int val) {
	if (val == 1)
		return "ROCK";
	else if (val == 2)
		return "PAPER";
	else if (val == 3)
		return "SCISSOR";
	else
		return "SYSTEM ERROR";
}