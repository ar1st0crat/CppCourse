#pragma once

/** @interface ICardGame
* <p>An interface for classes implementing card games</p>
*
* @author ar1st0crat
*/
class ICardGame
{
public:
	/** Virtual destructor */
	virtual ~ICardGame() {}
    /** Method prepares everything for the game process */
    virtual bool setup() = 0;
    /** Method contains logic of the entire game process */
    virtual void run() = 0;
	/** Method starts new game (one shuffle) */
	virtual void shuffle() = 0;
	/** Method shows the situation on the cardtable */
	virtual void showTable() const = 0;
	/** Method analyzes the results of a game */
	virtual void gameResults() = 0;
};
