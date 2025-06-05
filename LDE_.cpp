#include <stdio.h>
#include <stdlib.h>

struct dados{
	struct dados *esq;
	int info;
	struct dados *dir;
};

typedef struct dados NO;

void Ins_Inicio(NO **Inicio, NO **Fim, int val){
	NO *p;
	
	p=(NO *)calloc(1, sizeof(NO));
	p->info = val;
	p->esq = NULL;
	p->dir = *Inicio;
	if(*Inicio == NULL){
		*Fim = p;
	}else
		(*Inicio)->esq = p;
	*Inicio = p;
}

void Ins_Fim(NO **Inicio, NO **Fim, int val){
	NO *p;
	
	p = (NO *)calloc(1, sizeof(NO));
	p->info = val;
	p->dir = NULL;
	p->esq = *Fim;
	if(*Inicio == NULL){
		*Inicio = p;
	}else
		(*Fim)->dir = p;
	*Fim = p;
}

void Imprime(NO *Inicio)
{
	NO *p;
	
	p = Inicio;
	
	printf("\nNULL");
	while (p!=NULL)
	{
		printf("<--%d-->", p->info);
		p = p->dir;
	}
	printf("NULL\n");
}

void Rem_Inicio(NO **Inicio,NO **Fim){
	NO *p;
	
	p = *Inicio;
	
	if(*Inicio == *Fim) // Só existe 1 nó na lista
	{
		*Inicio = NULL;
		*Fim = NULL;
	}
	else
	{
		*Inicio = p->dir;
		(*Inicio)->esq = NULL;
	}
	free(p);
}

void Rem_Fim(NO **Inicio,NO **Fim){
	NO *p;
	
	p = *Fim;
	
	if(*Inicio == *Fim) // Só existe 1 nó na lista
	{
		*Inicio = NULL;
		*Fim = NULL;
	}
	else
	{
		*Fim = p->esq;
		(*Fim)->dir = NULL;
	}
	free(p);
}

NO *Consulta(NO *Inicio, int val){
	NO *p;
	
	p = Inicio;
	while(p!=NULL && p->info!=val)
		p = p->dir;
	
	return p;
}

void Rem_Meio(NO *r){
	NO *p, *q;
	
	p = r->esq;
	q = r->dir;
	
	p->dir = q;
	q->esq = p;
	
	free(r);
}

void Ins_Depois(NO *r, int val){
	NO *p, *q;
	
	p = (NO *)calloc(1, sizeof(NO));
	
	q = r->dir;
	
	p->info = val;
	p->dir = q;
	p->esq = r;
	
	r->dir = p;
	q->esq = p;
}

void Transf_Fim(NO **Inicio, NO **Fim, NO *r)
{
	NO *p, *q;
	
	if(r != *Inicio)
	{
	p = r->esq;
	q = r->dir;
	p->dir = q;
	q->esq =p;
	}
	else{
		*Inicio = r->dir;
		(*Inicio)->esq = NULL;
	}
	
	r->dir = NULL;
	r->esq = *Fim;
	(*Fim)->dir = r;
	*Fim = r;
}

void Transf_Inicio(NO **Inicio, NO **Fim, NO *r)
{
	NO *p, *q;
	
	if(r != *Fim)
	{
	p = r->esq;
	q = r->dir;
	p->dir = q;
	q->esq =p;
	}
	else{
		*Fim = r->esq;
		(*Fim)->dir = NULL;
	}
	
	r->esq = NULL;
	r->dir = *Inicio;
	(*Inicio)->esq = r;
	*Inicio = r;
}

Rem_repetidos(NO **Inicio, NO **Fim)
{
	NO *p, *q;
	
	p = *Inicio;
	q = p->dir;
	while(p!=*Fim){
		while(q!=NULL){
			if(q->info == p->info){
				if(q != *Fim)
					Rem_Meio(q);
				else
					Rem_Fim(Inicio, Fim);
				q = p->dir;
			}
			else
			    q = q->dir;
		}
		p = p->dir;
	}
}

