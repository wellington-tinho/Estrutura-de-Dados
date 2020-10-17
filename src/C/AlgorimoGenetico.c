#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Individuo {
    int* gene;
} Individuo;

typedef struct Populacao {
    size_t numero_individuo;
    size_t numero_cidades;
    size_t iteracao;
    double** rotas;
    Individuo* individuo;
} Populacao;

//Indentifica a distancia na matriz
int maior_numero(int a, int b) {
    return (a > b) ? a : b;
}
int menor_numero(int a, int b) {
    return (a < b) ? a : b;
}

//Cria matriz espelhada para identificar as rotas de uma cidade a outra com base no 'index'
Populacao* gera_rotas(Populacao* atual) {
    int i;
    atual->rotas = (double**)calloc(atual->numero_cidades - 1, sizeof(double*));
    for (i = 0; i < atual->numero_cidades - 1; i++) {
        atual->rotas[i] = (double*)calloc(i + 1, sizeof(double));
    }
    return atual;
}

//Gera distâncias aleatorias para as rotas criadas
void preenche_rotas(Populacao* atual) {
    int i, j;
    size_t limite = atual->numero_cidades - 1;
    for (i = 0; i < limite; i++) {
        for (j = i; j < limite ; j++) {
            atual->rotas[j][i] = 1 + rand() % 30;
            printf("[%d]-[%d] = %.2lf\n", i + 1, j + 2, atual->rotas[j][i]);
        }
    }
}

//Mostra as rotas
void mostrar_rotas_distancias(Populacao* atual) {
    int i, j;
    size_t limite = atual->numero_cidades - 1;
    for (i = 0; i < limite; i++) {
        for (j = i; j < limite ; j++) {
            printf("[%d]-[%d] = %.2lf\n", i + 1, j + 2, atual->rotas[j][i]);
        }
    }
}

//Gera os individuos iniciais
void gera_individuo(Populacao* atual) {
    int i;
    atual->individuo = (Individuo*)calloc(atual->numero_individuo, sizeof(Individuo));
    for (i = 0; i < atual->numero_individuo; i++) {
        atual->individuo[i].gene = (int*)calloc(atual->numero_cidades, sizeof(int));
    }
}

//Embaralha os genes
void embaralha_gene(Populacao* atual) {
    int pos, i, j, aux;
    srand(time(NULL));
    for (pos = 0; pos < atual->numero_individuo; pos++) {
        for (i = 0; i < atual->numero_cidades; i++) {
            j = rand() % (atual->numero_cidades);
            aux = atual->individuo[pos].gene[i];
            atual->individuo[pos].gene[i] = atual->individuo[pos].gene[j];
            atual->individuo[pos].gene[j] = aux;
        }
    }
}

//Cria o gene emordem crescente
void gera_gene(Populacao* atual) {
    int i, j;
    for (i = 0; i < atual->numero_individuo; i++) {	//denominando primeira linha para identificar individuo
        for (j = 0; j < atual->numero_cidades; j++) {
            atual->individuo[i].gene[j] = j;
        }
    }
    embaralha_gene(atual);// Chama a função de embaralhar
}

//Cria a população(Algoritmo genetico) com base no numero de cidades
Populacao* criar_populacao(int NumCit,int itera) {
    Populacao* atual = (Populacao*)calloc(1, sizeof(Populacao));
    atual->numero_cidades = NumCit;
    atual->numero_individuo = NumCit / 2;
    atual->iteracao =itera;
    atual = gera_rotas(atual);
    preenche_rotas(atual);
    gera_individuo(atual);
    gera_gene(atual);
    return atual;
}

//retorna a distância de cada individuo na struct
double distancia_individuo(Populacao* atual, int pos) {
    int i;
    unsigned coluna, linha;
    double soma = 0.0;
    for (i = 0; i < atual->numero_cidades - 1; i++) {
        linha = maior_numero(atual->individuo[pos].gene[i], atual->individuo[pos].gene[i + 1]) - 1;
        coluna = menor_numero(atual->individuo[pos].gene[i], atual->individuo[pos].gene[i + 1]);
        soma += atual->rotas[linha][coluna];
    }
    return soma;
}

