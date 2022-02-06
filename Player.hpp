#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

class Player {

public:
    // Constructeur
    Player(){}
    // Destructeur
    ~Player(){}

    /**
     * @brief Get the n hall object
     * 
     * @return int 
     */
    int get_n_hall() {
        return n_hall;
    }

    /**
     * @brief incrémente le numéro du hall
     * 
     */
    void incr_n_hall() {
        n_hall = (n_hall + 1) % 8;
    }

    /**
     * @brief décremente le numéro du hall
     * 
     */
    void decr_n_hall() {
        n_hall = (n_hall + 7) % 8;
    }


private:
    // le numéro du hall dans lequel le joueur se trouve
    int n_hall = 0;
};

#endif