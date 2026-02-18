#ifndef OFFSET_SCOREBOARD_H
#define OFFSET_SCOREBOARD_H

#include <stdint.h>

class OffsetScoreboard{
    public:
        OffsetScoreboard(uint16_t scoremax, uint16_t badscore);
        void reset_scores();
        void inc_score(uint64_t d);
        uint16_t get_best_offset(uint64_t &best_offset);
        bool any_at_max();

        inline static const uint64_t POTENTIAL_OFFSETS[] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 
                                                15, 16, 18, 20, 24, 25, 27, 3, 
                                                32, 36, 40, 45, 48, 50, 54, 60/*, 
                                                64, 72, 75, 80, 81, 90, 96, 100, 
                                                108, 120, 125*/};

        static constexpr uint16_t NUM_OFFSETS = sizeof(POTENTIAL_OFFSETS) / sizeof(POTENTIAL_OFFSETS[0]);

    private:
        uint64_t m_scores[NUM_OFFSETS];
        
        uint16_t M_SCOREMAX;
        uint16_t M_BADSCORE;
};

OffsetScoreboard::OffsetScoreboard(uint16_t scoremax, uint16_t badscore) 
{
    M_SCOREMAX = scoremax;
    M_BADSCORE = badscore;
}

void OffsetScoreboard::reset_scores() 
{
    for (uint64_t &score : m_scores) 
    {
        score = 0;
    }
}

void OffsetScoreboard::inc_score(uint64_t offset_idx) 
/**
 * increment offset score
 * return true if the score  reaches scoremax else return false
 */
{
    m_scores[offset_idx]++;
}

uint16_t OffsetScoreboard::get_best_offset(uint64_t &best_offset)
/**
 * Calculates the best offset which is passed by reference as an argument
 * Returns true if the best score is less than or equal to BADSCORE else false
 */
{
    best_offset = POTENTIAL_OFFSETS[0];
    uint16_t best_score = m_scores[0];

    cout << "best_score =[";

    for (int idx = 0; idx < NUM_OFFSETS; idx++)
    {
        cout << m_scores[idx] << ", ";
        
        if (m_scores[idx] > best_score) 
        {
            best_score = m_scores[idx];
            best_offset = POTENTIAL_OFFSETS[idx];
        }
    }

    cout << "]" << endl;

    return best_score;
}

bool OffsetScoreboard::any_at_max(){
    for (int i = 0; i < NUM_OFFSETS; i++){
        if (m_scores[i] >= SCOREMAX){
            return true;
        }
    }

    return false;
}

#endif