#include "Team.hpp"

Team::Team(const string &n, double t) {
    if (t < 0 || t > 1) {
        throw "Team talent skill has to be between 0 and 1";
    } 
    this->name = n;
    this->talent = t;
}

int Team::number_of_games_against(Team* ot) {
    if (this == ot) {
        throw "Team cant play against itself";
    }
    const string& ot_name = ot->get_name();
    int ret = 0;
    if (this->game_log.at(ot_name).first != UNKNOWN) {
        ret += 1;
    }
    if (this->game_log.at(ot_name).second != UNKNOWN) {
        ret += 1;
    }
    return ret;
}
const string& Team::get_name()const {
    return this->name;
}
const double Team::get_talent()const{
    return this->talent;
}
const u_int& Team::get_win_streak()const {
    return this->win_streak;
}
const u_int& Team::get_lose_streak()const {
    return this->lose_streak;
}
const map<const string, pair<int,int>>& Team::get_game_log()const {
    return this->game_log;
}
const u_int& Team::get_highest_win_streak()const {
    return this->highest_win_streak;
}
const u_int& Team::get_highest_lose_streak()const {
    return this->highest_lose_streak;
}
const u_int& Team::get_total_number_of_wins()const{
    return this->total_number_of_wins;
}
const u_int& Team::get_total_number_of_lose()const{
    return this->total_number_of_lose;
}
const u_int& Team::get_total_number_of_points_got()const{
    return this->total_number_of_points_got;
}
const u_int& Team::get_total_number_of_points_recieved()const{
    return this->total_number_of_points_recieved;
}
void Team::set_name(const string &n){
    this->name = n;
}
void Team::set_talent(const double &t){
    this->talent = t;
}
void Team::set_win_streak() {
    this->win_streak += 1;
    this->lose_streak = 0;
    this->total_number_of_wins += 1;
}
void Team::set_lose_streak() {
    this->lose_streak += 1;
    this->win_streak = 0;
    this->total_number_of_lose += 1;
}
void Team::set_highest_win_streak(const u_int& nw) {
    this->highest_win_streak = nw;
}
void Team::set_highest_lose_streak(const u_int& nl) {
    this->highest_lose_streak = nl;
}
void Team::set_total_number_of_points_got(const u_int& p){
    this->total_number_of_points_got += p;
}
void Team::set_total_number_of_points_recieved(const u_int& p){
    this->total_number_of_points_recieved += p;
}
