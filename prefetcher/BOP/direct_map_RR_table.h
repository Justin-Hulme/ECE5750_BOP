#pragma once

#include <stdint.h>
#include "RR_table.h"

template <uint8_t table_addr_width>
class DirectMapRRTable : public RRTable {
    static_assert(table_addr_width > 0, "table_addr_width must be greater than 0");
    static_assert(table_addr_width <= 16, "table_addr_width must be less or equal to 16");
    
    public:
        DirectMapRRTable();
        void insert(uint64_t address) override;
        bool exists(uint64_t address) override;
    private:
        static constexpr uint16_t m_table_size = (1U << table_addr_width);
        uint16_t hash_address(uint64_t address);
        uint64_t m_RR_table[m_table_size] = {};
};

template <uint8_t table_addr_width>
DirectMapRRTable<table_addr_width>::DirectMapRRTable(){}

template <uint8_t table_addr_width>
void DirectMapRRTable<table_addr_width>::insert(uint64_t address){
    uint16_t address_hash = hash_address(address);

    // cout << "direct map insert " << address << endl;

    m_RR_table[address_hash] = address;
}

template <uint8_t table_addr_width>
bool DirectMapRRTable<table_addr_width>::exists(uint64_t address){
    uint16_t address_hash = hash_address(address);

    cout << address << "does " << (m_RR_table[address_hash] == address ? "in fact " : "not ") << "exist" << endl;

    return m_RR_table[address_hash] == address;
}

template <uint8_t table_addr_width>
uint16_t DirectMapRRTable<table_addr_width>::hash_address(uint64_t address){
    uint16_t lower = address & ((1U << table_addr_width) - 1);
    uint16_t next_lower = (address >> table_addr_width) & ((1U << table_addr_width) - 1);

    return lower ^ next_lower;
}