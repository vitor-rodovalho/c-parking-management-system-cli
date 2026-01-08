#include "usuario.h"
#include "pagamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definindo macros para as cores
#define RESET   "\033[0m"
#define RED     "\033[31m" // Erro
#define GREEN   "\033[32m" // Sucesso
#define YELLOW  "\033[33m" // Aviso


// Função auxiliar para remover a quebra de linha (\n) do final da string lida
void remover_quebra_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Função para carregar os dados dos usuários a partir de um arquivo
UsuarioNode* carregar_dados(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        // Se o arquivo não existir, não é um erro crítico na primeira execução
        return NULL;
    }

    UsuarioNode* lista = NULL;
    Usuario* usuarioAtual = NULL;
    Veiculo* veiculoAtual = NULL;
    char linha[256];
    char tempNome[100] = "";

    while (fgets(linha, sizeof(linha), arquivo)) {
        remover_quebra_linha(linha);

        // Verifica o prefixo da linha para saber o que fazer
        if (strncmp(linha, "Nome: ", 6) == 0) {
            // Guarda o nome temporariamente e espera o CPF para criar o usuário
            strcpy(tempNome, linha + 6);
        }
        else if (strncmp(linha, "CPF: ", 5) == 0) {
            // Cria o usuário com o nome guardado e o CPF atual
            usuarioAtual = criar_usuario(tempNome, linha + 5);
            lista = adicionar_usuario(lista, usuarioAtual);
            veiculoAtual = NULL; // Reseta o ponteiro de veículo
        }
        else if (strncmp(linha, "Saldo: ", 7) == 0 && usuarioAtual) {
            usuarioAtual->saldo = atof(linha + 7);
        }
        else if (strncmp(linha, "Placa: ", 7) == 0 && usuarioAtual) {
            // Inicia um novo veículo manualmente para ter controle total dos campos
            veiculoAtual = (Veiculo*)malloc(sizeof(Veiculo));
            strcpy(veiculoAtual->placa, linha + 7);
            veiculoAtual->proximo = usuarioAtual->listaVeiculos; // Insere na cabeça da lista
            usuarioAtual->listaVeiculos = veiculoAtual;
        }
        else if (strncmp(linha, "Tipo: ", 6) == 0 && veiculoAtual) {
            veiculoAtual->tipo = atoi(linha + 6);
        }
        else if (strncmp(linha, "Plano: ", 7) == 0 && veiculoAtual) {
            veiculoAtual->plano = atoi(linha + 7);
        }
        else if (strncmp(linha, "Quantidade: ", 12) == 0 && veiculoAtual) {
            veiculoAtual->quantidade = atoi(linha + 12);
        }
        else if (strncmp(linha, "Custo: ", 7) == 0 && veiculoAtual) {
            veiculoAtual->custo_total = atof(linha + 7);
        }
        else if (strncmp(linha, "Estacionado: ", 13) == 0 && veiculoAtual) {
            veiculoAtual->estacionado = atoi(linha + 13);
        }
    }

    fclose(arquivo);
    return lista;
}

// Função para criar um novo usuário
Usuario* criar_usuario(const char* nome, const char* cpf) {
    Usuario* usuario = (Usuario*)malloc(sizeof(Usuario));
    if (usuario) {
        strcpy(usuario->nome, nome);
        strcpy(usuario->cpf, cpf);
        usuario->saldo = 0.0f;
        usuario->listaVeiculos = NULL;
    } else {
        printf(RED"Erro ao alocar memoria para o usuario.\n"RESET);
    }
    return usuario;
}

// Função para adicionar um usuário à lista encadeada
UsuarioNode* adicionar_usuario(UsuarioNode* lista, Usuario* usuario) {
    UsuarioNode* novoNode = (UsuarioNode*)malloc(sizeof(UsuarioNode));
    novoNode->usuario = usuario;
    novoNode->proximo = lista;
    return novoNode;
}

