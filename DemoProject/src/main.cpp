#include <iostream>
#include "Controller/BlackjackController.h"

#if 1

int main()
{
    BlackjackController().start();       // quite minimilastic, huh?
    return 0;
}



// change "#if 1" above to "#if 0" to compile this exotic version:

#else

#include "Controller/Rules/BlackjackDealStrategy.h"
#include "Controller/Rules/Misc/EarlyBlackjackStrategy.h"
#include "Controller/Rules/Misc/Rules25.h"
#include "View/ConsoleView.h"

int main()
{
    std::cout << "1. Early blackjack strategy" << std::endl;
    std::cout << "2. Rules 'Blackjack=25'" << std::endl;
    auto choice = '1';
    std::cin >> choice;

    if (choice == '1')
    {
        // we can play around with predefined decks and cards
        // (set via EarlyBlackjackStrategy class, see above):

        BlackjackController test(std::make_unique<ConsoleView>(),
                                 std::make_unique<misc::EarlyBlackjackStrategy>());
        test.start();
    }
    else
    {
        // ...and even with some new rules according to which blackjack is 25!
        // (set via Rules25 class, see above):

        BlackjackController cool(std::make_unique<ConsoleView>(),
                                 std::make_unique<BlackjackDealStrategy>(),
                                 std::make_unique<misc::Rules25>());
        cool.start();
    }

    return 0;
}

#endif
