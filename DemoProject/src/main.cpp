#include "BlackjackScoreCounter.h"
#include "BlackjackGame.h"

int main()
{
    // quite minimalistic, huh?
    BlackjackGame().run();

    /* === for experiments ===
     * injection of scorecounting strategy in blackjack constructor:
     *
     * auto counter = std::make_unique<BlackjackScoreCounter>();
     * BlackjackGame(std::move(counter)).run();
     *
     * ======================= */

    return 0;
}
