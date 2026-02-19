//  Arquivo ArvoreAVL.h
//  TAD: Arvore Balanceada AVL - v3

#include "LDED.h"

#ifndef FALSO
#define FALSO      0
#define VERDADEIRO 1
#endif

#ifndef OK
#define OK         1
#define ERRO       0
#endif


//Definição do tipo Arvore
struct NO_AVL{
    int cpf;
    int altura;
    struct NO_AVL *esq;
    struct NO_AVL *dir;
    Elem_ld *no_cor; // no correspondente da lista
};

typedef struct NO_AVL NodoArvAVL;
typedef struct NO_AVL *ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int valor, Elem_ld *el);
int remove_ArvAVL(ArvAVL *raiz, int valor);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, int valor);
void preOrdem_ArvAVL(ArvAVL *raiz);
void emOrdem_ArvAVL(ArvAVL *raiz);
void posOrdem_ArvAVL(ArvAVL *raiz);

// Local functions (Prototipo da funcao)
void libera_NO_AVL(struct NO_AVL* no);
int altura_NO_AVL(struct NO_AVL* no);
struct NO_AVL* procuraMenor_AVL(struct NO_AVL* atual);
int fatorBalanceamento_NO_AVL(struct NO_AVL* no);
int maior(int x, int y);
void RotacaoLL(ArvAVL *A);
void RotacaoRR(ArvAVL *A);
void RotacaoLR(ArvAVL *A);
void RotacaoRL(ArvAVL *A);

// Funções novas
Elem_ld *acha_primeiro_elemento(ArvAVL *raiz);
Elem_ld *acha_ultimo_elemento(ArvAVL *raiz);
void emOrdem_ArvAVL_linha(ArvAVL *raiz, FILE *f);
void preOrdem_ArvAVL_linha(ArvAVL *raiz, FILE *f);
