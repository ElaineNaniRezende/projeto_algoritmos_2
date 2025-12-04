#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#define N 5
using namespace std;

//constante para guardar o tamanho da string
const int TAM_STR = 100;

int totalUsu = 0;
int totalLivros = 0;
int totalAutores = 0;

// Estrutura para o cadastro do usuário
struct Usuario {
    int matricula;
    char nome[TAM_STR];
    char tipo[TAM_STR];
};

// Estrutura para o cadastro do livro
struct Livro {
    int codigo;
    char titulo[TAM_STR];
    char autor[TAM_STR];
    char edicao[TAM_STR];
    int matriculaUsuario;
};

// Estrutura para cadastro de autor/nova para projeto 2
struct Autor{
    char nome[TAM_STR];
    char nacionalidade[TAM_STR];
};

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
    cout << "9 - Salvar informacoes (Binario)\n";
    cout << "10 - Carregar informacoes (Binario)\n";
    cout << "11 - Sair\n";
    cout << "-------------------------------------------------\n";
    cout << "Digite sua opcao: ";
}

void limparBuffer() {
    cin.ignore(10000, '\n');
}

// Função para cadastrar usuário
void cadastrarUsu(Usuario usuarios[], int tamanMax) {
    if (totalUsu >= tamanMax) {
        cout << "Limite de usuarios atingido!\n";
        return;
    }

    Usuario novoUsu;
    memset(&novoUsu, 0, sizeof(Usuario));

    cout << "Digite a MATRICULA do Usuario: ";
    cin >> novoUsu.matricula;

    for (int i = 0; i < totalUsu; i++) {
        if (usuarios[i].matricula == novoUsu.matricula) {
            cout << "Essa matricula ja foi cadastrada!\n";
            cin.clear();
            limparBuffer();
            return;
        }
    }

    limparBuffer();

    cout << "Digite o NOME do Usuario: ";
    cin.getline(novoUsu.nome, TAM_STR);

    cout << "Digite o TIPO do usuario (Aluno ou Professor): ";
    cin.getline(novoUsu.tipo, TAM_STR);

    usuarios[totalUsu] = novoUsu;
    totalUsu++;

    cout << "Usuario cadastrado com sucesso!\n";
}

// Função para cadastrar autor (novo cadastro)
void cadastrarAutor(Autor autores[], int tamAutores){
    if (totalAutores >= tamAutores) {
        cout << "Limite de autores atingido!\n";
        return;
    }

    Autor novoAutor;
    memset(&novoAutor, 0, sizeof(Autor));

    cout << "Digite o NOME do Autor: ";
    cin.getline(novoAutor.nome, TAM_STR);

    cout << "Digite a NACIONALIDADE do autor: ";
    cin.getline(novoAutor.nacionalidade, TAM_STR);

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
    memset(&novoLivro, 0, sizeof(Livro));

    cout << "Digite o CODIGO do livro: ";
    cin >> novoLivro.codigo;

    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].codigo == novoLivro.codigo) {
            cout << "Esse codigo ja foi cadastrado!\n";
            cin.clear();
            limparBuffer();
            return;
        }
    }

    limparBuffer();

    cout << "Digite o TITULO do livro: ";
    cin.getline(novoLivro.titulo, TAM_STR);

    cout << "Digite o AUTOR do livro: ";
    cin.getline(novoLivro.autor, TAM_STR);

    cout << "Digite a EDICAO do livro: ";
    cin.getline(novoLivro.edicao, TAM_STR);

    cout << "Digite a MATRICULA do usuario que esta pegando o livro (0 se nao estiver emprestado): ";

    if (!(cin >> novoLivro.matriculaUsuario)) {
        cout << "Entrada de matricula invalida. Definindo para 0 (nao emprestado).\n";
        novoLivro.matriculaUsuario = 0;
        cin.clear();
        limparBuffer();
    }

    if (novoLivro.matriculaUsuario != 0) {
        int usuarioExiste = 0;
        for (int i = 0; i < totalUsu; i++) {
            if (usuarios[i].matricula == novoLivro.matriculaUsuario) {
                usuarioExiste = 1;
                break;
            }
        }

        if (usuarioExiste == 0) {
            cout << "AVISO: Usuario nao encontrado! O livro sera cadastrado, mas a matricula do emprestimo foi zerada.\n";
            novoLivro.matriculaUsuario = 0;
        }
    }

    livros[totalLivros] = novoLivro;
    totalLivros++;

    cout << "Livro cadastrado com sucesso!\n";
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
        if (livros[i].matriculaUsuario != 0) {
            for (int j = 0; j < totalUsu; j++) {
                if (usuarios[j].matricula == livros[i].matriculaUsuario) {
                    nomeUsuario = usuarios[j].nome;
                    break;
                }
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
    if (!(cin >> matriculaBusca)) {
        cout << "Entrada de matricula invalida.\n";
        cin.clear();
        limparBuffer();
        return;
    }

    int encontrou = 0;

    string nomeUsuario = "Matricula Inexistente";
    for (int i = 0; i < totalUsu; i++) {
        if (usuarios[i].matricula == matriculaBusca) {
            nomeUsuario = usuarios[i].nome;
            break;
        }
    }

    cout << "\nLivros emprestados para o usuario " << nomeUsuario << " (Matrícula " << matriculaBusca << "):\n";

    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].matriculaUsuario == matriculaBusca) {
            cout << "- " << livros[i].titulo << endl;
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        cout << "Nao ha livro encontrado para esse usuario.\n";
    }
}

