#include <iostream>
#include "Card.h"
#include "Game.h"
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>

stack<Card> Game::createDeck() {
    vector<Card> deck; 
    vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    vector<string> names = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    vector<int> values = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

    for (const string& suit : suits) {
        for (size_t i = 0; i < names.size(); ++i) {
            deck.emplace_back(suit, names[i], values[i]);
        }
    }

    // Shuffle the deck
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));

    // Load into a stack 

    stack<Card> deckStack;
    for (const Card& card : deck) {
        deckStack.push(card);
    }

        return deckStack;
}