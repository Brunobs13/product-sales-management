#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_VENDAS 1000

typedef struct {
    int codigo;
    char designacao[50];
    float preco;
    int quantidade_vendida;
} Produto;

typedef struct {
    int codigo_produto;
    int quantidade;
    char data[11];
} Venda;

Produto produtos[MAX_PRODUTOS];
int num_produtos = 0;

Venda vendas[MAX_VENDAS];
int num_vendas = 0;

void ler_produtos(char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        exit(1);
    }

    char linha[100];
    while (fgets(linha, 100, arquivo) != NULL) {
        Produto p;
        sscanf(linha, "%d,%[^,],%f", &p.codigo, p.designacao, &p.preco);
        p.quantidade_vendida = 0;
        produtos[num_produtos++] = p;
    }

    fclose(arquivo);
}

void ler_vendas(char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        exit(1);
    }

    char linha[100];
    while (fgets(linha, 100, arquivo) != NULL) {
        Venda v;
        sscanf(linha, "%d,%d,%s", &v.codigo_produto, &v.quantidade, v.data);
        vendas[num_vendas++] = v;

        for (int i = 0; i < num_produtos; i++) {
            if (produtos[i].codigo == v.codigo_produto) {
                produtos[i].quantidade_vendida += v.quantidade;
                break;
            }
        }
    }

    fclose(arquivo);
}

void adicionar_produto() {
    Produto p;
    printf("Código: ");
    scanf("%d", &p.codigo);
    printf("Designação: ");
    scanf("%s", p.designacao);
    printf("Preço: ");
    scanf("%f", &p.preco);
    p.quantidade_vendida = 0;
    produtos[num_produtos++] = p;
}

void remover_produto(int codigo) {
    for (int i = 0; i < num_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            for (int j = i; j < num_produtos - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            num_produtos--;
            break;
        }
    }
}

void editar_produto(int codigo) {
    for (int i = 0; i < num_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Novo código: ");
            scanf("%d", &produtos[i].codigo);
            printf("Nova designação: ");
            scanf("%s", produtos[i].designacao);
            printf("Novo preço: ");
            scanf("%f", &produtos[i].preco);
            break;
        }
    }
}

void gerar_relatorio() {
    float total_vendas = 0;
    float total_arrecadado = 0;

    printf("\nRelatório de Vendas\n");
    printf("-------------------\n");
    for (int i = 0; i < num_produtos; i++) {
        printf("%d - %s - %d\n", produtos[i].codigo, produtos[i].designacao, produtos[i].quantidade_vendida);
        total_vendas += produtos[i].quantidade_vendida;
        total_arrecadado += produtos[i].quantidade_vendida * produtos[i].preco;
    }
    
    printf("\nTotal de vendas: %.0f\n", total_vendas);
    printf("Total arrecadado: %.2f\n", total_arrecadado);
}

int main() {
    ler_produtos("products.csv");
    ler_vendas("sales.csv");
    
    int opcao;
    do {
        printf("\nMenu\n");
        printf("----\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Remover produto\n");
        printf("3 - Editar produto\n");
        printf("4 - Gerar relatório de vendas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                adicionar_produto();
                break;
            case 2:
                printf("Código do produto a remover: ");
                int codigo;
                scanf("%d", &codigo);
                remover_produto(codigo);
                break;
            case 3:
                printf("Código do produto a editar: ");
                scanf("%d", &codigo);
                editar_produto(codigo);
                break;
            case 4:
                gerar_relatorio();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}