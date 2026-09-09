#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdlib>

DWORD targetProcess(const char* name){
    HANDLE hSnap{CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0)};
    if (hSnap == INVALID_HANDLE_VALUE)
    {
        return EXIT_FAILURE;
    }
    
    PROCESSENTRY32 pe32{};
    pe32.dwSize = sizeof(PROCESSENTRY32);
    BOOL nav{Process32First(hSnap, &pe32)};

    while (nav != 0)
    {
        nav = Process32Next(hSnap, &pe32);
        if (_stricmp(pe32.szExeFile, name) == 0)
        {
            CloseHandle(hSnap);
            return pe32.th32ProcessID;
        }    
    }
    CloseHandle(hSnap);
    return EXIT_FAILURE;
}

HANDLE getKeyCurrent(DWORD pid){
    HANDLE keyCurrentProcess = OpenProcess(
        PROCESS_ALL_ACCESS, 
        FALSE, 
        pid
    );

    if (keyCurrentProcess == NULL){return NULL;}
    
    return keyCurrentProcess;   
}


void searchBytes(HANDLE key, uintptr_t addressBase, DWORD lenModule, DWORD pid){
  
    char* buffer = new char[lenModule];
    ReadProcessMemory(
        key,
        (LPCVOID)addressBase,
        buffer,
        lenModule,
        NULL
    );


    for (DWORD i = 0; i < lenModule; i++)
    {
        // Tabela ASCII
        if ((unsigned char)buffer[i] == 0x73 &&
            (unsigned char)buffer[i+1] == 0x65 &&
            (unsigned char)buffer[i+2] == 0x6E &&
            (unsigned char)buffer[i+3] == 0x68 &&
            (unsigned char)buffer[i+4] == 0x61)
        {
            std::cout << "[+] ENCONTRADO: [" << 
            buffer[i] << 
            buffer[i+1] << 
            buffer[i+2] << 
            buffer[i+3] << 
            buffer[i+4] << 
            "]\n";
        }
        
    }
}

void searchPatterns(DWORD pid){
    HANDLE mSnap{(CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid))};
    MODULEENTRY32 me32{};
    me32.dwSize = sizeof(MODULEENTRY32);

    uintptr_t addressBase{};
    DWORD sizeModule{};

    if (Module32First(mSnap,&me32) != 0)
    {
        addressBase = (uintptr_t)me32.modBaseAddr;
        sizeModule = me32.modBaseSize;
        std::cout << "[+] BaseAddress: [" << (void*)addressBase << "]\n";
    }

    HANDLE keyCurrent{getKeyCurrent(pid)};
    std::cout << "[+] Chave Fornecida: [" << keyCurrent << "]\n";
    searchBytes(keyCurrent, addressBase, sizeModule, pid);
    CloseHandle(keyCurrent);
    
}


int main(){
    const char* nameProcess = "senha.exe";
    DWORD getReturn{targetProcess(nameProcess)};
    if (getReturn == EXIT_FAILURE)
    {
        return 0;
    } 

    std::cout << "[+] Processo Rodando | PID [" << getReturn << "]\n";
    
    searchPatterns(getReturn);

    return 0;
}