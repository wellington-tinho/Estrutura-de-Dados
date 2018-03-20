//arvore binaria 

#include <stdio.h>
#include <stdlib.h>

typedef struct Arvore arv;

struct Arvore{
	int info;
	arv *dir;
	arv *esq;
};

arv* criaArvore(){
	return NULL;  //raiz da arvore inicializada em null
} 
int confere(arv* raiz){
	if(raiz==NULL) return 0;
	return 1; 
} 

void insere(arv	**raiz, int num){
	if(confere(*raiz)==0){
		(*raiz) = ((arv*)malloc(sizeof(arv)));
		(*raiz)->info = num;
		(*raiz)->dir = NULL;
		(*raiz)->esq = NULL;
	}
	else{
		if(num>(*raiz)->info) 
			   insere(&(*raiz)->dir,num);
		else{
			  insere(&(*raiz)->esq,num);
		}		
	}
}

void preOrdem(arv **raiz){//
	if(*raiz==NULL){
		return;
	}
	   	printf(" %d",(*raiz)->info);
		preOrdem(&(*raiz)->esq);
		preOrdem(&(*raiz)->dir);
	
}

void emOrdem(arv **raiz){ //
	if(*raiz==NULL){
		return;
	}
		emOrdem(&((*raiz)->esq));
		printf(" %d",(*raiz)->info);
		emOrdem(&((*raiz)->dir));
	
}

void posOrdem(arv **raiz){ //
	if(*raiz==NULL){	
		return;
     }
     posOrdem(&(*raiz)->esq);
     posOrdem(&(*raiz)->dir);
	 printf(" %d",(*raiz)->info);
	
}
arv *maiorD(arv **raiz){
		if((*raiz)->dir != NULL)
			return maiorD(&(*raiz)->dir);
		else{
			arv * ax = *raiz;
			if((*raiz)->esq!=NULL){
			   	*raiz = (*raiz)->esq;
			}else{
				 *raiz = NULL;
				 return ax;  
			}
		} printf("Erro no maior direita");
		return 0;
	  
	}

void remover (arv **raiz, int num){
	if(*raiz == NULL){
		return;
	}
	arv *aux = *raiz;
	if(num<(*raiz)->info){
		remover(&((*raiz)->esq),num);
		
	}else if(num>(*raiz)->info){
		remover(&((*raiz)->dir),num);
		
	}else if(((*raiz)->esq == NULL) && ((*raiz)->esq == NULL)){ //nao tiver nemhum filho
		free(aux);
		(*raiz) = NULL;
		
	}else if((*raiz)->esq == NULL){//filho a direita
		(*raiz) = (*raiz)->dir;
		free(aux);
		aux = NULL;	   
		
	}else if((*raiz)->dir == NULL){//filho a esquerda
		(*raiz) = (*raiz)->esq;
    	free(aux);
		aux = NULL;	
		   
    }else{
		aux = maiorD(&(*raiz)->esq);
		(*raiz)->info = aux->info;
		aux->info = num;
		remover(&(*raiz)->esq,num);
	}						
	
}

void imprima(arv *raiz){
		
	printf("\n\n [PreOrdem] ");
	preOrdem(&raiz);	
	
	printf("\n [emOrdem]  ");
	emOrdem(&raiz);
	
	printf("\n [posOrdem] ");
	posOrdem(&raiz);
}

int main(){
	arv *raiz = criaArvore();		//raiz onde ficara o primeiro elemento da arvore.
	insere(&raiz, 4);
	insere(&raiz, 5);
	insere(&raiz, 2);
	insere(&raiz, 7);
	insere(&raiz, 1);
	insere(&raiz, 3);

	imprima(raiz);
	remover(&raiz, 4);
	imprima(raiz);
	printf("\n\n");
	return 0;
	
}
