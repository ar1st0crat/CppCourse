#include "BlackjackGame.h"
#include "BlackjackScoreCounter.h"

/** Default constructor
* <p>By default an instance of BlackjackScoreCounter is created in BlackjackGame constructor</p> */
BlackjackGame::BlackjackGame()
{
    score_counter_ = std::make_unique<BlackjackScoreCounter>();
}

/** Parameterized constructor
* <p>The score counter is injected in BlackjackGame constructor</p> */
BlackjackGame::BlackjackGame(std::unique_ptr<IScoreCounter> score_counter)
{
    score_counter_ = std::move(score_counter);
}

/**
*/
bool BlackjackGame::setup()
{
    // initialize player's info
    std::string player_name = "";
    std::cout << "Enter your name please: ";
    std::cin >> player_name;

    // ask player about the amount the money he/she has
    int money = 0;
    std::cout << "How much money do you have? ";
    std::cin >> money;
    
    if (!checkEnoughMoney(money))
    {
        return false;
    }

    // we're ready to go, so create player and dealer
    player_ = std::make_shared<Player>(player_name, money);
    dealer_ = std::make_unique<CardHolder>("Dealer");

    return true;
}

/**
*/
void BlackjackGame::run()
{
    // first things first!
    if (!setup())
    {
        return;
    }
    // keep asking player to play until he/she has enough money
    // and he/she wishes to continue
    char choice = 'y';
    while (choice == 'y')
    {
        // new shuffle (new game)
        shuffle();
        // can player continue?
        if (!checkEnoughMoney(player_->getMoney()))
        {
            return;
        }
        std::cout << "Play again? (y/n)" << std::endl;
        std::cin >> choice;
    }
}

/** Check player's money. It should be enough for the minimal bet
*/
bool BlackjackGame::checkEnoughMoney(int money) const
{
    if (money < MIN_BET)
    {
        std::cout << "Sorry! You don't have enough money to continue playing!" << std::endl;
        return false;
    }
    return true;
}

/** Method shows the cardtable:
* <ul>
* <li>The number of cards in each deck</li>
* <li>Cards in the dealer's hand</li>
* <li>Cards in the player's hand</li>
* </ul>
*/
void BlackjackGame::showTable() const
{
    std::cout << std::endl;
    for (auto& deck : decks_)
    {
        std::cout << "[" << deck.getCardsCount() << "]  ";
    }
    std::cout << std::endl;
        
    dealer_->showHand();
    player_->showHand();
}

/** Method checks if a cardholder's got the BlackJack
* @param [in] CardHolder* card_holder    The pointer to a cardholder
* @returns bool true if a cardholder's got the BlackJack; false - otherwise */
bool BlackjackGame::checkBlackjack(const CardHolder* card_holder) const
{
    return card_holder->countScore(score_counter_.get()) == 21;
}

/** Method checks if a cardholder's got the BlackJack with "777" combination
* @param [in] CardHolder* cardHolder    The pointer to a cardholder
* @returns bool true if a cardholder's got the "777" combination; false - otherwise */
bool BlackjackGame::check777(const CardHolder* card_holder) const
{
    if (card_holder->countScore(score_counter_.get()) == 21)
    {
        auto hand = card_holder->getHand();

        if (hand.size() == 3)
        {
            return (hand[0].getRank() == 7 && 
                    hand[1].getRank() == 7 && 
                    hand[2].getRank() == 7);
        }
    }

    return false;
}

/** Method sets bonus stakes for a player under certain circumstances among which are:
* <ul>
* <li>Player's got Blackjack and dealer has more than one card</li>
* <li>Player's got Blackjack on the first two cards</li>
* <li>Player has 777</li>
* <li>Dealer's got blackjack</li>
* </ul>
*/
void BlackjackGame::setBonuses()
{
    // consider separately the cases with Blackjack (there are another rules for winning money calculation in those cases)
    if (checkBlackjack(player_.get()))
    {
        // if the player's got Blackjack while dealer hasn't, then we should also check how many cards do they have:
        if (!checkBlackjack(dealer_.get()))
        {   
            // and another one situation: if the player has the "777" combination, the player will take one more 1-to-1 bonus
            if (check777(player_.get()))
            {
                std::cout << "777!" << std::endl;
                player_->bonusStake(2);
            }
            // if the dealer has more than one card (i.e. the dealer was trying to take more cards in order to repeat the player's blackjack)
            else if (dealer_->getHand().size() > 1)
            {
                // then the player's winning size should be 3-to-2
                player_->bonusStake(1.5);
            }
            // there's also a situation in the very beginning of the game:
            // the dealer's got one card, and the player's got two cards
            else if (dealer_->getHand().size() == 1 && player_->getHand().size() == 2)
            {
                // in this case the player's winning size is also 3-to-2
                player_->bonusStake(1.5);
            }
        }
    }
}

/** Method is called when player wins */
void BlackjackGame::playerWins() const noexcept
{
    std::cout << std::endl << player_->getName() << " wins!" << std::endl;
    std::cout << "The winning size: " << player_->getStake() << std::endl;
    player_->winStake();
}

/** Method is called when dealer wins */
void BlackjackGame::dealerWins() const noexcept
{
    std::cout << std::endl << player_->getName() << " loses!" << std::endl;
    std::cout << "Losing size: " << player_->getStake() << std::endl;
    player_->loseStake();
}

