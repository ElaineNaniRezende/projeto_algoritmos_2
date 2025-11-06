#include <iostream>
#include <string>
#define N 5
using namespace std;

//Variáveis globais para controlar corretamente
int totalUsu = 0;
int totalLivros = 0;

// Estrutura para o cadastro do usuario
struct Usuario {
    int matricula;
    string nome;
    string tipo;
};

// Sub-rotinas
void mostrarMenu() {
    cout << " --------------------- MENU ---------------------\n";
    cout << "1 - Cadastrar Usuario.\n";//ok, funcionando
    cout << "2 - Cadastrar Livro.\n";//
    cout << "3 - Listar Usuarios.\n";//
    cout << "4 - Listar Livros.\n";//
    cout << "5 - Listar Livros por usuario.\n";//
    cout << "6 - Relatorio Final.\n";//
    cout << "7 - para sair.\n";//
    cout << "Digite sua opcao: ";//
}


void cadastrarUsu(Usuario usuarios[], int tamanMax){
    Usuario novoUsu;
    if (totalUsu >= tamanMax) {
        cout << "Limite atingido de usuários!!\n";
        return;
    }
    cout << "Digite a MATRICULA do Usuario: ";
    cin >> novoUsu.matricula;

    // Verifica se já existe um usuário com a mesma matrícula
    for (int i = 0; i < totalUsu; i++) {
        if (usuarios[i].matricula == novoUsu.matricula) {
            cout << "Essa matricula já foi utilizada!!!\n";
            return;
        }
    }

    cout << "Digite o NOME do Usuario: ";
    getline(cin, novoUsu.nome);

    cout << "Digite se o tipo do usuario (Aluno ou Professor): ";
    cin >> novoUsu.tipo;
}


void listarUsu(Usuario vet[]){
    if (totalUsu == 0) {
        cout << "Não possui usuario cadastrado.\n";
    return;
    }
    cout << "-----------------------------------\n";
    for(int i=0; i < totalUsu; i++) {
        cout << "Informacoes da pessoa cadastrada. ID: " << endl;;
        cout << "Matricula: " << vet[i].matricula << endl;
        cout << "Nome: " << vet[i].nome << endl;
        cout << "Tipo: " << vet[i].tipo << endl;
        cout << "-----------------------------------\n";

    }
}

int main() {
    Usuario esteUsuario;
    Usuario vetorUsuarios[N];
    int opcao;

    mostrarMenu();
    cin >> opcao;

    while (opcao != 7) {
        switch(opcao) {
            case 1:
                cadastrarUsu(vetorusuarios, tamanMaxUsuarios);
                break;
            case 3:
                listarUsu(vetorUsuarios);
                break;
        }

        mostrarMenu();
        cin >> opcao;
    }

    return 0;
}
