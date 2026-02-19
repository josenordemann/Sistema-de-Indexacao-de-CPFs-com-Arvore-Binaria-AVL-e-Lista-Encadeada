#include "ArvoreAVL.h" //inclui os Protótipos

// struct NO_AVL* remove_atual(struct NO* atual);

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO_AVL(struct NO_AVL* no){
    if(no == NULL)
        return;
    libera_NO_AVL(no->esq);
    libera_NO_AVL(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO_AVL(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO_AVL(struct NO_AVL* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO_AVL(struct NO_AVL* no){
    return labs(altura_NO_AVL(no->esq) - altura_NO_AVL(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        //printf("%d\n",(*raiz)->cpf);
        //printf("No %d: %d\n",(*raiz)->cpf,fatorBalanceamento_NO(*raiz));
        printf("No %d - ",(*raiz)->cpf);

        if ((*raiz)->esq != NULL) // Tem Esquerda?
            printf("Esq: %d - ",(*raiz)->esq->cpf);
        else
            printf("Esq: NULL - ");

        if ((*raiz)->dir != NULL) // Tem Direita?
            printf("Dir: %d \n",(*raiz)->dir->cpf);
        else
            printf("Dir: NULL \n");
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->cpf);
        //printf("No %d: H(%d) fb(%d)\n",(*raiz)->cpf,altura_NO_AVL(*raiz),fatorBalanceamento_NO_AVL(*raiz));
        printf("Dado: %d\n",(*raiz)->cpf);
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvAVL(&((*raiz)->esq));
        posOrdem_ArvAVL(&((*raiz)->dir));
        printf("%d\n",(*raiz)->cpf);
    }
}

int consulta_ArvAVL(ArvAVL *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO_AVL* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->cpf){
            return 1;
        }
        if(valor > atual->cpf)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

//=================================
void RotacaoLL(ArvAVL *A){//LL
    struct NO_AVL *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO_AVL((*A)->esq),altura_NO_AVL((*A)->dir)) + 1;
    B->altura = maior(altura_NO_AVL(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){//RR
    struct NO_AVL *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO_AVL((*A)->esq),altura_NO_AVL((*A)->dir)) + 1;
    B->altura = maior(altura_NO_AVL(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, int valor, Elem_ld *el){
    int res;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO_AVL *novo;
        novo = (struct NO_AVL*)malloc(sizeof(struct NO_AVL));
        if(novo == NULL)
            return 0;
        novo->no_cor = el;
        novo->cpf = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO_AVL *atual = *raiz;
    if(valor < atual->cpf){
        if((res = insere_ArvAVL(&(atual->esq), valor, el)) == 1){
            if(fatorBalanceamento_NO_AVL(atual) >= 2){
                if(valor < (*raiz)->esq->cpf ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(valor > atual->cpf){
            if((res = insere_ArvAVL(&(atual->dir), valor, el)) == 1){
                if(fatorBalanceamento_NO_AVL(atual) >= 2){
                    if((*raiz)->dir->cpf < valor){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO_AVL(atual->esq),altura_NO_AVL(atual->dir)) + 1;

    return res;
}

struct NO_AVL* procuraMenor_AVL(struct NO_AVL* atual){
    struct NO_AVL *no1 = atual;
    struct NO_AVL *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){// valor não existe
	    printf("valor não existe!!\n");
	    return 0;
	}

    int res;
	if(valor < (*raiz)->cpf){
	    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){
            if(fatorBalanceamento_NO_AVL(*raiz) >= 2){
                if(altura_NO_AVL((*raiz)->dir->esq) <= altura_NO_AVL((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->cpf < valor){
	    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO_AVL(*raiz) >= 2){
                if(altura_NO_AVL((*raiz)->esq->dir) <= altura_NO_AVL((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->cpf == valor){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nó tem 1 filho ou nenhum
			struct NO_AVL *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // nó tem 2 filhos
			struct NO_AVL* temp = procuraMenor_AVL((*raiz)->dir);
			(*raiz)->cpf = temp->cpf;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->cpf);
            if(fatorBalanceamento_NO_AVL(*raiz) >= 2){
				if(altura_NO_AVL((*raiz)->esq->dir) <= altura_NO_AVL((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO_AVL((*raiz)->esq),altura_NO_AVL((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO_AVL((*raiz)->esq),altura_NO_AVL((*raiz)->dir)) + 1;

	return res;
}

// Funções novas

// Função para achar o primeiro elemento. Note que utilizo a lógica do exercício para retornar o ponteiro para o elemento da LDED, assim apenas percorrendo a árvore binária (mais rápido)

Elem_ld *acha_primeiro_elemento(ArvAVL *raiz)
{
    if(raiz == NULL) {return NULL;}//erro
    if(*raiz == NULL) {return NULL;} //erro árvore vazia
    NodoArvAVL *ant = (*raiz); // auxiliares
    NodoArvAVL *atual = ((*raiz)->esq);
    {
        while (atual != NULL) // achar o elemento mais a esquerda
        {   
        ant = atual;
        atual = atual->esq;
        }
    }
    return ant->no_cor; // devolve o elemento mais a esquerda
}

// Função para achar o último elemento. Note que utilizo a lógica do exercício para retornar o ponteiro para o elemento da LDED, assim apenas percorrendo a árvore binária (mais rápido)

Elem_ld *acha_ultimo_elemento(ArvAVL *raiz)
{
    if(raiz == NULL) {return NULL;}//erro
    if(*raiz == NULL) {return NULL;} //erro arvore vazia
    NodoArvAVL *ant = (*raiz);// auxiliares
    NodoArvAVL *atual = ((*raiz)->dir);
    {
        while (atual != NULL) // achar o elemento mais a direita
        {   
        ant = atual;
        atual = atual->dir;
        }
    }
    return ant->no_cor; // devolve o elemento mais a direita
}

// Função para imprimir a árvore binária no arquivo, parecida com a função original de impressão
void emOrdem_ArvAVL_linha(ArvAVL *raiz, FILE *f)
{
    if(raiz == NULL)
        return;
    if(f == NULL)
        return;

    if(*raiz != NULL){
        emOrdem_ArvAVL_linha(&((*raiz)->esq), f);
        fprintf(f, "%09d\n",(*raiz)->cpf);          // cpf é Int
        emOrdem_ArvAVL_linha(&((*raiz)->dir), f);
    }
}

void preOrdem_ArvAVL_linha(ArvAVL *raiz, FILE *f)
{
 if(raiz == NULL)
        return;
    if(f == NULL)
        return;

    if(*raiz != NULL){

        fprintf(f, "%09d ",(*raiz)->cpf);          // cpf é Int

        if((*raiz)->esq == NULL)
        {
            fprintf(f, "E: NULL ");         
        }
        else
        {fprintf(f, "E: %09d ",(*raiz)->esq->cpf);}     
          
      if((*raiz)->dir == NULL)
        {
            fprintf(f, "D: NULL\n");         
        }
        else
        {fprintf(f, "D: %09d\n",(*raiz)->dir->cpf);}
        preOrdem_ArvAVL_linha(&((*raiz)->esq), f);
        preOrdem_ArvAVL_linha(&((*raiz)->dir), f);
    }
}
