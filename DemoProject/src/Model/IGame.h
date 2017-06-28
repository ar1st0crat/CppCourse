#pragma once

#include "Deck.h"
#include "Player.h"

/**
 * @interface IGame
 * @brief An interface for classes implementing card games
 *
 * @author ar1st0crat
 */
class IGame
{
public:
    /** Virtual destructor */
    virtual ~IGame() {}

    virtual Player* getPlayer() const = 0;
    virtual void setPlayer(const std::string& name, uint32_t money) = 0;
    virtual Player* getDealer() const = 0;
    virtual void setDealer(const std::string& name, uint32_t money = 0) = 0;
    virtual std::vector<Deck> getDecks() const = 0;
    virtual void setDecks(const std::vector<Deck>& decks) = 0;
};
