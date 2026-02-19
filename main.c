#include "ArvoreAVL.h"
#define DEBUG 0

int main()
{
    //int utilizado pelo switch case mais ao final do codigo, para saber se apenas executa return ou executa retrurn e system cat
    int i;
    scanf("%d", &i);


    //Criação da lista e da árvore para armazenar os dados
    Lista *li = cria_lista();
    ArvAVL *Arv = cria_ArvAVL();

    // Leitura da base de dados
    FILE *f;
    f = fopen("basedados.csv","r");

    // Verificação de erro
    if (f == NULL)
    {
        printf("Erro de leitura de arquivo!");
        system("pause");
        exit(1);
    }

    // else if(DEBUG) {printf("Leitura feita com sucesso!");}

    // Variáveis para armazenar os dados na lista e na árvore binária
    int cpf, cv, dia, mes, ano;
    char nome[50]; 
    int cont = 0;
    Elem_ld *el = NULL;
    while (1) 
    {
        fscanf(f, "%d,", &cpf);
        if(cpf == -1) {break;}
        fscanf(f, "%d,%d,%d,%d,%49[^,],", &cv, &dia, &mes, &ano, nome);
        //if(DEBUG) printf("fscanf ok!\n");

        /*   
        int a = 0;
        while(nome[a] != ',') 
        {
            a++;
        }
        nome[a] = '\0';  
        */

        // Podemos usar essa lógica para poder tirar a vírgula da string em vez de usar o %49[^,], 

        //if(DEBUG){printf("%d %d %d %d %d %s\n",cpf, cv, dia, mes, ano, nome);}

        insere_lista_inicio(li, cpf, cv, dia, mes, ano, nome, &el); // inserção na lista
        //if(DEBUG) printf("insercao na lista ok!\n");
        insere_ArvAVL(Arv, cpf, el); //inserção na árvore binária
        //if(DEBUG) printf("insercao na arvore ok!\n");
        cont++;
    }
        //if(DEBUG){imprime_lista(li);}
        //if(DEBUG){emOrdem_ArvAVL(Arv);}

    fclose(f);
    //fechamento do csv

    int total_nos = totalNO_ArvAVL(Arv);

    //1
    printf("%d\n", total_nos);

    int altura = altura_ArvAVL(Arv);

    //2
    printf("%d\n", altura);

    Elem_ld *primeiro_cpf = acha_primeiro_elemento(Arv);
    
    //3
    printf("%09d-%02d %02d/%02d/%04d %s\n", primeiro_cpf->cpf, primeiro_cpf->cv, primeiro_cpf->dia, primeiro_cpf->mes, primeiro_cpf->ano, primeiro_cpf->nome);

    Elem_ld *ultimo_cpf = acha_ultimo_elemento(Arv);
    //4
    printf("%09d-%02d %02d/%02d/%04d %s\n", ultimo_cpf->cpf, ultimo_cpf->cv, ultimo_cpf->dia, ultimo_cpf->mes, ultimo_cpf->ano, ultimo_cpf->nome);

    FILE *arq_1;
    arq_1 = fopen("dados1.txt","w");
    //5
    imprime_lista_linha(li, arq_1);
    fclose(arq_1);

    FILE *arq_2;
    arq_2 = fopen("dados2.txt","w");
    //6
    emOrdem_ArvAVL_linha(Arv, arq_2);
    fclose(arq_2);

    FILE *arq_3;
    arq_3 = fopen("dados3.txt","w");
    //7
    preOrdem_ArvAVL_linha(Arv, arq_3);
    fclose(arq_3);

    libera_lista(li); //free
    libera_ArvAVL(Arv); //free


    switch(i)
    {

    case(1):

   {return 0;}
    
    case(2):
    {
    system("cat dados1.txt");
    system("cat dados2.txt");
    system("cat dados3.txt");
    return 0;
    }

    //fim do case 2
    }

}