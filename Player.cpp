/*
Nicholas Morgan
Project 2
*/
#include "Player.h"
#include <iostream>

class Human : public Player
{
    private:
    std::vector<Card> hand;
    std::string name;
    int num_tricks;
    int bid;


    public:

 Human(std::string name) {
        this->name = name;
        num_tricks = 0;
        bid = 0;
        hand.clear();
    }

    const std::string& get_name() const override {
        return name;
    }

    void print_hand() {
        int i = 0;
        for(auto c: hand) {
            i++;
            std::cout << "[" << i << "]" << " " << c << std::endl;
        }

    }
     
    void set_bid() override   {
        char str;
        int bid_;
        
        
        std::cout << "Does Player " <<  name << " want to bid blind nil? [y/n]\n";
        std::cin >> str;
        while (str != 'n' and str != 'y'){
            std::cout << "Please answer using only `y` for yes or `n` for no." << std::endl;
            std::cin >> str;
        }
        

        if (str == 'y') {
            bid = -1;
        }

        else if (str == 'n') {
            std::sort(std::begin(hand), std::end(hand));
            print_hand();
            std::cout << "How much would you like to bid (0 to 13 inclusive)?\n";
            std::cin >> bid_;
            while (bid_ < 0 or bid_ > 13) {
                std::cout << "Please answer with values from 0 to 13 inclusive.\n";
                std::cin >> bid_;
            }
            bid = bid_;
        }
    }

    int get_bid() const override {
        if (bid == -1) {
            return 0;
        }
        return bid;
    }

    bool add_trick() override {
        if (num_tricks < MAX_HAND_SIZE) {
            num_tricks++;
            return true;
        }
        return false;

    }

    int get_trick() const override {
        return num_tricks;

    }

    bool nil_bid() const override{
        if (bid == 0) {
            return true;
        }
        return false;

    }

    bool blind_nil_bid() const override { //blind because hasnt looked at their cards
        if (bid == -1) {
            return true;
        }
        return false;
        
    }

    bool add_card(const Card& c) override{
        if (hand.size() < MAX_HAND_SIZE) {
            hand.push_back(c);
            sort(hand.begin(), hand.end());
            return true;
        }
        return false;
        
    }

//if true print all cards if false print all then spades according to test case
Card lead_card(bool broken_spade) override {//starts at 329 in testfile 
   
    int val = 0;
    std::vector<Card> playable_hand;   

    if(hand.size() == 0) {
        throw std::out_of_range("Player has no more cards to play with.");
    }
    
    if(broken_spade == false){
        for(auto i: hand) {
            if(i.get_suit() != Suit::SPADES) {
                //std::cout << i;
                playable_hand.push_back(i);
        }
    }
    }
    if (playable_hand.size() == 0) {
        for (auto i: hand ) {
            playable_hand.push_back(i);
    }
    }
    
    for(int i = 0; i < playable_hand.size(); i++) {
        std::cout << "[" << i+1 << "] " << playable_hand[i] << std::endl;
    }

    
    std::cout << "Please enter a number between 1 and " << playable_hand.size() << " inclusive:\n";
    std::cin >> val;
    

    while (val < 1 or val > playable_hand.size()) {
        std::cout << "Please enter a number between 1 and " << playable_hand.size() << " inclusive:\n";
        std::cin >> val;
    }
    


    // for(int i = 0; i < hand.size(); i++){
    //     if(hand[i] == playable_hand[val-1]){
    //         hand.erase(hand.begin() + i);
    //         break;
    //     }
    // }

    Card Focus = playable_hand[val-1];
    auto it = std::find(hand.begin(),hand.end(),Focus);
    hand.erase(it);
    Card pick = playable_hand[val-1];

    return pick;
}

Card play_card(Suit led_suit) override  {//lead card for lead player this function for players after 
    int val = 0;
    std::vector<Card> playable_hand;   

    if(hand.size() == 0)
        throw std::out_of_range("Player has no more cards to play with.");


    for(auto i : hand) {
        if(i.get_suit() == led_suit)
            playable_hand.push_back(i);
    }
    
    if(playable_hand.empty()) {
        playable_hand =  hand;
    }
    
    for(int i = 0; i < playable_hand.size(); i++)
        std::cout <<'[' << i+1 << "] " << playable_hand[i] << std::endl;

    do{
        std::cout << "Please enter a number between 1 and " << playable_hand.size() << " inclusive:\n";
        std::cin >> val;
    }while (val < 1 or val > playable_hand.size());
    
    Card Focus = playable_hand[val-1];
    auto it = std::find(hand.begin(),hand.end(),Focus);
    hand.erase(it);
    Card pick = playable_hand[val-1];
    return pick;
}

// this is a comment to test git commits 
// another comment
void reset()override {
        bid = 0;
        num_tricks = 0;
        hand.clear();

    }

static const int MAX_HAND_SIZE = 13;

virtual ~Human() {

}


};


Player* Player_factory(const std::string& name, const std::string& strategy) {
   if (strategy == "Human") {
        Human* x = new Human(name);
        return x;
   }
   return nullptr;

    
}; 

std::ostream& operator<<(std::ostream& os, const Player& p)  {
    os << p.get_name();
    return os;

};

//if bind nil bid then bid = -1 if normal nil bid is 0 
//newest error bc need a way that if u ask for bid it is 0 but a blind nil bid and a blind nil needs to be differnt