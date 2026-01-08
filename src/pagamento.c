#include "veiculo.h"
#include "pagamento.h"
#include <stdio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m" // Erro
#define GREEN   "\033[32m" // Sucesso
#define YELLOW  "\033[33m" // Aviso

// Calcula o valor de um plano de estacionamento
// Dependendo do valor de 'plano', a função retorna o valor correspondente.
float calcular_valor_plano(int plano,int quantidade) {
    switch (plano) {
        case PLANO_DIARIO:
            return 4.0f*quantidade;  // Valor para plano diário
        case PLANO_MENSAL:
            return 102.0f*quantidade;  // Valor para plano mensal
        case PLANO_ANUAL:
            return 1095.0f*quantidade;  // Valor para plano anual
        default:
            return 0.0f;  // Plano desconhecido
    }
}

// Processa o pagamento e marca o veículo como estacionado se o pagamento for bem-sucedido
void processar_pagamento_e_estacionar(float* saldo, float valor, Veiculo* veiculo) {
    if (*saldo >= valor) {
        *saldo -= valor;  // Deduz o valor do saldo
        veiculo->estacionado = 1;  // Marca o veículo como estacionado
        printf(GREEN"Pagamento realizado! Veiculo estacionado.\n"RESET);

        // Adiciona o valor ao caixa do estacionamento
        adicionar_ao_caixa(valor);
    } else {
        printf(RED"Saldo insuficiente! Valor necessario: %.2f\n"RESET, valor);
    }
}

// Função para obter o valor do caixa do estacionamento
float obter_caixa_estacionamento(void) {
    return caixa_estacionamento;
}

// Função para adicionar valor ao caixa
void adicionar_ao_caixa(float valor) {
    caixa_estacionamento += valor;
}

void verificar_caixa() {
    float caixa = obter_caixa_estacionamento();
    printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ CAIXA DO ESTACIONAMENTO $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("Total arrecadado: R$ %.2f\n", caixa);
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}
