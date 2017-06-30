#include <iostream>
#include "ConsoleView.h"

/**
 * @brief Method ouputs plain text in console
 * @param text text to output
 */
void ConsoleView::output(const std::string& text) const
{
    std::cout << text << std::endl;
}

/**
 * @brief Method shows card table in console
 *
 * Method shows such information as:
 * <ul>
 *   <li>The number of cards in each deck</li>
 *   <li>Cards in the dealer's hand</li>
 *   <li>Cards in the player's hand</li>
 * </ul>
 *
 * @param game card game
 */
void ConsoleView::outputCardTable(const IGame& game) const
{
    std::cout << std::endl;
    for (auto& deck : game.getDecks())
    {
        std::cout << "[" << deck.cardCount() << "]  ";
    }
    std::cout << std::endl;

    auto dealer = game.getDealer();
    std::cout << dealer->getName() << "\t";
    std::cout << dealer->getHand() << std::endl;

    auto player = game.getPlayer();
    std::cout << player->getName() << "\t";
    std::cout << player->getHand() << std::endl;
}

/**
 * @brief Method inputs player's choice from console
 * @return Player's choice as char ('1', '2', etc.)
 */
char ConsoleView::inputPlayerChoice() const
{
    auto choice = '0';
    std::cin >> choice;
    return choice;
}

/**
 * @brief Method asks player if he/she wants to continue playing
 * @return Player's answer as char ('y', 'n' or anything else actually)
 */
char ConsoleView::inputPlayerWantsToContinue() const
{
    auto answer = 'n';
    std::cout << "Play again? (y/n)" << std::endl;
    std::cin >> answer;
    return answer;
}

/**
 * @brief Method inputs player's stake from console
 * @return Player's stake
 */
int32_t ConsoleView::inputPlayerStake() const
{
    int32_t stake = 0;
    std::cout << "Your stake (bet)?" << std::endl;
    std::cin >> stake;
    return stake;
}

/**
 * @brief Method inputs player's name from console
 * @return Player's name
 */
std::string ConsoleView::inputPlayerName() const
{
    std::string player_name = "";
    std::cout << "Enter your name please: ";
    std::cin >> player_name;
    return player_name;
}

/**
 * @brief Method inputs amount of player's money from console
 * @return Player's money
 */
int32_t ConsoleView::inputPlayerMoney() const
{
    int32_t money = 0;
    std::cout << "How much money do you have? ";
    std::cin >> money;
    return money;
}

/**
 * @brief Overloaded output operator for a Card
 * @param os   Reference to an output stream
 * @param card Reference to a Card object to output
 * @return Reference to an output stream (for further using it in output chains)
 */
std::ostream& operator<<(std::ostream& os, const Card& card)
{
    static std::string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

#ifdef __linux__
    static std::string suit_symbols[] = { "\u2665", "\u2666", "\u2663", "\u2660" };
#else
    static std::string suit_symbols[] = { "\x03", "\x04", "\x05", "\x06" };
#endif

    os << ranks[card.rank_ - 2] << suit_symbols[static_cast<int>(card.suit_)];

    return os;
}

/**
 * @brief Overloaded output operator for a Hand
 * @param os   Reference to an output stream
 * @param hand Reference to vector of cards to output
 * @return Reference to an output stream (for further using it in output chains)
 */
std::ostream& operator<<(std::ostream& os, const std::vector<Card>& hand)
{
    for (auto& card : hand)
    {
        os << card << " ";
    }
    return os;
}
