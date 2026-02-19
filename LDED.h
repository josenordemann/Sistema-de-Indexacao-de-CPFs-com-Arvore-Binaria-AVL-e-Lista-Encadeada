//Arquivo LDED.h - Lista Dinamica Encadeada Dupla
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FALSO
#define FALSO      0
#define VERDADEIRO 1
#endif

#ifndef OK
#define OK         1
#define ERRO       0
#endif

//Definição do tipo lista
struct elemento_ld{
    struct elemento_ld *ant;
    int cpf;
    int cv;
    int dia;
    int mes;
    int ano;
    char nome[50];
    struct elemento_ld *prox;
};

typedef struct elemento_ld Elem_ld;

typedef struct elemento_ld* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int consulta_lista_pos(Lista* li, int pos, int *dt);
int consulta_lista_dado(Lista* li, int dt, Elem_ld **el);

//Funções alteradas da biblioteca original
int insere_lista_final(Lista* li, int cpf, int cv, int dia, int mes, int ano, char nome[50], Elem_ld **el); 
int insere_lista_inicio(Lista* li, int cpf, int cv, int dia, int mes, int ano, char nome[50], Elem_ld **el);

int insere_lista_ordenada(Lista* li, int dt);
int remove_lista(Lista* li, int dt);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
int lista_cheia(Lista* li);
void exibe_lista(Lista* li);
void imprime_lista(Lista* li);
void imprime_elemento(Lista* li, int cpf);

//Função nova
void imprime_lista_linha(Lista* li, FILE *f);