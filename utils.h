#ifndef _UTILSH_
#define _UTILSH_

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Consumir os caracteres do buffer até encontrar um newline ou EOF
    }
}

#endif