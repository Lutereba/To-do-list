
//header
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <windows.h>
#include <limits>

#define AZUL 11
#define VERDE 2
#define VERMELHO 4
#define BRANCO 7
#define BRANCO_FORTE 15

//namespace
using std::cin, std::cout, std::string, std::endl, std::fstream,
      std::ofstream, std::ifstream, std::getline, std::vector,
      std::setw, std::left, std::numeric_limits, std::streamsize;


//classe
class Task // Representa uma tarefa da lista
{
public:
    string Titulo, data,conteudo,feitoStr = "Nao";
    bool feito = false;
    
    
    void feitoTxt()
       {
            feitoStr = feito ? "sim" : "nao";
       }

    
};
using ListaTarefas = vector<Task>;

//utils

static void cor(int cor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}
static void linha(char c = '=')
{
    cout << "+" << string(50, c) << "+" << endl;
}
static void titulo(const string& texto)
{
    linha('=');

    int espacos = (50 - texto.size()) / 2;

    cout << "|"
        << string(espacos, ' ')
        << texto
        << string(50 - espacos - texto.size(), ' ')
        << "|" << endl;

    linha('=');
}
static void showMenu()
{
    titulo("TO-DO LIST");

    cout << "| 1 - Adicionar tarefa                             |\n";
    cout << "| 2 - Listar tarefas                               |\n";
    cout << "| 3 - Excluir tarefa                               |\n";
    cout << "| 4 - Editar tarefa                                |\n";
    cout << "| 5 - Sair                                         |\n";

    linha('=');

    cout << "Opcao -> ";
}
static void Enter() // Aguarda o usuário pressionar ENTER
{
    cor(BRANCO_FORTE);
    linha('=');
    cout << "\nPressione ENTER para voltar...";
    cor(BRANCO);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
static void limparTela() //limpa a tela
{
    system("cls");
}


//carregar/salvar

static void salvarArquivo(ListaTarefas& tarefas)
{
    std::ofstream arquivo("tarefas.txt");

    for (const auto& tarefa : tarefas)
    {
        arquivo << tarefa.Titulo << '\n';
        arquivo << tarefa.data << '\n';
        arquivo << tarefa.conteudo << '\n';
        arquivo << tarefa.feitoStr << '\n';
        arquivo << "###\n";
    }
}
static void carregarArquivo(ListaTarefas& tarefas)
{
    std::ifstream arquivo("tarefas.txt");


    if(!arquivo.is_open()){
        
        cor(VERMELHO);
        cout << "[ERRO] Falha ao abrir o arquivo";
        cor(BRANCO);

        return;
    }
    Task tarefa;
    string linha;

    while (getline(arquivo, tarefa.Titulo))
    {
        getline(arquivo, tarefa.data); 
        getline(arquivo, tarefa.conteudo);
        getline(arquivo, tarefa.feitoStr);
        getline(arquivo, linha);
        
        tarefas.push_back(tarefa);

    }
    
}

//botões
static void addTask(Task& tarefa)
 {

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Insira o Titulo da tarefa\n";
        cout << "-> ";
        getline(cin, tarefa.Titulo);
        

        cout << "insira a data da tarefa:\n";
        cout << "-> ";
        getline(cin, tarefa.data);

        cout << "insira o conteudo da tarefa:\n";
        cout << "-> ";
        getline(cin, tarefa.conteudo);

        
        
    }
static void criarTarefa(ListaTarefas& tarefas) // cria tarefa
{
    titulo("Criar Tarefa");

    Task list;
    addTask(list);

    tarefas.push_back(list);
    salvarArquivo(tarefas);

    cor(VERDE);
    cout << "\n[OK] Tarefa adicionada com sucesso!\n";
    cor(BRANCO);
    

}
static void mostrarTarefa(ListaTarefas& tarefas) // printa as tarefas
{

    if (tarefas.empty() == true)
    {
        cor(AZUL);
        cout << "[INFO] NAO EXISTEM TAREFAS CADASTRADAS.\n";
        cor(BRANCO);

    }
    else
    {
        titulo("LISTA DE TAREFAS");

        cout << left
            << setw(5) << "ID"
            << setw(20) << "Titulo"
            << setw(15) << "Data"
            << setw(35) << "Conteudo"
            << setw(40) << "Feito"
            << endl;

        cout << string(75, '-') << endl;
        for (size_t i = 0; i < tarefas.size(); i++) // Lista todas as tarefas cadastradas
        {

            cout << left
                << setw(5) << i
                << setw(20) << tarefas[i].Titulo
                << setw(15) << tarefas[i].data
                << setw(35) << tarefas[i].conteudo
                << setw(40) << tarefas[i].feitoStr
                << endl;
        }
    }
}
static void excluirTarefa(ListaTarefas& tarefas)
{
    size_t idUser;
    char confirmarApagar;

    titulo("EXCLUIR TAREFA");

    if (tarefas.empty())
    {
        cor(AZUL);
        cout << "[INFO] NAO EXISTEM TAREFAS CADASTRADAS.\n";
        cor(BRANCO);
        return;
    }

    cout << "ID -> ";
    cin >> idUser;

    if (idUser >= tarefas.size())
    {
        cor(VERMELHO);
        cout << "[ERRO] TAREFA NAO ENCONTRADA!\n";
        cor(BRANCO);
        return;
    }

    cout << "Realmente deseja apagar essa tarefa? [y/n] ";
    cin >> confirmarApagar;

    if (confirmarApagar == 'y' || confirmarApagar == 'Y')
    {
        tarefas.erase(tarefas.begin() + idUser);
        salvarArquivo(tarefas);

        cor(VERDE);
        cout << "[OK] Tarefa deletada com sucesso!\n";
        cor(BRANCO);
    }
    else
    {
        cor(AZUL);
        cout << "[INFO] Operacao cancelada.\n";
        cor(BRANCO);
    }
}
static void editarTarefa(ListaTarefas& tarefas)
{
    
    size_t idUser;
    int option;
    string novoTitulo, novaData, novoConteudo;
    bool encontrado = false;

    titulo("EDITAR TAREFA");

    if (tarefas.empty())
    {
        cor(AZUL);
        cout << "[INFO] NAO EXISTEM TAREFAS CADASTRADAS.\n";
        cor(BRANCO);
        return;
    }

    cout << "Insira o id para editar a tarefa\n";
    cout << "ID -> ";
    cin >> idUser;

    encontrado = (idUser < tarefas.size());

    if (!encontrado)
    {
        cor(VERMELHO);
        cout << "[ERRO] Tarefa nao encontrada!\n";
        cor(BRANCO);
        Enter();
        return;
    }

    cout << "1) Alterar Titulo\n";
    cout << "2) Alterar Data\n";
    cout << "3) Alterar Conteudo\n";
    cout << "4) Marcar como Concluido/A Fazer\n";
    linha('=');
    cout << "Opcao -> ";
    cin >> option;

    switch (option)
    {
    case 1:
        cin.ignore();
        cout << "Insira o novo titulo:\n";
        getline(cin, novoTitulo);

        tarefas[idUser].Titulo = novoTitulo;
        salvarArquivo(tarefas);

        cout << "Titulo alterado com sucesso!\n";
        break;

    case 2:
        cin.ignore();
        cout << "Insira a nova data:\n";
        getline(cin, novaData);

        tarefas[idUser].data = novaData;
        salvarArquivo(tarefas);

        cout << "Data alterada com sucesso!\n";
        break;

    case 3:
    
        cin.ignore();
        cout << "Insira o novo conteudo:\n";
        getline(cin, novoConteudo);

        tarefas[idUser].conteudo = novoConteudo;
        salvarArquivo(tarefas);

        cout << "Conteudo alterado com sucesso!\n";
        break;

    case 4:
        char escolha;

        if (tarefas[idUser].feito)
        {
            cor(AZUL);
            cout << "[INFO] Ja esta marcada como feita.\n";
            cor(BRANCO);

            cout << "Deseja marcar como 'A Fazer'? [y/n] ";
            cin >> escolha;

            if (escolha == 'y' || escolha == 'Y')
            {
                tarefas[idUser].feito = false;
                tarefas[idUser].feitoTxt();
                salvarArquivo(tarefas);

                cor(VERDE);
                cout << "[OK] Tarefa alterada com sucesso!\n";
                cor(BRANCO);
            }
            else
            {
                cor(AZUL);
                cout << "[INFO] Operacao cancelada.\n";
                cor(BRANCO);
            }
        }
        else
        {
            tarefas[idUser].feito = true;
            tarefas[idUser].feitoTxt();
            salvarArquivo(tarefas);

            cor(VERDE);
            cout << "[OK] Tarefa concluida!\n";
            cor(BRANCO);
        }

        break;
    }
}

//escolha
static void escolha(int op, ListaTarefas& tarefas) //escolha entre os elementos do crud 
{
    switch (op)
    {
    case 1: {
        limparTela();
        criarTarefa(tarefas);
        Enter();
        break;

    }
    case 2: {
        limparTela();
        mostrarTarefa(tarefas);
        Enter();
        break;

    }
    case 3: {
        limparTela();
        excluirTarefa(tarefas);
        Enter();
        break;
    }
    case 4: {
        limparTela();
        editarTarefa(tarefas);
        Enter();
        break;
    }
    case 5: {
        limparTela();
        cor(AZUL);
        titulo("FECHANDO PROGRAMA");
        cor(BRANCO);
        break;
    }

    default: {
        limparTela();
        cor(VERMELHO);
        cout << "Opcao invalida!" << endl;
        cor(BRANCO);
        Enter();
        break;
    }
        
    }
}

//main
int main() 
{

    ListaTarefas tarefas;
    carregarArquivo(tarefas);

    int option = 0;

    do { 
        limparTela();
        showMenu();
        cin >> option;
        escolha(option, tarefas);


    } while (option != 5);

}

