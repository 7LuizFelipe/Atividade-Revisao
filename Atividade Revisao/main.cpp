#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Ativo {
    string ticket;
    int quantidade;
    double preco_medio;
};

// Função para registrar uma compra
void registrarCompra(vector<Ativo>& carteira) {
    Ativo novo;
    cout << "Digite o ticket (max 6 letras): ";
    cin >> novo.ticket;
    cout << "Digite a quantidade comprada: ";
    cin >> novo.quantidade;
    cout << "Digite o valor do ativo: ";
    cin >> novo.preco_medio;

    for (auto& ativo : carteira) {
        if (ativo.ticket == novo.ticket) {
            double total = (ativo.preco_medio * ativo.quantidade + novo.preco_medio * novo.quantidade) / (ativo.quantidade + novo.quantidade);
            ativo.quantidade += novo.quantidade;
            ativo.preco_medio = total;
            return;
        }
    }
    carteira.push_back(novo);
}

// Função para registrar uma venda
void registrarVenda(vector<Ativo>& carteira) {
    string ticket;
    int quantidade_venda;
    double valor_venda;

    cout << "Digite o ticket: ";
    cin >> ticket;
    cout << "Digite a quantidade vendida: ";
    cin >> quantidade_venda;
    cout << "Digite o valor do ativo: ";
    cin >> valor_venda;

    for (auto& ativo : carteira) {
        if (ativo.ticket == ticket) {
            if (ativo.quantidade >= quantidade_venda) {
                ativo.quantidade -= quantidade_venda;
                return;
            } else {
                cout << "Quantidade insuficiente para venda." << endl;
                return;
            }
        }
    }
    cout << "Ativo nao encontrado." << endl;
}

// Função recursiva para busca binária
void verSaldo(const vector<Ativo>& carteira, const string& ticket, int esquerda, int direita) {
    if (esquerda > direita) {
        cout << "Ativo nao encontrado." << endl;
        return;
    }

    int meio = esquerda + (direita - esquerda) / 2;

    if (carteira[meio].ticket == ticket) {
        cout << "Ticket: " << carteira[meio].ticket << endl;
        cout << "Quantidade: " << carteira[meio].quantidade << endl;
        cout << "Preco Medio: " << fixed << setprecision(2) << carteira[meio].preco_medio << endl;
        return;
    }

    if (carteira[meio].ticket > ticket) {
        verSaldo(carteira, ticket, esquerda, meio - 1);
    } else {
        verSaldo(carteira, ticket, meio + 1, direita);
    }
}

// Função para listar o patrimônio
void listarPatrimonio(const vector<Ativo>& carteira) {
    cout << "Patrimonio: " << endl;
    for (const auto& ativo : carteira) {
        cout << "Ticket: " << ativo.ticket << " ";
        cout << "Quantidade: " << ativo.quantidade << " ";
        cout << "Preco Medio: " << fixed << setprecision(2) << ativo.preco_medio << endl;
    }
}

int main() {
    vector<Ativo> carteira;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Registrar compra" << endl;
        cout << "2. Registrar venda" << endl;
        cout << "3. Ver o saldo de um ativo (Busca por Ticket)" << endl;
        cout << "4. Listar Patrimonio" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opcao: ";

        int opcao;
        cin >> opcao;

        switch (opcao) {
            case 1:
                registrarCompra(carteira);
                break;
            case 2:
                registrarVenda(carteira);
                break;
            case 3: {
                string ticket;
                cout << "Digite o ticket: ";
                cin >> ticket;
                // Ordena carteira para a busca binaria
                sort(carteira.begin(), carteira.end(), [](const Ativo& a, const Ativo& b) {
                    return a.ticket < b.ticket;
                });
                verSaldo(carteira, ticket, 0, carteira.size() - 1);
                break;
            }
            case 4:
                listarPatrimonio(carteira);
                break;
            case 5:
                return 0;
            default:
                cout << "Opcao invalida." << endl;
                break;
        }
    }
}
