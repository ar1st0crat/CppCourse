#include "BlackjackScoreCounter.h"


/** Method implements the countScore() method of the IScoreCounter interface
* @param [in] const std::vector<Card>& hand The hand of a cardholder to calculate the total score for all cards in the set
* @returns int total score in the hand */
int BlackjackScoreCounter::countScore(const std::vector<Card>& hand) const
{
    int score = 0;

    // the number of aces in the hand to be counted as 11 ("11-aces")
    int aces = 0;

    // count each card in the hand
    for (auto& card : hand)
    {
        //int rank = hand[i].getRank();
        int rank = card.getRank();
        // set the value of J, Q, K equal to 10
        if (rank > 10)
        {
            // if we're dealing with Ace then first we increase the total score by 11
            // and increase the number of 11-aces in the hand (by default)
            if (rank == 14)
            {
                rank = 11;
                aces++;
            }
            else
            {
                rank = 10;
            }
        }
        score += rank;
    }
    // if we got so many aces that we got busted then try to count one ace as 1 (not as 11)
    // and decrease the number of "11-aces"
    while (score > 21 && aces > 0)
    {
        score -= 10;
        aces--;
    }

    return score;
}
