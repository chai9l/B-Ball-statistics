#include "League.hpp"

#define MAX_NUM_OF_CYCLES 38
#define MAX_NUM_OF_CYCLE_GAMES 20

class Schedule {
    public:
        Schedule();
        Schedule(League*);
        void old_cycle()const;
        League& get_league()const;
        void rotate(vector<Team *> &top, vector<Team *> &bot);
        void run_cycles()const;
        ~Schedule();
        Schedule &operator=(Schedule &&other) noexcept = default;
        Schedule(const Schedule &other) = default;
        Schedule(Schedule &&other) noexcept = default;
        Schedule &operator=(const Schedule &other) = default;
        class Cycle {
            private:
                vector<Game*> cycle_games;
            public:
                Cycle();
                void add_game(Game* game);
                vector<Game*>& get_cycle_games();
                void run_games();
                void print();
    };
    vector<Cycle*>& get_all_cycles();
    void print();
    private:
        League *league;
        vector<Cycle*> all_cycles;

        
};