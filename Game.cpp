#include <iostream>
#include "Card.h"
#include "Game.h"
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <fstream> // Read .Dat files 
#include <sstream> // Edit files 
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





int getHandValue(const vector<Card>& hand, bool dealerFlip) {
    int handValue = 0; 
    bool PlrHasAce = false; 
    int count = 0; 

    for (Card cardIter : hand) {
        if (dealerFlip) {
            return cardIter.getCardValue();
        }

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

   void iterateAndDisplayCards(const vector<Card>& hand, bool dealerFlip) {
    if (!dealerFlip) {
        for (auto& iter : hand) {
            iter.display();
        }
    }
    else {
        hand[0].display(); // Just display the first deealer card 
    }
    }

    int getPlrChips() {
        ifstream file("plrChips.dat"); // Open the file 

        if (!file.is_open()) {
            cerr << "Error: Failed to open player chips data"; // IO Exception 
            return -1;
        }

       int value; 
       file >> value; // Read the first line 
       file.close();
       return value; 

    }

    void adjustPlrChips(int& initalAmount, int& amount, bool result) {
        ifstream fileIn("plrChips.dat");

        if (!fileIn.is_open()) {
            cerr << "Error : Could not open the player chips data";
            return;
        }

        // Get new values 
        int newVal = 0; 

        if (result) {
            newVal = initalAmount + amount;
        } else {
            newVal = initalAmount - amount; 
        }

        vector<string> lines; 
        string line; 

        // Read all lines into a vector 
        if (!lines.empty()) {
            lines[0] = to_string(newVal); // Replace with the new value
        } else {
            lines.push_back(to_string(newVal)); // if the file is empty, we add the new value anyway
        }

        // Write back to file 
        ofstream fileOut("PlrChips.dat");
        if (!fileOut.is_open()) {
            cerr << "Error : Could not open file for writing";
            return;
        }

        for (const auto& l : lines) {
            fileOut << l << "\n";
        }

        fileOut.close(); // Close the file


    }

    void displayHands(const vector<Card>& dlrHand, const int& dlrHandValue, const vector<Card>& plrHand, const int& plrHandValue, bool dealerFlip) {
         cout << "Dealer hand: ";
        iterateAndDisplayCards(dlrHand, dealerFlip);
        cout << "\n";
        cout << "Dealer Hand Value: " << dlrHandValue;
        cout << "\n";
        cout << "\n------------------------------------\n"; // Seperation line
        cout << "Your hand: ";
        iterateAndDisplayCards(plrHand, dealerFlip);
        cout << "\n";
        cout << "Hand Value: " << plrHandValue;
        cout << "\n";
    }





void Game::startGame(stack<Card> deck) {
    cout << "The game has started! Welcome to blackjack... Please place your desired bet. \n";
    
    int initalPlrChips = getPlrChips();
    int plrBet = 0; 
    bool validBet = false;

    cout << "\n------------------------------------\n";
    cout << "Your chips: " << initalPlrChips;
    cout << "\n------------------------------------\n";

    cout << "Enter your bet amount: ";
    
    while (!validBet) {
    cin >> plrBet; 
        if (plrBet > initalPlrChips) {
            cout << "You cannot bet over the amount of chips you currently have!";
        } else if (plrBet <= 0) {
            cout << "You cannot bet zero or in any negative numbers!";
        } else {
            cout << "Bet Placed! You are betting " << plrBet << " Chips for this hand\n";
            validBet = true;
        }
    }

    cout << "We will deal cards now...\n"; 

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

    plrHandValue = getHandValue(plrHand, false);
    dlrHandValue = getHandValue(dlrHand, true);
    while (gameStatus) {
        // Get hand values  
        char plrMove = 0; 

        // Display player and dealer hands 
       displayHands(dlrHand, dlrHandValue, plrHand, plrHandValue, true);

        // Prompt player to get their move 
        cout << "Would you like to hit or stand? (h/s): ";
        cin >> plrMove; 

        if (plrMove == 'h') {
            Card cardToDraw = deck.top(); 
            deck.pop(); // remove card from top of deck 
            plrHand.emplace_back(cardToDraw); // Add to player hand 
            plrHandValue = getHandValue(plrHand, false); // Update the plr hand value 
            cout << "Card Drawn: ";
            cardToDraw.display(); 
             displayHands(dlrHand, dlrHandValue, plrHand, plrHandValue, true);
            cout << "\n";
        }

        if (dlrHandValue < 17) {
            Card cardToDrawDlr = deck.top();
            deck.pop(); // remove card from top of deck 
            dlrHand.emplace_back(cardToDrawDlr);
            dlrHandValue = getHandValue(dlrHand, false);
            cout << "Dealer card drawn: "; 
            cardToDrawDlr.display(); 
             displayHands(dlrHand, dlrHandValue, plrHand, plrHandValue, true);
            cout << "\n";
        }


        // Check for winners/losers 
        if (plrHandValue >= 22) {
            cout << "You have lost!" << " taking " << plrBet << " chips from your balance." << " Better luck next time!";
            adjustPlrChips(initalPlrChips, plrBet, false); 
            gameStatus = false; 
        } else if (dlrHandValue >= 22 || (dlrHandValue >= 17 && plrHandValue > dlrHandValue)) {
            cout << "You have won!" << " adding " << plrBet << " chips to your balance! Congratualations\n";
            adjustPlrChips(initalPlrChips, plrBet, true);
            gameStatus = false;
        } else if (dlrHandValue >= 17 && dlrHandValue == plrHandValue) {
            cout << "The game has resulted in a tie!"; 
            gameStatus = false; 
        }


    }


   

}


