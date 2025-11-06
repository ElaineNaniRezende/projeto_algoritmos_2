#include <iostream>
#include <string>
#define N 5
using namespace std;

// Variáveis globais para controle
int totalUsu = 0;
int totalLivros = 0;

// Estrutura para o cadastro do usuário
struct Usuario {
    int matricula;
    string nome;
    string tipo; // Aluno ou Professor
};

// Estrutura para o cadastro do livro
struct Livro {
    int codigo;
    string titulo;
    string autor;
    string edicao;
    int matriculaUsuario; // matrícula do usuário que pegou o livro (0 = livre)
};

// ===================== SUB-ROTINAS =====================

// Exibe o menu principal
void mostrarMenu() {
    cout << "\n--------------------- MENU ---------------------\n";
    cout << "1 - Cadastrar Usuario\n";
    cout << "2 - Cadastrar Livro\n";
    cout << "3 - Listar Usuarios\n";
    cout << "4 - Listar Livros\n";
    cout << "5 - Listar Livros por Usuario\n";
    cout << "6 - Relatorio Final\n";
    cout << "7 - Sair\n";
    cout << "-------------------------------------------------\n";
    cout << "Digite sua opcao: ";
}

// Função para cadastrar usuário
void cadastrarUsu(Usuario usuarios[], int tamanMax) {
    if (totalUsu >= tamanMax) {
        cout << "Limite de usuarios atingido!\n";
        return;
    }

    Usuario novoUsu;
    cout << "Digite a MATRICULA do Usuario: ";
    cin >> novoUsu.matricula;

    // Verifica se matrícula já existe
    for (int i = 0; i < totalUsu; i++) {
        if (usuarios[i].matricula == novoUsu.matricula) {
            cout << "Essa matricula ja foi cadastrada!\n";
            return;
        }
    }

    cin.ignore(); // limpar buffer
    cout << "Digite o NOME do Usuario: ";
    getline(cin, novoUsu.nome);

    cout << "Digite o TIPO do usuario (Aluno ou Professor): ";
    cin >> novoUsu.tipo;

    usuarios[totalUsu] = novoUsu;
    totalUsu++;

    cout << "Usuario cadastrado com sucesso!\n";
}

// Função para cadastrar livro
void cadastrarLivro(Livro livros[], Usuario usuarios[], int tamLivros, int tamUsuarios) {
    if (totalLivros >= tamLivros) {
        cout << "Limite de livros atingido!\n";
        return;
    }

    Livro novoLivro;
    cout << "Digite o CODIGO do livro: ";
    cin >> novoLivro.codigo;

    // Verifica duplicidade
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].codigo == novoLivro.codigo) {
            cout << "Esse codigo ja foi cadastrado!\n";
            return;
        }
    }

    cin.ignore();
    cout << "Digite o TITULO do livro: ";
    getline(cin, novoLivro.titulo);

    cout << "Digite o AUTOR do livro: ";
    getline(cin, novoLivro.autor);

    cout << "Digite a EDICAO do livro: ";
    getline(cin, novoLivro.edicao);

    cout << "Digite a MATRICULA do usuario que esta pegando o livro: ";
    cin >> novoLivro.matriculaUsuario;

    // Verifica se o usuário existe
    bool usuarioExiste = false;
    for (int i = 0; i < totalUsu; i++) {
        if (usuarios[i].matricula == novoLivro.matriculaUsuario) {
            usuarioExiste = true;
            break;
        }
    }

    if (!usuarioExiste) {
        cout << "Usuario nao encontrado! Livro nao cadastrado.\n";
        return;
    }

    livros[totalLivros] = novoLivro;
    totalLivros++;

    cout << "Livro cadastrado e associado com sucesso!\n";
}

// Lista todos os usuários cadastrados
void listarUsu(Usuario vet[]) {
    if (totalUsu == 0) {
        cout << "Nao ha usuarios cadastrados.\n";
        return;
    }

    cout << "\n---------- LISTA DE USUARIOS ----------\n";
    for (int i = 0; i < totalUsu; i++) {
        cout << "Matricula: " << vet[i].matricula << endl;
        cout << "Nome: " << vet[i].nome << endl;
        cout << "Tipo: " << vet[i].tipo << endl;
        cout << "---------------------------------------\n";
    }
}

// Lista todos os livros cadastrados
void listarLivros(Livro livros[], Usuario usuarios[]) {
    if (totalLivros == 0) {
        cout << "Nao ha livros cadastrados.\n";
        return;
    }

    cout << "\n---------- LISTA DE LIVROS ----------\n";
    for (int i = 0; i < totalLivros; i++) {
        cout << "Codigo: " << livros[i].codigo << endl;
        cout << "Titulo: " << livros[i].titulo << endl;
        cout << "Autor: " << livros[i].autor << endl;
        cout << "Edicao: " << livros[i].edicao << endl;

        string nomeUsuario = "Nao emprestado";
        for (int j = 0; j < totalUsu; j++) {
            if (usuarios[j].matricula == livros[i].matriculaUsuario) {
                nomeUsuario = usuarios[j].nome;
                break;
            }
        }
        cout << "Emprestado para: " << nomeUsuario << endl;
        cout << "-------------------------------------\n";
    }
}

// Buscar livros por matrícula de usuário
void buscarLivrosPorUsuario(Livro livros[], Usuario usuarios[]) {
    int matriculaBusca;
    cout << "Digite a matricula do usuario: ";
    cin >> matriculaBusca;

    bool encontrou = false;
    cout << "\nLivros emprestados para o usuario " << matriculaBusca << ":\n";

    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].matriculaUsuario == matriculaBusca) {
            cout << "- " << livros[i].titulo << endl;
            encontrou = true;
        }
    }

    if (!encontrou) {
        cout << "Nenhum livro encontrado para esse usuario.\n";
    }
}

// Relatório geral
void relatorioFinal(Livro livros[], Usuario usuarios[]) {
    cout << "\n----------- RELATORIO GERAL -----------\n";
    for (int i = 0; i < totalUsu; i++) {
        int contador = 0;
        for (int j = 0; j < totalLivros; j++) {
            if (livros[j].matriculaUsuario == usuarios[i].matricula) {
                contador++;
            }
        }
        cout << usuarios[i].nome << " possui " << contador << " livro(s) emprestado(s).\n";
    }
    cout << "---------------------------------------\n";
}

// ===================== FUNÇÃO PRINCIPAL =====================

int main() {
    Usuario vetorUsuarios[N];
    Livro vetorLivros[N];
    int opcao;

    do {
        mostrarMenu();
        cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrarUsu(vetorUsuarios, N);
                break;
            case 2:
                cadastrarLivro(vetorLivros, vetorUsuarios, N, N);
                break;
            case 3:
                listarUsu(vetorUsuarios);
                break;
            case 4:
                listarLivros(vetorLivros, vetorUsuarios);
                break;
            case 5:
                buscarLivrosPorUsuario(vetorLivros, vetorUsuarios);
                break;
            case 6:
                relatorioFinal(vetorLivros, vetorUsuarios);
                break;
            case 7:
                cout << "Sistema encerrado :|\n";
                break;
            default:
