#include <windows.h>
#include <iostream>

// converting bytes to GB
#define GB (1024.0*1024*1024)

void memory() {

    MEMORYSTATUSEX status ;
    status.dwLength = sizeof(status) ;

    if ( GlobalMemoryStatusEx(&status) ){ 
        std::cout << "Current Usage : " <<status.dwMemoryLoad << "%\n" ;
        std::cout << "Available Ram : " << status.ullAvailPhys/GB <<" GB\n" ;
        std::cout << "Total Ram : " <<status.ullTotalPhys/GB <<" GB\n" ;
        std::cout << "--------------------------\n" ;
    }


}