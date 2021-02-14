#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define NOME 30
#define ENDERECO 100
#define NUM 20
#define DATA 10
#define CONTATOS 30
#define CONTATO 200
#define DADOS 5

void verificarExistencia(){
    FILE *arq = fopen("contatos.dat", "r");
    if (arq == NULL){
        arq = fopen("contatos.dat", "a");
        fprintf(arq, "0\n");
        fclose(arq);
    }
}

char **carregarBuffer(){
    FILE *arq;
    char **buffer;

    arq = fopen("contatos.dat", "r");

    buffer = (char**)malloc(CONTATOS * sizeof(char*));

    for (int i = 0; i < CONTATOS; i++)
        buffer[i] = (char*)malloc(CONTATO * sizeof(char));
        
    for (int i = 0; fgets(buffer[i], CONTATO * sizeof(char), arq) != NULL; i++);

    fclose(arq);
    return buffer;
}

char *pesquisar(char **buffer, char *pesquisa){
    for (int i = 0; i < CONTATOS; i++){
        if (strstr(buffer[i], pesquisa) != NULL){
            return buffer[i];
            break;
        }
    }
}

char **dadosContato(char *contato){
    int p = 0;
    char **dados, lim[] = {NOME, ENDERECO, NUM, NUM, DATA};

    dados = (char**)malloc(DADOS * sizeof(char*));

    for (int i = 0; i < DADOS; i++)
        dados[i] = (char*)malloc(lim[i] * sizeof(char));
    
    for (int i = 0; i < DADOS; i++, p++){
        for (int j = 0; j < lim[i]; j++, p++){
            if (contato[p] == ';')
                break;
            dados[i][j] = contato[p];
        }
        puts(dados[i]);
    }
    return dados;
}
int menuAlterar(char *nomeContato){
    int opcao;

    printf("========================= Alterar %s ======================\n", nomeContato);
    printf("= (1) Nome\t\t\t");
    printf("(2) Endereço                   =\n");
    printf("= (3) Telefone Residencial\t");
    printf("(4) Telefone Celular           =\n");
    printf("= (5) Data de nascimento\t");
    printf("(6) Cancelar                   =\n");
    printf("================================================================\n");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}
void alterar(char **buffer, char *nomeContato){
    char **dados, *pesquisa;

    pesquisa = pesquisar(buffer, nomeContato);
    dados = dadosContato(pesquisa);

    switch(menuAlterar(nomeContato)){
        case 1: fgets(dados[0], CONTATO, stdin); break;
        case 2: fgets(dados[1], CONTATO, stdin); break;
        case 3: fgets(dados[2], CONTATO, stdin); break;
        case 4: fgets(dados[3], CONTATO, stdin); break;
        case 5: fgets(dados[4], CONTATO, stdin); break;
        case 6: exit(2);
    }

}

void alterarContato(){
    char *nomeContato, *pesquisa, **buffer, ch;

    nomeContato = (char*)malloc(NOME * sizeof(char));

    printf("Nome do contato: ");
    fgets(nomeContato, sizeof(nomeContato), stdin);

    alterar(carregarBuffer(), nomeContato);
}

int menuPrincipal(){
    int opcao;

    printf("============================ Menu ==============================\n");
    printf("= (1) Adicionar Novo Contato\t");
    printf("(2) Remover Contato Existente  =\n");
    printf("= (3) Pesquisar Contato\t\t");
    printf("(4) Alterar Contato            =\n");
    printf("= (5) Listar Todos os Contatos\t");
    printf("(6) Sair                       =\n");
    printf("================================================================\n");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}

int main(){
    setlocale(LC_ALL, "portuguese-brazilian");

    verificarExistencia();

    while(1){
        switch(menuPrincipal()){
            case 4: alterarContato(); break;
            case 6: system("clear"); exit(1);
        }
        system("clear");
    }
}   