#include <stdio.h>
#include <string.h>

#define MAX 50

// Estrutura para armazenar contato
struct Contato {
    char nome[50];
    char telefone[20];
    char email[50];
};

// Funções
void adicionarContato(struct Contato contatos[], int *total);
void listarContatos(struct Contato contatos[], int total);
void buscarContato(struct Contato contatos[], int total);
void removerContato(struct Contato contatos[], int *total);

// Função principal
int main() {
    struct Contato contatos[MAX];
    int total = 0;
    int opcao;

    do {
        printf("\n=== AGENDA DE CONTATOS ===\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Listar contatos\n");
        printf("3 - Buscar contato\n");
        printf("4 - Remover contato\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                adicionarContato(contatos, &total);
                break;
            case 2:
                listarContatos(contatos, total);
                break;
            case 3:
                buscarContato(contatos, total);
                break;
            case 4:
                removerContato(contatos, &total);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// Função para adicionar contato
void adicionarContato(struct Contato contatos[], int *total) {
    if (*total >= MAX) {
        printf("Agenda cheia! Não é possível adicionar mais contatos.\n");
        return;
    }

    printf("\n=== ADICIONAR CONTATO ===\n");
    printf("Nome: ");
    fgets(contatos[*total].nome, 50, stdin);
    contatos[*total].nome[strcspn(contatos[*total].nome, "\n")] = 0;

    printf("Telefone: ");
    fgets(contatos[*total].telefone, 20, stdin);
    contatos[*total].telefone[strcspn(contatos[*total].telefone, "\n")] = 0;

    printf("Email: ");
    fgets(contatos[*total].email, 50, stdin);
    contatos[*total].email[strcspn(contatos[*total].email, "\n")] = 0;

    // Validação simples
    if (strlen(contatos[*total].nome) == 0) {
        printf("Erro: Nome não pode ser vazio!\n");
        return;
    }
    if (strchr(contatos[*total].email, '@') == NULL) {
        printf("Erro: Email inválido!\n");
        return;
    }

    (*total)++;
    printf("Contato adicionado com sucesso!\n");
}

// Função para listar contatos
void listarContatos(struct Contato contatos[], int total) {
    printf("\n=== LISTA DE CONTATOS ===\n");

    if (total == 0) {
        printf("Nenhum contato cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d | Nome: %s | Tel: %s | Email: %s\n",
            i + 1,
            contatos[i].nome,
            contatos[i].telefone,
            contatos[i].email
        );
    }
}

// Função para buscar por nome
void buscarContato(struct Contato contatos[], int total) {
    char busca[50];
    int encontrado = 0;

    printf("\nDigite o nome que deseja buscar: ");
    fgets(busca, 50, stdin);
    busca[strcspn(busca, "\n")] = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(busca, contatos[i].nome) == 0) {
            printf("Contato encontrado!\n");
            printf("Nome: %s\nTelefone: %s\nEmail: %s\n",
                   contatos[i].nome, contatos[i].telefone, contatos[i].email);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Contato não encontrado!\n");
    }
}

// Função para remover contato
void removerContato(struct Contato contatos[], int *total) {
    int indice;

    listarContatos(contatos, *total);

    if (*total == 0) return;

    printf("\nDigite o número do contato que deseja remover: ");
    scanf("%d", &indice);
    getchar();

    if (indice < 1 || indice > *total) {
        printf("Contato inválido!\n");
        return;
    }

    indice--;

    for (int i = indice; i < *total - 1; i++) {
        contatos[i] = contatos[i + 1];
    }

    (*total)--;
    printf("Contato removido com sucesso!\n");
}