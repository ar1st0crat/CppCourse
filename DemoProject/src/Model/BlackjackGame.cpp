#include "BlackjackGame.h"

BlackjackGame::~BlackjackGame()
{
}

Player* BlackjackGame::getPlayer() const
{
    return player_.get();
}

void BlackjackGame::setPlayer(const std::string& name, uint32_t money)
{
    player_.reset(new Player(name, money));
}

Player* BlackjackGame::getDealer() const
{
    return dealer_.get();
}

void BlackjackGame::setDealer(const std::string& name, uint32_t money)
{
    dealer_.reset(new Player(name, money));
}

std::vector<Deck> BlackjackGame::getDecks() const
{
    return decks_;
}

void BlackjackGame::setDecks(const std::vector<Deck>& decks)
{
    decks_ = decks;
}

BlackjackSummary BlackjackGame::getSummary() const
{
    return summary_;
}

void BlackjackGame::updateSummary(BlackjackSummary summary)
{
    summary_ = summary;
}
