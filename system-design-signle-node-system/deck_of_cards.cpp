/*
https://github.com/donnemartin/system-design-primer/blob/master/solutions/object_oriented_design/deck_of_cards/deck_of_cards.ipynb

Design a deck of cards
Constraints and assumptions

Is this a generic deck of cards for games like poker and black jack?
Yes, design a generic deck then extend it to black jack
Can we assume the deck has 52 cards (2-10, Jack, Queen, King, Ace) and 4 suits?
Yes
Can we assume inputs are valid or do we have to validate them?
Assume they're valid


https://www.codeconvert.ai/python-to-c++-converter
converted example by Donne Martin in python
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

enum class Suit {
    HEART,
    DIAMOND,
    CLUBS,
    SPADE
};

class Card {
public:
    virtual int getValue() const = 0;
    virtual bool isAvailable() const = 0;
    virtual void setAvailable(bool available) = 0;
    virtual Suit getSuit() const = 0;
};

class BlackJackCard : public Card {
private:
    int value;
    Suit suit;
    bool available;

public:
    BlackJackCard(int value, Suit suit) : value(value), suit(suit), available(true) {}

    int getValue() const override {
        if (value == 1) {
            return 1;
        } else if (value > 10 && value <= 13) {
            return 10;
        } else {
            return value;
        }
    }

    bool isAvailable() const override {
        return available;
    }

    void setAvailable(bool available) override {
        this->available = available;
    }

    Suit getSuit() const override {
        return suit;
    }

    bool isAce() const {
        return value == 1;
    }

    bool isFaceCard() const {
        return value > 10 && value <= 13;
    }
};

class Hand {
protected:
    std::vector<Card*> cards;

public:
    void addCard(Card* card) {
        cards.push_back(card);
    }

    int score() const {
        int totalValue = 0;
        for (const auto& card : cards) {
            totalValue += card->getValue();
        }
        return totalValue;
    }
};

class BlackJackHand : public Hand {
public:
    static const int BLACKJACK = 21;

    int score() const override {
        int minOver = std::numeric_limits<int>::max();
        int maxUnder = -std::numeric_limits<int>::max();
        for (int score : possibleScores()) {
            if (BLACKJACK < score && score < minOver) {
                minOver = score;
            } else if (maxUnder < score && score <= BLACKJACK) {
                maxUnder = score;
            }
        }
        return maxUnder != -std::numeric_limits<int>::max() ? maxUnder : minOver;
    }

    std::vector<int> possibleScores() const {
        // Implement the logic to calculate possible scores, taking Aces into account
    }
};

class Deck {
private:
    std::vector<Card*> cards;
    int dealIndex = 0;

public:
    Deck(const std::vector<Card*>& cards) : cards(cards) {}

    int remainingCards() const {
        return cards.size() - dealIndex;
    }

    Card* dealCard() {
        if (dealIndex < cards.size()) {
            Card* card = cards[dealIndex];
            card->setAvailable(false);
            dealIndex++;
            return card;
        } else {
            return nullptr;
        }
    }

    void shuffle() {
        // Implement the shuffle logic
    }
};

