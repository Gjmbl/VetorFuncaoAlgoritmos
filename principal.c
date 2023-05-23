#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define USERS_MAX 1000

// Declarando vetores globais principais de atributos
int id[USERS_MAX];
char nome[USERS_MAX][256];
char email[USERS_MAX][256];
char genero[USERS_MAX][32];
char endereco[USERS_MAX][256];
double altura[USERS_MAX];
int vacinado[USERS_MAX];

void main(){
    // Habilitar acentuação
    setlocale(LC_ALL,"");

    printf("----~ Tarefa Vetores e Funções ~----\n");

    // Main loop
    char escolha;
    int ml_flag = 1, invalid_flag;

    while(ml_flag == 1){
        printf("Escolha uma das opções abaixo:\n");
        printf("(0) Finalizar Programa\n");
        printf("(1) Adicionar Usuário\n");
        printf("(2) Excluir Usuário\n");
        printf("(3) Editar Usuário\n");
        printf("(4) Buscar Usuário por e-mail\n");
        printf("(5) Imprimir Todos os Usuários Cadastrados\n");
        printf("(6) Criar Backup dos Usuários\n");
        printf("(7) Restaurar Backup\n> ");
        do{
            invalid_flag = 0;
            scanf(" %c", &escolha);
            switch(escolha){
            case '0':
                printf("Encerrando programa!");
                ml_flag = 0;
                break;
            case '1':
                adicionarUsuario();
                break;
            case '2':
                editarUsuario();
                break;
            case '3':
                removerUsuario();
                break;
            case '4':
                buscarUsuario();
                break;
            case '5':
                imprimirUsuarios();
                break;
            case '6':
                fazerBackup();
                break;
            case '7':
                restaurarBackup();
                break;
            default:
                invalid_flag = 1;
                printf("Escolha Inválida\n> ");
                break;
            }
        }while(invalid_flag == 1);
    }
}

// Funções Principais
void adicionarUsuario(){
    printf(">>> Adicionando Usuário <<<\n");
    float altra;
    int vacinacao;
    getchar();
    for(int i=0; i<3; i++){
        printf("\n");
        id[i] = gerarID();
        printf("O ID do usuario %d é: %d\n", i, id[i]);
        
        printf("Digite o nome do usuario %d: ",i);
        fgets(nome[i], 100, stdin);
        nome[i][strcspn(nome[i], "\n")] = '\0';

        printf("Digite o email do usuario %d: ",i);
        fgets(email[i], 100, stdin);
        email[i][strcspn(email[i], "\n")] = '\0';
        while(strchr(email[i],'@') == NULL){
            printf("E-mail não é válido, digite um e-mail válido: ");
            fgets(email[i], 100, stdin);
            email[i][strcspn(email[i], "\n")] = '\0';
        }

        printf("Digite o gênero do usuario %d: ",i);
        fgets(genero[i], 100, stdin);
        genero[i][strcspn(genero[i], "\n")] = '\0';
        while(strcmp(genero[i],"feminino")!=0 && strcmp(genero[i],"masculino")!=0 && strcmp(genero[i],"indiferente")!=0){
            printf("Você digitou errado! Digite (feminino, masculino ou indiferente): ",i);
            fgets(genero[i], 100, stdin);
            genero[i][strcspn(genero[i], "\n")] = '\0';
        }

        printf("Digite o endereço do usuario %d: ",i);
        fgets(endereco[i], 100, stdin);
        endereco[i][strcspn(endereco[i], "\n")] = '\0';
        
        printf("Digite a altura do usuario %d: ",i);
        scanf("%f",&altra);
        while (altra < 1 || altra > 2){
            printf("Digite um valor entre 1 e 2 metros: ");
            scanf("%f",&altra);
        };
        altura[i] = altra;

        printf("Digite (0) se o usuário não for vacinado ou (1) se o usuário for vacinado: ");
        scanf("%i",&vacinacao);
        while(vacinacao!=0 && vacinacao!=1){
            printf("Você digitou errado. Digite (0) se o usuário não for vacinado ou (1) se o usuário for vacinado: ");
            scanf("%i",&vacinacao);
        }
        vacinado[i] = vacinacao;

        getchar();
    }
}

void editarUsuario(){
    printf(">>> Editando Usuário <<<\n");
}

void removerUsuario(){
    printf(">>> Excluindo Usuário <<<\n");
}

void buscarUsuario(){
    printf(">>> Buscando Usuário <<<\n");
}

void imprimirUsuarios(){
    printf(">>> Imprimindo Todos os Usuários <<<\n");
    for(int i=0; i<quantidadeUsuarios();i++){
        printf("Id: %d\n",id[i]);
        printf("Nome: %d\n",nome[i]);
        printf("E-mail: %d\n",email[i]);
        printf("Gênero: %d\n",genero[i]);
        printf("Endereço: %d\n",endereco[i]);
        printf("Altura: %d\n",altura[i]);
        printf("Vacinou: %d\n",vacinado[i]);
        printf("\n");
    }
}

void fazerBackup(){
    printf(">>> Criando Backup <<<\n");
}

void restaurarBackup(){
    printf(">>> Restaurando Backup <<<\n");
}

// Funções Utilitárias
int gerarID(){
    int gerarID = rand();
    return gerarID;
}

int quantidadeUsuarios(){
    int contador = 0;
    for(int j=0;j<1000;j++){
        if(id[j]>=1){
            contador++;
        } else{
            return contador;
        }
    }
}