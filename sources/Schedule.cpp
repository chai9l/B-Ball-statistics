#include "Schedule.hpp"

Schedule::Cycle::Cycle() {

}

void Schedule::Cycle::print() {
    for (Game *g : cycle_games) {
        g->print();
    }
}

void Schedule::print() {
    for (Cycle *c: all_cycles) {
        cout << "--------- START CYCLE -----------" << endl;
        c->print();
        cout << "--------- END CYCLE -----------" << endl;
    }
}

Schedule::~Schedule() {
    for (Cycle *c : all_cycles) {
        for (Game* g : c->get_cycle_games()) {
            delete(g);
        }
    }
    for (Team* t : this->get_league().get_all_teams()) {
        delete(t);
    }
}

vector<Schedule::Cycle*>& Schedule::get_all_cycles() {
    return this->all_cycles;
}

vector<Game*>& Schedule::Cycle::get_cycle_games() {
    return this->cycle_games;
}

void Schedule::Cycle::add_game(Game* game) {
   this->cycle_games.push_back(game); 
}

void Schedule::Cycle::run_games() {
    for (Game* g : this->cycle_games) {
        g->run_game();
    }
}

void Schedule::rotate(vector<Team *> &top, vector<Team *> &bot) {
    std::vector<Team *> top_copy{top.begin(), top.end()};
    std::vector<Team *> bot_copy{bot.begin(), bot.end()};

    top[1] = bot_copy[0];
    for (unsigned int i = 2; i < top.size(); i++) {
        top[i] = top_copy[i-1];
    }

    bot[bot.size()-1] = top_copy[top_copy.size()-1];
    for (unsigned int i = bot.size()-2; i >= 0; i--) {
        if (i == (unsigned int) -1) {
            break;
        }
        bot[i] = bot_copy[i+1];
    }
}

Schedule::Schedule()
{
    this->league = new League();
    vector<Team*> all_teams = this->league->get_all_teams();
    vector<Team*> top;
    vector<Team*> bot;
    for (unsigned int i = 0; i < all_teams.size(); i++) {
        if (i < all_teams.size() / 2) {
            top.push_back(all_teams.at(i));
        }
        else {
            bot.push_back(all_teams.at(i));
        }
    }
    for (unsigned int i = 0; i < all_teams.size()-1; i++) {
        if (i > 0) {
            rotate(top,bot);
        }
        Cycle *c = new Cycle();
        Cycle *c_transpose = new Cycle;
        unsigned int index = 0;
        while(index < top.size()) {
            Team* a = top[index];
            Team* b = bot[index];
            c->add_game(new Game(a,b));
            c_transpose->add_game(new Game(b,a));
            index++;
        }
        this->all_cycles.push_back(c);
        this->all_cycles.push_back(c_transpose);
    }
}

Schedule::Schedule(League *lg)
{
    this->league = lg;
    vector<Team*> all_teams = this->league->get_all_teams();
    vector<Team*> top;
    vector<Team*> bot;
    for (unsigned int i = 0; i < all_teams.size(); i++) {
        if (i < all_teams.size() / 2) {
            top.push_back(all_teams.at(i));
        }
        else {
            bot.push_back(all_teams.at(i));
        }
    }
    for (unsigned int i = 0; i < all_teams.size()-1; i++) {
        if (i > 0) {
            rotate(top,bot);
        }
        Cycle *c = new Cycle();
        Cycle *c_transpose = new Cycle;
        unsigned int index = 0;
        while(index < top.size()) {
            Team* a = top[index];
            Team* b = bot[index];
            c->add_game(new Game(a,b));
            c_transpose->add_game(new Game(b,a));
            index++;
        }
        this->all_cycles.push_back(c);
        this->all_cycles.push_back(c_transpose);
    }
}

League &Schedule::get_league() const
{
    return *this->league;
}

void Schedule::run_cycles()const {
    for (Cycle* c : this->all_cycles) {
        c->run_games();
    }
}