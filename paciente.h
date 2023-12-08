#ifndef _PACIENTEH_
#define _PACIENTEH_
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#define MAX_CHAR 50

struct Paciente;

typedef struct Paciente
{
    char nome[50];
    char problema[50];
    int gravidade;
    struct Paciente *prox;
} Paciente;

#include "mergeSort.h"

// Função para salvar a fila em um arquivo binário
void salvarFila(const char *nomeArquivo, Paciente *fila)
{
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    while (fila != NULL)
    {
        fwrite(fila, sizeof(Paciente), 1, arquivo);
        fila = fila->prox;
    }

    fclose(arquivo);
}

void salvaPacienteNaListaDeHistorico(char * nomeDoArquivo, Paciente paciente) {
     // Abra o arquivo no modo de escrita no final
    FILE *arquivo = fopen(nomeDoArquivo, "a"); // "a" para abrir o arquivo em modo de escrita no final

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Escreva os detalhes do paciente no arquivo como texto
    fprintf(arquivo, "Nome: %s, problema: %s\n", paciente.nome, paciente.problema);

    // Feche o arquivo
    fclose(arquivo);
}

// Função para criar um novo paciente
Paciente *criarPaciente(const char *nome, const char *problema, int gravidade)
{
    Paciente *novoPaciente = (Paciente *)malloc(sizeof(Paciente));
    if (novoPaciente != NULL)
    {
        snprintf(novoPaciente->nome, sizeof(novoPaciente->nome), "%s", nome);
        snprintf(novoPaciente->problema, sizeof(novoPaciente->problema), "%s", problema);
        novoPaciente->gravidade = gravidade;
        novoPaciente->prox = NULL;
    }
    return novoPaciente;
}

// Função para adicionar um paciente à fila ordenada por gravidade decrescente
void adicionarPacienteOrdenado(Paciente **fila, Paciente *novoPaciente)
{
    if (*fila == NULL || novoPaciente->gravidade < (*fila)->gravidade)
    {
        novoPaciente->prox = *fila;
        *fila = novoPaciente;
    }
    else
    {
        Paciente *atual = *fila;
        while (atual->prox != NULL && novoPaciente->gravidade >= atual->prox->gravidade)
        {
            atual = atual->prox;
        }
        novoPaciente->prox = atual->prox;
        atual->prox = novoPaciente;
    }
}

// Função para chamar o próximo paciente da fila
Paciente *chamarPaciente(char * nomeDoArquivoDeHistorico, char * nomeDoArquivoDaFila,  Paciente **fila, int inicio, int fim)
{
    if (*fila == NULL)
    {
        printf("A fila de pacientes está vazia.\n");
        return NULL;
    }

    Paciente *anterior = NULL;
    Paciente *atual = *fila;

    while (atual != NULL && atual->gravidade < inicio)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL || atual->gravidade > fim)
    {
        printf("Nenhum paciente encontrado dentro do intervalo.\n");
        return NULL;
    }

    if (anterior == NULL)
    {
        *fila = atual->prox;
    }
    else
    {
        anterior->prox = atual->prox;
    }

    salvaPacienteNaListaDeHistorico(nomeDoArquivoDeHistorico, *atual);
    salvarFila(nomeDoArquivoDaFila, *fila);
    return atual;
}

// Função para imprimir a fila de pacientes
void imprimirFila(Paciente *fila)
{
    printf("Fila de pacientes:\n");
    while (fila != NULL)
    {
        printf("Nome: %s, Problema: %s, Gravidade: %d\n", fila->nome, fila->problema, fila->gravidade);
        fila = fila->prox;
    }
    printf("\n");
}

void cadastrarPaciente(Paciente **root, char *nomeDoArquivo)
{
    char nome[50];
    printf("Nome: ");
    scanf("%[^\n]", nome);
    // fgets(nome, 50, stdin);
    limparBuffer();
    char problema[50];
    printf("\nProblema: ");
    scanf("%[^\n]", problema);
    // fgets(problema, 50, stdin);
    limparBuffer();
    printf("Prioridade: ");
    int prioridade;
    scanf("%d", &prioridade);
    Paciente *novoPaciente = criarPaciente(nome, problema, prioridade);
    adicionarPacienteOrdenado(root, novoPaciente);
    salvarFila(nomeDoArquivo, novoPaciente);
    // imprimirFila(*root);
}



int verificarBackup()
{
    FILE *fp;
    fp = fopen("backupFila.bin", "rb");
    if (fp)
    {
        fclose(fp);
        return 1;
    }
    else
    {
        return 0;
    }
}

// Função para carregar a fila a partir de um arquivo binário
Paciente *carregarFila(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo para leitura");
        return NULL;
    }

    Paciente *fila = NULL;
    Paciente paciente;

    while (fread(&paciente, sizeof(Paciente), 1, arquivo) == 1)
    {
        Paciente *novoPaciente = criarPaciente(paciente.nome, paciente.problema, paciente.gravidade);
        if (novoPaciente != NULL)
        {
            novoPaciente->prox = fila;
            fila = novoPaciente;
        }
    }

    fclose(arquivo);
    return fila;
}


Paciente * lerHistorico() {
        // Abra o arquivo para leitura
    FILE *arquivo = fopen("historico.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char linha[MAX_CHAR * 4]; // Ajuste o tamanho conforme necessário
    struct Paciente *listaPacientes = NULL;
    struct Paciente *ultimoPaciente = NULL;

    // Ler cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Processar a linha para extrair o nome e o problema
        char nome[MAX_CHAR], problema[MAX_CHAR * 2];
        if (sscanf(linha, "Nome: %[^\n,], problema: %[^\n]", nome, problema) == 2) {
            // Criar um novo paciente
            struct Paciente *novo = criarPaciente(nome, problema, 0);

            // Adicionar o novo paciente à lista
            if (novo != NULL) {
                if (listaPacientes == NULL) {
                    listaPacientes = novo;
                } else {
                    ultimoPaciente->prox = novo;
                }
                ultimoPaciente = novo;
            }
        }
    }

    // Fechar o arquivo
    fclose(arquivo);

    // Exemplo: percorrendo a lista de pacientes criada
    /* struct Paciente *atual = listaPacientes;
    int i = 1;
    while (atual != NULL) {
        printf("%d - Nome: %s | Problema: %s\n", i++, atual->nome, atual->problema);
        atual = atual->prox;
    } */

    

    return listaPacientes;
}


void imprimeListaDePacientes() {
    Paciente * root = lerHistorico();
    printf("Deseja imprimir o histórico de pacientes em qual ordem? \n");
    printf("1 - Data de atendimento\n");
    printf("2 - Ordem alfabetica\n");
    int opcao;
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        printf("Imprimindo lista cronologicamente:\n");
        imprimirFila(root);
        break;
    case 2: 
        printf("Imprimindo lista alfabeticamente:\n");
        mergeSort(&root);
        imprimirFila(root);
        break;
    default:
        printf("Opcao indisponivel");
        return;
    }

    // Limpar a memória alocada para os pacientes
    Paciente * atual = root;
    while (atual != NULL) {
        struct Paciente *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

#endif