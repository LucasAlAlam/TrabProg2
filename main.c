#include <stdio.h>
#include <stdlib.h>
#include "menu_principal.h"
#include "paciente.h"
#include "utils.h"

int main() {
    int opcao = 0;
    Paciente * root = NULL;
    while(opcao != 6) {
        opcao = imprimeMenuERetornaOpcao();
        limparBuffer();
        switch (opcao)
        {
        case 1:
            chamarPaciente(&root, 1, 2);
            break;
        case 2:
            chamarPaciente(&root, 3, 3);
            break;

        case 3: 
            imprimirFila(root);
            break;
        case 5: 
            cadastrarPaciente(&root, "fila.txt");
            break;
        
        default:
            opcao = 6;
            break;
        }
    }

    return 0;
}