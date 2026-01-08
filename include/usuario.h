#ifndef USUARIO_H
#define USUARIO_H

#include "veiculo.h"

// Estrutura do usuário
typedef struct Usuario {
    char nome[100];         // Nome do usuário
    char cpf[12];           // CPF do usuário
    float saldo;            // Saldo do usuário para pagamentos
    Veiculo* listaVeiculos; // Lista encadeada de veículos do usuário
} Usuario;

// Estrutura para lista encadeada de usuários
typedef struct UsuarioNode {
    Usuario* usuario;            // Ponteiro para um usuário
    struct UsuarioNode* proximo; // Ponteiro para o próximo nó da lista
} UsuarioNode;

// Cria um novo usuário
Usuario* criar_usuario(const char* nome, const char* cpf);

// Adiciona um usuário à lista encadeada
UsuarioNode* adicionar_usuario(UsuarioNode* lista, Usuario* usuario);

// Busca um usuário na lista encadeada pelo CPF
Usuario* buscar_usuario(UsuarioNode* lista, const char* cpf);

// Adiciona saldo ao usuário
void adicionar_saldo(Usuario* usuario, float valor);

// Adiciona um veículo à lista do usuário
void adicionar_veiculo(Usuario* usuario, const char* placa, int tipo, int plano, int quantidade);

// Busca um veículo na lista de veículos do usuário
Veiculo* buscar_veiculo(Usuario* usuario, const char* placa);

// Lista os veículos de um usuário
void listar_veiculos_usuario(const Usuario* usuario);

// Exibe os dados do usuário
void exibir_dados_usuario(const Usuario* usuario);

// Remove o usuário e libera a memória de seus veículos
void destruir_usuario(Usuario* usuario);

// Funções para manipulação de veículos

// Altera o plano de um veículo estacionado
void alterar_plano_veiculo(UsuarioNode* usuarios);

// Funções para retirar e estacionar veículos
void retirar_veiculo(Usuario* usuario, Veiculo* veiculo);
void estacionar_veiculo(Usuario* usuarioSelecionado);

// Função para remover um veículo do cadastro
void remover_veiculo(Usuario* usuario, Veiculo* veiculo);

// Salva todos os dados dos usuários em um arquivo
void salvar_dados(UsuarioNode* lista, const char* nomeArquivo);

// Carrega todos os dados de usuários a partir de um arquivo
UsuarioNode* carregar_dados(const char* nomeArquivo);

// Função para validar o CPF (somente números e 11 dígitos)
int validar_cpf(const char* cpf);

// Funções relacionadas ao estacionamento e caixa (se necessário)
void exibir_usuarios_cadastrados(const UsuarioNode* lista);
void verificar_veiculos_estacionados(UsuarioNode* lista);
void verificar_caixa();

// Função para remover o usuário da lista
void remover_usuario(UsuarioNode** lista, const char* cpf, const char* nomeArquivo);
#endif