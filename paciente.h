#ifndef _PACIENTEH_
#define _PACIENTEH_
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct Paciente
{
    char nome[50];
    char problema[50];
    int gravidade;
    struct Paciente *prox;
} Paciente;

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
Paciente *chamarPaciente(Paciente **fila, int inicio, int fim)
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

    return atual;
}

void imprimirFila(Paciente *fila);
void salvarFila(const char *nomeArquivo, Paciente *fila);

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

#endif