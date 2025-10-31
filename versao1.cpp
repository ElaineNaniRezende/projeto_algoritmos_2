#include <iostream>
#include <string>
#define N 5
using namespace std;

//variável global para controlar cada posição do array
int posicao;

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


void cadastrar(Usuario *u){
    cout << "Digite a MATRICULA do Usuario: ";
    cin >> u->matricula;

    cout << "Digite o NOME do Usuario: ";
    cin.ignore();
    getline(cin, u->nome);

    cout << "Digite se o usuario eh ALUNO ou PROFESSOR: ";
    cin >> u->tipo;
}


void listar(Usuario vet[]){
    for(int i=0; i<=posicao; i++) {
        cout << "Informacoes da pessoa cadastrada. ID: " << endl;;
        cout << " Numero de Matricula: " << vet[i].matricula << endl;
        cout << "Nome: " << vet[i].nome << endl;
        cout << "Tipo: " << vet[i].tipo << endl;

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
                Usuario(&esteUsuario);//erro aqui
                break;
            case 3:
                listar(vetorUsuarios);
                break;
        }

        mostrarMenu();
        cin >> opcao;
    }

    return 0;
}
