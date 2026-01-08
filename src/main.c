// gcc src/main.c src/usuario.c src/veiculo.c src/pagamento.c -I include -o estacionamento

#include "usuario.h"
#include "pagamento.h"
#include "veiculo.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definindo macros para as cores
#define RESET   "\033[0m"
#define RED     "\033[31m" // Erro
#define GREEN   "\033[32m" // Sucesso
#define YELLOW  "\033[33m" // Aviso

// Funções auxiliares para validações
int validar_cpf(const char* cpf);
int validar_placa(const char *placa);
int validar_tipo(int tipo);
int validar_plano(int plano);
int validar_quantidade(int quantidade);


void limpar_terminal() {
    // Verificar se o sistema é Windows ou Linux/macOS
    #ifdef _WIN32
        system("cls");  // Comando para Windows
    #else
        system("clear");  // Comando para Linux/macOS
    #endif
}

// Função para exibir o menu principal
void exibir_menu() {
    printf("\n===================================== SISTEMA DE ESTACIONAMENTO =====================================\n");
    printf("1. Cadastrar Usuario\n");
    printf("2. Selecionar Usuario\n");
    printf("3. Exibir Usuarios Cadastrados\n");
    printf("4. Verificar Veiculos Estacionados\n");
    printf("5. Verificar Caixa do Estacionamento\n");
    printf("6. Alterar Plano de Veiculo\n");
    printf("7. Excluir Usuario\n");
    printf("8. Sair\n");
    printf("====================================================================================================\n");
    printf("Escolha uma opcao: ");
}

