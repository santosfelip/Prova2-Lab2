#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Lista
{
    int codigo;
    char nome[200];
    int ano;
    char criador[200];
    char genero[30];
    char nac[10];
    int duracao;
    float avaliacao;
    struct Lista *prox;
}Livro;

FILE *open(char *nome, char *type);
Livro *loadDados2(int tam,FILE *arq);
void inserirOrdenado(Livro **dados,Livro *novo);
Livro *criaDado(int codigo,char *nome,int ano,char *criador, char *genero, char *nac, int duracao, float avaliacao);
void print(Livro *dados);
int remover(Livro **dados,int codigo);
int Buscar(Livro **dados,char *nome);
int Buscar2(Livro **dados,char *genero, int ano, int duracao);
void Backup(FILE *arq, Livro *topo);
void Ler_Backup(FILE *arq, Livro *topo);


int main()
{
    FILE *fp;
    int cod;
    Livro *topo = NULL;
    char nome[200];
    char genero[200];
    int ano;
    int duracao;

    fp = open("ListaFilmes.txt","r");
    topo = loadDados2(1,fp);

    printf("Digite o codigo para remover: ");
    scanf("%d",&cod);

    if (remover(&topo,cod)==0)
    {
        printf("Erro ao remover %s!\n",nome);
    }

    print(topo);

    printf("Digite o nome para buscar: ");
    scanf("%s",nome);

    if (Buscar(&topo,nome)==0)
    {
        printf("Erro ao remover %s!\n",nome);
    }else{
        printf("Encontrado!");

    }

    printf("Busca avancada: ");
    printf("Genero: ");
    scanf("%s",genero);
    printf("ano: ");
    scanf("%d",&ano);
    printf("duracao: ");
    scanf("%d",&duracao);
    if (Buscar2(&topo,genero,ano,duracao)==0)
    {
        printf("Erro ao remover %s!\n",nome);
    }else{
        printf("Encontrado!");

    }

    fclose(fp);

    fp = fopen("Backup.txt","wb");
    Backup(fp,topo);
    fclose(fp);

    fp = fopen("Backup.txt","rb");
    Ler_Backup(fp,topo);
    fclose(fp);

    return 0;
}

FILE *open(char *nome, char *type)
{
    FILE *arq = NULL;
    arq = fopen(nome,type);
    if(arq==NULL){
        printf("ERRO ao criar ao arquivo!");
        return NULL;
    }
    return arq;
}

Livro *loadDados2(int tam,FILE *arq)
{
    int i=0;
    Livro *novo=NULL,*dados=NULL;
    char linha[200];
    int codigo;
    char nome[200];
    int ano;
    char criador[200];
    char genero[30];
    char nac[10];
    int duracao;
    float avaliacao;

    for (i=0;i<tam;i++)
    {
        fgets(linha,200,arq);
        codigo = atoi(linha);
        printf("%d\n",codigo);

        fgets(nome,200,arq);
        printf("%s",nome);

        fgets(linha,200,arq);
        ano = atoi(linha);
        printf("%d\n",ano);

        fgets(criador,200,arq);
        printf("%s",criador);

        fgets(genero,200,arq);
        printf("%s",genero);

        fgets(nac,200,arq);
        printf("%s",nac);

        fgets(linha,200,arq);
        duracao = atoi(linha);
        printf("%d\n",duracao);

        fgets(linha,200,arq);
        avaliacao = atof(linha);
        printf("%f\n",avaliacao);

        novo=criaDado(codigo,nome,ano,criador,genero,nac,duracao,avaliacao);
        inserirOrdenado(&dados,novo);
   }
    return dados;
}

void inserirOrdenado(Livro **dados,Livro *novo)
{
    Livro *aux=NULL,*anterior=NULL;
    if (*dados == NULL)
    {
        *dados = novo;
    }
    else
    {
        aux = *dados;
        while (aux!=NULL && aux->avaliacao > novo->avaliacao)
        {
            anterior = aux;
            aux = aux->prox;
        }

        if (anterior==NULL)
        {
            novo->prox = aux;
            *dados = novo;
        }
        else
        {
            novo->prox=aux;
            anterior->prox=novo;
        }
    }
}

