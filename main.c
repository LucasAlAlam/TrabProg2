#include <stdio.h>

//--------------------------- ESTRUTURA CADASTRO DE USUÁRIOS ---------------------------------//
typedef struct      //dados que serão armazenados dos pacientes
{
    unsigned int id;
    char *nome;
    unsigned int gravidade;
    char *problema;
} dadosPaciente;

typedef struct aux
{
    dadosPaciente dados;
    struct aux* prox;
} registro;             //dados que serão de fato armazenados em memória. irão conter uma estrutura para os dados do paciente e um ponteiro para a próxima estrutura de dados do paciente.

typedef registro* ponteiroRegistro;

typedef struct
{
    ponteiroRegistro inicio;
} lista; //a estrutura de lista tem apenas o ponteiro de início. Assim, esse ponteiro irá apontar sempre para o início da lista

