#include <stdio.h>
#include <stdlib.h>
#include "menu_principal.h"
#include <locale.h>
#include <wchar.h>

// Definindo a estrutura do paciente
typedef struct Paciente {
    char nome[50];
    char problema[50];
    int gravidade;
    struct Paciente *prox;
} Paciente;

// Função para criar um novo paciente
Paciente *criarPaciente(const char *nome, const char *problema, int gravidade) {
    Paciente *novoPaciente = (Paciente *)malloc(sizeof(Paciente));
    if (novoPaciente != NULL) {
        snprintf(novoPaciente->nome, sizeof(novoPaciente->nome), "%s", nome);
        snprintf(novoPaciente->problema, sizeof(novoPaciente->problema), "%s", problema);
        novoPaciente->gravidade = gravidade;
        novoPaciente->prox = NULL;
    }
    return novoPaciente;
}

// Função para adicionar um paciente à fila ordenada por gravidade decrescente
void adicionarPacienteOrdenado(Paciente **fila, Paciente *novoPaciente) {
    if (*fila == NULL || novoPaciente->gravidade > (*fila)->gravidade) {
        novoPaciente->prox = *fila;
        *fila = novoPaciente;
    } else {
        Paciente *atual = *fila;
        while (atual->prox != NULL && atual->prox->gravidade >= novoPaciente->gravidade) {
            atual = atual->prox;
        }
        novoPaciente->prox = atual->prox;
        atual->prox = novoPaciente;
    }
}

// Função para salvar a fila em um arquivo binário
void salvarFila(const char *nomeArquivo, Paciente *fila) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    while (fila != NULL) {
        fwrite(fila, sizeof(Paciente), 1, arquivo);
        fila = fila->prox;
    }

    fclose(arquivo);
}

// Função para carregar a fila a partir de um arquivo binário
Paciente *carregarFila(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return NULL;
    }

    Paciente *fila = NULL;
    Paciente paciente;

    while (fread(&paciente, sizeof(Paciente), 1, arquivo) == 1) {
        Paciente *novoPaciente = criarPaciente(paciente.nome, paciente.problema, paciente.gravidade);
        if (novoPaciente != NULL) {
            novoPaciente->prox = fila;
            fila = novoPaciente;
        }
    }

    fclose(arquivo);
    return fila;
}

// Função para chamar o próximo paciente da fila
void chamarProximoPaciente(Paciente **fila) {
    if (*fila == NULL) {
        printf("Fila de pacientes vazia.\n");
    } else {
        Paciente *removido = *fila;
        printf("Chamando paciente: %s\n", removido->nome);
        *fila = (*fila)->prox;
        free(removido);
    }
}

// Função para imprimir a fila de pacientes
void imprimirFila(Paciente *fila) {
    printf("Fila de pacientes:\n");
    while (fila != NULL) {
        printf("Nome: %s, Problema: %s, Gravidade: %d\n", fila->nome, fila->problema, fila->gravidade);
        fila = fila->prox;
    }
    printf("\n");
}

// Função principal
int main() {
    Paciente *fila = NULL;
    setlocale(LC_ALL,"Portuguese");
    int opcao = 0;
    while(opcao != 6) {
        opcao = imprimeMenuERetornaOpcao();

    }
    
    /*adicionarPacienteOrdenado(&fila, criarPaciente("Paciente1", "Febre", 3));
    adicionarPacienteOrdenado(&fila, criarPaciente("Paciente2", "Fratura", 5));
    adicionarPacienteOrdenado(&fila, criarPaciente("Paciente3", "Dor de cabeça", 2));

    // Imprimir a fila antes de chamar um paciente
    imprimirFila(fila);

    // Salvar a fila em um arquivo binário
    salvarFila("pacientes.bin", fila);

    // Chamar o próximo paciente
    chamarProximoPaciente(&fila);

    // Imprimir a fila após chamar um paciente
    imprimirFila(fila);

    // Carregar a fila a partir do arquivo binário
    Paciente *filaCarregada = carregarFila("pacientes.bin");

    // Imprimir a fila carregada
    imprimirFila(filaCarregada);

    // Libera a memória antes de sair do programa
    while (fila != NULL) {
        Paciente *temp = fila;
        fila = fila->prox;
        free(temp);
    }

    // Libera a memória da fila carregada
    while (filaCarregada != NULL) {
        Paciente *temp = filaCarregada;
        filaCarregada = filaCarregada->prox;
        free(temp);
    }*/

    return 0;
}