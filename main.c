#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef char texto_t[80];
typedef struct contato_t contato;

struct contato_t{
    texto_t inf[5];
    contato *proximo;
};

typedef struct lista_encadeada_t{
    contato *primeiro;
}lista_encadeada;

contato* criar_contato(){
    contato *cont = (contato*)malloc(sizeof(contato));
    cont->proximo = NULL;
    return cont;
}

lista_encadeada* criar_lista_encadeada(){
    lista_encadeada *lista = (lista_encadeada*)malloc(sizeof(lista_encadeada));
    lista->primeiro = NULL;
    return lista;
}

// inserir sempre no final
void inserir_contato(lista_encadeada *lista, contato *novo){
    if (lista->primeiro == NULL)
        lista->primeiro = novo;
    else{
        contato *aux = lista->primeiro;
        while(aux->proximo != NULL)
            aux = aux->proximo;
        aux->proximo = novo;
    }
}

void carregar_lista_encadeada(lista_encadeada *lista){
    FILE *arq;
    contato *aux;
    int n_cont;

    arq = fopen("contatos.dat", "r");
    n_cont = fgetc(arq) - '0';
    fgetc(arq);

    while (n_cont--){
        aux = criar_contato();
        for (int j = 0; j < 5; j++){
            for (int k = 0; aux->inf[j][k] = fgetc(arq); k++)
                if (aux->inf[j][k] == ';')
                    break;
            if (j == 4)
                fgetc(arq);
        }
        inserir_contato(lista, aux);
    }
    fclose(arq);
} 

// NULL: se o contato não existe na lista
// !NULL: contato existe na lista
contato* pesquisar_contato(lista_encadeada *lista, char *cont){
    contato *aux = lista->primeiro;

    while (aux != NULL){
        if (strstr(aux->inf[0], cont) != NULL)
            return aux;
        aux = aux->proximo;
    }
    return NULL;
}

// 1: se foi excluído com sucesso
// 0: se contato não existe na lista
int excluir_contato(lista_encadeada *lista, char *cont){
    contato *aux;

    if (strstr(lista->primeiro->inf[0], cont) != NULL){
        lista->primeiro = lista->primeiro->proximo;
        return 1;
    }

    aux = lista->primeiro;
    while (aux != NULL){
        if (strstr(aux->proximo->inf[0], cont) != NULL){
            aux->proximo = aux->proximo->proximo;
            return 1;
        }
        aux = aux->proximo;
    }
    return 0;
}

void verificar_existencia(){
    FILE *arq = fopen("contatos.dat", "r");
    if (arq == NULL){
        arq = fopen("contatos.dat", "a");
        fprintf(arq, "0\n");
        fclose(arq);
    }
}

int tamanho_lista(lista_encadeada *lista){
    int cont = 0;
    contato *aux = lista->primeiro;
    while(aux != NULL){
        aux = aux->proximo;
        cont++;
    }
    return cont;
}

void escrever_lista(lista_encadeada *lista, int n_cont){
    FILE *arq;
    contato *aux;

    arq = fopen("contatos.dat", "w");
    fprintf(arq, "%d\n", n_cont);

    aux = lista->primeiro;

    for (int i = 0; i < n_cont; i++){
        for (int j = 0; j < 5; j++){
            for (int k = 0; k < strlen(aux->inf[j]); k++){
                fputc(aux->inf[j][k], arq);
                if (aux->inf[j][k] == ';')
                    break;
            }
        }
        fputc('\n', arq);
        aux = aux->proximo;
    }
    fclose(arq);
}

int menu_alterar(contato *cont){
    while(1){
        int opcao;

        printf("=========================== Alterar ============================\n");
        printf("= (1) Nome\t\t\t");
        printf("(2) Endereço                   =\n");
        printf("= (3) Telefone Residencial\t");
        printf("(4) Telefone Celular           =\n");
        printf("= (5) Data de nascimento\t");
        printf("(6) Voltar                     =\n");
        printf("================================================================\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1: printf("Nome do contato: ");fgets(cont->inf[0], sizeof(cont->inf[0]), stdin); cont->inf[0][strlen(cont->inf[0])-1] = cont->inf[0][strlen(cont->inf[0])]; cont->inf[0][strlen(cont->inf[0])] = ';'; break;
            case 2: printf("Novo endereço: ");fgets(cont->inf[1], sizeof(cont->inf[1]), stdin); cont->inf[1][strlen(cont->inf[1])-1] = cont->inf[1][strlen(cont->inf[1])]; cont->inf[1][strlen(cont->inf[1])] = ';'; break;
            case 3: printf("Novo telefone Residencial: ");fgets(cont->inf[2], sizeof(cont->inf[2]), stdin); cont->inf[2][strlen(cont->inf[2])-1] = cont->inf[2][strlen(cont->inf[2])]; cont->inf[2][strlen(cont->inf[2])] = ';'; break;
            case 4: printf("Novo telefone Celular: ");fgets(cont->inf[3], sizeof(cont->inf[3]), stdin); cont->inf[3][strlen(cont->inf[3])-1] = cont->inf[3][strlen(cont->inf[3])]; cont->inf[3][strlen(cont->inf[3])] = ';'; break;
            case 5: printf("Novo telefone Celular: ");fgets(cont->inf[4], sizeof(cont->inf[4]), stdin); cont->inf[4][strlen(cont->inf[4])-1] = cont->inf[4][strlen(cont->inf[4])]; cont->inf[4][strlen(cont->inf[4])] = ';'; break;
            case 6: return 0;
            default: printf("Opção Inválida (Pressione ENTER)"); getchar();
        }
    }
}

