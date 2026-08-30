#include <iostream>

const int key{42};


void printRAM(int* ptr, int length){
    std::cout << "Execute Function printRAM {}\n";
    int count{0};
    while (count < length)
    {
        std::cout << "P:[" << count << "]" << "A:[" << ptr << "]" << "V:[" << *ptr << "]\n";
        count++;
        ptr++;
    }
    
}

void injectDATA(int* ptr, int length, int* canary){
    std::cout << "Run Funtion injectDATA {}\n";
    std::cout << "Enter position: ";
    int userPosition{};
    std::cin >> userPosition;
    std::cout << "Enter value: ";
    int userValue{};
    std::cin >> userValue;

    int sub{length - 1};
    std::cout << "LEN: " << sub << '\n';
    if (userPosition >= sub || userPosition < 0)
    {
        std::cout << "[WARN] BUFFER OVERFLOW\n";
    } else {
        int* change{ptr + userPosition};
        std::cout << "[BEFORE] P:[" << userPosition << "]" << " V:[" << *change << "]\n";
        *change = userValue ^ key;
        std::cout << "[AFTER]  P:[" << userPosition << "]" << " V:[" << *change << "]\n";
    } 

    int *checkCanary{&canary[sub]};
    std::cout << "CANARY: " << *checkCanary << '\n'; 
    if (*checkCanary != 999)
    {
        std::cout << "[DANGER] O CANARY CHANGED !\n";
    }
}

void scanMemory(int* ptr, int len){
    std::cout << "RUN funciton scanMemory {}\n";
    std::cout << "Enter value to found: ";
    int valueTarget{};
    std::cin >> valueTarget;

    int targetReverse{valueTarget ^ key};
    for (int i = 0; i < len; i++)
    {
        if (*ptr == targetReverse)
        {
           std::cout << "[FOUND]: [" << *ptr << "] XOR [" << valueTarget << "] " << " in position: [" << i << "]\n"; 
            break;
        }
        ptr++;
    }
    
}

int main(){
    int dataRam[]{10,20,30,40,50,999};
    int len{sizeof(dataRam) / sizeof(dataRam[0])};
    int choice{-1};
    while (choice != 0)
    {
        std::cout << "[1] Inject Encrypted Data (XOR)\n" << "[2] Scan Memory (Search)\n" << "[3] Print RAM Status\nChoice a option: ";
        std::cin >> choice;

        if (choice == 1)
        {
            injectDATA(dataRam,len,dataRam);
        }
        if (choice == 2){

            scanMemory(dataRam, len);
        }
        if (choice == 3)
        {
            printRAM(dataRam,len);
        }
        
        
    }
    
    
    return 0;
}