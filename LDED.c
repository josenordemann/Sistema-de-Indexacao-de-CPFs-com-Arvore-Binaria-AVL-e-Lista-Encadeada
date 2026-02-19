#include "ArvoreAVL.h"
//inclui os Protótipos


Lista* cria_lista()
{
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li)
{
    if (li != NULL)
	{
        Elem_ld* no;
        while ((*li) != NULL)
		{
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, int *dt)
{
    if (li == NULL || pos <= 0)
        return ERRO;
    Elem_ld *no = *li;
    int i = 1;
    while (no != NULL && i < pos)
	{
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return ERRO;
    else
	{
        *dt = no->cpf;
        return OK;
    }
}

int consulta_lista_dado(Lista* li, int dt, Elem_ld **el)
{
    if (li == NULL)
        return 0;
    Elem_ld *no = *li;
    while (no != NULL && no->cpf != dt){
        no = no->prox;
    }
    if (no == NULL)
        return ERRO;
    else
	{
        *el = no;
        return OK;
    }
}

int insere_lista_final(Lista* li, int cpf, int cv, int dia, int mes, int ano, char nome[50], Elem_ld **el)
{
    Elem_ld *no;
    if (li == NULL) return ERRO;
    no = (Elem_ld*) malloc(sizeof(Elem_ld));
    if (no == NULL)  return ERRO;

    no->cpf = cpf;
    no->cv = cv;
    no->dia = dia;
    no->mes = mes;
    no->ano = ano;
    strcpy(no->nome, nome);
    no->prox = NULL;

    if (el != NULL) {
        *el = no; 
    }
    
	if ((*li) == NULL)
	{   //lista vazia: insere início
        no->ant = NULL;
        *li = no;
    }else
	{
        Elem_ld *aux;
        aux = *li;
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return OK;
}

int insere_lista_inicio(Lista* li, int cpf, int cv, int dia, int mes, int ano, char nome[50], Elem_ld **el)
{
    if (li == NULL)
        return ERRO;
    Elem_ld* no;
    no = (Elem_ld*) malloc(sizeof(Elem_ld));
    if (no == NULL)
        return ERRO;

    no->cpf = cpf;
    no->cv = cv;
    no->dia = dia;
    no->mes = mes;
    no->ano = ano;
    strcpy(no->nome, nome);    no->prox = (*li);
    no->ant = NULL;

    if (el != NULL) {
    *el = no; 
    }

	if (*li != NULL) //lista não vazia: apontar para o anterior!
    (*li)->ant = no;
    *li = no;
    return OK;
}

int insere_lista_ordenada(Lista* li, int dt)
{
    if (li == NULL)
        return ERRO;
    Elem_ld *no = (Elem_ld*) malloc(sizeof(Elem_ld));
    if (no == NULL)
        return ERRO;
    no->cpf = dt;
    if ((*li) == NULL)
	{  //lista vazia: insere início
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return OK;
    }
    else{
        Elem_ld *ante, *atual = *li;
        while (atual != NULL && atual->cpf < dt)
		{
            ante = atual;
            atual = atual->prox;
        }
        if (atual == *li)
		{   //insere início
            no->ant = NULL;
            (*li)->ant = no;
            no->prox = (*li);
            *li = no;
        } else
		{
            no->prox = ante->prox;
            no->ant = ante;
            ante->prox = no;
            if (atual != NULL)
                atual->ant = no;
        }
        return OK;
    }
}

int remove_lista(Lista* li, int dt)
{   //TERMINAR
    if (li == NULL)
        return ERRO;
    if ((*li) == NULL)//lista vazia
        return ERRO;
    Elem_ld *no = *li;
    while (no != NULL && no->cpf != dt){
        no = no->prox;
    }
    if (no == NULL)//não encontrado
        return ERRO;

    if (no->ant == NULL)//remover o primeiro?
        *li = no->prox;
    else
        no->ant->prox = no->prox;

    if (no->prox != NULL)//não é o último?
        no->prox->ant = no->ant;

    free(no);
    return OK;
}


int remove_lista_inicio(Lista* li)
{
    if (li == NULL)
        return ERRO;
    if ((*li) == NULL)//lista vazia
        return ERRO;

    Elem_ld *no = *li;
    *li = no->prox;
    if (no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return OK;
}

int remove_lista_final(Lista* li)
{
    if (li == NULL)
        return ERRO;
    if ((*li) == NULL) //lista vazia
        return ERRO;

    Elem_ld *no = *li;
    while (no->prox != NULL)
        no = no->prox;

    if (no->ant == NULL) //remover o primeiro e único
        *li = no->prox;
    else
        no->ant->prox = NULL;

    free(no);
    return OK;
}

int tamanho_lista(Lista* li)
{
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem_ld* no = *li;
    while (no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li)
{
    return FALSO;
}

int lista_vazia(Lista* li)
{
    if (li == NULL)
        return OK;
    if (*li == NULL)
        return OK;
    return FALSO;
}

void exibe_lista(Lista* li)
{
    Elem_ld* no = *li;

    if (li == NULL)
        return;
    while (no != NULL)
    {
        printf("%d # ",no->cpf);
        no = no->prox;
    }
    printf("\n");
}

void imprime_lista(Lista* li)
{
    Elem_ld* no = *li;

    if (li == NULL)
        return;
    while (no != NULL)
    {
        printf("%09d-%02d %02d/%02d/%04d %s\n", no->cpf, no->cv, no->dia, no->mes, no->ano, no->nome);
        no = no->prox;
    }
}

void imprime_elemento(Lista* li, int cpf)
{
    if(li == NULL){return;}
    if(*li == NULL){return;}
    Elem_ld *atual = *li;
    while(atual->cpf != cpf)
    {
        atual = atual->prox;
    }
    if(atual != NULL){printf("%05d-%01d %02d/%02d/%04d %s", atual->cpf, atual->cv, atual->dia, atual->mes, atual->ano, atual->nome);}
}

// Função nova

// Função para imprimir a lista no arquivo, parecida com a função original de impressão
void imprime_lista_linha(Lista* li, FILE *f) 
{
    Elem_ld* no = *li;

    if (li == NULL)
        return;
    while (no != NULL)
    {
        fprintf(f, "%09d-%02d %02d/%02d/%04d %s\n", no->cpf, no->cv, no->dia, no->mes, no->ano, no->nome);
        no = no->prox;
    }
}