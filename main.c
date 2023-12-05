#include <stdio.h>
#include <stdlib.h>
#include "menu_principal.h"
#include <locale.h>
#include <wchar.h>

int main() {
    setlocale(LC_ALL,"Portuguese");
    int opcao = 0;
    while(opcao != 6) {
        opcao = imprimeMenuERetornaOpcao();

    }

    return 0;
}