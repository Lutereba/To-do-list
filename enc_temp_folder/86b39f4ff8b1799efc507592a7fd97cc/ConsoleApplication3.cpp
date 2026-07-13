
//includes
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#define NOMINMAX
#include <windows.h>
#include <limits>

//namespace
using namespace std;
using ListaTarefas = vector<Task>;

//classe
class Task // Representa uma tarefa da lista
{
public:
    string Titulo, data, conteudo;

    void addTask() {
        cin.ignore();
        cout << "Insira o Titulo da tarefa\n";
        cout << "-> ";
        getline(cin,Titulo);
        

        cout << "insira a data da tarefa:\n";
        cout << "-> ";
        getline(cin, data);

        cout << "insira o conteudo da tarefa:\n";
        cout << "-> ";
        getline(cin, conteudo);
    }
};
#define AZUL 11
#define VERDE 2
#define VERMELHO 4
#define BRANCO 7
#define BRANCO_FORTE 15

//ajudas
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
    cout << "| 5 - Exibir Tarefa                                |\n";
    cout << "| 6 - Sair                                         |\n";

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
static void tituloDocumento(const string& titulo)
{
    int largura = 74;
    int espacos = (largura - titulo.size()) / 2;

    cout << string(espacos, ' ');
    cout << titulo << endl;
}

//botões
static void criarTarefa(ListaTarefas& tarefas) // cria tarefa
{
    titulo("Criar Tarefa");

    Task list;
    list.addTask();

    tarefas.push_back(list);
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
            << endl;

        cout << string(75, '-') << endl;
        for (int i = 0; i < tarefas.size(); i++) // Lista todas as tarefas cadastradas
        {

            cout << left
                << setw(5) << i
                << setw(20) << tarefas[i].Titulo
                << setw(15) << tarefas[i].data
                << setw(35) << tarefas[i].conteudo
                << endl;
        }
    }
}
static void excluirTarefa(ListaTarefas& tarefas)
{

    int idUser;

    titulo("EXCLUIR TAREFA");
    cout << "ID -> ";
    cin >> idUser;

    if(tarefas.empty())
    {
        cor(AZUL);
        cout << "[INFO] NAO EXISTEM TAREFAS CADASTRADAS.\n";
        cor(BRANCO);
    }
    else
    {
        for (int idTarefa = 0; idTarefa < tarefas.size(); idTarefa++)
        {
            if (idUser == idTarefa)
            {
                tarefas.erase(tarefas.begin() + idTarefa);
                cor(VERDE);
                cout << "veiculo deletado com sucesso" << endl;
                cor(BRANCO);
                break;
            }
            else
            {
                cor(VERMELHO);
                cout << "[ERRO] TAREFA NAO ENCONTRADA!\n";
                cor(BRANCO);
            }
        }
    }
}
static void editarTarefa(ListaTarefas& tarefas)
{

    
    int idUser,option;
    string novoTitulo, novaData, novoConteudo;
    bool encontrado = false;
    titulo("EDITAR TAREFA");
    
    cout << "Insira o id para editar a tarefa" << endl;
    cout << "ID->";
    cin >> idUser;
    if (tarefas.empty()) {
        cor(AZUL);
        cout << "[INFO] NAO EXISTEM TAREFAS CADASTRADAS.\n";
        cor(BRANCO);
    }
    else
    {
        for (int idTarefa = 0; idTarefa < tarefas.size(); idTarefa++)
        {
            if (idUser == idTarefa)
            {
                encontrado = true;
                cout << "1) Alterar Titulo\n";
                cout << "2) Alterar Data\n";
                cout << "3) Alterar Conteudo\n";
                cout << "==============================\n";
                cout << "Opcao -> ";
                cin >> option;

                switch (option)
                {
                case 1: {
                    cin.ignore();

                    cout << "insira o novo titulo" << endl;
                    getline(cin, novoTitulo);
                    tarefas[idTarefa].Titulo = novoTitulo;

                    cout << "Titulo alterado com sucesso" << endl;
                    break;
                }
                case 2: {
                    cin.ignore();

                    cout << "insira a nova data" << endl;
                    getline(cin, novaData);
                    tarefas[idTarefa].data = novaData;

                    cout << "data alterada com sucesso" << endl;
                    break;
                }
                case 3: {
                    cin.ignore();

                    cout << "insira o novo conteudo" << endl;
                    getline(cin, novoConteudo);
                    tarefas[idTarefa].conteudo = novoConteudo;

                    cout << "conteudo alterado com sucesso" << endl;
                    break;
                }
                default:
                    cout << "Insira uma opcao valida!" << endl;
                    break;

                }
            }
        if (!encontrado)
        {
            cor(VERMELHO);
            cout << "[ERRO] Tarefa nao encontrada!\n";
            cor(BRANCO);
            Enter();
        }
        }
    }
}
static void visualizarTask(const ListaTarefas& tarefas)
{
    linha('=');

    int largura = 50;
    int espacos = (largura - tarefas.Titulo.size()) / 2;

    cout << "|"
        << string(espacos, ' ')
        << tarefas.Titulo
        << string(largura - espacos - tarefas.Titulo.size(), ' ')
        << "|\n";

    linha('-');

    cout << "| Data: " << left << setw(42) << tarefas.data << "|\n";

    linha('-');

    cout << "| " << left << setw(48) << tarefas.conteudo << "|\n";

    linha('=');
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
        visualizarTask(tarefas);
        Enter();
        break;
    }
    case 6: {
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

    int option = 0;

    do { 
        limparTela();
        showMenu();
        cin >> option;
        escolha(option, tarefas);


    } while (option != 6);

}

