#include "Card.h"
#include <array>
#include <string>


/* Default constructor
* @post Initializes Card to Two of Clubs
*/
Card::Card(){
    rank = Rank::TWO;
    suit = Suit::CLUBS;
}

/* Parameterized constructor
* @post Initializes Card to the specified rank and suit
* @param rank The rank for the card
* @param suit The suit for the card
*/
Card::Card(Rank rank, Suit suit){
    this->rank = rank;
    this->suit = suit;
}
    
/* Getter for rank
* @return Rank of the card
*/
Rank Card::get_rank() const{
    return rank;
    
}

/* Getter for suit
* @return Suit of the card
*/
Suit Card::get_suit() const{
    return suit;
    
}

/* Determines if the Card is of the trump suit
* @return True if card has a suit of Spades
*/

bool Card::is_trump() const{
    if (suit == Suit::SPADES) {
        return true;
    }
    return false;
    
}

/* Converts a string representing a Rank to a Rank object
* @pre The str represents a valid Rank ("Two", "Three", ... , "Ace")
*	If the string is not valid,
	throw std::invalid_argument("Invalid value for string_to_rank function.");
* @param str The string representing the rank
* @return Rank object
*/
Rank string_to_rank(const std::string& str){
    if (str == "Two")
        return Rank::TWO;
     if (str == "Three")
        return Rank::THREE;
     if (str == "Four")
        return Rank::FOUR;
     if (str == "Five")
        return Rank::FIVE;
     if (str == "Six")
        return Rank::SIX;
     if (str == "Seven")
        return Rank::SEVEN;
     if (str == "Eight")
        return Rank::EIGHT;
     if (str == "Nine")
        return Rank::NINE;
     if (str == "Ten")
        return Rank::TEN;
     if (str == "Jack")
        return Rank::JACK;
     if (str == "Queen")
        return Rank::QUEEN;
     if (str == "King")
        return Rank::KING;
     if (str == "Ace")
        return Rank::ACE;
    throw std::invalid_argument("Invalid value for string_to_rank function.");
}

/* Prints the rank to the stream object
* @param os The ostream object to print to
* @param rank The rank to print 
* @return reference to ostream object passed into the function
*/
std::ostream& operator<<(std::ostream& os, Rank rank){
    switch (rank)
    {
        case Rank::TWO:
            os << "Two";
            break;
        case Rank::THREE:
            os << "Three";
            break;
        case Rank::FOUR:
            os << "Four";
            break;
        case Rank::FIVE:
            os << "Five";
            break;
        case Rank::SIX:
            os << "Six";
            break;
        case Rank::SEVEN:
            os << "Seven";
            break;
        case Rank::EIGHT:
            os << "Eight";
            break;
        case Rank::NINE:
            os << "Nine";
            break;
        case Rank::TEN:
            os << "Ten";
            break;
        case Rank::JACK:
            os << "Jack";
            break;
        case Rank::QUEEN:
            os << "Queen";
            break;
        case Rank::KING:
            os << "King";
            break;
        case Rank::ACE:
            os << "Ace";
            break;
    }

    return os;
}

/* Updates the rank object to the rank from the stream
* @pre The read input must be a valid rank, (HINT: use string_to_rank)
* @param is The istream object where the data is coming from
* @param rank The rank to update
* @return reference to istream object passed into the function
*/
std::istream& operator>>(std::istream& is, Rank& rank){
    std::string input;
    is >> input;
    
    rank = string_to_rank(input);
    
    return is;
}


/* Prints the Card to the stream
* @post Prints to stream the card in this format: `[rank] of [suit]`. 
*	 Examples: "Two of Spades", "Queen of Hearts", "Ace of Diamonds"
* @param os The ostream object to print to
* @param card The card to print
* @return Reference to ostream object passed into the function
*/

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    os << card.get_rank() << " of " << card.get_suit(); // Assuming Card has member functions getRank() and getSuit() that return the rank and suit respectively
    return os;
}

/* Converts a string representing a Suit to a Suit object
* @pre The str represents Suit ("Spades", "Hearts", "Clubs", or "Diamonds")
*	If the string is not valid,
*	throw std::invalid_argument("Invalid value for string_to_suit function.");
* @param str The string representing the suit
* @return Suit object
*/
Suit string_to_suit(const std::string& str) {

    if (str == "Spades"){
        return Suit::SPADES;
    }
    else if (str == "Hearts"){
        return Suit::HEARTS;
    }  
    else if (str == "Clubs"){
        return Suit::CLUBS;
    } 
    else if (str == "Diamonds"){
        return Suit::DIAMONDS;
    }  
    else {
        throw std::invalid_argument("Invalid value for string_to_suit function.");

    }

}

/* Reads a Card from a stream into a Card object
* Since this function was declared a friend of the Card class, it has access
* to the Card's private members (card.rank and card.suit)
* @pre stream contains valid representation of Card
* @post Reads in a Card from the stream in the format of `[rank] of [suit]`
*	 and use those values to update the card object
* @param is The istream object where the data is coming from
* @param card The card to update
* @return reference to istream object passed into the function
*/

std::istream& operator>>(std::istream& is, Card& card)
{
    std::string input;
    std::string rank_;
    std::string suit_;

//Two of Diamonds
    is >> rank_;
    is >> input;
    is >> suit_;

    card.rank = (string_to_rank(rank_));
    card.suit = (string_to_suit(suit_));
    return is;
}


