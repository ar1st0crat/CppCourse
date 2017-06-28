#pragma once

#include <memory>
#include "IGame.h"
#include "BlackjackSummary.h"

/**
 * @class BlackjackGame
 * @brief Represents the BlackJack card game entity
 *
 * @author ar1st0crat
 */
class BlackjackGame : public IGame
{
public:
    virtual ~BlackjackGame();

    Player* getPlayer() const override;
    void setPlayer(const std::string& name, uint32_t money) override;
    Player* getDealer() const override;
    void setDealer(const std::string& name, uint32_t money=0) override;
    std::vector<Deck> getDecks() const override;
    void setDecks(const std::vector<Deck>& decks) override;
    BlackjackSummary getSummary() const;
    void updateSummary(BlackjackSummary summary);

protected:
    /** Shoes contain N decks (N is defined by RuleService) */
    std::vector<Deck> decks_;
    /** BlackJackGame aggregates the player_ */
    std::shared_ptr<Player> player_;
    /** BlackJackGame is a composite for the dealer_ */
    std::unique_ptr<Player> dealer_;
    /** Summary */
    BlackjackSummary summary_;
};
