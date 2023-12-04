#include <stdio.h>
#include <stdlib.h>

//--------------------------- ESTRUTURA CADASTRO PACIENTES ---------------------------------//
typedef struct // dados que serão armazenados dos pacientes
{
    unsigned int id;
    char nome[50];
    unsigned int gravidade;
    char problema[300];
} dadosPaciente;

typedef struct aux
{
    dadosPaciente dados;
    struct aux *prox;
} registro; // dados que serão de fato armazenados em memória. irão conter uma estrutura para os dados do paciente e um ponteiro para a próxima estrutura de dados do paciente.

typedef registro *ponteiroRegistro;

typedef struct
{
    ponteiroRegistro inicio;
} listaPacientes; // a estrutura de listaPacientes tem apenas o ponteiro de início. Assim, esse ponteiro irá apontar sempre para o início da listaPacientes

//---------------------------- INICILIZAÇÕES DAS ESTRUTURAS ----------------------------------//
void inicializarListaPacientes(listaPacientes *l)
{
    l->inicio = NULL;
}

//--------------------------- FUNÇÕES CADASTRO PACIENTES ------------------------------------//

dadosPaciente *pegarDadosPaciente(listaPacientes *l)
{
    dadosPaciente *dados;
    printf("Digite o nome do paciente: ");
    scanf("%[^\n]", dados->nome);
    __fpurge(stdin);
    printf("%s\n", dados->nome);
    printf("Digite o problema do paciente: ");
    scanf("%[^\n]", dados->problema);
    __fpurge(stdin);
    printf("%s\n", dados->problema);
    printf("Digite a gravidade do problema: ");
    scanf("%i", &dados->gravidade);
    while (dados->gravidade < 0 || dados->gravidade > 5)
    {
        printf("Dado inválido! Informe um valor entre 0 e 5\n");
        scanf("%i", &dados->gravidade);
    }
    printf("\n");
    return dados;
}

int arquivoEstaVazio(FILE *arq)
{

    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq);
    if (tam == 0)
        return 0;
    printf("tam = %d \n", tam);
    return tam;
}

int tamanhoLista(listaPacientes *l)
{
    int tam = 0;
    ponteiroRegistro end = l->inicio;
    while (end != NULL)
    {
        tam++;
        end = end->prox;
    }
    return tam;
}

void insereRegistroLista(listaPacientes *l, dadosPaciente dados)
{
    registro *novo = (registro *)malloc(sizeof(registro));
    novo->dados = dados;
    registro *aux;
    if (tamanhoLista(l) == 0)
    {
        novo->prox = l->inicio; // o proximo endeereço em novo será NULL
        l->inicio = novo;
    }
    else
    {
        aux = l->inicio;
        for (int i = 0; i < tamanhoLista(l) - 1; i++)
            aux = aux->prox;
        novo->prox = aux->prox;
        aux->prox = novo;
    }
}

int cadastrarPaciente(listaPacientes *l)
{
    FILE *arq;
    if ((arq = fopen("Lista de pacientes.dat", "ab")) == NULL)
    {
        printf("Erro ao acessar o arquivo");
        return -1;
    }
    dadosPaciente *dados = pegarDadosPaciente(l);
    dadosPaciente auxiliar;
    if (!(arquivoEstaVazio(arq))) // verifica se o arquivo está vazio. verdadeiro -> if, falso -> else
    {
        dados->id = 0;
    }
    else
    {
        fseek(arq, -1 * sizeof(dadosPaciente), SEEK_END);
        fread(&auxiliar, sizeof(dadosPaciente), 1, arq);
        printf("\n nome do auxiliar %s e id %d \n", auxiliar.nome, auxiliar.id);
        dados->id = (auxiliar.id)+1;
        //BUG: Não está lendo o id do paciente anterior
    }
    fwrite(dados, sizeof(dadosPaciente), 1, arq);
    insereRegistroLista(l, *dados);
    fclose(arq);
}

void exibirLista(listaPacientes *l)
{
    ponteiroRegistro end = l->inicio;
    printf("Lista: \" ");
    while (end != NULL)
    {
        printf("%i %s %s %i\n", end->dados.id, end->dados.nome, end->dados.problema, end->dados.gravidade);
        end = end->prox;
    }
    printf("\"\n");
}

//----------------------------------------- MAIN --------------------------------------------------//

int main()
{
    listaPacientes listaPacientes;
    inicializarListaPacientes(&listaPacientes);
    cadastrarPaciente(&listaPacientes);
    printf("%d\n", tamanhoLista(&listaPacientes));
    exibirLista(&listaPacientes);
    FILE *arq = fopen("Lista de pacientes.dat", "rb");
    dadosPaciente pacientesRegistrados;
    while (!feof(arq))
    {
        fread(&pacientesRegistrados, sizeof(dadosPaciente), 1, arq);
        printf("{ id: %i, nome: %s, problema: %s, gravidade: %i }", pacientesRegistrados.id, pacientesRegistrados.nome, pacientesRegistrados.problema, pacientesRegistrados.gravidade);
    }
    fclose(arq);
    return 0;
}