void alterar_contato(lista_encadeada *lista){
    contato *contato_alterado;
    char *nome_cont;
    int n_cont;

    nome_cont = (char*)malloc(sizeof(80 * sizeof(char)));

    printf("Nome do contato: ");
    fgets(nome_cont, sizeof(nome_cont), stdin);

    nome_cont[strlen(nome_cont)-1] = nome_cont[strlen(nome_cont)];

    contato_alterado = pesquisar_contato(lista, nome_cont);
    menu_alterar(contato_alterado);
    escrever_lista(lista, tamanho_lista(lista));
}
void escrever_contato(contato *cont){
    for (int j = 0; j < 5; j++){
        for (int k = 0; k < 80; k++){
            if (cont->inf[j][k] == ';'){
                putchar('\n');
                break;
            }
            printf("%c", cont->inf[j][k]);
        }
    }
}

void listar_contatos(lista_encadeada *lista, int n_cont){
    contato *aux = lista->primeiro;
    while (n_cont--){
        escrever_contato(aux);
        aux = aux->proximo;
    }
}

void pesquisar(lista_encadeada *lista){
    char *nome_cont;

    nome_cont = (char*)malloc(sizeof(80 * sizeof(char)));

    printf("Nome do contato: ");
    fgets(nome_cont, sizeof(nome_cont), stdin);

    nome_cont[strlen(nome_cont)-1] = nome_cont[strlen(nome_cont)];

    escrever_contato(pesquisar_contato(lista, nome_cont));
}

void excluir(lista_encadeada *lista){
    char *nome_cont;

    nome_cont = (char*)malloc(sizeof(80 * sizeof(char)));

    printf("Nome do contato: ");
    fgets(nome_cont, sizeof(nome_cont), stdin);

    nome_cont[strlen(nome_cont)-1] = nome_cont[strlen(nome_cont)];
    
    excluir_contato(lista, nome_cont);
    escrever_lista(lista, tamanho_lista(lista));
}

void adicionar_contato(lista_encadeada *lista){
    contato *novo_contato;

    novo_contato = criar_contato();
    printf("Nome do contato: ");
    fgets(novo_contato->inf[0], sizeof(novo_contato->inf[0]), stdin);
    novo_contato->inf[0][strlen(novo_contato->inf[0])-1] = novo_contato->inf[0][strlen(novo_contato->inf[0])];
    novo_contato->inf[0][strlen(novo_contato->inf[0])] = ';';
    
    printf("Endereço do contato: ");
    fgets(novo_contato->inf[1], sizeof(novo_contato->inf[1]), stdin);
    novo_contato->inf[1][strlen(novo_contato->inf[1])-1] = novo_contato->inf[0][strlen(novo_contato->inf[1])];
    novo_contato->inf[1][strlen(novo_contato->inf[1])] = ';';

    printf("Telefone Residencial: ");   
    fgets(novo_contato->inf[2], sizeof(novo_contato->inf[2]), stdin);
    novo_contato->inf[2][strlen(novo_contato->inf[2])-1] = novo_contato->inf[2][strlen(novo_contato->inf[2])];
    novo_contato->inf[2][strlen(novo_contato->inf[2])] = ';';

    printf("Telefone Celular: ");
    fgets(novo_contato->inf[3], sizeof(novo_contato->inf[3]), stdin);
    novo_contato->inf[3][strlen(novo_contato->inf[3])-1] = novo_contato->inf[3][strlen(novo_contato->inf[3])];
    novo_contato->inf[3][strlen(novo_contato->inf[3])] = ';';

    printf("Data de nascimento: ");
    fgets(novo_contato->inf[4], sizeof(novo_contato->inf[4]), stdin);
    novo_contato->inf[4][strlen(novo_contato->inf[4])-1] = novo_contato->inf[0][strlen(novo_contato->inf[4])];
    novo_contato->inf[4][strlen(novo_contato->inf[4])] = ';';


    inserir_contato(lista, novo_contato);
    escrever_lista(lista, tamanho_lista(lista));
}

int menu_principal(lista_encadeada *lista){
    while(1){
        int opcao;

        printf("\n============================ Menu ==============================\n");
        printf("= (1) Adicionar Novo Contato\t");
        printf("(2) Remover Contato Existente  =\n");
        printf("= (3) Pesquisar Contato\t\t");
        printf("(4) Alterar Contato            =\n");
        printf("= (5) Listar Todos os Contatos\t");
        printf("(6) Sair                       =\n");
        printf("================================================================\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1: adicionar_contato(lista);break;
            case 2: excluir(lista);break;
            case 3: pesquisar(lista);break;
            case 4: alterar_contato(lista); break;
            case 5: listar_contatos(lista, tamanho_lista(lista)); break;
            case 6: system("clear"); return 0; break;
            default: printf("Opção Inválida (Pressione ENTER)"); getchar();
        }
    }
}
int main(){
    lista_encadeada *lista;
    setlocale(LC_ALL, "portuguese-brazilian");
    verificar_existencia();
    lista = criar_lista_encadeada();
    carregar_lista_encadeada(lista);
    menu_principal(lista);
    return 0;
}