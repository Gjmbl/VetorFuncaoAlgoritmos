#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char *nome;
    char *email;
    char sexo;
    char *endereco;
    float altura;
    int tomouVacina;
    int id;
} Usuario;

typedef struct No {
    Usuario usuario;
    struct No *proximo;
} No;

No* criarNo(Usuario usuario) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->usuario = usuario;
    novoNo->proximo = NULL;
    return novoNo;
}

int gerarID() {
    srand(time(NULL));
    return rand();
}

void inserirUsuario(No **lista, Usuario usuario) {
    No *novoNo = criarNo(usuario);
    
    if (*lista == NULL) {
        *lista = novoNo;
    } else {
        No *atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
}

Usuario* buscarUsuario(No *lista, const char *email) {
    No *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->usuario.email, email) == 0) {
            return &(atual->usuario);
        }
        atual = atual->proximo;
    }
    return NULL;
}

void excluirUsuario(No **lista, const char *email) {
    No *anterior = NULL;
    No *atual = *lista;
    
    while (atual != NULL) {
        if (strcmp(atual->usuario.email, email) == 0) {
            if (anterior == NULL) {
                *lista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual->usuario.nome);
            free(atual->usuario.email);
            free(atual->usuario.endereco);
            free(atual);
            printf("Usuario excluido com sucesso.\n");
            return;
        }
        
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("Usuario nao encontrado.\n");
}

void imprimirUsuarios(No *lista) {
    No *atual = lista;
    
    while (atual != NULL) {
        printf("\nInformacoes do usuario:\n");
        printf("ID: %d\n", atual->usuario.id);
        printf("Nome: %s\n", atual->usuario.nome);
        printf("Email: %s\n", atual->usuario.email);
        printf("Sexo: %c\n", atual->usuario.sexo);
        printf("Endereco: %s\n", atual->usuario.endereco);
        printf("Altura: %.2f\n", atual->usuario.altura);
        
        if (atual->usuario.tomouVacina == 1) {
            printf("Tomou vacina: Sim\n");
        } else if (atual->usuario.tomouVacina == 2) {
            printf("Tomou vacina: Nao\n");
        } else {
            printf("Tomou vacina: Nao informado\n");
        }
        
        atual = atual->proximo;
    }
}

void liberarLista(No **lista) {
    No *atual = *lista;
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual->usuario.nome);
        free(atual->usuario.email);
        free(atual->usuario.endereco);
        free(atual);
        atual = proximo;
    }
    *lista = NULL;
}

int main() {
    No *lista = NULL;
    int opcao;
    
    do {
        printf("\nMenu:\n");
        printf("1. Inserir usuario\n");
        printf("2. Buscar usuario por email\n");
        printf("3. Excluir usuario por email\n");
        printf("4. Imprimir todos os usuarios\n");
        printf("5. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: {
                Usuario novoUsuario;
                printf("Nome: ");
                char nomeTemp[50];
                scanf(" %[^\n]s", nomeTemp);
                novoUsuario.nome = (char*)malloc((strlen(nomeTemp) + 1) * sizeof(char));
                strcpy(novoUsuario.nome, nomeTemp);
                
                printf("Email: ");
                char emailTemp[50];
                scanf(" %[^\n]s", emailTemp);
                novoUsuario.email = (char*)malloc((strlen(emailTemp) + 1) * sizeof(char));
                strcpy(novoUsuario.email, emailTemp);
                
                printf("Sexo (M/F): ");
                scanf(" %c", &novoUsuario.sexo);
                
                printf("Endereco: ");
                char enderecoTemp[100];
                scanf(" %[^\n]s", enderecoTemp);
                novoUsuario.endereco = (char*)malloc((strlen(enderecoTemp) + 1) * sizeof(char));
                strcpy(novoUsuario.endereco, enderecoTemp);
                
                printf("Altura: ");
                scanf("%f", &novoUsuario.altura);
                
                printf("Tomou vacina? (1 - Sim / 2 - Nao): ");
                scanf("%d", &novoUsuario.tomouVacina);
                
                novoUsuario.id = gerarID();
                
                inserirUsuario(&lista, novoUsuario);
                printf("Usuario inserido com sucesso.\n");
                break;
            }
            case 2: {
                char emailBusca[50];
                printf("Email para busca: ");
                scanf(" %[^\n]s", emailBusca);
                Usuario *usuarioEncontrado = buscarUsuario(lista, emailBusca);
                if (usuarioEncontrado != NULL) {
                    printf("\nInformacoes do usuario:\n");
                    printf("ID: %d\n", usuarioEncontrado->id);
                    printf("Nome: %s\n", usuarioEncontrado->nome);
                    printf("Email: %s\n", usuarioEncontrado->email);
                    printf("Sexo: %c\n", usuarioEncontrado->sexo);
                    printf("Endereco: %s\n", usuarioEncontrado->endereco);
                    printf("Altura: %.2f\n", usuarioEncontrado->altura);
                    if (usuarioEncontrado->tomouVacina == 1) {
                        printf("Tomou vacina: Sim\n");
                    } else if (usuarioEncontrado->tomouVacina == 2) {
                        printf("Tomou vacina: Nao\n");
                    } else {
                        printf("Tomou vacina: Nao informado\n");
                    }
                } else {
                    printf("Usuario nao encontrado.\n");
                }
                break;
            }
            case 3: {
                char emailExclusao[50];
                printf("Email para exclusao: ");
                scanf(" %[^\n]s", emailExclusao);
                excluirUsuario(&lista, emailExclusao);
                break;
            }
            case 4: {
                printf("\nTodos os usuarios:\n");
                imprimirUsuarios(lista);
                break;
            }
            case 5:
                printf("Encerrando o programa.\n");
                liberarLista(&lista);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);
    
    return 0;
}
