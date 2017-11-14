// project includes
#include "Game.hpp"

using namespace CheckerZ;
using namespace CheckerZ::API::Utils;

#pragma region HELPERS DECLARATIONS

// simulate the game loop
void runGame(Game& t_game);
// loads game data from a save file into the current game object
void CheckerZ::loadGame(Game& t_game);

#pragma endregion

#pragma region UI HELPER FUNCTIONS
const enum GameMode
{
	HumanVSHuman = 1,	///> human-vs-human
	HumanVSMachine = 2,	///> human-vs-machine
	MachineVMachine = 3,	///> machine-vs-machine
};

void printStartMenuDialog()
{
	std::cout << "\t\t\t\t\t\t____________________\n";
	std::cout << "\t\t\t\t\t\t|                  |\n";
	std::cout << "\t\t\t\t\t\t|   [Start Menu]   |\n";
	std::cout << "\t\t\t\t\t\t|__________________|\n\n";
	std::cout << "\t\t\t\t\t\t[1] - human VS human\n";
	std::cout << "\t\t\t\t\t\t[2] - human VS machine\n";
	std::cout << "\t\t\t\t\t\t[3] - machine VS machine\n";
}

void printPreferencesDialog()
{
	std::cout << "\t\t\t\t\t\t_____________________\n";
	std::cout << "\t\t\t\t\t\t|                   |\n";
	std::cout << "\t\t\t\t\t\t|   [Preferences]   |\n";
	std::cout << "\t\t\t\t\t\t|___________________|\n\n";
}

bool chooseColor(std::string& t_color)
{
	t_color = "";
	std::cout << "\t\t\t\t\t\tPick color (black/red)\n";
	std::cout << "\t\t\t\t\t\tb/r: ";
	std::cin >> t_color;
	std::cout << "\n";

	if (t_color == "reset" || t_color == "0")
		return true;

	return false;
}

bool chooseName(std::string& t_name)
{
	t_name = "";
	std::cout << "\t\t\t\t\t\tChoose name (short please)\n";
	std::cout << "\t\t\t\t\t\tName: ";
	std::cin >> t_name;
	std::cout << "\n";
	
	if (t_name == "reset" || t_name == "0")
		return true;

	return false;
}

bool chooseDifficulty(int& t_difficulty)
{
	t_difficulty = 0;
	std::cout << "\t\t\t\t\t\tChoose level of difficulty\n";
	std::cout << "\t\t\t\t\t\t[1] - Easy\n";
	std::cout << "\t\t\t\t\t\t[2] - Medium\n";
	std::cout << "\t\t\t\t\t\t[3] - Hard\n";
	std::cout << "\t\t\t\t\t\tDifficulty: ";
	std::cin >> t_difficulty;
	std::cout << "\n";

	if (t_difficulty == 0)
		return true;

	return false;
}
#pragma endregion

