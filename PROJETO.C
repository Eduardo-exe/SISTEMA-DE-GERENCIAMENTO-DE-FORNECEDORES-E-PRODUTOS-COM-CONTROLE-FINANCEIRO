#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_FORNECEDORES 100
#define MAX_PRODUTOS 100
#define TAM_NOME 50
#define TAM_CATEGORIA 50
#define TAM_DATA 11
#define ARQUIVO_FORNECEDORES "fornecedores.csv"
#define ARQUIVO_PRODUTOS "produtos.csv"

typedef struct {
    int id;
    char nome[TAM_NOME];
    char telefone[15];
    char email[50];
    char dataInclusao[TAM_DATA];
} Fornecedor;

typedef struct {
    int id;
    char nome[TAM_NOME];
    int quantidade;
    float preco;
    float precoVenda;
    char categoria[TAM_CATEGORIA];
    char dataInclusao[TAM_DATA];
} Produto;

Fornecedor fornecedores[MAX_FORNECEDORES];
Produto produtos[MAX_PRODUTOS];
int contadorFornecedores = 0;
int contadorProdutos = 0;

// Protótipos de funções
void carregarFornecedores();
void salvarFornecedores();
void incluirFornecedor();
void buscarFornecedor();
void alterarFornecedor();
void excluirFornecedor();
void carregarProdutos();
void salvarProdutos();
void incluirProduto();
void buscarProduto();
void alterarProduto();
void excluirProduto();
void menuFornecedores();
void menuProdutos();
void menuGerenciamentoFinanceiro();
void obterDataAtual(char *data);
void abrirDadosNoExcel(const char *arquivo);
void calcularMargemLucro();

void incluirFornecedor() {
    if (contadorFornecedores < MAX_FORNECEDORES) {
        Fornecedor novo;
        novo.id = rand();
        printf("ID do novo fornecedor: %d\n", novo.id);

        printf("Nome: ");
        getchar();
        fgets(novo.nome, TAM_NOME, stdin);
        novo.nome[strcspn(novo.nome, "\n")] = '\0';

        printf("Telefone: ");
        fgets(novo.telefone, 15, stdin);
        novo.telefone[strcspn(novo.telefone, "\n")] = '\0';

        printf("Email: ");
        fgets(novo.email, 50, stdin);
        novo.email[strcspn(novo.email, "\n")] = '\0';

        printf("Data de inclusao (DD/MM/AAAA): ");
        fgets(novo.dataInclusao, TAM_DATA, stdin);
        novo.dataInclusao[strcspn(novo.dataInclusao, "\n")] = '\0';

        fornecedores[contadorFornecedores++] = novo;
        salvarFornecedores();
        printf("Fornecedor incluído com sucesso!\n");
    } else {
        printf("Limite de fornecedores atingido!\n");
    }
}

void buscarFornecedor() {
    char nome[TAM_NOME];
    printf("Nome do fornecedor para busca: ");
    getchar();
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < contadorFornecedores; i++) {
        if (strcmp(fornecedores[i].nome, nome) == 0) {
            printf("Fornecedor encontrado:\n");
            printf("ID: %d\n", fornecedores[i].id);
            printf("Nome: %s\n", fornecedores[i].nome);
            printf("Telefone: %s\n", fornecedores[i].telefone);
            printf("Email: %s\n", fornecedores[i].email);
            printf("Data de Inclusao: %s\n", fornecedores[i].dataInclusao);
            return;
        }
    }
    printf("Fornecedor não encontrado.\n");
}

