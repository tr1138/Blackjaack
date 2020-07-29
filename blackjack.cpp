#include <iostream>
#include <array>
#include <algorithm>
#include <ctime>
#include <random>

enum class CardRank
{
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,

    MAX_RANKS,
};

enum class CardSuit
{
    CLUB,
    DIAMOND,
    HEART,
    SPADE,

    MAX_SUITS,
};

struct Card
{
    CardRank rank{};
    CardSuit suit{};
};

void printCard(const Card &card)
{
    switch (card.rank)
    {
    case CardRank::RANK_2:
        std::cout << '2';
        break;
    case CardRank::RANK_3:
        std::cout << '3';
        break;
    case CardRank::RANK_4:
        std::cout << '4';
        break;
    case CardRank::RANK_5:
        std::cout << '5';
        break;
    case CardRank::RANK_6:
        std::cout << '6';
        break;
    case CardRank::RANK_7:
        std::cout << '7';
        break;
    case CardRank::RANK_8:
        std::cout << '8';
        break;
    case CardRank::RANK_9:
        std::cout << '9';
        break;
    case CardRank::RANK_10:
        std::cout << 'T';
        break;
    case CardRank::RANK_JACK:
        std::cout << 'J';
        break;
    case CardRank::RANK_QUEEN:
        std::cout << 'Q';
        break;
    case CardRank::RANK_KING:
        std::cout << 'K';
        break;
    case CardRank::RANK_ACE:
        std::cout << 'A';
        break;
    
    default:
        std::cout << '?';
        break;
    }

    switch (card.suit)
    {
    case CardSuit::CLUB:
        std::cout << 'C';
        break;
    case CardSuit::DIAMOND:
        std::cout << 'D';
        break;
    case CardSuit::HEART:
        std::cout << 'H';
        break;
    case CardSuit::SPADE:
        std::cout << 'S';
        break;
        
    default:
        std::cout << '?';
        break;
    }
}

using deck_type = std::array<Card, 52>;
using index_type = deck_type::size_type;

deck_type createDeck()
{
    deck_type deck{};

    auto suits{ static_cast<index_type>(CardSuit::MAX_SUITS) };
    auto ranks{ static_cast<index_type>(CardRank::MAX_RANKS) };

    index_type card{ 0 };
    for (index_type suit{ 0 }; suit < suits; ++suit)
    {
        for (index_type rank{ 0 }; rank < ranks; ++rank)
        {
            deck[card].rank = static_cast<CardRank>(rank);
            deck[card].suit = static_cast<CardSuit>(suit);
            ++card;
        }
    }

    return deck;
}

void printDeck(const deck_type& deck)
{
    for (const auto &card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }
    std::cout << "\n\n";
}

void shuffleDeck(deck_type& deck)
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    
    std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(const Card& card)
{
    if (card.rank <= CardRank::RANK_10)
    {
        return (static_cast<int>(card.rank) + 2);
    }
    switch (card.rank)
    {
    case CardRank::RANK_JACK:
    case CardRank::RANK_QUEEN:
    case CardRank::RANK_KING:
        return 10;
    case CardRank::RANK_ACE:
        return 11;

    default:
        return 0;
    }
}

bool playBlackjack(const deck_type& deck)
{
    index_type card{ 0 };
    int dealerScore{ getCardValue(deck[card++]) };
    std::cout << "The dealer's score is: " << dealerScore << '\n';
   
    int playerScore{ getCardValue(deck[card++]) };
    
    bool playerHit{ false };
    do
    {
        playerScore += getCardValue(deck[card++]);
        std::cout << "The player's score is: " << playerScore << '\n';
        if (playerScore > 21)
        {
            std::cout << "Player bust!\n";
            return 0;
        }

        std::cout << "\nHit (h) or Stand (s)?\n";
        char c{};
        std::cin >> c;
        playerHit = (c == 'h');
    } while (playerHit);
    
    do
    {
        std::cout << "Dealer draws\n";
        dealerScore += getCardValue(deck[card++]);
        std::cout << "Dealer's score is: " << dealerScore << '\n';
        if (dealerScore > 21)
        {
            std::cout << "Dealer bust!\n";
            return 1;
        }
    } while (dealerScore < 17);

    return (playerScore > dealerScore);
}

int main()
{
    auto deck{ createDeck() };

    //printDeck(deck);
    
    shuffleDeck(deck);
    
    printDeck(deck);

    bool result{ playBlackjack(deck) };
    if (result)
        std::cout << "You win!\n";
    else
        std::cout << "You lose!\n";

    return 0;
}