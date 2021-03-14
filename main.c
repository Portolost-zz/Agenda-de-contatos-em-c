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

contato** carregar_lista_encadeada(lista_encadeada *lista){
    FILE *arq;
    contato **contatos;
    int n_cont;

    arq = fopen("contatos.dat", "r");
    n_cont = fgetc(arq) - '0';
    fgetc(arq);

    contatos = (contato**)malloc(n_cont * sizeof(contato*));

    for (int i = 0; i < n_cont; i++)
        contatos[i] = criar_contato();

    for (int i = 0; i < n_cont; i++){
        for (int j = 0; j < 5; j++){
            for (int k = 0; contatos[i]->inf[j][k] = fgetc(arq); k++){
                if (contatos[i]->inf[j][k] == ';')
                    break;
                printf("%c", contatos[i]->inf[j][k]);
            }
        }
        contatos[i]->proximo = contatos[i+1];
    }
    lista->primeiro = contatos[0];
    return contatos;
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
int excluir_contato(lista_encadeada *lista, char *nome_cont){
    contato *aux = pesquisar_contato(lista, nome_cont);
    if (aux == NULL)
        return 0;
    aux->proximo = aux->proximo->proximo;
    return 1;
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

void escrever_lista(contato **contatos, int n_cont){
    FILE *arq;

    arq = fopen("contatos.dat", "w");
    fprintf(arq, "%d\n", n_cont);

    for (int i = 0; i < n_cont; i++){
        for (int j = 0; j < 5; j++){
            for (int k = 0; k < strlen(contatos[i]->inf[j]); k++){
                if (contatos[i]->inf[j][strlen(contatos[i]->inf[j])] != ';')
                    contatos[i]->inf[j][strlen(contatos[i]->inf[j])] = ';';
                fputc(contatos[i]->inf[j][k], arq);
                if (contatos[i]->inf[j][k] == ';')
                    break;
            }
        }
        fputc('\n', arq);
    }
}

int menu_alterar(contato *cont){
    while(1){
        int opcao;
        contato *aux = criar_contato();

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
            case 1: fscanf(stdin, "%s", cont->inf[0]); break;
            case 2: fgets(cont->inf[1], sizeof(texto_t), stdin); break;
            case 3: fgets(cont->inf[2], sizeof(texto_t), stdin); break;
            case 4: fgets(cont->inf[3], sizeof(texto_t), stdin); break;
            case 5: fgets(cont->inf[4], sizeof(texto_t), stdin); break;
            case 6: return 0;
            default: printf("Opção Inválida (Pressione ENTER)"); getchar();
        }
    }
}

void alterar_contato(lista_encadeada *lista, contato **contatos){
    contato *contato_alterado;
    char *nome_cont;
    int n_cont;

    nome_cont = (char*)malloc(sizeof(80 * sizeof(char)));

    printf("Nome do contato: ");
    fgets(nome_cont, sizeof(nome_cont), stdin);

    contato_alterado = pesquisar_contato(lista, nome_cont);
    menu_alterar(contato_alterado);
    puts(contatos[0]->inf[0]);
    escrever_lista(contatos, 1);
    carregar_lista_encadeada(lista);
}

int menu_principal(lista_encadeada *lista, contato **contatos){
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
            case 4: alterar_contato(lista, contatos); break;
            case 6: system("clear"); return 0; break;
            default: printf("Opção Inválida (Pressione ENTER)"); getchar();
        }
    }
}
int main(){
    lista_encadeada *lista;
    contato **contatos;
    setlocale(LC_ALL, "portuguese-brazilian");
    verificar_existencia();
    lista = criar_lista_encadeada();
    contatos = carregar_lista_encadeada(lista);
    menu_principal(lista, contatos);
    return 0;
}