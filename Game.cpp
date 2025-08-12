#include <iostream>
#include "Card.h"
#include "Game.h"
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
using namespace std;

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

int getHandValue(const vector<Card>& hand) {
    int handValue = 0; 
    bool PlrHasAce = false; 

    for (Card cardIter : hand) {
        if (cardIter.getCardName() == "Ace") {
            PlrHasAce = true; 
        }
        handValue += cardIter.getCardValue();
    }

    if (PlrHasAce) {
        if (handValue > 22) {
            handValue -= 10;
        }
    }

    return handValue;
}

   void iterateAndDisplayCards(const vector<Card>& hand) {
        for (Card iter : hand) {
            iter.display();
        }
    }




void Game::startGame(stack<Card> deck) {
    cout << "The game has started! Welcome to blackjack... Please place your desired bet. \n";
   // int plrBet = 0; Skip for now

   // cin >> plrBet; 

    cout << "Bet placed! We will deal cards now...\n"; 

    // Draw inital cards
    int initalDrawCount = 0; 
    bool isPlayerDraw = true; // Player gets dealt first 
    vector<Card> plrHand; 
    vector<Card> dlrHand; 

    while (initalDrawCount < 4) {
        Card currCard = deck.top(); 

        if (isPlayerDraw) {
        deck.pop(); // Remove card 
        plrHand.emplace_back(currCard);
        isPlayerDraw = false; 
        } else {
            deck.pop(); // Remove card 
            dlrHand.emplace_back(currCard);
            isPlayerDraw = true;
        }

        initalDrawCount++; 

    }

    bool gameStatus = true; 

    // Enter the loop of the game 
    int plrHandValue = 0; 
    int dlrHandValue = 0; 

    plrHandValue = getHandValue(plrHand);
    dlrHandValue = getHandValue(dlrHand);
    while (gameStatus) {
        // Get hand values  
        char plrMove = 0; 

        // Display player and dealer hands 
        cout << "Dealer hand: ";
        iterateAndDisplayCards(dlrHand);
        cout << "\n";
        cout << "Dealer Hand Value: " << dlrHandValue;
        cout << "\n";
        cout << "\n------------------------------------\n"; // Seperation line
        cout << "Your hand: ";
        iterateAndDisplayCards(plrHand);
        cout << "\n";
        cout << "Hand Value: " << plrHandValue;
        cout << "\n";

        // Prompt player to get their move 
        cout << "Would you like to hit or stand? (h/s)";
        cin >> plrMove; 

        if (plrMove == 'h') {
            Card cardToDraw = deck.top(); 
            deck.pop(); // remove card from top of deck 
            plrHand.emplace_back(cardToDraw); // Add to player hand 
            plrHandValue = getHandValue(plrHand); // Update the plr hand value 
            cout << "Card Drawn: ";
            cardToDraw.display(); 
            cout << "\n";
        }

        if (dlrHandValue < 17) {
            Card cardToDrawDlr = deck.top();
            deck.pop(); // remove card from top of deck 
            dlrHand.emplace_back(cardToDrawDlr);
            dlrHandValue = getHandValue(dlrHand);
            cout << "Dealer card drawn: "; 
            cardToDrawDlr.display(); 
            cout << "\n";
        }


        // Check for winners/losers 
        if (plrHandValue >= 22) {
            cout << "You have lost!";
            gameStatus = false; 
        } else if (dlrHandValue >= 22 || (dlrHandValue >= 17 && plrHandValue > dlrHandValue)) {
            cout << "You have won!";
            gameStatus = false;
        } else if (dlrHandValue >= 17 && dlrHandValue == plrHandValue) {
            cout << "The game has resulted in a tie!"; 
            gameStatus = false; 
        }


    }
   

}