//retorna as distâncias de individuos filhos mais adptados na matriz
double distancia_individuo_matriz_int(Populacao* p, int * * atual, int pos) {
    int i;
    unsigned coluna, linha;
    double soma = 0.0;
    for (i = 0; i < p->numero_cidades - 1; i++) {
        linha = maior_numero(atual[pos][i], atual[pos][i + 1]) - 1;
        coluna = menor_numero(atual[pos][i], atual[pos][i + 1]);
        soma += p->rotas[linha][coluna];
    }
    return soma;
}

//Troca os individuos
void troca_individuos(Populacao* atual, int a, int b) {
    int i, aux;
    for (i = 0; i < atual->numero_cidades; i++) {
        aux = atual->individuo[a].gene[i];
        atual->individuo[a].gene[i] = atual->individuo[b].gene[i];;
        atual->individuo[b].gene[i] = aux;
    }
}

//Ordena os individuos como Bubble Sort
void ordena_individuo(Populacao* atual) {
    int i, j;
    for (i = 0; i < atual->numero_individuo; i++) {
        for (j = 0; j < atual->numero_individuo; j++) {
            if (distancia_individuo(atual, i) < distancia_individuo(atual, j)) {
                troca_individuos(atual, i, j);
            }
        }
    }
}

//Mostra a população
void exibe_individuo(Populacao* atual) {
    int i, j;
    ordena_individuo(atual);
    for (i = 0; i < atual->numero_individuo; i++) {
        printf("individuo %d :", i + 1);
        for (j = 0; j < atual->numero_cidades; j++) {
            printf("%d ", 1 + atual->individuo[i].gene[j]);
        }
        printf(": %.3lf", distancia_individuo(atual, i));
        printf("\n");
    }
    printf("\n\n");
}

//Saber se tem gene repetido no individuo
int se_repete(int* v, int valor, int total) {
    int i, repete = 0;
    for (i = 0; i < total; i++) {
        if (v[i] == valor) {
            repete++;
            if (repete == 2) {
                return 1;
            }
        }
    }
    return 0;
}

//Saber qual gene está no individuo
int numero_existe(int* v, int valor, int total) {
    int i;
    for (i = 0; i < total; i++) {
        if (v[i] == valor) {
            return 1;
        }
    }
    return 0;
}

//Saber qual gene está faltando no individuo
int numero_falta(int* v, int total) {
    int i;
    for (i = 0; i < total; i++) {
        if (!numero_existe(v, i, total)) {
            return i;
        }
    }
    return -1;
}

//Para validar os genes, ou seja o novo individuo está perfeito
void valida_cross(Populacao* atual, int * * individuo_cross) {
    int i, j;
    for (i = 0; i < atual->numero_individuo / 2; i++) {
        for (j = 0; j < atual->numero_cidades; j++) {
            if (se_repete(individuo_cross[i], individuo_cross[i][j], atual->numero_cidades)) {
                individuo_cross[i][j] = numero_falta(individuo_cross[i], atual->numero_cidades);;
            }
        }
    }
}

//Confere se já existe um filho igual
int Confere_existencia(Populacao* atual, int * * individuo_cross,int posi) {
    int j,k,confere=0;
    for (k = 0; k < atual->numero_individuo; k++) {
        confere = 0;
        for (j = 0; j < atual->numero_cidades; j++) {
            if ((individuo_cross[posi][j])==atual->individuo[k].gene[j])
                confere++;
        }
        if (confere==atual->numero_cidades)
            return 0;
    }
    return 1;
}


//Seleciona somente os melhores
void selecao_natural(Populacao* atual, int * * individuo_cross) {
    int i,j,k;
    for (k = 0; k <atual->numero_individuo / 2 ; k++) {
        for (i = atual->numero_individuo / 2; i < atual->numero_individuo; i++) {
            if (Confere_existencia(atual,individuo_cross,(k))) //funçao confere se ja existe
                if (distancia_individuo(atual, i) > distancia_individuo_matriz_int(atual, individuo_cross,k)) {
                    for (j = 0; j < atual->numero_cidades; j++) {
                        atual->individuo[i].gene[j] = individuo_cross[k][j];
                    }
                }
        }
    }
}

