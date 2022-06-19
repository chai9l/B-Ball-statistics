#include <string>
#include <map>
#include <iostream>

#define LOSE 0
#define WIN 1
#define UNKNOWN 2

using namespace std;

class Team {
    private:
        string name;
        double talent;
        u_int win_streak = 0;
        u_int lose_streak = 0;
        u_int highest_win_streak = 0;
        u_int highest_lose_streak = 0;
        u_int total_number_of_wins = 0;
        u_int total_number_of_lose = 0;
        u_int total_number_of_points_got = 0;
        u_int total_number_of_points_recieved = 0;
    public:    
        map<const string, pair<int, int>> game_log; // (Team Name, <(Home win/lose),(Guest win/lose)>)
// -------- Constructors --------
        Team(const string&, double);
// -------- Functions -------
        int number_of_games_against(Team* ot);
// -------- Getters/Setters --------
        const string& get_name()const;
        const double get_talent()const;
        const u_int& get_win_streak()const;
        const u_int& get_lose_streak()const;
        const u_int& get_highest_win_streak()const;
        const u_int& get_highest_lose_streak()const;
        const u_int& get_total_number_of_wins()const;
        const u_int& get_total_number_of_lose()const;
        const u_int& get_total_number_of_points_got()const;
        const u_int& get_total_number_of_points_recieved()const;
        const map<const string, pair<int,int>>& get_game_log()const;
        void set_name(const string &n);
        void set_talent(const double &t);
        void set_win_streak();
        void set_lose_streak();
        void set_highest_win_streak(const u_int& nw);
        void set_highest_lose_streak(const u_int& nl);
        void set_total_number_of_points_got(const u_int& p);
        void set_total_number_of_points_recieved(const u_int& p);
};