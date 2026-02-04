#pragma once
#include <stdint.h>

template <uint16_t table_size>
class DirectMapRRTable {
    public:
        DirectMapRRTable();
        void insert(uint64_t address);
        bool exists(uint64_t address);
    private:
        uint8_t hash_address(uint64_t address);
        uint64_t m_RR_table[table_size] = {};
};

template <uint16_t table_size>
DirectMapRRTable<table_size>::DirectMapRRTable(){}

template <uint16_t table_size>
void DirectMapRRTable<table_size>::insert(uint64_t address){
    uint8_t address_hash = hash_address(address);

    m_RR_table[address_hash] = address;
}

template <uint16_t table_size>
bool DirectMapRRTable<table_size>::exists(uint64_t address){
    uint8_t address_hash = hash_address(address);

    return m_RR_table[address_hash] == address;
}