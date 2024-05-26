#include <iostream>
#include <string>
#include <stdlib.h>

enum GameType {
	NONE,
	PLAYER_VS_PLAYER,
	PLAYER_VS_COMPUTER
};

enum class PlayerType {
	HUMAN,
	AI
};

class Player {
public:
	Player() : name(""), type(PlayerType::AI), marker('\0')
	{}
	bool checkValidName(std::string& name)
	{
		return true;
	}
	void inputName()
	{
		std::cout << "Enter your name : ";
		std::string nam("");
		std::cin >> nam;
		while (checkValidName(nam) == false)
		{
			std::cout << "Please type a valid name : ";
			std::cin >> nam;
		}
		this->name = nam;
		this->type = PlayerType::HUMAN;
		if (this->marker == '\0')
		{
			char ch = '\0';
			while (!(ch == 'X' || ch == 'O'))
			{
				std::cout << "Please Choose your marker(X or O)";
				std::cin >> ch;
			}
			this->marker = ch;
		}
	}

	const std::string& getName() const {
		return name;
	}

	void setMarker(char c)
	{
		if (c == 'X')
			this->marker = 'O';
		else 
			this->marker = 'X';
	}

	char getMarker()
	{
		return this->marker;
	}

	std::pair<int,int> makeMove()
	{
		if (this->type == PlayerType::HUMAN)
		{
			std::cout << name << "'s turn" << std::endl;
			int x, y;
			std::cout << "Enter Coordinates : (0 0)..(2 2)";
			std::cin >> x >> y;
			return { x,y };
		}
		else {
			return { -1,-1 };
		}
	}
private:
	std::string name;
	PlayerType type;
	char marker;
};

class GameMap
{
public:
	GameMap() : numMoves(0), winner(EMPTY)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				board[i][j] = EMPTY;
	}

	void printBoard()
	{
		system("cls"); // not good method to clear console TODO: change it
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				std::cout << board[i][j];
				if (j < 2)
					std::cout << " | ";
			}
			std::cout << std::endl;
		}
	}

	bool checkValidMove(int x, int y)
	{
		if (x > 2 || y > 2 || x < 0 || y < 0)
			return false;
		if (board[x][y] == EMPTY)
		{
			return true;
		}
		return false;
	}

	void setMove(int x, int y, char c)
	{
		if (board[x][y] == EMPTY)
		{
			board[x][y] = c;
			numMoves++;
			if (checkWinner(x, y, c))
			{
				winner = c;
			}
		}
	}

	inline bool valid_coords(int r, int c)
	{
		return (0 <= r && r <= 2 && 0 <= c && c <= 2);
	}

	bool checkWinner(int x, int y, char c)
	{
		//check col
		if (x == 0)
		{
			if (board[x + 1][y] == c && board[x + 2][y] == c)
				return true;
		}
		if (x == 1)
		{
			if (board[x - 1][y] == c && board[x + 1][y] == c)
				return true;
		}
		if (x == 2)
		{
			if (board[x - 2][y] == c && board[x - 1][y] == c)
				return true;
		}
		//check row
		if (y == 0)
		{
			if (board[x][y+1] == c && board[x][y+2] == c)
				return true;
		}
		if (y == 1)
		{
			if (board[x][y-1] == c && board[x][y+1] == c)
				return true;
		}
		if (y == 2)
		{
			if (board[x][y-2] == c && board[x][y-1] == c)
				return true;
		}
		//check diagonal
		if (x == 0 && y == 0)
		{
			if (board[1][1] == c && board[2][2] == c)
				return true;
		}
		if (x == 0 && y == 2)
		{
			if (board[1][1] == c && board[2][0] == c)
				return true;
		}
		if (x == 1 && y == 1)
		{
			if (board[0][0] == c && board[2][2] == c)
				return true;
		}
		if (x == 2 && y == 0)
		{
			if (board[1][1] == c && board[0][2] == c)
				return true;
		}
		if (x == 2 && y == 2)
		{
			if (board[1][1] == c && board[0][0] == c)
				return true;
		}
		return false;
	}

	bool isTie()
	{
		return winner == EMPTY;
	}

	bool gameOver()
	{
		if (numMoves >= 9)
		{
			std::cout << "It's a tie!!" << std::endl;
			return true;
		}
		else if (winner != EMPTY)
		{
			//std::cout << "Winner is " << winner << std::endl;
			return true;
		}
		return false;
	}
	
private:
	char board[3][3];
	const char EMPTY = '_';
	char winner;
	int numMoves;
};


int main()
{
	Player players[2];
	std::string name;
	int gameType_;
	GameType gameType;
	players[0].inputName();
	GameMap map;
	std::cout << "for Player vs Player type 1, for Player vs Computer type 2 : ";
	std::cin >> gameType_;
	gameType = static_cast<GameType>(gameType_);
	if (gameType == GameType::PLAYER_VS_PLAYER)
	{
		players[1].setMarker(players[0].getMarker());
		players[1].inputName();
		map.printBoard();
		int curr_player = 0;
		while (!map.gameOver())
		{
			while (true) {
				auto move = players[curr_player].makeMove();
				if (map.checkValidMove(move.first, move.second))
				{
					map.setMove(move.first, move.second,players[curr_player].getMarker());
					map.printBoard();
					break;
				}
				else {
					std::cout << "Invalid Move.. Try Again ";
				}
			}
			if(map.isTie())
				curr_player = (curr_player + 1) % 2;
		}
		if (!map.isTie())
		{
			std::cout << "Winner is " << players[curr_player].getName() << std::endl;
		}
	}
	else {
		// vs AI
	}
}