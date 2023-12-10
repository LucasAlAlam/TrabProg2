#ifndef _UTILSH_
#define _UTILSH_

// Limpa o buffer de entrada. Útil quando se quer ler strings
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

#endif