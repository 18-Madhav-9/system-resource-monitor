#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

void process(){

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0) ;

    PROCESSENTRY32 current ;
    current.dwSize = sizeof(current) ;

    if (Process32First(snapshot,&current)) {
        while ( Process32Next(snapshot,&current) ) {
            std::wcout << "Process Name : "<<current.szExeFile << "\n" ;
            std::wcout << "Process Id : " << current.th32ProcessID << "\n" ;
        }
    }
    
    CloseHandle(snapshot) ;

}

int main() {

    process();
    return 0 ;
}