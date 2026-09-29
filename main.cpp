#include <iostream>
#include <string>
#include <limits> // Necessario para limpar o buffer do cin com numeric_limits

using namespace std;

int main() {
    // =========================================================================
    // 1. DECLARAÇÃO DE VARIÁVEIS OBRIGATÓRIAS (Etapa 1 + Desafio de 5 contas)
    // =========================================================================
    
    const int TAMANHO_MAXIMO = 5; // Capacidade para até 5 contas

    // Alterado numeroConta para 'long long' para suportar mais de 9/10 digitos
    long long numeroConta[TAMANHO_MAXIMO]; // Numero da conta (long long)
    string nomeCliente[TAMANHO_MAXIMO];   // Nome do titular (string)
    string cpf[TAMANHO_MAXIMO];           // CPF do titular (string)
    int tipoConta[TAMANHO_MAXIMO];        // Tipo da conta: 1 = Corrente; 2 = Poupanca (int)
    double saldo[TAMANHO_MAXIMO];         // Saldo atual (double)
    bool contaAtiva[TAMANHO_MAXIMO];      // Indica se a conta esta ativa (bool)

    // Variável extra
    string emailCliente[TAMANHO_MAXIMO];  // E-mail do titular (string)

    // Variáveis de controle do sistema
    int totalContas = 0;                  // Contador de contas cadastradas
    int opcao = 0;                        // Armazena a opcao escolhida no menu

    // Inicializando todas as variáveis com valores padrão
    for (int i = 0; i < TAMANHO_MAXIMO; i++) {
        numeroConta[i] = 0;
        nomeCliente[i] = "";
        cpf[i] = "";
        tipoConta[i] = 0;
        saldo[i] = 0.0;
        contaAtiva[i] = false;
        emailCliente[i] = "";
    }

    // =========================================================================
    // 2. MENU E EXECUÇÃO DO SISTEMA (do-while + switch)
    // =========================================================================
    do {
        cout << "\n*****************************\n";
        cout << "****     RibeiroBANK     ****\n";
        cout << "*****************************\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Consultar conta\n";
        cout << "3 - Verificar saldo\n";
        cout << "4 - Alterar tipo da conta\n";
        cout << "5 - Ativar/Desativar conta\n";
        cout << "6 - Sair\n";
        cout << "Escolha uma opcao: ";
        
        if (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nOpcao invalida. Digite um numero de 1 a 6.\n";
            continue;
        }

        switch (opcao) {
            case 1: {
                if (totalContas >= TAMANHO_MAXIMO) {
                    cout << "\nErro: Limite maximo de " << TAMANHO_MAXIMO << " contas atingido!\n";
                    break;
                }

                cout << "\n--- Cadastro de Conta (" << (totalContas + 1) << " de " << TAMANHO_MAXIMO << ") ---\n";

                // Validação: Numero da conta maior que zero (suporta numeros grandes)
                long long numTemp;
                do {
                    cout << "Digite o numero da conta (maior que zero): ";
                    cin >> numTemp;

                    if (cin.fail() || numTemp <= 0) {
                        cin.clear(); // Limpa o estado de erro do cin
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta entrada invalida
                        cout << "Erro: O numero da conta deve ser um valor numerico valido e maior que zero!\n";
                        numTemp = 0;
                    }
                } while (numTemp <= 0);
                
                numeroConta[totalContas] = numTemp;

                // Limpa o buffer do teclado antes de usar getline
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Nome do titular: ";
                getline(cin, nomeCliente[totalContas]);

                cout << "CPF: ";
                getline(cin, cpf[totalContas]);

                cout << "E-mail (Variavel Extra): ";
                getline(cin, emailCliente[totalContas]);

                // Validação: Tipo de conta deve ser 1 ou 2
                int tipoTemp;
                do {
                    cout << "Tipo da conta (1 = Corrente, 2 = Poupanca): ";
                    cin >> tipoTemp;

                    if (cin.fail() || (tipoTemp != 1 && tipoTemp != 2)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Erro: Tipo invalido! Digite 1 para Corrente ou 2 para Poupanca.\n";
                        tipoTemp = 0;
                    }
                } while (tipoTemp != 1 && tipoTemp != 2);
                
                tipoConta[totalContas] = tipoTemp;

                // Validação: Saldo inicial não pode ser negativo
                double saldoTemp;
                bool saldoValido = false;
                do {
                    cout << "Saldo inicial (R$): ";
                    cin >> saldoTemp;

                    if (cin.fail() || saldoTemp < 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Erro: O saldo inicial deve ser um valor valido e nao negativo!\n";
                    } else {
                        saldoValido = true;
                    }
                } while (!saldoValido);
                
                saldo[totalContas] = saldoTemp;

                contaAtiva[totalContas] = true;
                totalContas++;

                cout << "\nConta cadastrada com sucesso no RibeiroBANK!\n";
                break;
            }

            case 2: {
                if (totalContas == 0) {
                    cout << "\nNenhuma conta cadastrada ainda.\n";
                } else {
                    cout << "\n--- Relatorio de Contas Cadastradas ---\n";
                    for (int i = 0; i < totalContas; i++) {
                        cout << "\n[ Conta #" << (i + 1) << " ]\n";
                        cout << "Numero da Conta: " << numeroConta[i] << "\n";
                        cout << "Titular: " << nomeCliente[i] << "\n";
                        cout << "CPF: " << cpf[i] << "\n";
                        cout << "E-mail: " << emailCliente[i] << "\n";
                        cout << "Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << "\n";
                        cout << "Status: " << (contaAtiva[i] ? "Ativa" : "Inativa") << "\n";
                    }
                }
                break;
            }

            case 3: {
                if (totalContas == 0) {
                    cout << "\nNenhuma conta cadastrada ainda.\n";
                } else {
                    int indice;
                    cout << "\nDigite o indice da conta (1 a " << totalContas << "): ";
                    cin >> indice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Erro: Indice invalido!\n";
                        break;
                    }

                    indice--; // Ajusta para indice de vetor (0 a totalContas - 1)

                    if (indice < 0 || indice >= totalContas) {
                        cout << "Erro: Conta nao encontrada!\n";
                    } else if (!contaAtiva[indice]) {
                        cout << "Operacao negada. A conta esta inativa.\n";
                    } else {
                        cout << "Saldo atual da conta " << numeroConta[indice] << ": R$ " << saldo[indice] << "\n";
                    }
                }
                break;
            }

            case 4: {
                if (totalContas == 0) {
                    cout << "\nNenhuma conta cadastrada ainda.\n";
                } else {
                    int indice;
                    cout << "\nDigite o indice da conta para alterar (1 a " << totalContas << "): ";
                    cin >> indice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Erro: Indice invalido!\n";
                        break;
                    }

                    indice--;

                    if (indice < 0 || indice >= totalContas) {
                        cout << "Erro: Conta nao encontrada!\n";
                    } else if (!contaAtiva[indice]) {
                        cout << "Operacao negada. A conta esta inativa.\n";
                    } else {
                        tipoConta[indice] = (tipoConta[indice] == 1) ? 2 : 1;
                        cout << "Tipo de conta alterado com sucesso para: " 
                             << (tipoConta[indice] == 1 ? "Corrente" : "Poupanca") << "\n";
                    }
                }
                break;
            }

            case 5: {
                if (totalContas == 0) {
                    cout << "\nNenhuma conta cadastrada ainda.\n";
                } else {
                    int indice;
                    cout << "\nDigite o indice da conta (1 a " << totalContas << "): ";
                    cin >> indice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Erro: Indice invalido!\n";
                        break;
                    }

                    indice--;

                    if (indice < 0 || indice >= totalContas) {
                        cout << "Erro: Conta nao encontrada!\n";
                    } else {
                        contaAtiva[indice] = !contaAtiva[indice];
                        cout << "Status da conta " << numeroConta[indice] << " alterado para: " 
                             << (contaAtiva[indice] ? "Ativa" : "Inativa") << "\n";
                    }
                }
                break;
            }

            case 6:
                cout << "\nEncerrando o sistema RibeiroBANK. Ate logo!\n";
                break;

            default:
                cout << "\nOpcao invalida. Tente novamente.\n";
                break;
        }

    } while (opcao != 6);

    return 0;
}