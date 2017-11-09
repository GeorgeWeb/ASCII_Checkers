#include "EventManager.hpp"

namespace CheckerZ { namespace API { namespace Events {

	Movement Events::EventManager::handleState(Movement t_move, GameHistoryState t_historyState)
	{
		Movement moveToDisplay;

		if (t_historyState == GameHistoryState::DO)
		{
			gameHistory.push_back(t_move);

			undoStack.push(t_move);
			moveToDisplay = t_move;
		}
		else
		{
			if (t_historyState == GameHistoryState::UNDO)
			{
				moveToDisplay = manageUndo();
			}
			else if (t_historyState == GameHistoryState::REDO)
			{
				moveToDisplay = manageRedo();
			}
			else if (t_historyState == GameHistoryState::REPLAY)
			{
				manageReplay();
			}
			else
			{
				throw std::logic_error("Sorry but there's no such option.");
			}
		}

		return moveToDisplay;
	}

	Movement EventManager::manageUndo()
	{
		Movement moveToDisplay;

		if (!undoStack.empty())
		{
			Movement move = undoStack.top();
			moveToDisplay = move;
			redoStack.push(move);
			undoStack.pop();
		}
		else
		{
			throw std::logic_error("Sorry but there's nothing to be undoed.");
		}

		return moveToDisplay;
	}

	Movement EventManager::manageRedo()
	{
		Movement moveToDisplay;

		if (!redoStack.empty())
		{
			moveToDisplay = redoStack.top();
			Movement move = moveToDisplay;
			undoStack.push(move);
		}
		else
		{
			throw std::logic_error("Sorry but there's nothing to be redoed.");
		}

		return moveToDisplay;
	}

	void EventManager::manageReplay()
	{
	
	}

} } }