/* Prints the suit to the stream object
* @param os The ostream object to print to
* @param suit The suit to print
* @return reference to ostream object passed into the function
*/
std::ostream& operator<<(std::ostream& os, Suit suit){
    if(suit == Suit::CLUBS)
        os  << "Clubs";
    else if(suit == Suit::DIAMONDS)
        os  << "Diamonds";
    else if(suit == Suit::HEARTS)
        os  << "Hearts";
    else if(suit == Suit::SPADES)
        os  << "Spades";
    return os; 
}


/* Updates the suit object to the suit from the stream
* @pre The read input must be a valid suit, (HINT: use string_to_suit)
* @param is The istream object where the data is coming from
* @param suit The suit to update
* @return reference to istream object passed into the function
*/
std::istream& operator>>(std::istream& is, Suit& suit){
    std::string input;
    is >> input;
    
    if (input == "Clubs")
        suit = Suit::CLUBS;
    else if (input == "Diamonds")
        suit = Suit::DIAMONDS;
    else if (input == "Hearts")
        suit = Suit::HEARTS;
    else if (input == "Spades")
        suit = Suit::SPADES;
    
    return is;
}





/* Less than comparision of two cards
* @param lhs Card on left handside of operator
* @param rhs Card on right handside of operator
* @return true if lhs is lower value than rhs. Doesn't consider lead or trump
*/
bool operator<(const Card& lhs, const Card& rhs){
    if (lhs.get_suit() < rhs.get_suit()) {
        return true;
    }
    if (lhs.get_suit() == rhs.get_suit()) {
        if (lhs.get_rank() < rhs.get_rank()) {
            return true;
        }
    }
    return false;
}//not sure if get_rank returns comparable values 

/* Less than or equal to comparision of two cards
* @param lhs Card on left handside of operator
* @param rhs Card on right handside of operator
* @return true if lhs is lower value than rhs or the same card as rhs.
*		   Does not consider lead or trump
*/
bool operator<=(const Card& lhs, const Card& rhs) {
    if (lhs.get_suit() < rhs.get_suit()) {
        return true;
    }
     if (lhs.get_suit() == rhs.get_suit()) {
        if (lhs.get_rank() <= rhs.get_rank()) {
            return true;
        }
    }
    return false;
}

/* Greater than comparision of two cards
* @param lhs Card on left handside of operator
* @param rhs Card on right handside of operator
* @return true if lhs is higher value than rhs. Doesn't consider lead or trump
*/
bool operator>(const Card& lhs, const Card& rhs){
    if (lhs.get_suit() > rhs.get_suit()) {
        return true;
    }
    if (lhs.get_suit() == rhs.get_suit()) {
        if (lhs.get_rank() > rhs.get_rank()) {
            return true;
        }
    }
    return false;
}

/* Greater than or equal to comparision of two cards
* @param lhs Card on left handside of operator
* @param rhs Card on right handside of operator
* @return true if lhs is higher value than rhs or the same card as rhs.
*   Doesn't consider lead or trump
*/
bool operator>=(const Card& lhs, const Card& rhs) {
    if (lhs.get_suit() > rhs.get_suit()) {
        return true;
    }
     if (lhs.get_suit() == rhs.get_suit()) {
        if (lhs.get_rank() >= rhs.get_rank()) {
            return true;
        }
    }
    return false;
}

/* Equality comparision of two cards
* @param lhs Card on left handside of operator
* @param rhs Card on right handside of operator
* @return true if lhs is same card as rhs. Does not consider lead or trump
*/
bool operator==(const Card& lhs, const Card& rhs){
    if (lhs.get_suit() == rhs.get_suit()) {
        if (lhs.get_rank() == rhs.get_rank()) {
            return true;
        }
    }
    return false;
}

/* Inequality comparision of two cards
* @param lhs Card on left handside of operator
* @param rhs Card on right handside of operator
* @return true if lhs is not the same card as rhs. 
*   Does not consider lead or trump
*/
bool operator!=(const Card& lhs, const Card& rhs) {
    return !(lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit());
     
}

/* Determine if a is a lower value than b based on Spade rules
* @param a First card
* @param b Second card
* @param lead the lead suit during a trick
* @return true if a is a lower value than b based on Spade rules.
*   Must take into account the if the cards are Spades, a
*   leading suit, or neither
*/
bool Card_less(const Card& a, const Card& b, Suit lead) {
    if (a.get_suit() == b.get_suit()) {   //both lead or both same
        if(a.get_rank() < b.get_rank()) {
            return true;
        }//all this waste of time enums have numerical values
        return false;
    }
    if (a.get_suit() == lead && b.get_suit() != Suit::SPADES ) { //lead and not spades doesnt need to account for both lead cause already checked
        return false;
    }
    if (a.get_suit() == lead && b.get_suit() == Suit::SPADES) { // if one is spades and other isnt 
        return true;
    }
    if (a.get_suit() == Suit::SPADES && b.get_suit() != Suit::SPADES) { // if one is spades and other isnt 
        return  false;
    }
    if (a.get_suit() == Suit::CLUBS and b.get_suit() != Suit::CLUBS) {
        return true;
    }
    return true;

    }