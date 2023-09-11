/* CSCI 200: Final Project
 *
 * Author: XXXX (Peyton Calvert)
 * Resources used (Online Resources):
 * Online resources were used to figure out how certain things worked such as goto statements.
 *
 * XXXXXXXX (MORE_COMPLETE_DESCRIPTION_HERE)
 * This program implements the game of blackjack the player has a balance that they start with and can play as many games as they
 * would like until they want to stop or run out of money. The player can hit stand double down and surrender. 
 */
#include "Deck.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "Dealer.hpp"
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

string getPlayerAction(const vector<Card> HAND, const int BAL, const int BET){
    bool isValidAction = false;
    string input;
    while(!isValidAction){
        cout << "Would you like to Hit Stand Double Down or Surrender: (H,S,D,SS) ";
        cin >> input;
        cout << endl;
        if(input == "H" || input == "S" || input == "SS"){
            isValidAction = true;
        }
        else if(input == "D" && (HAND.size() == 2) && ((BET*2) <= BAL)){
            isValidAction = true;
        }
        else{
            cout << "Please enter a valid action" << endl;
        }
    }
    return input;
}
int getHandValue(const vector<Card> HAND){
    int handValue = 0;
    int numAces = 0;
    //loop to evaluate the value of a hand as an integer
    for(int i=0;i<HAND.size();i++){
        //for now evaluate any Aces to 11 will adjust the value later if necessary
        if(HAND.at(i).value == "A"){
            handValue += 11;
            numAces++;
        }
        else if(HAND.at(i).value == "2"){
            handValue += 2;
        }
        else if(HAND.at(i).value == "3"){
            handValue += 3;
        }
        else if(HAND.at(i).value == "4"){
            handValue += 4;
        }
        else if(HAND.at(i).value == "5"){
            handValue += 5;
        }
        else if(HAND.at(i).value == "6"){
            handValue += 6;
        }
        else if(HAND.at(i).value == "7"){
            handValue += 7;
        }
        else if(HAND.at(i).value == "8"){
            handValue += 8;
        }
        else if(HAND.at(i).value == "9"){
            handValue += 9;
        }
        else if(HAND.at(i).value == "10"){
            handValue += 10;
        }
        else if(HAND.at(i).value == "J"){
            handValue += 10;
        }
        else if(HAND.at(i).value == "Q"){
            handValue += 10;
        }
        else if(HAND.at(i).value == "K"){
            handValue += 10;
        }
    }
    //loop for correcting ace values
    for(int i=0;i<numAces;i++){
        //as long as there are aces left and the hand value is greater than 21 subtract 10
        if(handValue > 21){
            handValue -= 10;
        }
        else;
    }
    return handValue;
}
bool isHandBlackJack(const vector<Card> HAND){
    //if the hand size is greater than 2 the player cannot have a blackjack
    if(HAND.size()>2){
        return false;
    }
    //since we know the size is now 2 if the player has 21 they have a blackjack
    else if(getHandValue(HAND) == 21){
        return true;
    }   
    return false;
}
int getBetAmount(const int playerBalance){
    bool validBetInput = false;
    int betAmount;
    while(!validBetInput){
        cout << "Current Balance: " << playerBalance << endl;
        cout << "How much money would you like to bet? ";
        cin >> betAmount;
        if(betAmount > 0 && betAmount <= playerBalance){
            //if input is greater than 0 all is good
            validBetInput = true;
        }
        else if(cin.fail()){
            //otherwise clear the input and try again
            cout << "Not a valid bet amount " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        else{
            cout << "Not a valid bet amount " << endl;
        }
    }
    return betAmount;
}
void playGame(int &playerBalance){
    Player P1(playerBalance);
    Dealer D1;
    int numDecks;
    bool validNumInput = false;
    //this block prompts the user for how many decks they want in the shoe and validates that input
    while(!validNumInput){
        cout << "How many decks would you like to play with? ";
        cin >> numDecks;
        if(numDecks > 0){
            //if input is greater than 0 all is good
            validNumInput = true;
        }
        else if(cin.fail()){
            //otherwise clear the input and try again
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
    }
    //make the game deck with the number of decks inputted by the player
    Deck gameDeck(numDecks);
    //shuffle the game deck
    gameDeck.shuffle();
    //next the main gameplay loop until the player runs out of money or chooses to quit
    while(playerBalance > 0){
        START:
        //check if the deck is over halfway empty if so reshuffle and reset
        if(gameDeck.getDeck().size() <= (numDecks*52)/2){
            cout << "Reshuffling Decks " << endl;
            gameDeck.restart();
        }
        string input;
        while(input != "Y" && input != "N"){
            cout << "Would you like to play a hand of black jack? (Y/N)";
            cin >> input;
        }
        cout << endl;
        if(input == "Y"){
            //ask the player how much they would like to bet and play a hand of black jack
            cout << "Playing game" << endl;
            //call method for getting the players bet
            int betAmount = getBetAmount(playerBalance);
            //reset player and Dealers hand
            P1.clearHand();
            D1.clearHand();
            //give dealer their initial hand
            D1.hit(gameDeck);
            D1.hit(gameDeck);
            //Print out the dealers hand but keep one of the cards hidden
            cout << "Dealer Hand: " << D1.getHand().at(0).value << " " << D1.getHand().at(1).value << endl;
            //give the Player their initial hand and print it out with both cards showing
            P1.hit(gameDeck);
            P1.hit(gameDeck);
            cout << "Player Hand: " << P1.getHand().at(0).value << " " << P1.getHand().at(1).value << endl;
            //next loop to get the players action until they choose to stand 
            string playerAction;
            while(playerAction != "S" && getHandValue(P1.getHand()) < 21){
                //call method to get the players action
                playerAction = getPlayerAction(P1.getHand(),playerBalance,betAmount);
                //then do what the player wants
                //if player surrenders stop game and give back half original bet
                if(playerAction == "SS"){
                    playerBalance -= (betAmount/2);
                    goto START;
                }
                //if player stands just continue and the loop will stop itself
                else if(playerAction == "S"){
                    continue;
                }
                //if player doubles down they get one more card and double their bet
                else if(playerAction == "D"){
                    betAmount *= 2;
                    P1.hit(gameDeck);
                    break;
                }
                //if player hits
                else if(playerAction == "H"){
                    P1.hit(gameDeck);
                }
                else;
                cout << "Dealers hand: ";
                for(int i=0;i<D1.getHand().size();i++){
                    cout << D1.getHand().at(i).value << " ";
                }
                cout << endl;
                cout << "Player Hand: ";
                for(int i=0;i<P1.getHand().size();i++){
                    cout << P1.getHand().at(i).value << " ";
                }
                cout << endl;
            }
            //first check if the player busted
            if(getHandValue(P1.getHand()) > 21){
                cout << "Player busted " << endl;
                playerBalance -= betAmount;
                continue;
            }
            //then check if player has a blackjack
            else if(isHandBlackJack(P1.getHand())){
                cout << "Black Jack! " << endl;
                playerBalance += ((betAmount)*(3/2));
                cout << "Balance: " << playerBalance << endl;
                goto START;
            }
            //after the player is done the dealer takes their actions based on Dealer hit 16 stay 17
            if(getHandValue(D1.getHand()) <= 16){
                D1.hit(gameDeck);
            }
            //if the hand is greater than 16 do nothing and continue
            else;
            //then after the dealer is done determine the winner and adjust the players balance accordingly
            //print Dealers hand
            cout << "Dealers hand: ";
            for(int i=0;i<D1.getHand().size();i++){
                cout << D1.getHand().at(i).value << " ";
            }
            cout << endl;
            //print players hand
            cout << "Players hand: ";
            for(int i=0;i<P1.getHand().size();i++){
                cout << P1.getHand().at(i).value << " ";
            }
            cout << endl;
            //if the player has a greater valued hand they win
            if(getHandValue(D1.getHand()) > 21){
                cout << "Dealer Busts " << endl;
                playerBalance += betAmount;
            }
            else if(getHandValue(P1.getHand()) > getHandValue(D1.getHand())){
                cout << "Player Wins! " << endl;
                playerBalance += betAmount;
            }
            //if the dealer wins the player loses the bet amount
            else if(getHandValue(P1.getHand()) < getHandValue(D1.getHand())){
                cout << "Player Loses! " << endl;
                playerBalance -= betAmount;
            }
            //if they tie nothing happens
            else{
                //do nothing
                cout << "WRONG:" << endl;
            }
            
        }
        else{
            //write the players current balance to a txt file and quit the game
            cout << "Balance " << playerBalance;
            return;
        }
    }
}
int main(){
    //file to read from
    ifstream readBalance;
    //file to write to
    ofstream writeBalance;
    //default balance value
    int playerBalance = 100;
    string input;
    while(input != "Y" && input != "N"){
        cout << "Welcome to Black Jack would you like to keep your balance from last time? (Y/N)";
        cin >> input;
    }
    cout << endl;
    if(input == "Y"){
        int previousBal = 0;
        //open and read the balance from last time and pass to play game
        readBalance.open("balance.txt");
        if(readBalance.is_open() && readBalance>>previousBal){
            readBalance >> previousBal;
            playGame(previousBal);
            //if player runs out of money bail them out for next game
            if(previousBal == 0){
                cout << "Player ran out of money giving them $20 " << endl;
                previousBal += 20; 
            }
            writeBalance.open("balance.txt");
            writeBalance << previousBal;
        }
        else{
            cerr << "ERROR READING BALANCE";
            return -1;  
        }
    }
    else{
        playGame(playerBalance);
        writeBalance.open("balance.txt");
        writeBalance << playerBalance;
    }
    
    
    writeBalance.close();
    readBalance.close();
    return 0;
}