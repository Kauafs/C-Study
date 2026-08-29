#include <iostream>

// Varredura de memória (MemoryScan) busca de Padrões.
// Usando apenas o tipo in

/*
    Tentando simular ferramentas de segurança ou trapaças de jogos que vasculham a memória atrás de um valor específico
*/

int userInput()
{
    std::cout << "Informe a senha: ";
    int input{};
    std::cin >> input;

    return input;

}

int storagePassword(){
    int storagePassword[4]{};
    int senhaSucess{8999};
    int anyPass{4444};

    // Armazenando senhas (diversificando as formas)
    storagePassword[0] = 8888;
    storagePassword[1] = anyPass;
    storagePassword[2] = 7777;
    storagePassword[3] = senhaSucess;

    int* ptrAddr{storagePassword};
    int searchUser{userInput()};
    int cont{0};
    while (cont < 4)
    {
        if (*ptrAddr == searchUser)
        {
            std::cout << "Is equal: " << *ptrAddr << " Address Memory: "<< ptrAddr << " : " << storagePassword[cont] << '\n';
            return 9999;
        }
        std::cout << "Not's equal. Try: "<< cont  << '\n';
        cont++;
        ptrAddr++;
    }

    return 0000;
}

void panelInfors(int opc){
    int get{storagePassword()};
    if (opc == 1)
    {
        if (get == 9999){
            std::cout << "Password Found\n";   
        } else {
            std::cout << "Password not Found\n";
        }
    }
    
}

int main(){
    std::cout << "[1] - SearchPassword\nChoise a option: ";
    int options{};
    std::cin >> options;
    if (options < 2 && options > 0){
        panelInfors(options);
    } else {
        std::cout << "[-] Nao existe essa opcao\n";
    }
    return 0;
}