void alterarFornecedor() {
    char nome[TAM_NOME];
    printf("Nome do fornecedor para alteracao: ");
    getchar();
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < contadorFornecedores; i++) {
        if (strcmp(fornecedores[i].nome, nome) == 0) {
            printf("Fornecedor encontrado:\n");
            printf("ID: %d\n", fornecedores[i].id);
            printf("Nome atual: %s\n", fornecedores[i].nome);
            printf("Telefone atual: %s\n", fornecedores[i].telefone);
            printf("Email atual: %s\n", fornecedores[i].email);
            printf("Data de Inclusao atual: %s\n", fornecedores[i].dataInclusao);

            printf("\nDigite os novos dados (pressione Enter para manter o atual):\n");

            printf("Novo nome: ");
            char novoNome[TAM_NOME];
            fgets(novoNome, TAM_NOME, stdin);
            if (novoNome[0] != '\n') {
                novoNome[strcspn(novoNome, "\n")] = '\0';
                strcpy(fornecedores[i].nome, novoNome);
            }

            printf("Novo telefone: ");
            char novoTelefone[15];
            fgets(novoTelefone, 15, stdin);
            if (novoTelefone[0] != '\n') {
                novoTelefone[strcspn(novoTelefone, "\n")] = '\0';
                strcpy(fornecedores[i].telefone, novoTelefone);
            }

            printf("Novo email: ");
            char novoEmail[50];
            fgets(novoEmail, 50, stdin);
            if (novoEmail[0] != '\n') {
                novoEmail[strcspn(novoEmail, "\n")] = '\0';
                strcpy(fornecedores[i].email, novoEmail);
            }

            printf("Nova data de inclusao (DD/MM/AAAA): ");
            char novaDataInclusao[TAM_DATA];
            fgets(novaDataInclusao, TAM_DATA, stdin);
            if (novaDataInclusao[0] != '\n') {
                novaDataInclusao[strcspn(novaDataInclusao, "\n")] = '\0';
                strcpy(fornecedores[i].dataInclusao, novaDataInclusao);
            }

            salvarFornecedores();
            printf("Fornecedor alterado com sucesso!\n");
            return;
        }
    }
    printf("Fornecedor não encontrado.\n");
}

void excluirFornecedor() {
    char nome[TAM_NOME];
    printf("Nome do fornecedor para exclusao: ");
    getchar();
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < contadorFornecedores; i++) {
        if (strcmp(fornecedores[i].nome, nome) == 0) {
            for (int j = i; j < contadorFornecedores - 1; j++) {
                fornecedores[j] = fornecedores[j + 1];
            }
            contadorFornecedores--;
            salvarFornecedores();
            printf("Fornecedor excluido com sucesso!\n");
            return;
        }
    }
    printf("Fornecedor nao encontrado.\n");
}

void incluirProduto() {
    if (contadorProdutos < MAX_PRODUTOS) {
        Produto novo;
        novo.id = rand();
        printf("ID do novo produto: %d\n", novo.id);

        printf("Nome do produto: ");
        getchar();
        fgets(novo.nome, TAM_NOME, stdin);
        novo.nome[strcspn(novo.nome, "\n")] = '\0';

        printf("Quantidade: ");
        scanf("%d", &novo.quantidade);

        printf("Preco de compra: ");
        scanf("%f", &novo.preco);

        printf("Preco de venda: ");  // Novo campo
        scanf("%f", &novo.precoVenda);

        printf("Categoria do produto: ");
        getchar();
        fgets(novo.categoria, TAM_CATEGORIA, stdin);
        novo.categoria[strcspn(novo.categoria, "\n")] = '\0';

        printf("Data de inclusao (DD/MM/AAAA): ");
        fgets(novo.dataInclusao, TAM_DATA, stdin);
        novo.dataInclusao[strcspn(novo.dataInclusao, "\n")] = '\0';

        produtos[contadorProdutos++] = novo;
        salvarProdutos();
        printf("Produto incluído com sucesso!\n");
    } else {
        printf("Limite de produtos atingido!\n");
    }
}

