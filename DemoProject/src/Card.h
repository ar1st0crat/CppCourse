/** @file */

#pragma once
#include <iostream>
#include <vector>
#include "Suit.h"


/** @class Card
* <p>Represents the Card entity</p>
*
* Card numbers : 0..51  
*       <ul>        
*       <li>0..12  ->  hearts    suit = 0   </li>
*       <li>13..25 ->  diamonds  suit = 1   </li>
*       <li>26..38 ->  clubs     suit = 2   </li>
*       <li>39-51  ->  spades    suit = 3   </li>
*       </ul>
* <p>Card ranks:</p>
*       2..10 J=11 Q=12 K=13 A=14 ( J, Q, K, A will be interpreted differently depending on the game type )
*
* @author ar1st0crat
*/
class Card
{
public:
    Card() noexcept;
    Card(Suit suit, size_t card_no) noexcept;

    size_t getNumber() const noexcept;
    void setNumber(size_t card_no) noexcept;
    short getRank() const noexcept;
    
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend std::ostream& operator<<(std::ostream& os, const std::vector<Card>& hand);

protected:
    Suit suit_;
    short rank_;
};
