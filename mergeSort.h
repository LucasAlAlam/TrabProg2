#ifndef _MERGESORTH_
#define _MERGESORTH_
#include <stdio.h>
#include <string.h>
#include "paciente.h" 

Paciente *merge(Paciente *left, Paciente *right) {
    Paciente *result = NULL;

    // Verifica se um dos lados está vazio, retorna o outro lado diretamente
    if (left == NULL) {
        return right;
    } else if (right == NULL) {
        return left;
    }

    if (strcmp(left->nome, right->nome) <= 0) {
        result = left;
        result->prox = merge(left->prox, right);
    } else {
        result = right;
        result->prox = merge(left, right->prox);
    }

    return result;
}

void split(Paciente *head, Paciente **front, Paciente **back) {
    Paciente *fast;
    Paciente *slow;

    if (head == NULL || head->prox == NULL) {
        *front = head;
        *back = NULL;
    } else {
        slow = head;
        fast = head->prox;

        // Usa fast e slow para dividir a lista ao meio
        while (fast != NULL) {
            fast = fast->prox;
            if (fast != NULL) {
                slow = slow->prox;
                fast = fast->prox;
            }
        }
        // Define os ponteiros para a lista da frente e de trás
        *front = head;
        *back = slow->prox;
        slow->prox = NULL; // Garante que em uma iteração termine na metade da lista. Ex. while (fila != NULL)
    }
}

void mergeSort(Paciente **head) {
    Paciente *tempHead = *head;
    Paciente *left;
    Paciente *right;

    if (tempHead == NULL || tempHead->prox == NULL) {
        return;
    }

    split(tempHead, &left, &right); // Divide a lista em duas metades

    mergeSort(&left);
    mergeSort(&right);

    *head = merge(left, right); // Mescla as duas metades ordenadas
}

#endif