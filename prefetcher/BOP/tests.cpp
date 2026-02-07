#include <iostream>

#include "full_associative_RR_table.h"
#include "direct_map_RR_table.h"
#include "RR_table.h"

int main(){
    DirectMapRRTable<8> direct_map_RR_table;

    direct_map_RR_table.insert(0xDEADBEEF);
    std::cout << "DEADBEEF\texpect true\t" << std::boolalpha << direct_map_RR_table.exists(0xDEADBEEF) << std::endl ;

    std::cout << "------" << std::endl;

    direct_map_RR_table.insert(0xDEADDEAD);
    std::cout << "DEADDEAD\texpect true\t" << std::boolalpha << direct_map_RR_table.exists(0xDEADDEAD) << std::endl ;
    std::cout << "DEADBEEF\texpect true\t" << std::boolalpha << direct_map_RR_table.exists(0xDEADBEEF) << std::endl ;

    std::cout << "------" << std::endl;

    direct_map_RR_table.insert(0xBEEFBEEF);
    std::cout << "BEEFBEEF\texpect true\t" << std::boolalpha << direct_map_RR_table.exists(0xBEEFBEEF) << std::endl ;
    std::cout << "DEADBEEF\texpect false\t" << std::boolalpha << direct_map_RR_table.exists(0xDEADBEEF) << std::endl ;

    std::cout << "-----------------------------------------------" << std::endl;
    
    FullyAssociativeRRTable<8,2> fully_associative_RR_table;

    fully_associative_RR_table.insert(0xDEADBEEF);
    std::cout << "DEADBEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xDEADBEEF) << std::endl ;

    std::cout << "------" << std::endl;

    fully_associative_RR_table.insert(0xDEADDEAD);
    std::cout << "DEADDEAD\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xDEADDEAD) << std::endl ;
    std::cout << "DEADBEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xDEADBEEF) << std::endl ;

    std::cout << "------" << std::endl;

    fully_associative_RR_table.insert(0xBEEFBEEF);
    std::cout << "BEEFBEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xBEEFBEEF) << std::endl ;
    std::cout << "DEADBEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xDEADBEEF) << std::endl ;

    std::cout << "------" << std::endl;

    fully_associative_RR_table.insert(0x0000BEEF);
    std::cout << "0000BEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0x0000BEEF) << std::endl ;
    std::cout << "BEEFBEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xBEEFBEEF) << std::endl ;
    std::cout << "DEADBEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xDEADBEEF) << std::endl ;

    std::cout << "------" << std::endl;

    fully_associative_RR_table.insert(0x0010BEEF);
    std::cout << "0010BEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0x0010BEEF) << std::endl ;
    std::cout << "0000BEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0x0000BEEF) << std::endl ;
    std::cout << "BEEFBEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xBEEFBEEF) << std::endl ;
    std::cout << "DEADBEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xDEADBEEF) << std::endl ;

    std::cout << "------" << std::endl;

    fully_associative_RR_table.insert(0x0100BEEF);
    std::cout << "0100BEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0x0100BEEF) << std::endl ;
    std::cout << "0010BEEF\texpect false\t" << std::boolalpha << fully_associative_RR_table.exists(0x0010BEEF) << std::endl ;
    std::cout << "0000BEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0x0000BEEF) << std::endl ;
    std::cout << "BEEFBEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xBEEFBEEF) << std::endl ;
    std::cout << "DEADBEEF\texpect true\t" << std::boolalpha << fully_associative_RR_table.exists(0xDEADBEEF) << std::endl ;
}