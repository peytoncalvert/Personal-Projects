#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>

using namespace std;

struct Card{
    //stores the value of a card as a string 
    string value;
    Card(string value);
};

Card::Card(string value){
    this->value = value;
}

#endif