Livro *criaDado(int codigo,char *nome,int ano,char *criador, char *genero, char *nac, int duracao, float avaliacao)
{


    Livro *novo = malloc(sizeof(Livro));
    novo->codigo = codigo;
    strcpy(novo->nome,nome);
    novo->ano = ano;
    strcpy(novo->criador,criador);
    strcpy(novo->genero,genero);
    strcpy(novo->nac,nac);
    novo->duracao = duracao;
    novo->avaliacao = avaliacao;
    novo->prox = NULL;

    return novo;

}

void print(Livro *dados)
{

    Livro *aux;

	aux = dados;

	if (aux==NULL)
	{
        printf("Lista Vazia!");
	}else{
		do{
			printf("%d\n",aux->codigo);
            printf("%s",aux->nome);
            printf("%d\n",aux->ano);
            printf("%s",aux->criador);
            printf("%s",aux->genero);
            printf("%s",aux->nac);
            printf("%d\n",aux->duracao);
            printf("%f\n",aux->avaliacao);

			aux = aux->prox;
		}while(aux!=NULL);
	}
}

int remover(Livro **dados,int codigo)
{
    Livro *aux=NULL,*anterior=NULL;
    if (*dados==NULL)
    {
        return 0;
    }
    else
    {
        aux = *dados;
        while (aux!=NULL && aux->codigo!=codigo)
        {
            anterior = aux;
            aux = aux->prox;
        }

        if (aux==NULL)
        {
            return 0;
        }
        else
        {
            if (anterior==NULL)
            {
                *dados = aux->prox;
            }
            else
            {
                anterior->prox = aux->prox;
            }
            free(aux);
            return 1;
        }
    }
}

int Buscar(Livro **dados,char *nome)
{
    Livro *aux=NULL,*anterior=NULL;
    if (*dados==NULL)
    {
        return 0;
    }
    else
    {
        aux = *dados;
        while (aux!=NULL && strcmp(aux->nome,nome)!=0)
        {
            anterior = aux;
            aux = aux->prox;
        }

        if (aux==NULL)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

int Buscar2(Livro **dados,char *genero, int ano, int duracao)
{
    Livro *aux=NULL,*anterior=NULL;
    if (*dados==NULL)
    {
        return 0;
    }
    else
    {
        aux = *dados;
        while (aux!=NULL)
        {
            if(strcmp(aux->genero,genero)==0 && aux->ano<=ano && aux->duracao==duracao){
                print(aux);
            }
            anterior = aux;
            aux = aux->prox;
        }

        if (aux==NULL)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

void Backup(FILE *arq, Livro *topo)
{
    fprintf(arq,"%d\n",topo->codigo);
    fprintf(arq,"%s",topo->nome);
    fprintf(arq,"%d\n",topo->ano);
    fprintf(arq,"%s",topo->criador);
    fprintf(arq,"%s",topo->genero);
    fprintf(arq,"%s",topo->nac);
    fprintf(arq,"%d\n",topo->duracao);
    fprintf(arq,"%f\n",topo->avaliacao);
}

void Ler_Backup(FILE *arq, Livro *topo)
{
    char linha[200];
    int codigo;
    char nome[200];
    int ano;
    char criador[200];
    char genero[30];
    char nac[10];
    int duracao;
    float avaliacao;

    do{
       fgets(linha,200,arq);
        codigo = atoi(linha);
        printf("%d\n",codigo);

        fgets(nome,200,arq);
        printf("%s",nome);

        fgets(linha,200,arq);
        ano = atoi(linha);
        printf("%d\n",ano);

        fgets(criador,200,arq);
        printf("%s",criador);

        fgets(genero,200,arq);
        printf("%s",genero);

        fgets(nac,200,arq);
        printf("%s",nac);

        fgets(linha,200,arq);
        duracao = atoi(linha);
        printf("%d\n",duracao);

        fgets(linha,200,arq);
        avaliacao = atof(linha);
        printf("%f\n",avaliacao);

    }while(!feof(arq));

}
