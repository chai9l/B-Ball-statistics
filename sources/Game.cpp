#include "Game.hpp"
#include <random>
#include <cmath>
#include <iostream>

#define LOSE 0
#define WIN 1
#define UNKNOWN 2

Game::Game(Team* t1, Team* t2) {
    if (t1 == t2) {
        throw "A team cannot play against itself";
    }
    this->home_team = t1;
    this->guest_team = t2;
}

void Game::run_game() {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> Home{77, 22}; // 55-100
    std::normal_distribution<> Guest{75, 25}; // 50-100
    int home_talent = this->home_team->get_talent() * 10;
    unsigned int h_score = Home(gen) + home_talent;
    int guest_talent = this->guest_team->get_talent() * 10;
    unsigned int g_score = Guest(gen) + guest_talent;
    if (h_score > 100) {
        h_score = 100;
        this->home_score = 100;
    }
    while (h_score < 55) {
        h_score = Home(gen) + home_talent;
        if (h_score > 100) {
            h_score = 100;
            this->home_score = 100;
        }
    }
    if (g_score > 100) {
        g_score = 100;
        this->guest_score = 100;
    }
    while (g_score < 50) {
        g_score = Guest(gen) + guest_talent;
        if (g_score > 100) {
            g_score = 100;
            this->guest_score = 100;
        }
    }
    this->set_home_score(h_score);
    this->set_guest_score(g_score);
    this->home_team->set_total_number_of_points_got(h_score);
    this->guest_team->set_total_number_of_points_got(g_score);
    this->home_team->set_total_number_of_points_recieved(h_score);
    this->guest_team->set_total_number_of_points_recieved(h_score);
    check_winner();
}

void Game::print() {
    cout << "Home " << home_team->get_name() << ", " << "Away: " << guest_team->get_name() << endl;
}

void Game::check_winner() {
    // Home team won
    if (this->home_score > this->guest_score) {
        this->home_team->game_log.at(this->guest_team->get_name()).first = WIN;
        this->home_team->set_win_streak();
        this->guest_team->game_log.at(this->home_team->get_name()).second = LOSE;
        if (this->home_team->get_highest_win_streak() < this->home_team->get_win_streak()) {
            this->home_team->set_highest_win_streak(this->home_team->get_win_streak());
        }
        if (this->guest_team->get_highest_lose_streak() < this->guest_team->get_lose_streak()) {
            this->guest_team->set_highest_lose_streak(this->guest_team->get_lose_streak());
        }
        
    }
    // Guest team won
    else if (this->home_score < this->guest_score) {
        this->home_team->game_log.at(this->guest_team->get_name()).first = LOSE;
        this->home_team->set_lose_streak();
        this->guest_team->game_log.at(this->home_team->get_name()).second = WIN;
        this->guest_team->set_win_streak();
        if (this->home_team->get_highest_lose_streak() < this->home_team->get_lose_streak()) {
            this->home_team->set_highest_lose_streak(this->home_team->get_lose_streak());
        }
        if (this->guest_team->get_highest_win_streak() < this->guest_team->get_win_streak()) {
            this->guest_team->set_highest_win_streak(this->guest_team->get_win_streak());
        }
    }
    // Its a tie - The team with less talent wins
    else if (this->home_score == this->guest_score) {
        if (this->home_team->get_talent() > this->guest_team->get_talent()) {
            this->home_team->game_log.at(this->guest_team->get_name()).first = LOSE;
            this->home_team->set_lose_streak();
            this->guest_team->game_log.at(this->home_team->get_name()).second = WIN;
            this->guest_team->set_win_streak();
            if (this->home_team->get_highest_lose_streak() < this->home_team->get_lose_streak()) {
                this->home_team->set_highest_lose_streak(this->home_team->get_lose_streak());
            }
            if (this->guest_team->get_highest_win_streak() < this->guest_team->get_win_streak()) {
                this->guest_team->set_highest_win_streak(this->guest_team->get_win_streak());
            }
        }
        else if (this->home_team->get_talent() < this->guest_team->get_talent()) {
            this->home_team->game_log.at(this->guest_team->get_name()).first = WIN;
            this->home_team->set_win_streak();
            this->guest_team->game_log.at(this->home_team->get_name()).second = LOSE;
            this->guest_team->set_lose_streak();
            if (this->home_team->get_highest_win_streak() < this->home_team->get_win_streak()) {
                this->home_team->set_highest_win_streak(this->home_team->get_win_streak());
            }
            if (this->guest_team->get_highest_lose_streak() < this->guest_team->get_lose_streak()) {
                this->guest_team->set_highest_lose_streak(this->guest_team->get_lose_streak());
            }      
        }
        // Talent is the same - Guest team wins
        else if (this->home_team->get_talent() == this->guest_team->get_talent()) {
            this->home_team->game_log.at(this->guest_team->get_name()).first = LOSE;
            this->home_team->set_lose_streak();
            this->guest_team->game_log.at(this->home_team->get_name()).second = WIN;
            this->guest_team->set_win_streak();
            if (this->home_team->get_highest_lose_streak() < this->home_team->get_lose_streak()) {
                this->home_team->set_highest_lose_streak(this->home_team->get_lose_streak());
            }
            if (this->guest_team->get_highest_win_streak() < this->guest_team->get_win_streak()) {
                this->guest_team->set_highest_win_streak(this->guest_team->get_win_streak());
            }
        }
    }
}

Team& Game::get_guest_team()const {
    return *this->guest_team;
}
unsigned int Game::get_guest_score()const {
    return this->guest_score;
}
void Game::set_guest_score(unsigned int s) {
    this->guest_score = s;
}

Team& Game::get_home_team()const {
    return *this->home_team;
}
unsigned int Game::get_home_score()const {
    return this->home_score;
}
void Game::set_home_score(unsigned int s) {
    this->home_score = s;
}
void Game::set_home_team(Team* t) {
    this->home_team = t;
}
void Game::set_guest_team(Team* t) {
    this->guest_team = t;
}