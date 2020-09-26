#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tipoElemento{
        char nome[30];
        char endereco[200];
        int id;
}TElemento;


typedef struct tipoNo{
        TElemento elemento;
        struct tipoNo *esq, *dir;
}TNo;


TNo* inserir (TNo *raiz, TElemento *novoElemento){
        if (raiz == NULL){
                raiz = new TNo;
                raiz->elemento.id = novoElemento->id;
                strcpy(raiz->elemento.nome, novoElemento->nome);
                strcpy (raiz->elemento.endereco, novoElemento->endereco);
                raiz->esq = NULL;
                raiz->dir = NULL;
        }
        else{
                if (novoElemento->id < raiz->elemento.id){
                        raiz->esq = inserir (raiz->esq, novoElemento);
                }
                else{
                        raiz->dir = inserir (raiz->dir, novoElemento); 
                }
        }
        return raiz;
}
TNo* criar (TNo *raiz, TElemento *novoElemento){


                raiz = new TNo;
                raiz->elemento.id = novoElemento->id;
                strcpy (raiz->elemento.nome, novoElemento->nome);
                strcpy (raiz->elemento.endereco, novoElemento->endereco);
                raiz->esq = NULL;
                raiz->dir = NULL;
        
        return raiz;
}

void preOrdem (TNo *raiz)
{
	if (raiz != NULL)
	{
		printf("\n id:  %d ",raiz->elemento.id);
        printf("\n nome: %s",raiz->elemento.nome);
        printf("\n endereco: %s \n",raiz->elemento.endereco);;
		preOrdem (raiz->esq);
		preOrdem (raiz->dir);
	}
}

void emOrdem (TNo *raiz)
{
	if (raiz != NULL)
	{
		emOrdem (raiz->esq);
		
		printf("\n id:  %d ",raiz->elemento.id);
        printf("\n nome: %s",raiz->elemento.nome);
        printf("\n endereco: %s \n",raiz->elemento.endereco);;
        
		emOrdem (raiz->dir);
	}
}

void posOrdem (TNo *raiz)
{
	if (raiz != NULL)
	{
		posOrdem (raiz->esq);	
		posOrdem (raiz->dir);
		
		printf("\n id:  %d ",raiz->elemento.id);
        printf("\n nome: %s",raiz->elemento.nome);
        printf("\n endereco: %s \n",raiz->elemento.endereco);
	}
}


void lerDados (TElemento *novoElemento){        
fflush(stdin);
    
        printf("\n Informe valor da id: ");
        scanf("%d", &novoElemento->id);
        fflush(stdin);
        printf("\n Informe nome: ");
        gets(novoElemento->nome);
        fflush(stdin);
          printf("\n Informe endereco: ");
        gets(novoElemento->endereco);
}
void pesquisar(TNo *raiz,int valor){
        if (raiz != NULL){   
                if (valor == raiz->elemento.id){
                		printf("\n id:  %d ",raiz->elemento.id);
                        printf("\n nome: %s",raiz->elemento.nome);
                        printf("\n endereco: %s \n",raiz->elemento.endereco);
            }
                pesquisar(raiz->esq,valor);
                pesquisar(raiz->dir,valor);
        }
}
int sobeMaiorDireita (TNo *raiz)
{
	while (raiz->dir != NULL)
	{
		raiz = raiz->dir;
	}
	return raiz->elemento.id;
}

TNo* exclusao (TNo *raiz, int aux)
{
	if (raiz == NULL)
	{
		printf("\n Elemento nao existe");
	}
	else
	{
		if (aux < raiz->elemento.id)
		{
			raiz->esq = exclusao(raiz->esq, aux);
		}
		else
		{
			if (aux > raiz->elemento.id)
			{
				raiz->dir = exclusao(raiz->dir, aux);
			}
			else //encontrou elemento
			{
				if (raiz->dir == NULL)
				{
					TNo *aux2;
					aux2 = raiz;
					raiz = raiz->esq;
					free(aux2);
				}
				else
				{
					if (raiz->esq == NULL)
					{
						TNo *aux2;
						aux2 = raiz;
						raiz = raiz->dir;
						free(aux2);
					}
					else // elemento com 2 sub-árvores
					{
						raiz->elemento.id = sobeMaiorDireita(raiz->esq);
						raiz->esq = exclusao (raiz->esq, raiz->elemento.id);
					}
				}
			}
		}
	}
	return raiz;
}


        
        






int main(){
        TNo *raiz;
        raiz = NULL;
        
        TElemento novoElemento;
        
        int opcao,aux;
        
        do{
                printf("\n 1 - insercao novo ponto ");
                printf("\n 2 - busca pelo id a ser pesquisada ");
				printf("\n 3 - percorrimento arvore (pre-ordem)");
	 			printf("\n 4 - percorrimento arvore (em-ordem)");
	 			printf("\n 5 - percorrimento arvore (pos-ordem)");
				printf("\n 6 - exclusao elemento na arvore");        
                printf("\n 0 - Sair");
                printf("\n Escolha uma opcao: ");
                scanf("%d", &opcao);
                switch(opcao)
                {
                        case 1:
                                {
                                        lerDados (&novoElemento);
                                        raiz = inserir (raiz, &novoElemento);
                                        break;
                                }
                        case 2:
                                {  
                                        printf("\n Informe valor: ");
                        scanf("%d", &aux);        
                                    pesquisar(raiz,aux);
                                        break;        
                                }
                        case 3: preOrdem (raiz); break;
						case 4: emOrdem (raiz); break;
						case 5: posOrdem (raiz); break;
						case 6:
							{
								int aux;
								printf("\n Informe id para exclusao: ");
								scanf("%d", &aux);
								raiz = exclusao(raiz, aux); 
								break;
							}
                }
        }while (opcao != 0);
}
