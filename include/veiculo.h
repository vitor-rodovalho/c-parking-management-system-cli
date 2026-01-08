#ifndef VEICULO_H
#define VEICULO_H

extern float caixa_estacionamento;

#include <string.h>  // Necessário para usar funções como strcpy

// Macros para representar planos
#define PLANO_DIARIO 1
#define PLANO_MENSAL 2
#define PLANO_ANUAL  3

// Macros para representar tipos de veículo
#define TIPO_CARRO_GRANDE 1
#define TIPO_CARRO_PEQUENO 2
#define TIPO_MOTO 3

// Definindo a estrutura Veiculo
typedef struct Veiculo {
    char placa[10];           // Placa do veículo (formato: ABC1234)
    char donoCPF[12];         // CPF do dono do veículo
    int estacionado;          // 1 = estacionado, 0 = não estacionado
    int plano;                // Plano do veículo (1 = diário, 2 = mensal, 3 = anual)
    int tipo;                 // Tipo do veículo (1 = carro grande, 2 = carro pequeno, 3 = moto)
    int quantidade;           // Quantidade associada ao plano (horas, meses ou anos)
    float custo_total;        // Custo total calculado com base no plano e na quantidade
    struct Veiculo* proximo;  // Ponteiro para o próximo veículo na lista
} Veiculo;

// Funções relacionadas ao Veículo

// Cria um novo veículo
Veiculo* criar_veiculo(const char* placa, int tipo, int plano, const char* donoCPF, int quantidade);

// Atualiza o plano do veículo
void atualizar_plano(Veiculo* veiculo, int novoPlano);

// Atualiza o status do veículo (estacionado ou não)
void atualizar_status(Veiculo* veiculo, int novoStatus);

// Libera a memória alocada para o veículo
void destruir_veiculo(Veiculo* veiculo);

// Exibe as informações do veículo
void exibir_informacoes_veiculo(const Veiculo* veiculo);

// Função para calcular o valor do estacionamento de acordo com o tipo e o plano
float calcular_valor_estacionamento(Veiculo* veiculo);

#endif