// Relatório geral
void relatorioFinal(Livro livros[], Usuario usuarios[], Autor vet[]) {
    cout << "\n----------- RELATORIO GERAL -----------\n";
    cout << "--- Contagem de Livros por Usuario ---\n";
    for (int i = 0; i < totalUsu; i++) {
        int contador = 0;
        for (int j = 0; j < totalLivros; j++) {
            if (livros[j].matriculaUsuario == usuarios[i].matricula) {
                contador++;
            }
        }
        cout << usuarios[i].nome << " possui " << contador << " livro(s) emprestado(s).\n";
    }
    cout << "--- Total de Cadastros ---\n";
    cout << "Total de Usuarios cadastrados: " << totalUsu << endl;
    cout << "Total de Livros cadastrados: " << totalLivros << endl;
    cout << "Total de Autores cadastrados: " << totalAutores << endl;
    cout << "---------------------------------------\n";
}

// Salva as informações de todos os cadastros e contadores em um arquivo binário
void salvar(Usuario vet[], Livro livros[], Autor autor[], int n) {
    fstream meuArquivo;

    meuArquivo.open("biblioteca.bin", ios::out | ios::binary | ios::trunc);

    if(meuArquivo.is_open()) {
        meuArquivo.write((char *) &totalUsu, sizeof(totalUsu));
        meuArquivo.write((char *) &totalLivros, sizeof(totalLivros));
        meuArquivo.write((char *) &totalAutores, sizeof(totalAutores));

        meuArquivo.write((char *) vet, sizeof(Usuario) * totalUsu);
        meuArquivo.write((char *) livros, sizeof(Livro) * totalLivros);
        meuArquivo.write((char *) autor, sizeof(Autor) * totalAutores);

        meuArquivo.close();
        cout << "Informacoes salvas com sucesso em 'biblioteca.bin'!\n";
    }
    else {
        cout << "Falha ao gravar informacoes. Verifique as permissoes de escrita.\n";
    }
}

// Carrega as informações de todos os cadastros e contadores de um arquivo binário
void carregar(Usuario vet[], Livro livros[], Autor autor[], int n) {
    fstream meuArquivo;
    meuArquivo.open("biblioteca.bin", ios::in | ios::binary);

    if(meuArquivo.is_open()) {
        meuArquivo.read((char *) &totalUsu, sizeof(totalUsu));
        meuArquivo.read((char *) &totalLivros, sizeof(totalLivros));
        meuArquivo.read((char *) &totalAutores, sizeof(totalAutores));

        if (totalUsu > N || totalLivros > N || totalAutores > N) {
             cout << "ERRO: O arquivo contem mais dados do que o limite do sistema (N=" << N << "). Dados podem estar incompletos.\n";
             totalUsu = (totalUsu > N) ? N : totalUsu;
             totalLivros = (totalLivros > N) ? N : totalLivros;
             totalAutores = (totalAutores > N) ? N : totalAutores;
        }

        meuArquivo.read((char *) vet, sizeof(Usuario) * totalUsu);
        meuArquivo.read((char *) livros, sizeof(Livro) * totalLivros);
        meuArquivo.read((char *) autor, sizeof(Autor) * totalAutores);

        meuArquivo.close();
        cout << "Informacoes carregadas com sucesso de 'biblioteca.bin'!\n";
    } else {
        cout << "Falha ao carregar informacoes. O arquivo 'biblioteca.bin' pode nao existir ou esta inacessivel.\n";
        totalUsu = 0;
        totalLivros = 0;
        totalAutores = 0;
    }
}

int main() {
    Usuario vetorUsuarios[N];
    Livro vetorLivros[N];
    Autor vetorAutores[N];
    int opcao;

    do {
        mostrarMenu();

        if (!(cin >> opcao)) {
            cout << "Entrada invalida. Por favor, digite um numero.\n";
            cin.clear();
            limparBuffer();
            opcao = 0;
            continue;
        }

        limparBuffer();


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
                cout << "\nPressione ENTER para voltar ao menu...";
                cin.get();
                break;
            case 10:
                carregar(vetorUsuarios, vetorLivros, vetorAutores, N );

                cout << "\n--- Dados carregados! Exibindo Usuarios... ---";
                listarUsu(vetorUsuarios);

                cout << "\nPressione ENTER para voltar ao menu...";
                cin.get();
                break;
            case 11:
                cout << "Sistema encerrado!\n";
                break;
            default:
                cout << "Opcao invalida! Tente de novo.\n";
                break;
        }
    } while (opcao != 11);

    return 0;
}
