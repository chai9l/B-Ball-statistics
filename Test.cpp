#include "doctest.h"
#include "sources/Schedule.hpp"

TEST_CASE("GOOD INPUT") {
        std::vector<Team *> vec;
    for(uint i = 0; i < 10; i++) {
        vec.push_back(new Team(std::to_string(i), 0.5));
    }

    League *league = new League();
    CHECK_EQ(league->get_all_teams().size(), 20); // all random teams, should be filled with 20 random teams

    league = new League(vec);
    CHECK_EQ(league->get_all_teams().size(), 20); // sent in 10 teams, should be filled with 10 random teams

    for(uint i = 0; i < 10; i++) {
        vec.push_back(new Team(std::to_string(i), 0.5));
    }
    league = new League(vec);
    CHECK_EQ(league->get_all_teams().size(), 20);


    // check that all scores are between 50-110 (55-110 for home teams) 110 and not 100 since the bonus
    Schedule sc{league};
    sc.run_cycles();
    for(uint i = 0; i < sc.get_all_cycles().size(); i++) {
        for(uint j = 0; j < sc.get_all_cycles()[i]->get_cycle_games().size(); j++) {
            CHECK(sc.get_all_cycles()[i]->get_cycle_games()[j]->get_home_score() < 110);
            CHECK(sc.get_all_cycles()[i]->get_cycle_games()[j]->get_home_score() > 54);
            CHECK(sc.get_all_cycles()[i]->get_cycle_games()[j]->get_guest_score() < 110);
            CHECK(sc.get_all_cycles()[i]->get_cycle_games()[j]->get_guest_score() > 49);
        }
    }
}

TEST_CASE("BAD INPUT") {
    Team a{"a", 0.5};
    Team b{"b", 0.75};

    Team* c;
    CHECK_THROWS(c = new Team("Skill", -1)); // skill has to be > 0 and < 1
    CHECK_THROWS(c = new Team("Skill", 2)); // skill has to be > 0 and < 1
    Game* game;
    CHECK_THROWS(game = new Game(&a, &a)); // a team cant play vs itself
    
}

