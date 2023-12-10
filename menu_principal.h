#include <stdio.h>
#include "utils.h"

// Imprime o menu e retorna a opção selecionada
int imprimeMenuERetornaOpcao() {
    printf("O que deseja fazer?\n");
    printf("1 - Chamar proximo paciente para emergencia\n");
    printf("2 - Chamar proximo paciente para consulta\n");
    printf("3 - Visualizar fila\n");
    printf("4 - Visualizar lista de pacientes\n");
    printf("5 - Cadastrar novo paciente\n");
    printf("6 - Encerrar programa\n");
    printf("Selecione uma opcao: ");
    int opcao;
    scanf("%d", &opcao);
    printf("\n");
    return opcao;
}