void buscarProduto() {
    char nome[TAM_NOME];
    printf("Nome do produto para busca: ");
    getchar();
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int produtosEncontrados = 0;

    for (int i = 0; i < contadorProdutos; i++) {
        if (strcmp(produtos[i].nome, nome) == 0) {
            printf("Produto encontrado:\n");
            printf("ID: %d\n", produtos[i].id);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Preco de compra: %.2f\n", produtos[i].preco);
            printf("Preco de venda: %.2f\n", produtos[i].precoVenda);
            printf("Categoria: %s\n", produtos[i].categoria);
            printf("Data de Inclusao: %s\n", produtos[i].dataInclusao);
            produtosEncontrados++;
        }
    }

    if (produtosEncontrados == 0) {
        printf("Produto nao encontrado.\n");
    }
}

void alterarProduto() {
    char nome[TAM_NOME];
    printf("Nome do produto para alteracao: ");
    getchar();
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < contadorProdutos; i++) {
        if (strcmp(produtos[i].nome, nome) == 0) {
            printf("Produto encontrado:\n");
            printf("ID: %d\n", produtos[i].id);
            printf("Nome atual: %s\n", produtos[i].nome);
            printf("Quantidade atual: %d\n", produtos[i].quantidade);
            printf("Preco de compra atual: %.2f\n", produtos[i].preco);
            printf("Preco de venda atual: %.2f\n", produtos[i].precoVenda);
            printf("Categoria atual: %s\n", produtos[i].categoria);
            printf("Data de Inclusao atual: %s\n", produtos[i].dataInclusao);

            printf("\nDigite os novos dados (pressione Enter para manter o atual):\n");

            printf("Novo nome: ");
            char novoNome[TAM_NOME];
            fgets(novoNome, TAM_NOME, stdin);
            if (novoNome[0] != '\n') {
                novoNome[strcspn(novoNome, "\n")] = '\0';
                strcpy(produtos[i].nome, novoNome);
            }

            printf("Nova quantidade: ");
            char quantidadeStr[10];
            fgets(quantidadeStr, 10, stdin);
            if (quantidadeStr[0] != '\n') {
                produtos[i].quantidade = atoi(quantidadeStr);
            }

            printf("Novo preco de compra: ");
            char precoStr[20];
            fgets(precoStr, 20, stdin);
            if (precoStr[0] != '\n') {
                produtos[i].preco = atof(precoStr);
            }

            printf("Novo preco de venda: ");
            char precoVendaStr[20];
            fgets(precoVendaStr, 20, stdin);
            if (precoVendaStr[0] != '\n') {
                produtos[i].precoVenda = atof(precoVendaStr);
            }

            printf("Nova categoria: ");
            char novaCategoria[TAM_CATEGORIA];
            fgets(novaCategoria, TAM_CATEGORIA, stdin);
            if (novaCategoria[0] != '\n') {
                novaCategoria[strcspn(novaCategoria, "\n")] = '\0';
                strcpy(produtos[i].categoria, novaCategoria);
            }

            printf("Nova data de inclusao (DD/MM/AAAA): ");
            char novaDataInclusao[TAM_DATA];
            fgets(novaDataInclusao, TAM_DATA, stdin);
            if (novaDataInclusao[0] != '\n') {
                novaDataInclusao[strcspn(novaDataInclusao, "\n")] = '\0';
                strcpy(produtos[i].dataInclusao, novaDataInclusao);
            }

            salvarProdutos();
            printf("Produto alterado com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}


void excluirProduto() {
    char nome[TAM_NOME];
    printf("Nome do produto para exclusao: ");
    getchar();
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < contadorProdutos; i++) {
        if (strcmp(produtos[i].nome, nome) == 0) {
            for (int j = i; j < contadorProdutos - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            contadorProdutos--;
            salvarProdutos();
            printf("Produto excluido com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

void calcularMargemLucro() {
    char categoria[TAM_CATEGORIA];
    int quantidadeVendida;
    float valorCompraTotal = 0.0;
    float valorVendaTotal = 0.0;
    float lucroTotal = 0.0;
    float percentualLucro = 0.0;

    printf("Categoria do produto: ");
    getchar();
    fgets(categoria, TAM_CATEGORIA, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    printf("Quantidade vendida: ");
    scanf("%d", &quantidadeVendida);

    for (int i = 0; i < contadorProdutos; i++) {
        if (strcmp(produtos[i].categoria, categoria) == 0) {
            int quantidadeConsiderada = (quantidadeVendida <= produtos[i].quantidade) ? quantidadeVendida : produtos[i].quantidade;
            float valorCompraProduto = produtos[i].preco * quantidadeConsiderada;
            float valorVendaProduto = produtos[i].precoVenda * quantidadeConsiderada;
            float lucroProduto = valorVendaProduto - valorCompraProduto;
            
            valorCompraTotal += valorCompraProduto;
            valorVendaTotal += valorVendaProduto;
            lucroTotal += lucroProduto;

            quantidadeVendida -= quantidadeConsiderada;
            if (quantidadeVendida <= 0) {
                break;
            }
        }
    }

    if (valorCompraTotal > 0) {
        percentualLucro = (lucroTotal / valorCompraTotal) * 100;
    }

    printf("Categoria: %s\n", categoria);
    printf("Valor total de compra: %.2f\n", valorCompraTotal);
    printf("Valor total de venda: %.2f\n", valorVendaTotal);
    printf("Lucro total: %.2f\n", lucroTotal);
    printf("Margem de lucro: %.2f%%\n", percentualLucro);

    // Salvar os dados em um arquivo CSV
    FILE *arquivo = fopen("margem_lucro.csv", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de margem de lucro para escrita.\n");
        return;
    }
    // Obter data atual
    char dataAtual[TAM_DATA];
    obterDataAtual(dataAtual);
    
    fprintf(arquivo, "%s;%s;%.2f;%.2f;%.2f;%.2f\n", dataAtual, categoria, valorCompraTotal, valorVendaTotal, lucroTotal, percentualLucro);
    fclose(arquivo);
}


void iniciarArquivoMargemLucro() {
    FILE *arquivo = fopen("margem_lucro.csv", "r");
    if (arquivo == NULL) {
        arquivo = fopen("margem_lucro.csv", "w");
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo de margem de lucro.\n");
            return;
        }
        fprintf(arquivo, "Data;Categoria;ValorCompraTotal;ValorVendaTotal;LucroTotal;PercentualLucro\n");
    }
    fclose(arquivo);
}



void carregarFornecedores() {
    FILE *arquivo = fopen(ARQUIVO_FORNECEDORES, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de fornecedores");
        return;
    }

    contadorFornecedores = 0;
    // Ignorar a primeira linha (cabeçalho)
    char linha[200];
    fgets(linha, sizeof(linha), arquivo);
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d;%[^;];%[^;];%[^;];%s\n", &fornecedores[contadorFornecedores].id,
               fornecedores[contadorFornecedores].nome, fornecedores[contadorFornecedores].telefone,
               fornecedores[contadorFornecedores].email, fornecedores[contadorFornecedores].dataInclusao);
        contadorFornecedores++;
    }

    fclose(arquivo);
    printf("Fornecedores carregados com sucesso!\n");
}

void salvarFornecedores() {
    FILE *arquivo = fopen(ARQUIVO_FORNECEDORES, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de fornecedores para escrita.\n");
        return;
    }

    fprintf(arquivo, "ID;Nome;Telefone;Email;DataInclusao\n");
    for (int i = 0; i < contadorFornecedores; i++) {
        fprintf(arquivo, "%d;%s;%s;%s;%s\n", fornecedores[i].id, fornecedores[i].nome,
                fornecedores[i].telefone, fornecedores[i].email, fornecedores[i].dataInclusao);
    }

    fclose(arquivo);
}

void carregarProdutos() {
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
    if (arquivo == NULL) return;

    contadorProdutos = 0;
    // Ignorar a primeira linha (cabeçalho)
    char linha[200];
    fgets(linha, sizeof(linha), arquivo);
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d;%[^;];%d;%f;%f;%[^;];%s\n", &produtos[contadorProdutos].id,
               produtos[contadorProdutos].nome, &produtos[contadorProdutos].quantidade,
               &produtos[contadorProdutos].preco, &produtos[contadorProdutos].precoVenda,
               produtos[contadorProdutos].categoria, produtos[contadorProdutos].dataInclusao);
        contadorProdutos++;
    }

    fclose(arquivo);
}


void salvarProdutos() {
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de produtos para escrita.\n");
        return;
    }

    fprintf(arquivo, "ID;Nome;Quantidade;PrecoCompra;PrecoVenda;Categoria;DataInclusao\n");
    for (int i = 0; i < contadorProdutos; i++) {
        fprintf(arquivo, "%d;%s;%d;%.2f;%.2f;%s;%s\n", produtos[i].id, produtos[i].nome,
                produtos[i].quantidade, produtos[i].preco, produtos[i].precoVenda,
                produtos[i].categoria, produtos[i].dataInclusao);
    }

    fclose(arquivo);
}


void obterDataAtual(char *data) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void abrirDadosNoExcel(const char *arquivo) {
    char comando[100];
    sprintf(comando, "start excel.exe %s", arquivo);
    system(comando);
}

void menuFornecedores() {
    int opcao;
    do {
        printf("\n=== Menu de Fornecedores ===\n");
        printf("1. Incluir fornecedor\n");
        printf("2. Buscar fornecedor\n");
        printf("3. Alterar fornecedor\n");
        printf("4. Excluir fornecedor\n");
        printf("5. Abrir fornecedores no Excel\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirFornecedor();
                break;
            case 2:
                buscarFornecedor();
                break;
            case 3:
                alterarFornecedor();
                break;
            case 4:
                excluirFornecedor();
                break;
            case 5:
                abrirDadosNoExcel(ARQUIVO_FORNECEDORES);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menuProdutos() {
    int opcao;
    do {
        printf("\n=== Menu de Produtos ===\n");
        printf("1. Incluir produto\n");
        printf("2. Buscar produto\n");
        printf("3. Alterar produto\n");
        printf("4. Excluir produto\n");
        printf("5. Abrir produtos no Excel\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirProduto();
                break;
            case 2:
                buscarProduto();
                break;
            case 3:
                alterarProduto();
                break;
            case 4:
                excluirProduto();
                break;
            case 5:
                abrirDadosNoExcel(ARQUIVO_PRODUTOS);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void gerarGraficoMargemLucro(const char *mesAno) {
    char comando[256];
    sprintf(comando, "python gerar_grafico.py %s", mesAno);
    system(comando);
}

void abrirDadosMargemLucroNoExcel() {
    abrirDadosNoExcel("margem_lucro.csv");
}

void menuGerenciamentoFinanceiro() {
    int opcao;
    char mesAno[8]; 

    do {
        printf("\n=== Gerenciamento Financeiro ===\n");
        printf("1. Calcular margem de lucro\n");
        printf("2. Gerar gráfico de margem de lucro\n");
        printf("3. Abrir Margem de lucro no Excel\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                calcularMargemLucro();
                break;
            case 2:
                printf("Digite o mes e ano (MM/AAAA): ");
                scanf("%s", mesAno);
                gerarGraficoMargemLucro(mesAno);
                break;
            case 3:
                abrirDadosMargemLucroNoExcel();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    iniciarArquivoMargemLucro();
    carregarFornecedores();
    carregarProdutos();

    int opcao;
    do {
        printf("\n=== Sistema de Gerenciamento ===\n");
        printf("1. Gerenciamento de fornecedores\n");
        printf("2. Gerenciamento de produtos\n");
        printf("3. Gerenciamento Financeiro\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuFornecedores();
                break;
            case 2:
                menuProdutos();
                break;
            case 3:
                menuGerenciamentoFinanceiro();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
