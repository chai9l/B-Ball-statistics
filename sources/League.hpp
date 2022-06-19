#include "Game.hpp"
#include "vector"

using namespace std;

class League {
    private:
        vector<Team *> all_teams;

    public:
    // -------- Constructors --------
        League();
        League(vector<Team *>&);
    // -------- Functions --------
        string get_best_winlose_ratio()const;
        const string get_highest_winstreak()const;
        const string get_highest_losestreak()const;
        vector<Team*> get_teams_ranking()const;
        void print_top_teams(const u_int& amount)const;
        void print_teams_with_pos_points_diff()const;
        void print_teams_with_high_talent()const;
        void print_teams_with_low_talent()const;
        void print_league_total_number_of_points()const;
    // -------- Getters/Setters --------
        vector<Team *>& get_all_teams();  
};