/** Method analyzes and outputs the results of the game */
void BlackjackGame::gameResults()
{
    // first, we check for different situations, and if there's a need set bonuses to the player
    setBonuses();           
        
    // if the dealer's got Blackjack then we simply print this information
    if (checkBlackjack(dealer_.get()))
    {
        std::cout << dealer_->getName() << " Blackjack!" << std::endl;
    }

    // next, we compare total scores of the dealer and the player
    auto score_counter = score_counter_.get();

    if (player_->countScore(score_counter) < dealer_->countScore(score_counter))
    {
        dealerWins();
    }
    else if (player_->countScore(score_counter) == dealer_->countScore(score_counter))
    {
        std::cout << std::endl << "Tie!" << std::endl;
    }
    else if (player_->countScore(score_counter) > dealer_->countScore(score_counter))
    {
        playerWins();
    }
}

/** Method emulates the actions of a dealer */
void BlackjackGame::dealerActions()
{
    unsigned char choice = '0';

    // here's one of the most difficult part: we check right away if the player's got Blackjack with 2 cards
    if (checkBlackjack(player_.get()))
    {
        std::cout << player_->getName() << " Blackjack!" << std::endl;

        // we should also check that the dealer's first card is 10, J, Q, K or A
        // (but this is necessary only for the case if the player has only 2 cards)
        if (player_->getHand().size() == 2)
        {
            if (dealer_->countScore(score_counter_.get()) >= 10)
            {
                // if the dealer's got Ace then (according to rules) we can propose player the two following options:
                if (dealer_->countScore(score_counter_.get()) == 11)
                {
                    do
                    {
                        std::cout << "1. Take the winning 1 to 1" << std::endl;     // option 1
                        std::cout << "2. Keep playing" << std::endl;                // option 2
                        std::cin >> choice;
                    }
                    while (choice != '1' && choice != '2');

                    // The player may simply take the win 1-to-1 right away; otherwise the player may win with bonus 3-to-2 
                    // (if the dealer hasn't got Blackjack after he/she tries to repeat the player's Blackjack)
                    if (choice == '1')
                    {
                        // in this case the player wins and we return immediately
                        player_->winStake();
                        return;                         
                    }
                }
            }
            // if the player's got Blackjack with 2 cards and the value of the first dealer's card is less than 10,
            // then the dealer loses immediately
            else
            {
                return;             
            }
        }
    }

    // here the dealer takes cards while his/her total score is less than 17
    int score = dealer_->countScore(score_counter_.get());

    while (score < 17)
    {
        dealer_->takeCard(decks_, DECKS_COUNT);

        // The exception is possible here! (it'll be caught in the function one level higher)
        score = dealer_->countScore(score_counter_.get());
        if (score > 21)
        {
            throw BustException(dealer_->getName(), score);     // we're throwing an exception here (so watch out!)
        }
    }

    showTable();
}

/** Method starts new game (new shuffle) */
void BlackjackGame::shuffle()
{
    unsigned char choice = '0';

    int stake = 0;

    do
    {
        std::cout << "Your bet?" << std::endl;
        std::cin >> stake;
    }
    while (stake < MIN_BET || stake > player_->getMoney());

    player_->setStake(stake);
    
    // clear all hands
    dealer_->clearHand();                
    player_->clearHand();

    // randomly shuffle all decks
    unsigned int seed = 10;
    for (auto& deck : decks_)
    {
        deck.shuffle(seed);
        seed += 100;
    }
    
    // the player's given 2 cards
    player_->takeCard(decks_, DECKS_COUNT);
    player_->takeCard(decks_, DECKS_COUNT);

    // the dealer takes 1 card
    dealer_->takeCard(decks_, DECKS_COUNT);
        
    // show the cardtable
    showTable();

    // we place the try-block here since at any time both the dealer and the dealer may be busted
    try         
    {
        // main loop, while the player doesn't specify "Stand" or the player has total score of 21
        while (choice != '2' && player_->countScore(score_counter_.get()) != 21)
        {
            // Here the third option ("Double") will be available only when the player's got enough money to double down
            char third_option = '1';

            if (player_->canDoubleStake())
            {
                third_option = '3';
            }

            do  
            {
                // propose player the two standard options and perhaps "Double"
                std::cout << "1. Hit" << std::endl;             
                std::cout << "2. Stand" << std::endl;
                if (player_->canDoubleStake()) std::cout << "3. Double" << std::endl;
                    
                std::cin >> choice;
            }
            while (choice != '1' && choice != '2' && choice != third_option);

            switch (choice)
            {
                case '3':
                    // double the stake if it's possible
                    player_->bonusStake(2);
                    // and move on to branch 'case 1':
                case '1':
                    // the player's given one card
                    player_->takeCard(decks_, DECKS_COUNT);
                    int score = player_->countScore(score_counter_.get());
                    if (score > 21)
                    {
                        throw BustException(player_->getName(), score);     // we're throwing an exception here (so watch out!)
                    }

                    // show the cardtable after player took the card
                    showTable();                    

                    break;
            }
        }

        dealerActions();

        gameResults();
    }
    // if someone's got busted the controlflow immediately goes here
    catch (BustException& ex)       
    {
        // we show the cardtable (primarily, to show who's got busted)
        showTable();

        // print who's got busted
        std::cout << ex.getPlayerName() << " : " << ex.what() << std::endl;     
                
        // if the one who's got busted is the dealer, then:
        if (ex.getPlayerName() == dealer_->getName())
        {
            setBonuses();                   
            playerWins();                   
        }
        // if the one who's got busted is the player, then:
        else                                
        {
            dealerWins();
        }
    }

    // show player's money after this (already completed) shuffle
    player_->showMoney();            
}
