#pragma once

#include <stdint.h>

class RRTable {
    public:
        virtual void insert(uint64_t address) = 0;
        virtual bool exists(uint64_t address) = 0;
};