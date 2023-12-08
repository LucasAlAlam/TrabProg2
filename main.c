#include <stdio.h>
#include <stdlib.h>
#include "menu_principal.h"
#include "paciente.h"
#include "utils.h"
int main() {
    int opcao = 0;
    Paciente * root = NULL;
    int flagRecuperacao;
    FILE *arqFila;
    if (verificarBackup())
    {
        printf("Deseja recuperar a fila existente? (1)Sim ou (2)Não: ");
        scanf("%i", &flagRecuperacao);
        while (flagRecuperacao!=1 && flagRecuperacao!=2)
        {
            printf("Opção inválida! Digite 1 para \"Sim\" ou 2 para \"Não\": ");
            scanf("%i", &flagRecuperacao);
        }
        if (flagRecuperacao==1)
            root = carregarFila("backupFila.bin");
        else remove("backupFila.bin");
    }
    
    while(opcao != 6) {
        opcao = imprimeMenuERetornaOpcao();
        limparBuffer();
        switch (opcao)
        {
        case 1:
            chamarPaciente("historico.txt", "backupFila.bin", &root, 1, 2);
            break;
        case 2:
            chamarPaciente("historico.txt", "backupFila.bin", &root, 3, 3);
            break;

        case 3: 
            imprimirFila(root);
            break;
        case 4: 
            imprimeListaDePacientes();
            break;
        case 5: 
            cadastrarPaciente(&root, "backupFila.bin");
            break;
        
        default:
            opcao = 6;
            break;
        }
    }

    return 0;
}