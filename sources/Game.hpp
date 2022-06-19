#include "Team.hpp"

using namespace std;

class Game {
    private:
        Team *home_team;
        Team *guest_team;
        unsigned int home_score = 0;
        unsigned int guest_score = 0;

    public:
    // -------- Constructors --------
        Game(Team*, Team*);
    // -------- Functions --------
        void run_game();
        void check_winner();
    // -------- Getters/Setters --------
        Team& get_home_team()const;
        Team& get_guest_team()const;
        unsigned int get_home_score()const;
        unsigned int get_guest_score()const;
        void set_home_team(Team* t);
        void set_guest_team(Team* t);
        void set_home_score(unsigned int);
        void set_guest_score(unsigned int);
        void print();
};