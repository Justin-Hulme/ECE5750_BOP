#pragma once

#include <stdint.h>
#include "RR_table.h"
#include <iostream>
#include <iomanip>

template <uint16_t table_addr_width, uint8_t associativity_width>
class FullyAssociativeRRTable : public RRTable {
    static_assert(table_addr_width > 0, "table_addr_width must be greater than 0");
    static_assert(table_addr_width <= 16, "table_addr_width must be less or equal to 16");
    static_assert(associativity_width > 0, "associativity_width must be greater than 0");
    static_assert(associativity_width <= 8, "associativity_width must be less than or equal to 8");

    public:
        FullyAssociativeRRTable();
        void insert(uint64_t address) override;
        bool exists(uint64_t address) override;
        uint16_t get_m_table_size();
        uint16_t get_m_associativity();
        void print_table_entry(uint16_t index);
        void print_LRU_entry(uint16_t index);
    private:
        static constexpr uint16_t m_table_size = (1U << table_addr_width);
        static constexpr uint16_t m_associativity = (1U << associativity_width);
        uint16_t hash_address(uint64_t address);
        uint64_t m_RR_table[m_table_size][m_associativity] = {};
        uint16_t m_RR_table_LRU[m_table_size][m_associativity] = {};
};

template <uint16_t table_addr_width, uint8_t associativity_width>
FullyAssociativeRRTable<table_addr_width, associativity_width>::FullyAssociativeRRTable(){}

template <uint16_t table_addr_width, uint8_t associativity_width>
void FullyAssociativeRRTable<table_addr_width, associativity_width>::insert(uint64_t address){
    uint8_t address_hash = hash_address(address);

    if (!exists(address)){
        uint8_t max_LRU_val_index = 0;

        for (uint8_t i = 0; i < m_associativity; i++){
            if (m_RR_table_LRU[address_hash][i] > m_RR_table_LRU[address_hash][max_LRU_val_index]){
                max_LRU_val_index = i;
            }
        }

        m_RR_table[address_hash][max_LRU_val_index] = address;
        m_RR_table_LRU[address_hash][max_LRU_val_index] = 0;
    }
}

template <uint16_t table_addr_width, uint8_t associativity_width>
bool FullyAssociativeRRTable<table_addr_width, associativity_width>::exists(uint64_t address){
    uint8_t address_hash = hash_address(address);

    bool exists_flag = false;

    for (uint8_t i = 0; i < m_associativity; i++){
        if (m_RR_table[address_hash][i] == address){
            m_RR_table_LRU[address_hash][i] = 0;
            
            exists_flag = true;
        }

        if (m_RR_table_LRU[address_hash][i] < 0xFFFF){
            m_RR_table_LRU[address_hash][i] ++;
        }
    }

    return exists_flag;
}

template <uint16_t table_addr_width, uint8_t associativity_width>
uint16_t FullyAssociativeRRTable<table_addr_width, associativity_width>::get_m_table_size(){
    return m_table_size;
}

template <uint16_t table_addr_width, uint8_t associativity_width>
uint16_t FullyAssociativeRRTable<table_addr_width, associativity_width>::get_m_associativity(){
    return m_associativity;
}

template <uint16_t table_addr_width, uint8_t associativity_width>
void FullyAssociativeRRTable<table_addr_width, associativity_width>::print_table_entry(uint16_t index){
    std::cout << "Set " << index << ":\n";

    for (size_t way = 0; way < m_associativity; ++way) {
        std::cout << "  Way " << way
                    << " | Addr: 0x"
                    << std::hex << std::setw(16) << std::setfill('0')
                    << m_RR_table[index][way]
                    << std::dec << "\n";
    }
}

template <uint16_t table_addr_width, uint8_t associativity_width>
void FullyAssociativeRRTable<table_addr_width, associativity_width>::print_LRU_entry(uint16_t index){
    std::cout << "Set " << index << ":\n";

    for (size_t way = 0; way < m_associativity; ++way) {
        std::cout << "  Way " << way
                    << " | LRU: "
                    << m_RR_table_LRU[index][way]
                    << "\n";
    }
}

template <uint16_t table_addr_width, uint8_t associativity_width>
uint16_t FullyAssociativeRRTable<table_addr_width, associativity_width>::hash_address(uint64_t address){
    uint16_t lower = address & ((1U << table_addr_width) - 1);
    uint16_t next_lower = (address >> table_addr_width) & ((1U << table_addr_width) - 1);

    return lower ^ next_lower;
}