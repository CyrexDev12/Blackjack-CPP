#include <iostream>
#include <stack>
#include "Card.h"
#include "Game.h"
using namespace std;



int main() {
    Game game;
    stack<Card> Deck = game.createDeck();
    // cout << "Deck size: " + Deck.size() << "\n";
    while (!Deck.empty()) {
        Card topCard = Deck.top();
        topCard.display();
        cout << "\n"; // Newline 
        Deck.pop();
    }

    return 0; 
}