//Faz a propabiblidade da mutação com Fitness de 10% ocorrer depois analisa-se se não existe individuo igual
void mutacao(Populacao* atual) {
    int i,j,caso1,caso2,aux,k,*indi_aux;
    indi_aux = (int*)calloc(atual->numero_cidades, sizeof(int));
    srand(atual->iteracao);
    i = rand() % (atual->numero_individuo); //seleciona individuo
    j= rand()%10;//probabilidade de escolha
    caso1 = rand() % (atual->numero_cidades);
    do {
        caso2 = rand() % (atual->numero_cidades);
    } while (caso2==caso1);
    if (j<1) {
        printf("\nOcorreu uma mutaçao no individuo %d\n",i+1);
        aux = atual->individuo[i].gene[caso1];
        atual->individuo[i].gene[caso1] = atual->individuo[i].gene[caso2];
        atual->individuo[i].gene[caso2] = aux;
        
        for(k = 0; k < atual->numero_cidades ; k++){
			indi_aux[k]=atual->individuo[i].gene[k];
		}
        
        //desfez
		if (Confere_existencia(atual,&indi_aux,0)) {
			printf(" \n desfez\n");
            aux = atual->individuo[i].gene[caso2];
            atual->individuo[i].gene[caso2] = atual->individuo[i].gene[caso1];
            atual->individuo[i].gene[caso1] = aux;
        }
    }
}

//Faz o croos Over para um individuo mais adptado ou não
void cross_over(Populacao* atual) {
    int i, j, aux, * * individuo_cross;
    individuo_cross = (int**)calloc(atual->numero_individuo / 2, sizeof(int*));
    for (i = 0; i < atual->numero_individuo / 2; i++) {
        individuo_cross[i] = (int*)calloc(atual->numero_cidades, sizeof(int));
    }
    ordena_individuo(atual);
    for (i = 0; i < atual->numero_individuo / 2; i ++) {
        for (j = 0; j < atual->numero_cidades; j++) {
            (individuo_cross[i][j]) = (atual->individuo[i].gene[j]);
        }
    }
    srand(atual->iteracao);
    for (i = 0; (i + 1) < atual->numero_individuo / 2; i += 2) { //pegar os primeiros individuos *os melhores*
        for (j = 0 ; j < rand() % (atual->numero_cidades  - 1) + 1; j++) { // pegar os primeiros genes para cruzar
            aux = (individuo_cross[i][j]);
            (individuo_cross[i][j]) = (individuo_cross[i + 1][j]);
            (individuo_cross[i + 1][j]) = aux;
        }
    }
    valida_cross(atual, individuo_cross);
    selecao_natural(atual, individuo_cross);
    mutacao(atual);
    for (i = 0; i < atual->numero_individuo / 2; i++) {
        free(individuo_cross[i]);
    }
    free(individuo_cross);
    exibe_individuo(atual);
}

//Libera a população
Populacao* libera_populacao(Populacao* atual) {
    int i;
    /*libera as rotas*/
    for (i = 0; i < atual->numero_cidades - 1; i++) {
        free(atual->rotas[i]);
        atual->rotas[i] = NULL;
    }
    free(atual->rotas);
    atual->rotas[i] = NULL;
    /*liberando individuo*/
    for (i = 0; i < atual->numero_individuo; i++) {
        free(atual->individuo[i].gene);
        atual->individuo[i].gene = NULL;
    }
    free(atual->individuo);
    atual->individuo = NULL;
    /*libera a populacao*/
    free(atual);
    atual = NULL;
    return atual;
}

//Chama todas as funções
int main(int argc, char const* argv[]) {
    int NumCit,itera,j;
    printf("\t Algorimo genetico \n "
           "informe com quantas cidades deseja frequentar: e quantas iterecoes deseja para descobrir a melhor rota ");
    scanf("%d %d", &NumCit, &itera);
    Populacao* atual = criar_populacao(NumCit,itera);
    printf("\n\n");
    exibe_individuo(atual);
    printf("\n");
    while (atual->iteracao-- > 0) {
        printf("\n\n iteraçao %d\n",itera-atual->iteracao);
        cross_over(atual);
    }
    printf("\n A melhor rota para passar em todas cidadades percorrendo a menor distancia \n  : ");
    for (j = 0; j < atual->numero_cidades; j++)
            printf("%d ",(atual->individuo[0].gene[j])+1);
    atual = libera_populacao(atual);
    printf("\n\n");
    return 0;
}