// Função para buscar um usuário pelo CPF
Usuario* buscar_usuario(UsuarioNode* lista, const char* cpf) {
    UsuarioNode* atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->usuario->cpf, cpf) == 0) {
            return atual->usuario;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Função para adicionar saldo ao usuário
void adicionar_saldo(Usuario* usuario, float valor) {
    if (usuario != NULL && valor > 0) {
        usuario->saldo += valor;
        printf(GREEN"Saldo adicionado com sucesso! Novo saldo: %.2f\n"RESET, usuario->saldo);
    } else {
        printf(RED"Valor invalido para adicionar ao saldo.\n"RESET);
    }
}

// Função para adicionar um veículo à lista do usuário
void adicionar_veiculo(Usuario* usuario, const char* placa, int tipo, int plano, int quantidade) {
    Veiculo* novoVeiculo = criar_veiculo(placa, tipo, plano, usuario->cpf, quantidade);
    novoVeiculo->proximo = usuario->listaVeiculos;  // Insere o veículo no início da lista
    usuario->listaVeiculos = novoVeiculo;  // Atualiza a lista de veículos
}


// Função para buscar um veículo pelo CPF
Veiculo* buscar_veiculo(Usuario* usuario, const char* placa) {
    Veiculo* atual = usuario->listaVeiculos;
    while (atual) {
        if (strcmp(atual->placa, placa) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Função para listar os veículos cadastrados de um usuário
void listar_veiculos_usuario(const Usuario* usuario) {
    if (usuario == NULL) {
        printf(YELLOW"Nenhum usuario encontrado.\n"RESET);
        return;
    }
    Veiculo* atual = usuario->listaVeiculos;
    printf(GREEN"Veiculos cadastrados para o usuario %s (CPF: %s):\n"RESET, usuario->nome, usuario->cpf);
    while (atual) {
        printf("- Placa: %s, Tipo: %d, Plano: %d, Quantidade: %d, Custo Total: R$ %.2f, Estacionado: %s\n",
               atual->placa, atual->tipo, atual->plano, atual->quantidade,
               atual->custo_total, atual->estacionado ? "Sim" : "Nao");
        atual = atual->proximo;
    }
}

// Função para alterar o plano de um veículo
void alterar_plano_veiculo(UsuarioNode* usuarios) {
    char cpf[12], placa[10];
    printf("Digite o CPF do usuario: ");
    scanf(" %11[^\n]", cpf); // Limitando leitura para evitar buffer overflow

    // Busca o usuário pelo CPF
    Usuario* usuario = buscar_usuario(usuarios, cpf);
    if (!usuario) {
        printf(RED"Usuario nao encontrado.\n"RESET);
        return;
    }

    listar_veiculos_usuario(usuario);  // Lista os veículos do usuário
    printf("Digite a placa do veiculo para alterar o plano: ");
    scanf(" %9[^\n]", placa);

    Veiculo* veiculo = buscar_veiculo(usuario, placa);
    if (!veiculo) {
        printf(RED"Veiculo nao encontrado.\n"RESET);
        return;
    }

    if (veiculo->estacionado) {
        printf(YELLOW"O veiculo esta estacionado. Alteracao de plano nao permitida.\n"RESET);
        return;  // Impede alteração se o veículo estiver estacionado
    }

    int novoPlano;
    printf("Selecione o novo plano para o veiculo:\n");
    printf("1 - Diario\n2 - Mensal\n3 - Anual\n");
    scanf("%d", &novoPlano);

    if (novoPlano < PLANO_DIARIO || novoPlano > PLANO_ANUAL) {
        printf(RED"Plano invalido.\n"RESET);
        return;
    }

    // Atualiza o plano
    atualizar_plano(veiculo, novoPlano);

    // Agora, solicita a quantidade dependendo do plano
    int quantidade;
    printf("Digite a quantidade (horas, meses ou anos, conforme o plano): ");
    scanf("%d", &quantidade);

    veiculo->quantidade = quantidade;  // Atualiza a quantidade associada ao plano

    // Calcula o custo total baseado no tipo e quantidade
    veiculo->custo_total = calcular_valor_estacionamento(veiculo);

    printf(GREEN"Plano alterado com sucesso! Novo Custo Total: R$ %.2f\n"RESET, veiculo->custo_total);
}

// Função para retirar um veículo do estacionamento
void retirar_veiculo(Usuario* usuario, Veiculo* veiculo) {
    if (veiculo == NULL) {
        printf(YELLOW"Veiculo nao encontrado ou ja retirado do estacionamento.\n"RESET);
        return;
    }

    if (!veiculo->estacionado) {
        printf(YELLOW"O veiculo ja esta fora do estacionamento.\n"RESET);
        return;
    }

    atualizar_status(veiculo, 0);  // Atualiza o status do veículo
    printf(YELLOW"Veiculo com placa %s retirado do estacionamento.\n"RESET, veiculo->placa);
}

// Função para exibir os dados do usuário e seus veículos
void exibir_dados_usuario(const Usuario* usuario) {
    printf("Nome: %s\nCPF: %s\nSaldo: %.2f\n", usuario->nome, usuario->cpf, usuario->saldo);
    Veiculo* atual = usuario->listaVeiculos;
    while (atual) {
        printf("- Placa: %s, Tipo: %d, Plano: %d, Estacionado: %s\n",
               atual->placa, atual->tipo, atual->plano, atual->estacionado ? "Sim" : "Nao");
        atual = atual->proximo;
    }
}

// Função para remover um veículo do cadastro
void remover_veiculo(Usuario* usuario, Veiculo* veiculo) {
    Veiculo** veiculoAtual = &usuario->listaVeiculos;
    while (*veiculoAtual) {
        if (*veiculoAtual == veiculo) {
            *veiculoAtual = veiculo->proximo;
            free(veiculo);
            return;
        }
        veiculoAtual = &(*veiculoAtual)->proximo;
    }
    printf(RED"Veiculo nao encontrado.\n"RESET);
}

// Função para destruir o usuário e liberar a memória
void destruir_usuario(Usuario* usuario) {
    if (usuario) {
        Veiculo* atual = usuario->listaVeiculos;
        while (atual) {
            Veiculo* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        free(usuario);
    }
}

// Função para exibir os usuários cadastrados
void exibir_usuarios_cadastrados(const UsuarioNode* lista) {
    if (!lista) {
        printf(YELLOW"Nenhum usuario cadastrado.\n"RESET);
        return;
    }

    const UsuarioNode* atual = lista;
    while (atual != NULL) {
        printf("Nome: %s, CPF: %s\n", atual->usuario->nome, atual->usuario->cpf);
        atual = atual->proximo;
    }
}

// Função para verificar os veículos estacionados
void verificar_veiculos_estacionados(UsuarioNode* lista) {
    if (!lista) {
        printf(YELLOW"Nenhum usuario cadastrado.\n"RESET);
        return;
    }

    const UsuarioNode* atual = lista;
    while (atual != NULL) {
        printf("Veiculos estacionados do usuario %s:\n", atual->usuario->nome);
        Veiculo* veiculo = atual->usuario->listaVeiculos;
        while (veiculo) {
            if (veiculo->estacionado) {
                printf("- Placa: %s, Tipo: %d, Plano: %d, Quantidade: %d\n",
                    veiculo->placa, veiculo->tipo, veiculo->plano, veiculo->quantidade);
            }
            veiculo = veiculo->proximo;
        }
        atual = atual->proximo;
    }
}

// Função para remover o usuário da lista
void remover_usuario(UsuarioNode** lista, const char* cpf, const char* nomeArquivo) {
    UsuarioNode** atual = lista;
    while (*atual) {
        if (strcmp((*atual)->usuario->cpf, cpf) == 0) {
            UsuarioNode* temp = *atual;
            *atual = (*atual)->proximo;
            destruir_usuario(temp->usuario); // Libera memória do usuário
            free(temp);
            printf(GREEN"Usuario excluido com sucesso.\n"RESET);

            // Atualiza o arquivo após a remoção
            salvar_dados(*lista, nomeArquivo);
            return;
        }
        atual = &(*atual)->proximo;
    }
    printf(RED"Usuario nao encontrado.\n"RESET);
}


// Função para salvar os dados de todos os usuários em um arquivo
void salvar_dados(UsuarioNode* lista, const char* nomeArquivo) {
    if (lista == NULL) {
        // Se a lista estiver vazia, apenas cria o arquivo vazio ou apaga o anterior
        FILE* arquivo = fopen(nomeArquivo, "w");
        if (arquivo) fclose(arquivo);
        return;
    }

    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf(RED"Erro ao abrir o arquivo para escrita.\n"RESET);
        return;
    }

    UsuarioNode* atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "Nome: %s\n", atual->usuario->nome);
        fprintf(arquivo, "CPF: %s\n", atual->usuario->cpf);
        fprintf(arquivo, "Saldo: %.2f\n", atual->usuario->saldo);

        Veiculo* veiculo = atual->usuario->listaVeiculos;
        while (veiculo != NULL) {
            fprintf(arquivo, "Placa: %s\n", veiculo->placa);
            fprintf(arquivo, "Tipo: %d\n", veiculo->tipo);
            fprintf(arquivo, "Plano: %d\n", veiculo->plano);
            // Novos campos essenciais adicionados:
            fprintf(arquivo, "Quantidade: %d\n", veiculo->quantidade);
            fprintf(arquivo, "Custo: %.2f\n", veiculo->custo_total);
            fprintf(arquivo, "Estacionado: %d\n", veiculo->estacionado);
            fprintf(arquivo, "###\n"); // Separador visual (opcional, mas bom para leitura humana)
            veiculo = veiculo->proximo;
        }
        atual = atual->proximo;
    }

    fclose(arquivo);
    // Removido o print de sucesso aqui para não poluir o terminal na saída do programa
}
