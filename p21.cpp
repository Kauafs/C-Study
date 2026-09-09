#include <iostream>

const int key_unlocked{9999};
const int key_locked{40};

void showData(int* visualize, int len);

int cryptData(int *ptr, int length){
    int add{0};
    
    while (add < length){
        *ptr = *ptr ^ key_locked;
        ptr++;
        add++;
    }

    if (add == length){
        return 0;
    }
    
    return 1;
}

int decryptData(int* data, int len){
    int userKey{};
    std::cout << "Enter with Key: ";
    std::cin >> userKey;
    if (userKey == key_unlocked)
    {
        for (int i = 0; i < len; i++)
        {
            *data = *data ^ key_locked;
            data++;
        }

        return 0;
    } 
    return 1;
    
}

void showData(int* visualize, int len){
    for (int i = 0; i < len; i++)
    {
        std::cout << "[" << i << "]" << " [" << *visualize << "]\n";
        visualize++;
    }
}

int main(){
    int dataEmployeer[8]{111,222,333,444,555,666,777,8888};
    int length{sizeof(dataEmployeer) / sizeof(dataEmployeer[0])};
    
    int options{-1};
    while (options != 0)
    {
        std::cout << "[1] Encrypted\n[2] Decrypt\n[0] Sair\nChoice: ";
        std::cin >> options;

        switch (options)
        {
        case 1:{
            int get{cryptData(dataEmployeer, length)};
            if (get == 0)
            {
                std::cout << "[+] ENCRYPTED \n";
                showData(dataEmployeer, length);
            }
            break;
        }
        case 2:{ 
            int get{decryptData(dataEmployeer, length)};
            if (get == 0)
            {
                std::cout << "[-] DECRYPTED \n";
                showData(dataEmployeer, length);
            } else {
                std::cout << "[-] KEY ERROR \n";
            }
        }
        default:
            break;
        }
    }
    return 0;
}