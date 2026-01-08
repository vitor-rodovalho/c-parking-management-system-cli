#include "usuario.h"
#include "veiculo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo valores de estacionamento
#define PRECO_CARRO_GRANDE_DIARIO 20.0f
#define PRECO_CARRO_PEQUENO_DIARIO 15.0f
#define PRECO_MOTO_DIARIO 10.0f

#define PRECO_CARRO_GRANDE_MENSAL 200.0f
#define PRECO_CARRO_PEQUENO_MENSAL 150.0f
#define PRECO_MOTO_MENSAL 100.0f

#define PRECO_CARRO_GRANDE_ANUAL 2400.0f
#define PRECO_CARRO_PEQUENO_ANUAL 1800.0f
#define PRECO_MOTO_ANUAL 1200.0f

float caixa_estacionamento = 0.0f;

// Função para verificar se o saldo do usuário é suficiente para pagar o valor do estacionamento
int verificar_saldo(Usuario* usuario, float preco) {
    if (usuario->saldo >= preco) {
        return 1;  // Saldo suficiente
    } else {
        printf("Saldo insuficiente! O valor de R$ %.2f nao pode ser pago com o saldo atual de R$ %.2f.\n", preco, usuario->saldo);
        return 0;  // Saldo insuficiente
    }
}

// Cria um novo veículo com quantidade de horas, meses ou anos
Veiculo* criar_veiculo(const char* placa, int tipo, int plano, const char* donoCPF, int quantidade) {
    Veiculo* veiculo = (Veiculo*)malloc(sizeof(Veiculo));
    if (veiculo) {
        // Inicializa os dados do veículo
        strcpy(veiculo->placa, placa);
        strcpy(veiculo->donoCPF, donoCPF);
        veiculo->tipo = tipo;
        veiculo->plano = plano;
        veiculo->quantidade = quantidade;   // Quantidade associada ao plano (horas, meses ou anos)
        veiculo->custo_total = calcular_valor_estacionamento(veiculo);  // Calcula o custo com base no tipo e plano
        veiculo->estacionado = 0;  // Inicialmente, o veículo não está estacionado
        veiculo->proximo = NULL;   // Próximo veículo na lista é NULL
    }
    return veiculo;
}

// Função para calcular o valor do estacionamento baseado no tipo e plano
float calcular_valor_estacionamento(Veiculo* veiculo) {
    float preco = 0.0f;

    // Calcular o preço com base no tipo de veículo e plano
    switch (veiculo->tipo) {
        case TIPO_MOTO:
            if (veiculo->plano == PLANO_DIARIO) {
                preco = PRECO_MOTO_DIARIO * veiculo->quantidade;  // Preço baseado na quantidade de dias
            } else if (veiculo->plano == PLANO_MENSAL) {
                preco = PRECO_MOTO_MENSAL * veiculo->quantidade;  // Preço baseado na quantidade de meses
            } else if (veiculo->plano == PLANO_ANUAL) {
                preco = PRECO_MOTO_ANUAL * veiculo->quantidade;  // Preço baseado na quantidade de anos
            }
            break;
        case TIPO_CARRO_PEQUENO:
            if (veiculo->plano == PLANO_DIARIO) {
                preco = PRECO_CARRO_PEQUENO_DIARIO * veiculo->quantidade;
            } else if (veiculo->plano == PLANO_MENSAL) {
                preco = PRECO_CARRO_PEQUENO_MENSAL * veiculo->quantidade;
            } else if (veiculo->plano == PLANO_ANUAL) {
                preco = PRECO_CARRO_PEQUENO_ANUAL * veiculo->quantidade;
            }
            break;
        case TIPO_CARRO_GRANDE:
            if (veiculo->plano == PLANO_DIARIO) {
                preco = PRECO_CARRO_GRANDE_DIARIO * veiculo->quantidade;
            } else if (veiculo->plano == PLANO_MENSAL) {
                preco = PRECO_CARRO_GRANDE_MENSAL * veiculo->quantidade;
            } else if (veiculo->plano == PLANO_ANUAL) {
                preco = PRECO_CARRO_GRANDE_ANUAL * veiculo->quantidade;
            }
            break;
        default:
            printf("Tipo de veiculo invalido.\n");
            return 0.0f;  // Retorna 0 caso o tipo de veículo seja inválido
    }

    return preco;
}

// Estaciona o veículo e desconta o valor do saldo
void estacionar_veiculo(Usuario* usuarioSelecionado) {
    char placa[10];
    printf("Digite a placa do veiculo para estacionar: ");
    scanf(" %9[^\n]", placa);

    Veiculo* veiculo = buscar_veiculo(usuarioSelecionado, placa);
    if (veiculo) {
        if (veiculo->estacionado) {
            printf("O veiculo ja esta estacionado.\n");
        } else {
            float preco = veiculo->custo_total;  // O preço já foi calculado quando o veículo foi cadastrado

            // Verificar se o saldo do usuário é suficiente
            if (verificar_saldo(usuarioSelecionado, preco)) {
                // Autorizando o pagamento
                usuarioSelecionado->saldo -= preco;  // Desconta o valor do saldo
                caixa_estacionamento += preco;  // Adiciona o valor ao caixa do estacionamento
                atualizar_status(veiculo, 1);  // Marca o veículo como estacionado
                printf("Veiculo com placa %s estacionado com sucesso! Preco: R$ %.2f\n", placa, preco);
            }
        }
    } else {
        printf("Veiculo nao encontrado.\n");
    }
}

// Exibe as informações de um veículo
void exibir_informacoes_veiculo(const Veiculo* veiculo) {
    if (veiculo) {
        printf("Placa: %s\n", veiculo->placa);
        printf("Tipo: %d\n", veiculo->tipo);
        printf("Plano: %d\n", veiculo->plano);
        printf("Quantidade: %d\n", veiculo->quantidade);
        printf("Custo Total: %.2f\n", veiculo->custo_total);
        printf("Estacionado: %s\n", veiculo->estacionado ? "Sim" : "Nao");
    }
}

// Atualiza o plano do veículo
void atualizar_plano(Veiculo* veiculo, int novoPlano) {
    if (veiculo) {
        veiculo->plano = novoPlano;  // Atualiza diretamente o valor numérico do plano
    }
}

// Atualiza o status do veículo (estacionado ou não)
void atualizar_status(Veiculo* veiculo, int novoStatus) {
    if (veiculo) {
        veiculo->estacionado = novoStatus;  // Atualiza diretamente o status
    }
}

// Remove o veículo
void destruir_veiculo(Veiculo* veiculo) {
    if (veiculo) {
        free(veiculo);  // Libera a memória alocada
    }
}