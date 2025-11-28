#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#define N 5
using namespace std;

// Variáveis globais para controle
int totalUsu = 0;
int totalLivros = 0;
int totalAutores = 0;

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
    int matriculaUsuario; // matrícula do usuário que emprestou
};

//estrutura para cadastro de autor
struct Autor{
    string nome;
    string nacionalidade;
};

// sub rotinas

// Exibe o menu principal
void mostrarMenu() {
    cout << "\n--------------------- MENU ---------------------\n";
    cout << "1 - Cadastrar Usuario\n";
    cout << "2 - Cadastrar autor\n";
    cout << "3 - Cadastrar Livro\n";
    cout << "4 - Listar Usuarios\n";
    cout << "5 - Listar Livros\n";
    cout << "6 - Listar Autores\n";
    cout << "7 - Listar Livros por Usuario\n";
    cout << "8 - Relatorio Final\n";
    cout << "9 - Salvar informacoes\n";
    cout << "10 - Carregar informacoes\n";
    cout << "11 - Sair\n";
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

void cadastrarAutor(Autor autores[], int tamAutores){
    if (totalAutores >= tamAutores) {
        cout << "Limite de livros atingido!\n";
        return;
    }

    Autor novoAutor;
    cin.ignore();
    cout << "Digite o primeiro NOME do Autor: ";
    getline(cin, novoAutor.nome);

    cout << "Digite a NACIONALIDADE do autor): ";
    cin >> novoAutor.nacionalidade;

    autores[totalAutores] = novoAutor;
    totalAutores++;

    cout << "Autor cadastrado com sucesso!\n";

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
    int usuarioExiste = 0;
    for (int i = 0; i < totalUsu; i++) {
        if (usuarios[i].matricula == novoLivro.matriculaUsuario) {
            usuarioExiste = 1;
            break;
        }
    }

    if (usuarioExiste == 0) {
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
        cout << "Nao possui livros cadastrados.\n";
        return;
    }

    cout << "\n---------- LISTA DE LIVROS ----------\n";
    for (int i = 0; i < totalLivros; i++) {
        cout << "Codigo: " << livros[i].codigo << endl;
        cout << "Titulo: " << livros[i].titulo << endl;
        cout << "Autor: " << livros[i].autor << endl;
        cout << "Edicao: " << livros[i].edicao << endl;

        string nomeUsuario = "Nao foi emprestado";
        for (int j = 0; j < totalUsu; j++) {
            if (usuarios[j].matricula == livros[i].matriculaUsuario) {
                nomeUsuario = usuarios[j].nome;
                break;
            }
        }
        cout << "Foi emprestado para: " << nomeUsuario << endl;
        cout << "-------------------------------------\n";
    }
}

// Lista todos os autores cadastrados
void listarAutores(Autor autor[]) {
    if (totalAutores == 0) {
        cout << "Nao possui autores cadastrados.\n";
        return;
    }

    cout << "\n---------- LISTA DE AUTORES ----------\n";
    for (int i = 0; i < totalAutores; i++) {
        cout << "Nome: " << autor[i].nome << endl;
        cout << "Nacionalidade: " << autor[i].nacionalidade << endl;
        cout << "-------------------------------------\n";
    }
}

// Lista livros por usuário
void buscarLivrosPorUsuario(Livro livros[], Usuario usuarios[]) {
    int matriculaBusca;
    cout << "Digite a matricula do usuario: ";
    cin >> matriculaBusca;

    int encontrou = 0;
    cout << "\nLivros emprestados para o usuario " << matriculaBusca << ":\n";

    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].matriculaUsuario == matriculaBusca) {
            cout << "- " << livros[i].titulo << endl;
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        cout << "Nao tem livro encontrado para esse usuario.\n";
    }
}

// Relatório geral com quantos  livros estão emprestados para cada usuário e autores cadastrados
void relatorioFinal(Livro livros[], Usuario usuarios[], Autor vet[]) {
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

// salvar as informacoes
void salvar(Usuario vet[], Livro livros[], Autor autor[], int n){//salvou string?
    fstream meuArquivo;

    meuArquivo.open("biblioteca.bin", ios::out | ios::binary);

    if(meuArquivo.is_open()) {
        meuArquivo.write((char *) vet, sizeof(Usuario) * n);
        meuArquivo.write((char *) livros, sizeof(Livro) * n);
        meuArquivo.write((char *) autor, sizeof(Autor) * n);
        meuArquivo.write((char *) &totalUsu, sizeof(totalUsu));
        meuArquivo.write((char *) &totalLivros, sizeof(totalLivros));
        meuArquivo.write((char *) &totalAutores, sizeof(totalAutores));
        meuArquivo.close();
        cout << "Informacoes salvas com sucesso!!\n";
    }
    else {
        cout << "Falha ao gravar informacoes.\n";
    }
}
void carregar(Usuario vet[], Livro livros[], Autor autor[], int n) {
    fstream meuArquivo;
    meuArquivo.open("biblioteca.bin", ios::in | ios::binary);

    if(meuArquivo.is_open()) {
        meuArquivo.read((char *) vet, sizeof(Usuario) * n);
        meuArquivo.read((char *) livros, sizeof(Livro) * n);
        meuArquivo.read((char *) autor, sizeof(Autor) * n);
        meuArquivo.read((char *) &totalUsu, sizeof(totalUsu));
        meuArquivo.read((char *) &totalLivros, sizeof(totalLivros));
        meuArquivo.read((char *) &totalAutores, sizeof(totalAutores));
        meuArquivo.close();
        cout << "Informacoes carregadas com sucesso!!\n";
    } else {
        cout << "Falha ao carregar informacoes.\n";
    }
}



int main() {
    Usuario vetorUsuarios[N];
    Livro vetorLivros[N];
    Autor vetorAutores[N];
    int opcao;

    do {
        mostrarMenu();
        cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrarUsu(vetorUsuarios, N);
                break;
            case 2:
                cadastrarAutor(vetorAutores, N);
                break;
            case 3:
                cadastrarLivro(vetorLivros, vetorUsuarios, N, N);
                break;
            case 4:
                listarUsu(vetorUsuarios);
                break;
            case 5:
                listarLivros(vetorLivros, vetorUsuarios);
                break;
            case 6:
                listarAutores(vetorAutores);
                break;
            case 7:
                buscarLivrosPorUsuario(vetorLivros, vetorUsuarios);
                break;
            case 8:
                relatorioFinal(vetorLivros, vetorUsuarios, vetorAutores);
                break;
            case 9:
                salvar(vetorUsuarios, vetorLivros, vetorAutores, N );
            case 10:
                carregar(vetorUsuarios, vetorLivros, vetorAutores, N );
            case 11:
                cout << "Sistema encerrado ;|\n";
                break;
            default:
                cout << "Nao deu certo! Tente de novo.\n";
                break;
        }
    } while (opcao != 12);

    return 0;
}
