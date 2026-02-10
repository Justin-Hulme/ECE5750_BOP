#ifndef OFFSET_SCOREBOARD_H
#define OFFSET_SCOREBOARD_H

#include <stdint.h>
#include <map>

#define SCOREMAX 31
#define ROUNDMAX 100
#define BADSCORE 1

class OffsetScoreboard{
    public:
        OffsetScoreboard();
        void reset_scores();
        bool inc_score(uint64_t d);
        bool get_best_offset(uint64_t &best_offset);

        static const uint64_t POTENTIAL_OFFSETS[] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 
                                                15, 16, 18, 20, 24, 25, 27, 3, 
                                                32, 36, 40, 45, 48, 50, 54, 60, 
                                                64, 72, 75, 80, 81, 90, 96, 100, 
                                                108, 120, 125};

        static constexpr uint16_t NUM_OFFSETS = sizeof(potential_offsets) / sizeof(potential_offsets[0]);

    private:
        uint64_t m_scores[NUM_OFFSETS];
};

OffsetScoreboard::OffsetScoreboard() 
{
    for (uint64_t &score : m_scores) 
    {
        score = 0;
    }
}

void OffsetScoreboard::reset_scores() 
{
    for (uint64_t &score : m_scores) 
    {
        score = 0;
    }
}

bool OffsetScoreboard::inc_score(uint64_t offset_idx) 
/**
 * increment offset score
 * return true if the score  reaches scoremax else return false
 */
{
    m_scores[offset_idx]++;

    return (m_scores[offset_idx] >= SCOREMAX);
}

bool OffsetScoreboard::get_best_offset(uint64_t &best_offset)
/**
 * Calculates the best offset which is passed by reference as an argument
 * Returns true if the best score is less than or equal to BADSCORE else false
 */
{
    best_offset = 1;
    uint16_t best_score = 0;

    for (int ix = 0; idx < NUM_OFFSETS; idx++)
    {
        if (scores[idx] > best_score) 
        {
            best_score = scores[idx];
            best_offset = potential_offsets[idx];
        }
    }

    return (best_score <= BADSCORE);
}

#endif