auto main(void) -> int32
{
	std::string choice;
	Logger::message(MessageType::INF, "\t\t\t\tLOAD an existing game OR START a new one\n");
	Logger::message(MessageType::INF, "\t\t\t\tload/start:", EndingDelimiter::SPACE);
	std::cin >> choice;
	
	for (auto& ch : choice) ch = toupper(ch);	
	if (choice == "LOAD")
	{
		Game game;
		loadGame(game);
		//runGame(game);
		std::string filePath = ""; std::cin >> filePath;
	}
	else if (choice == "START")
	{	
		Game game;

		std::string errMsg = "";
		bool isMenuOn = true;
		while (isMenuOn)
		{
			system("cls");
			printStartMenuDialog();
			
			if(!errMsg.empty())
				Logger::message(MessageType::ERR, "\n", errMsg);

			int mode = 0;
			std::cout << "\n\t\t\t\t\t\tChoose game mode: "; std::cin >> mode;
			GameMode gameMode = static_cast<GameMode>(mode);
			
			std::string color = "";
			std::string name = "";
			int difficulty = 0;

			switch (gameMode)
			{
				case HumanVSHuman:
					system("cls");
					printPreferencesDialog();
				
					// first human choosing
					isMenuOn = chooseColor(color);	if (isMenuOn) break;
					isMenuOn = chooseName(name);	if (isMenuOn) break;
					// set the values of the player
					if (color[0] == 'r')
					{
						game.setRedPlayer(HUMAN, name);
						
						// second human choosing
						std::cout << "\n\t\t\t\t\t\tNext player's color is going to be black.\n";
						isMenuOn = chooseName(name);	if (isMenuOn) break;
						game.setBlackPlayer(HUMAN, name);
					}
					else if (color[0] == 'b')
					{
						game.setBlackPlayer(HUMAN, name);

						std::cout << "\n\t\t\t\t\t\tNext player's color is going to be red.\n";
						isMenuOn = chooseName(name);	if (isMenuOn) break;
						game.setRedPlayer(HUMAN, name);
					}
					
					break;
				case HumanVSMachine:
					system("cls");
					printPreferencesDialog();
					
					// Human choosing
					isMenuOn = chooseColor(color);				if (isMenuOn) break;
					isMenuOn = chooseName(name);				if (isMenuOn) break;
					isMenuOn = chooseDifficulty(difficulty);	if (isMenuOn) break;

					// set the values of the player
					if (color[0] == 'r')
					{
						game.setRedPlayer(HUMAN, name);
						game.setBlackPlayer(static_cast<PlayerType>(difficulty));
					}
					else if (color[0] == 'b')
					{
						game.setRedPlayer(static_cast<PlayerType>(difficulty));
						game.setBlackPlayer(HUMAN, name);
					}

					break;
				case MachineVMachine:
					system("cls");
					printPreferencesDialog();
					
					// AIbot 1
					isMenuOn = chooseDifficulty(difficulty);	if (isMenuOn) break;
					game.setRedPlayer(static_cast<PlayerType>(difficulty));

					// AIbot 2
					isMenuOn = chooseDifficulty(difficulty);	if (isMenuOn) break;
					game.setBlackPlayer(static_cast<PlayerType>(difficulty));
					
					break;
				default:
					errMsg = "\t\t\t\t\t\tInvalid input. Try choosing again.";
					
					isMenuOn = true;
					break;
			}
		}

		game.setTitle("<A GAME OF CHECKERS>");
		runGame(game);
	}
	else
	{
		Logger::message(MessageType::ERR, "Error: you have typed an invalid command.");
	}

	return EXIT_SUCCESS;
}

#pragma region HELPERS DEFINITIONS

void runGame(Game& t_game)
{
	// create game board and assign players
	t_game.begin();

	// Game Loop!
	while (t_game.getIsRunning())
	{
		// update the frames (game movement)
		t_game.update();

		// switch players and re-draw board each turn
		if (t_game.getNextTurn())
		{
			// do the rendering (draw in console)
			t_game.draw();
		}

		// check for win condition & exit the loop
		t_game.end();
	}
}

void CheckerZ::loadGame(Game& t_game)
{
	std::vector<char> gameBoardData;
	API::Events::EventManager::getInstance().loadGame(gameBoardData);
	t_game.setTitle("<A GAME OF CHECKERS>");

	for (auto data : gameBoardData)
	{
		Logger::message(MessageType::INF, "pawn: " + data);
	}
	
	/*
	CheckerZ::API::Board::board<CheckerZ::API::Pawn, CheckerZ::API::Board::s_boardLen> loadedBoard;

	int i = 0;
	for (size_t row = 0; row < 8; row++)
	{
		for (size_t col = 0; col < 8; col++)
		{
			loadedBoard[row][col].getMesh() = gameBoardData[i];
			i++;
		}
	}
	
	t_game.getGameBoard()->setBoard(loadedBoard);
	*/
}

#pragma endregion