#ifndef PAGAMENTO_H
#define PAGAMENTO_H
#include <stdio.h>
#include <time.h>
#include "veiculo.h"

// Calcula o valor de acordo com o plano de estacionamento
float calcular_valor_plano(int plano, int quantidade);

// Função para processar o pagamento e marcar o veículo como estacionado
void processar_pagamento_e_estacionar(float* saldo, float valor, Veiculo* veiculo);

// Função para obter o valor do caixa do estacionamento
float obter_caixa_estacionamento(void);

// Função para adicionar valor ao caixa
void adicionar_ao_caixa(float valor);

#endif