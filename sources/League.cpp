#include "League.hpp"

#define MAX_TEAM_NUMBER 20
#define MAX_NUMBER_OF_GAMES 38
#define LOW_TALENT 0.499999

League::League() {
    string team_name = "a";
    for (int i = 0; i < MAX_TEAM_NUMBER; i++) {
        double r = ((double) rand() / (RAND_MAX));
        Team *temp = new Team(team_name, r);
        this->all_teams.push_back(temp);
        team_name[0]++;
    }
    for (Team* t : this->all_teams) {
        for (Team* ot : this->all_teams) {
            if (t == ot) {
                continue;
            }
            t->game_log.insert({ot->get_name(), {UNKNOWN, UNKNOWN}});
        }
    }
}

League::League(vector<Team*>& t_vec) {
    int tvec_size = t_vec.size();
    if (tvec_size < MAX_TEAM_NUMBER) {
        for (Team* t : t_vec) {
            this->all_teams.push_back(t);
        }
        string team_name = "a";
        for (int i = tvec_size; i < MAX_TEAM_NUMBER; i++) {
            double r = ((double) rand() / (RAND_MAX));
            Team *temp = new Team(team_name, r);
            this->all_teams.push_back(temp);
            team_name[0]++;
        }
    }
    else if(tvec_size > MAX_TEAM_NUMBER) {
        for (Team* t : t_vec) {
            if (this->all_teams.size() == 20) {
                break;
            }
            this->all_teams.push_back(t);
        }
    }
    else {
        for (Team* t : t_vec) {
            this->all_teams.push_back(t);
        }
    }
    for (Team* t : this->all_teams) {
        for (Team* ot : this->all_teams) {
            if (t == ot) {
                continue;
            }
            t->game_log.insert({ot->get_name(), {UNKNOWN, UNKNOWN}});
        }
    }
    
}

vector<Team*>& League::get_all_teams() {
    return this->all_teams;
}

string League::get_best_winlose_ratio()const{
    string ret;
    float b_wl_ratio = 0;
    for (Team* t : this->all_teams) {
        float num_of_wins = t->get_total_number_of_wins();
        float t_wl_ratio = num_of_wins/MAX_NUMBER_OF_GAMES;
        if (b_wl_ratio < t_wl_ratio) {
            b_wl_ratio = t_wl_ratio;
            ret = "Team Name: ";
            ret.append(t->get_name()).append(" ,Has the best W/L Ratio of: ").append(to_string(b_wl_ratio));
        }
    }
    return ret;
}

const string League::get_highest_winstreak()const{
    string ret;
    unsigned int h_ws = 0;
    for (Team* t : this->all_teams) {
        unsigned int t_ws = t->get_highest_win_streak();
        if (t_ws > h_ws) {
            h_ws = t_ws;
            ret = "Team Name: ";
            ret.append(t->get_name()).append(" ,Has the highest winstreak of: ").append(to_string(h_ws));
        }
    }
    return ret;
}

const string League::get_highest_losestreak()const{
    string ret;
    u_int h_ls = 0;
    for (Team* t : this->all_teams) {
        u_int t_ls = t->get_highest_lose_streak();
        if(t_ls > h_ls) {
            h_ls = t_ls;
            ret = "Team Name: ";
            ret.append(t->get_name()).append(" ,Has the highest losestreak of: ").append(to_string(h_ls));
        }
    }
    return ret;
}

vector<Team*> League::get_teams_ranking()const {
    vector<Team*> sorted;
    vector<Team*> all_teams = this->all_teams;
    int size = all_teams.size();
    Team* curr_best_team = nullptr;
    u_int index = 0;
    while (sorted.size() < size) {
        curr_best_team = nullptr;
        for (unsigned int i = 0; i < all_teams.size(); i++) {
            if (curr_best_team == nullptr || all_teams.at(i)->get_total_number_of_wins() > curr_best_team->get_total_number_of_wins()) {
                curr_best_team = all_teams.at(i);
                index = i;
            }
            if (all_teams.at(i)->get_total_number_of_wins() == curr_best_team->get_total_number_of_wins()) {
                u_int t_point_diff = all_teams.at(i)->get_total_number_of_points_got() - all_teams.at(i)->get_total_number_of_points_recieved();
                u_int cbt_point_diff = curr_best_team->get_total_number_of_points_got() - curr_best_team->get_total_number_of_points_recieved();
                if (t_point_diff > cbt_point_diff) {
                    curr_best_team = all_teams.at(i);
                    index = i;
                }
            }
        }
        sorted.emplace_back(curr_best_team);
        all_teams.erase(all_teams.begin() + index);
    }
    return sorted;
}

void League::print_top_teams(const u_int& amount)const {
    vector<Team*> vec = this->get_teams_ranking();
    for(unsigned int i = 0; i < amount; i++) {
        string ret = "Team in the ";
        ret.append(to_string(i+1)).append(" Place is: ").append(vec.at(i)->get_name()).append(" with: ").append(to_string(vec.at(i)->get_total_number_of_wins())).append(" wins.");;     
        cout << ret << endl;
    }
}

void League::print_teams_with_pos_points_diff()const {
    for (Team* t : this->all_teams) {
        unsigned int p_got = t->get_total_number_of_points_got();
        unsigned int p_recieved = t->get_total_number_of_points_recieved();
        unsigned int diff = p_got - p_recieved;
        if (diff > 0) {
            string ret = "Team Name: ";
            ret.append(t->get_name()).append(" has more points got than recieved with:")
            .append(to_string(p_got)).append(" points got and ").append(to_string(p_recieved))
            .append(" points recieved.");
            cout << ret << endl;
        }
    }
}
void League::print_teams_with_high_talent()const{
    for (Team* t : this->all_teams) {
        double t_talent = t->get_talent();
        if (t_talent > LOW_TALENT) {
            string ret = "Team Name: ";
            ret.append(t->get_name()).append(" has high talent of: ")
            .append(to_string(t_talent));
            cout << ret << endl;
        }
    }
}
void League::print_teams_with_low_talent()const{
        for (Team* t : this->all_teams) {
        double t_talent = t->get_talent();
        if (t_talent < LOW_TALENT) {
            string ret = "Team Name: ";
            ret.append(t->get_name()).append(" has low talent of: ")
            .append(to_string(t_talent));
            cout << ret << endl;
        }
    }
}

void League::print_league_total_number_of_points()const{
    int total = 0;
    for (Team* t : this->all_teams) {
        total += t->get_total_number_of_points_got();
    }
    string ret = "The total number of points in the league is: ";
    ret.append(to_string(total));
    cout << ret << endl;
}