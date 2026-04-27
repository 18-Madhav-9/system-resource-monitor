#include <windows.h>
#include <iostream>

// converting bytes to GB
#define GB (1024.0*1024*1024)

void getMemoryUsage(double &ramusage,double &availram,double &totalram) {

    MEMORYSTATUSEX status ;
    status.dwLength = sizeof(status) ;

    if ( GlobalMemoryStatusEx(&status) ){ 
        ramusage = status.dwMemoryLoad ;
        availram = status.ullAvailPhys/GB ;
        totalram = status.ullTotalPhys/GB; 
        //std::cout << "Current Usage : " <<status.dwMemoryLoad << "%\n" ;
        //std::cout << "Available Ram : " << status.ullAvailPhys/GB <<" GB\n" ;
        //std::cout << "Total Ram : " <<status.ullTotalPhys/GB <<" GB\n" ;
        //std::cout << "--------------------------\n" ;
    }


}