// Função auxiliar para exibir o menu do usuario selecionado
void exibir_menu_usuario() {
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MENU DO USUARIO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1. Cadastrar Veiculo\n");
    printf("2. Consultar Veiculo\n");
    printf("3. Remover Veiculo\n");
    printf("4. Retirar Veiculo\n");
    printf("5. Estacionar Veiculo\n");
    printf("6. Exibir Dados do Usuario\n");
    printf("7. Adicionar Saldo\n");  // Corrigido para a função correta
    printf("8. Voltar ao Menu Principal\n");  // Corrigido para a função correta
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Escolha uma opcao: ");
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    UsuarioNode* usuarios = NULL;  // Lista encadeada de usuarios
    Usuario* usuarioSelecionado = NULL;
    int opcao;

    // Carregar os dados do arquivo
    usuarios = carregar_dados("dados_usuarios.txt");
    if (usuarios) {
        printf(GREEN"Dados carregados com sucesso.\n"RESET);
    } else {
        printf(YELLOW"Nenhum dado encontrado. Iniciando com sistema vazio.\n"RESET);
    }

    do {
        // Exibe o menu principal
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {  // Verifica se a entrada é um número
            printf(RED"Entrada invalida. Tente novamente.\n"RESET);
            while (getchar() != '\n'); // Limpa o buffer do teclado
            continue;
        }

        switch (opcao) {
            case 1: {  // Cadastrar Usuario
                char nome[100], cpf[12];
                printf("Digite seu nome: ");
                scanf(" %99[^\n]", nome);

                int cpf_valido = 0;
                while (!cpf_valido) {
                    printf("Digite seu CPF (somente numeros): ");
                    scanf(" %11[^\n]", cpf);

                    if (validar_cpf(cpf)) {
                        if (buscar_usuario(usuarios, cpf)) {
                            printf(YELLOW"CPF ja cadastrado. Tente outro.\n"RESET);
                        } else {
                            cpf_valido = 1;
                        }
                    } else {
                        printf(RED"CPF invalido! Deve conter 11 digitos numericos.\n"RESET);
                    }
                }

                Usuario* novoUsuario = criar_usuario(nome, cpf);
                usuarios = adicionar_usuario(usuarios, novoUsuario);
                printf(GREEN"Usuario cadastrado com sucesso!\n"RESET);
                break;
            }

            case 2: {  // Selecionar Usuario
                if (usuarios == NULL) {
                    printf(YELLOW"Nenhum usuario cadastrado.\n"RESET);
                    break;
                }

                char cpf[12];
                printf("Digite o CPF do usuario para selecionar: ");
                scanf(" %11[^\n]", cpf);

                Usuario* usuario = buscar_usuario(usuarios, cpf);
                if (usuario) {
                    usuarioSelecionado = usuario;
                    printf(GREEN"Usuario %s selecionado.\n"RESET, usuario->nome);

                    // Submenu do usuario
                    int subOpcao;
                    do {
                        exibir_menu_usuario();
                        if (scanf("%d", &subOpcao) != 1) {  // Verifica se a entrada é um número
                            printf(RED"Entrada invalida. Tente novamente.\n"RESET);
                            while (getchar() != '\n'); // Limpa o buffer do teclado
                            continue;
                        }

                        switch (subOpcao) {
                            case 1:{ // Cadastrar Veículo
                                char placa[10];
                                int tipo, plano, quantidade;

                                // Entrada e validação da placa
                                do
                                {
                                    printf("Digite a placa do veiculo (formato ABC-1234): ");
                                    scanf(" %9[^\n]", placa);
                                    if (!validar_placa(placa))
                                    {
                                        printf(RED"\033[31mPlaca inválida! Tente novamente.\033[0m\n"RESET);
                                    }
                                } while (!validar_placa(placa));

                                // Entrada e validação do tipo do veículo
                                do
                                {
                                    printf("Selecione o tipo do veiculo:\n");
                                    printf("1 - Carro Grande\n2 - Carro Pequeno\n3 - Moto\n");
                                    scanf("%d", &tipo);
                                    if (!validar_tipo(tipo))
                                    {
                                        printf(RED"\033[31mTipo inválido! Escolha 1, 2 ou 3.\033[0m\n"RESET);
                                    }
                                } while (!validar_tipo(tipo));

                                // Entrada e validação do plano do veículo
                                do
                                {
                                    printf("Selecione o plano do veiculo:\n");
                                    printf("1 - Diario\n2 - Mensal\n3 - Anual\n");
                                    scanf("%d", &plano);
                                    if (!validar_plano(plano))
                                    {
                                        printf(RED"\033[31mPlano inválido! Escolha 1, 2 ou 3.\033[0m\n"RESET);
                                    }
                                } while (!validar_plano(plano));

                                // Entrada e validação da quantidade
                                do
                                {
                                    printf("Digite a quantidade (horas, meses ou anos, conforme o plano): ");
                                    scanf(" %d", &quantidade); // Lê até a nova linha, permitindo espaços.
                                    if (!validar_quantidade(quantidade))
                                    {
                                        printf(RED"\033[31mQuantidade inválida! Deve ser maior que zero.\033[0m\n"RESET);
                                    }
                                } while (!validar_quantidade(quantidade));

                                // Cadastro do veículo
                                adicionar_veiculo(usuarioSelecionado, placa, tipo, plano, quantidade);
                                printf(GREEN"\033[32mVeiculo cadastrado com sucesso!\033[0m\n"RESET);
                                break;
                            }
                            case 2: {  // Consultar Veículo
                                char placa[10];
                                printf("Digite a placa do veiculo para consultar: ");
                                scanf(" %9[^\n]", placa);

                                Veiculo* veiculo = buscar_veiculo(usuarioSelecionado, placa);
                                if (veiculo) {
                                    exibir_informacoes_veiculo(veiculo);
                                } else {
                                    printf(RED"Veiculo nao encontrado.\n"RESET);
                                }
                                break;
                            }
                            case 3: {  // Remover Veículo
                                char placa[10];
                                printf("Digite a placa do veiculo para remover: ");
                                scanf(" %9[^\n]", placa);

                                Veiculo* veiculoRemover = buscar_veiculo(usuarioSelecionado, placa);
                                if (veiculoRemover) {
                                    remover_veiculo(usuarioSelecionado, veiculoRemover);
                                    printf(GREEN"Veiculo removido com sucesso!\n"RESET);
                                } else {
                                    printf(RED"Veiculo nao encontrado.\n"RESET);
                                }
                                break;
                            }
                            case 4: {  // Retirar Veículo
                                char placa[10];
                                printf("Digite a placa do veiculo para retirar: ");
                                scanf(" %9[^\n]", placa);

                                Veiculo* veiculo = buscar_veiculo(usuarioSelecionado, placa);
                                if (veiculo) {
                                    retirar_veiculo(usuarioSelecionado, veiculo);
                                } else {
                                    printf(RED"Veiculo nao encontrado.\n"RESET);
                                }
                                break;
                            }
                            case 5: {  // Estacionar Veículo
                                estacionar_veiculo(usuarioSelecionado);
                                break;
                            }
                            case 6: {  // Exibir Dados do Usuário
                                exibir_dados_usuario(usuarioSelecionado);
                                break;
                            }
                            case 7: {  // Adicionar Saldo
                                float valor;
                                printf("Digite o valor a ser adicionado ao saldo: ");
                                scanf("%f", &valor);
                                adicionar_saldo(usuarioSelecionado, valor);
                                break;
                            }
                            case 8: {  // Voltar ao Menu Principal
                                printf(YELLOW"Voltando ao menu principal...\n"RESET);
                                limpar_terminal();
                                break;
                            }
                            default: {  // Opção Inválida
                                printf(RED"Opcao invalida. Tente novamente.\n"RESET);
                            }
                        }
                    } while (subOpcao != 8);  // Continua até selecionar "Voltar ao Menu Principal"
                } else {
                    printf(RED"Usuario nao encontrado.\n"RESET);
                }
                break;
            }

            case 3:
                exibir_usuarios_cadastrados(usuarios);
                break;

            case 4:
                verificar_veiculos_estacionados(usuarios);
                break;

            case 5:
                verificar_caixa();
                break;

            case 6:
                alterar_plano_veiculo(usuarios);
                break;

            case 7: {  // Excluir Usuário
                if (usuarios == NULL) {
                    printf(YELLOW"Nenhum usuario cadastrado.\n"RESET);
                    break;
                }

                char cpf[12];
                printf("Digite o CPF do usuario para excluir: ");
                scanf(" %11[^\n]", cpf);

                remover_usuario(&usuarios, cpf,"dados_usuarios.txt");  // Chama a função de remoção
                if (usuarioSelecionado && strcmp(usuarioSelecionado->cpf, cpf) == 0) {
                    usuarioSelecionado = NULL; // Reseta a seleção para evitar erro
                    printf(YELLOW"O usuario selecionado foi excluido. Selecao removida.\n"RESET);
                }
                break;
            }

            case 8:
                printf(YELLOW"Saindo do sistema...\n"RESET);
                break;

            default:
                printf(RED"Opcao invalida. Tente novamente.\n"RESET);
        }
    } while (opcao != 8);

    // Salvar os dados no arquivo
    salvar_dados(usuarios, "dados_usuarios.txt");
    printf(GREEN"Dados salvos com sucesso.\n"RESET);

    // Libera a memoria alocada para os usuarios
    UsuarioNode* atual = usuarios;
    while (atual != NULL) {
        UsuarioNode* temp = atual;
        destruir_usuario(atual->usuario);
        atual = atual->proximo;
        free(temp);
    }

    return 0;
}

// Função para validar CPF
int validar_cpf(const char* cpf) {
    if (strlen(cpf) != 11) {
        return 0;
    }
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }
    return 1;
}

// Verifica se a placa está no formato "ABC-1234"
int validar_placa(const char *placa) {
    int i;
    if (strlen(placa) != 8) return 0; // Placa deve ter 8 caracteres (ABC-1234)
    for (i = 0; i < 3; i++) {
        if (!isalpha(placa[i])) return 0; // Três primeiros devem ser letras
    }
    if (placa[3] != '-') return 0; // Quarto caractere deve ser '-'
    for (i = 4; i < 8; i++) {
        if (!isdigit(placa[i])) return 0; // Últimos quatro devem ser números
    }
    return 1;
}

// Verifica se o tipo do veículo é válido (1, 2 ou 3)
int validar_tipo(int tipo) {
    return (tipo >= 1 && tipo <= 3);
}

// Verifica se o plano é válido (1, 2 ou 3)
int validar_plano(int plano) {
    return (plano >= 1 && plano <= 3);
}

// Verifica se a quantidade é válida (maior que zero)
int validar_quantidade(int quantidade) {
    return (quantidade > 0);
}