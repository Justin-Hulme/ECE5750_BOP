#ifndef OFFSET_SCOREBOARD_H
#define OFFSET_SCOREBOARD_H

#include <stdint.h>
#include <map>

#define SCOREMAX 31
#define ROUNDMAX 100
#define BADSCORE 1

uint64_t POTENTIAL_OFFSETS[] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 
                                    15, 16, 18, 20, 24, 25, 27, 3, 
                                    32, 36, 40, 45, 48, 50, 54, 60, 
                                    64, 72, 75, 80, 81, 90, 96, 100, 
                                    108, 120, 125};

uint64_t NUM_OFFSETS = sizeof(POTENTIAL_OFFSETS) / sizeof(POTENTIAL_OFFSETS[0]);

class OffsetScoreboard{
    public:
        OffsetScoreboard();
        bool inc_score(uint64_t d);
        void reset_scores();
        uint64_t get_best_offset();

    private:
        std::map<uint64_t, uint16_t> m_scores;
};

OffsetScoreboard::OffsetScoreboard() 
{
    for (uint64_t offset : POTENTIAL_OFFSETS) 
    {
        m_scores[offset] = 0;
    }
}

bool OffsetScoreboard::inc_score(uint64_t offset) 
/**
 * increment offset score
 * return true if the score  reaches scoremax else return false
 */
{
    m_scores[offset]++;

    return (m_scores[offset] == SCOREMAX);
}

void OffsetScoreboard::reset_scores() 
/**
 * Reset all scores to 0
 */
{
    for (uint64_t offset : POTENTIAL_OFFSETS) 
    {
        m_scores[offset] = 0;
    }
}

uint64_t OffsetScoreboard::get_best_offset()
/**
 * Returns the score with the highest score;
 */
{
    uint64_t best_offset = 1;
    uint16_t best_score = 0;

    for(const auto& [offset, score] : m_scores)
    {
        if (score > best_score)
        {
            best_offset = offset;
            best_score = score;
        }
    }

    return best_offset;
}

#endif