main(){
	NO *Inicio, *Fim, *r;
	int val, op;
	
	// Criando a lista vazia
	
	Inicio = NULL;
	Fim = NULL;
	
	do{
		system("cls");
		printf("\n1 - Inserir no Inicio");
		printf("\n2 - Inserir no Fim");
		printf("\n3 - Imprimir a Lista");
		printf("\n4 - Remover no Inicio");
		printf("\n5 - Remover no Fim");
		printf("\n6 - Consultar um Valor");
		printf("\n7 - Remover um Valor");
		printf("\n8 - Inserir depois de um valor");
		printf("\n9 - Transferir valor para o Fim");
		
		printf("\n10 - Transferir valor para o Inicio");
		
		printf("\n11 - Remover valores repetidos");
		/*
		
		está opção valera nota = 2.5 pontos.
		
		vc deve implementar um algoritmo que remova todos os
		valores que se repetem. Ao terminar, na lista restará
		apenas um valor de cada.
		
		Dica: Use os algoritmos já prontos: Rem_Fim e Rem_Meio
		
		*/
		
		printf("\n0 - Sair do programa");
		
		printf("\nDigite a opcao: ");
		scanf("%d", &op);
		
		switch(op)
		{
			case 1: printf("Digite o valor a inserir: ");
					scanf("%d", &val);
					Ins_Inicio(&Inicio, &Fim, val);
					break;
			
			case 2: printf("Digite o valor a inserir: ");
					scanf("%d", &val);
					Ins_Fim(&Inicio, &Fim, val);
					break;
			
			case 3: if( Inicio == NULL)
						printf("\nLista Vazia!\n");
					else
						Imprime(Inicio);
					system("pause");
					break;
					
			case 4: if(Inicio == NULL)
						printf("\nLista Vazia!\n");
					else
						Rem_Inicio(&Inicio, &Fim);
					system("pause");
					break;
			
			case 5: if(Inicio == NULL)
						printf("\nLista Vazia!\n");
					else
						Rem_Fim(&Inicio, &Fim);
					system("pause");
					break;
					
			case 6: printf("\nDigite o valor a procurar: ");
					scanf("%d", &val);
					
					r = Consulta(Inicio, val);
					
					if(r==NULL)
						printf("\nValor nao existe!\n");
					else
						printf("\nValor: %d\n", r->info);
						
					system("pause");
					break;
					
			case 7: printf("\nDigite o valor a remover: ");
					scanf("%d", &val);
					
					r = Consulta(Inicio, val);
					
					if(r==NULL)
						printf("\nValor nao existe!\n");
					else{
					
						if(r==Inicio)
							Rem_Inicio(&Inicio, &Fim);
						else
							if(r==Fim)
								Rem_Fim(&Inicio, &Fim);
							else
								Rem_Meio(r);
					}
					system("pause");
					break;		
					
			case 8: printf("\nDigite o valor a procurar: ");
					scanf("%d", &val);
					
					r = Consulta(Inicio, val);
					
					if(r==NULL)
						printf("\nValor nao existe!\n");
					else
					{
						printf("\nDigite o valor a inserir: ");
						scanf("%d", &val);
						if(r == Fim)
							Ins_Fim(&Inicio, &Fim, val);
						else
							Ins_Depois(r, val);
					}
					system("pause");
					break;
					
			case 9: printf("\nDigite o valor a transferir: ");
				scanf("%d", &val);
				
				r = Consulta(Inicio, val);
				
				if(r==NULL)
					printf("\nValor nao existe!\n");
				else
				{
					if(r==Fim)
						printf("\nValor ja eh o ultimo!\n");
					else
						Transf_Fim(&Inicio, &Fim, r);	
				}
				system("pause");
				break;
		
		case 10: printf("\nDigite o valor a transferir: ");
				scanf("%d", &val);
				
				r = Consulta(Inicio, val);
				
				if(r==NULL)
					printf("\nValor nao existe!\n");
				else
				{
					if(r==Inicio)
						printf("\nValor ja eh o primeiro!\n");
					else
						Transf_Inicio(&Inicio, &Fim, r);	
				}
				system("pause");
				break;
		
		case 11: Rem_repetidos(&Inicio, &Fim);
				 printf("\nLista com as remocoes:\n");
				 Imprime(Inicio);
				 system("pause");
				 break;
			}
		
	}while (op!=0);
	
}
