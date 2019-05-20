#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMNOME 100
#define TAMMAX 100

// Codigo das Rotas Terrestres

	void mostraCidades(char cidades[TAMMAX][TAMNOME]){
		system("cls");
		printf("----- Cidades Existentes -----\n");
		for(int i = 0; i < TAMMAX; i++){
			if(strcmp(cidades[i],"") != 0){
				printf("Codigo:%d\tCidade:%s\n",i,cidades[i]);
			}else{
				return;
			}
		}
		
	}

	/*Reserva uma linha e uma coluna na matriz de adjacência para representar a cidade inserida*/
	void insereCidade(char cidades[TAMMAX][TAMNOME], double distancias[TAMMAX][TAMMAX]){
		system("cls");
		char nome[TAMMAX];
		printf("----- Adicionar Cidade -----\n");
		printf("Digite o nome da cidade:");
		// Utilizar a função scanf com %s nao funciona pois nome de cidades compostas, ou seja, que tenha espaço buga o programa
		fflush(stdin);
		gets(nome);

		// percorre a lista de nomes para ver se a cidade ja foi inserida
		for(int i = 0; i < TAMMAX; i++){
			// Como nao ha remocao de cidade o espaco vazio no nome sempre simbolizara o tamanho atual do vetor -1
			if(strcmp(cidades[i],"") != 0){
				if(strcmp(cidades[i],nome) == 0){
					printf("\n** Cidade ja existe no sistema. **\n\n");
					return;
				}
			}else{
				strcpy(cidades[i],nome);
				break;
			}
		}		
	} 

	/*ocorre similarmente à inserção de rotas, porém a rota deverá estar previamenteinserida*/
	void atualizaRotaTerrestre(double distancia[TAMMAX][TAMMAX], int i, int j){
		char escolha;
		do{
			printf("Atualizar distancias entre as cidades? (s/n):");
			fflush(stdin);
			scanf("%c",&escolha);
			if(escolha == 'n' || escolha == 'N'){
				return;
			}
		}while (!(escolha == 'S' || escolha == 's' || escolha == 'n' || escolha == 'N'));
		
		double dist;
		do{
			printf("Nova distancia entre as cidades:");
			scanf("%lf",&dist);
		}while (dist<=0);

		distancia[i][j] = dist;

	}

	/*Insere uma rota entre um par de cidades*/
	void insereRotaTerrestre(char cidade[TAMNOME][TAMNOME], double distancia[TAMMAX][TAMMAX]){
		system("cls");

		mostraCidades(cidade);
		
		int codigo, codigo2;
		do{
			printf("----- Adicionar Rota -----\n");
			printf("Digite o codigo da cidade:");
			scanf("%d",&codigo);

			if(strcmp(cidade[codigo],"") == 0){
				printf("\n** Cidade nao existe no sistema. **\n\n");
				system("pause");	
				system("cls");
			}
		}while(strcmp(cidade[codigo],"") == 0);

		do{
			printf("Digite o codigo da cidade que tera ligacao:");
			scanf("%d",&codigo2);
			if(strcmp(cidade[codigo2],"") == 0){
				printf("\n** Cidade nao existe no sistema. **\n\n");
				system("pause");	
				system("cls");
			}
		} while (strcmp(cidade[codigo2],"") == 0);

		// Verifica qual codigo é maior para poder localizar a distancia na matriz superior
		int i, j;
		if(codigo > codigo2){
			i = codigo;
			j = codigo2;
		}else{
			i = codigo2;
			j = codigo;
		}

		// verifica se a rota ja foi criada anteriormente
		if(distancia[i][j] > 0){
			atualizaRotaTerrestre(distancia,i,j);
		}else{
			double dist;
			do{
				printf("Distancia entre as cidades %s->%s:",cidade[i],cidade[j]);
				scanf("%lf",&dist);
			}while (dist<=0);
			
			distancia[i][j] = dist;
		}
	}

	/*Após o usuário escolher uma cidade, lista todas as cidades vizinhas, inclusive com asdistâncias para cada uma delas*/
	void listaCidadesVizinhas(char cidade[TAMMAX][TAMNOME], double distancia[TAMMAX][TAMMAX]){

		system("cls");

		mostraCidades(cidade);
		
		int codigo;
		do{
			printf("----- Lista Cidades Vizinhas -----\n");
			printf("Digite o codigo da cidade:");
			scanf("%d",&codigo);

			if(strcmp(cidade[codigo],"") == 0){
				printf("\n** Cidade nao existe no sistema. **\n\n");
				system("pause");	
				system("cls");
			}
		}while(strcmp(cidade[codigo],"") == 0);

		printf("\n\n----- Cidades Vizinhas de %s -----\n", cidade[codigo]);
		for(int i = 0; i < codigo; i++){
			if(distancia[codigo][i] > 0){
				if(strcmp(cidade[i],"") != 0){
					printf("\t-> Codigo:%d\tCidade:%s\tDistancia:%.2lf\n",i,cidade[i],distancia[codigo][i]);
				}
			}
		}
		for(int i = codigo; i < TAMMAX; i++){
			if(distancia[i][codigo] > 0){
				if(strcmp(cidade[i],"") != 0){
					printf("\t-> Codigo:%d\tCidade:%s\tDistancia:%.2lf\n",i,cidade[i],distancia[i][codigo]);
				}
			}
		}
	}


	/*Retorna o somatório de todas as distâncias das rotas terrestres cadastradas*/
	void calculaDistTerrestres(char cidade[TAMMAX][TAMNOME], double distancia[TAMMAX][TAMMAX]){
		if(strcmp(cidade[0],"") != 0){
			double somatorio = 0;
			for(int i = 0; i < TAMMAX; i++){
				for(int j = 0; j < TAMMAX; j++){
					somatorio += distancia[i][j];
				}
			}
			printf("\nSomatorio de todos os Voos cadastrados:%.2lf",somatorio);
		}else{
			printf("\n** Nao ha cidades cadastradas no sistema. **\n\n");
		}
	}

// Fim Codigo das Rotas Terrestres

// Codigo das Rotas Aereas
	int indice=0;

	// Lista de adjacentes
		// Tipo Item da Lista Principal

		typedef struct TipoCelula *TipoApontadorLista;
		typedef struct TipoCelulaVet *TipoApontadorVet;

		// Celula que mostra as cidades disponiveis do Item da Lista Principal 
		struct TipoCelulaVet{
			int indice;
			char nome[TAMNOME];
			double custoVoo;
			TipoApontadorVet prox;
		};
		
		// Celula Principal da Lista
		struct TipoCelula{
			int indice;
			char nome[TAMNOME];
			TipoApontadorVet primeiro; 
			TipoApontadorLista prox;
		};
		
		// Estrutura Principal da Lista
		struct TipoLista{
			TipoApontadorLista primeiro,ultimo;
		};

		// Zera a lista colocando Null
		void FListaVazia(TipoLista *lista){
			lista->primeiro = (TipoApontadorLista) malloc(sizeof(TipoCelula));
			lista->ultimo = lista->primeiro;
			lista->primeiro->prox = NULL;
			lista->primeiro->primeiro = NULL;
		}

		// Verifica se a lista esta vazia
		int ListaVazia(TipoLista lista){
			return (lista.primeiro==lista.ultimo);
		}

		void InsereLista(int indice, char nome[TAMNOME],TipoLista *lista){
			lista->ultimo->prox = (TipoApontadorLista) malloc(sizeof(TipoCelula));
			lista->ultimo = lista->ultimo->prox;
			lista->ultimo->indice = indice;
			strcpy(lista->ultimo->nome,nome);
			lista->ultimo->primeiro = NULL;
			lista->ultimo->prox = NULL;
		}

		void InsereVet(int numIndice, char nome[TAMNOME], double custoVoo, TipoApontadorVet *auxVet){
			(*auxVet)->indice = numIndice;
			strcpy((*auxVet)->nome,nome);
			(*auxVet)->custoVoo = custoVoo;
			(*auxVet)->prox = NULL;
		}

		void mostraAeroportos(TipoLista lista){
			TipoApontadorLista aux;

			aux = lista.primeiro;
			system("cls");
			printf("---- Cidades -----\n");
			while(aux!=NULL){
				printf("Indice:%d", aux->indice);
				printf("\nCidade:%s\n\n", aux->nome);
				aux = aux->prox;
			}
		}

		TipoApontadorLista buscaRotaAerea(TipoLista lista, int numIndice){
			TipoApontadorLista aux;

			aux = lista.primeiro;
			while(aux!=NULL){
				if(aux->indice == numIndice)
					return aux;

				aux = aux->prox;
			}

			return NULL;
		}

	// Fim lista de adjacentes

	/*Reserva uma posição na lista de adjacência para representar o aeroporto inserido*/
	void insereAeroporto(TipoLista *lista){

		mostraAeroportos(*lista);

		char cidade[TAMNOME];

		system("cls");
		printf("----- Adicionar Aeroporto -----\n");
		printf("Nome da Cidade:");
		scanf("%s", &cidade);
		
		// Caso nao tenha nenhum elemento na lista
		if(indice == 1 ){
			InsereLista(indice++, cidade, lista);
			lista->primeiro = lista->primeiro->prox;
		}else{

			TipoApontadorLista aux = lista->primeiro;
			while(aux != NULL){
				if (strcmp(cidade, aux->nome) == 0){
					printf("\n** Aeroporto ja existe no sistema. **\n\n");
					return;
				}
				aux = aux->prox;
			}

			InsereLista(indice++, cidade, lista);
		}
		
		mostraAeroportos(*lista);
	}
	
	/*Utilize as mesmas considerações para a atualização de rotas terrestres, porém para omódulo de aeroportos e rotas aéreas*/
	void atualizaRotaAerea(TipoApontadorVet aux){
		char escolha;
		
		do{
			printf("Atualizar Rota ? (s/n):");
			fflush(stdin);
			scanf("%c",&escolha);
		}while(!(escolha == 'S' || escolha == 's' || escolha == 'n' || escolha == 'N'));

		if(escolha == 'S' || escolha == 's'){
			double custoVoo;
			do{
				printf("Novo valor da rota:");
				scanf("%lf",&custoVoo);
			}while(custoVoo < 0);

			aux->custoVoo = custoVoo;
		}
	}
	
	/*Insere uma rota de um aeroporto para outro*/
	void insereRotaAerea(TipoLista lista){

		mostraAeroportos(lista);

		int numIndice;

		system("cls");
		mostraAeroportos(lista);
		printf("----- Adicionar Rota Aerea -----\n");
		printf("Indice do Aeroporto:");
		scanf("%d", &numIndice);
		
		// Aux e o aeroporto Origem, Aux2 e o aeroporto Destino
		TipoApontadorLista aux = buscaRotaAerea(lista, numIndice), aux2;

		if (aux == NULL){
			printf("\n** Aeroporto nao existe no sistema. **\n");
		}else{
			char escolha;
			do{
				printf("\nO aeroporto que sera adicionado rotas areas e '%s' ? (s/n)\n", aux->nome);
				printf("Opcao:");
				fflush(stdin);
				scanf("%c",&escolha);
			}while(!(escolha == 'S' || escolha == 's' || escolha == 'N' || escolha == 'n'));
			
			if (escolha == 'S' || escolha == 's'){
				// Usuario Indica o indice do aeroporto destino
				printf("Indice do aeroporto destino:", aux->nome);
				scanf("%d",&numIndice);
				
				if (numIndice == aux->indice){
					printf("\n** Nao e possivel adicionar rota aerea para o mesmo aeroporto. **\n ");
				}else{

					// Busca na Lista se o indice que será adicionado como destino existe
					aux2 = buscaRotaAerea(lista, numIndice);
				
					if(aux2 == NULL){
						printf("\n** Aeroporto nao existe no sistema. **\n");
					}else{
						
						TipoApontadorVet vet = aux->primeiro;
						
						// verifica se ja foi adicionado esta rota aerea
						while(vet != NULL){
							if (vet->indice == numIndice){
								atualizaRotaAerea(vet);
								return;
							}
							vet = vet->prox;
						}

						// retorna a primeira posicao do vetor
						vet = aux->primeiro;
						double custoVoo;
						do{
							printf("Custo do Voo entre  %s -> %s:", aux->nome, aux2->nome);
							scanf("%lf",&custoVoo);
						}while(custoVoo < 0);
						
						// Caso o aeroporto não tenha nenhuma rota aerea
						if(vet == NULL){
							aux->primeiro = (TipoApontadorVet) malloc(sizeof(TipoCelulaVet));
							InsereVet(aux2->indice,aux2->nome,custoVoo,&(aux->primeiro));
						}else{
							// Percorre ate a ultima casa da Lista
							while(true){
								if(vet->indice == numIndice){
									printf("\n** Rota Ja Cadastrada no sistema. **\n");
									return;
								}
								if(vet->prox == NULL){
									break;
								}
								vet = vet->prox;
							}
							vet->prox = (TipoApontadorVet) malloc(sizeof(TipoCelulaVet));
							InsereVet(aux2->indice,aux2->nome,custoVoo,&(vet->prox));
						}
						
					}
				}
			}
		}

	}

	/*Após o usuário escolher um aeroporto, lista todos os aeroportos que possuem rotasde destino cadastradas, inclusive com os custos totais para cada uma delas*/
	void listaAeroportosDestino(TipoLista *lista){		

		mostraAeroportos(*lista);

		system("cls");
		int numIndice;
		printf("----- Pesquisar Rotas Destino do Aeroporto -----\n");
		printf("Indice do aeroporto:");
		scanf("%d",&numIndice);
		
		TipoApontadorLista aux = buscaRotaAerea(*lista,numIndice);
		
		if(aux == NULL){
			printf("\n** Aeroporto nao existe no sistema. **\n");
		}else{		
			if(aux->primeiro == NULL){
				printf("\n** Aeroporto nao contem rotas aereas. **\n");
			}else{
				TipoApontadorVet vet = aux->primeiro;
				
				printf("\n---- Rotas Aereas do aeroporto '%s' ----\n", aux->nome);
				while(vet != NULL){
					printf("\tIndice do Aeroporto:%d\t Custo do Voo:%.2lf\tNome:%s\n",vet->indice,vet->custoVoo,vet->nome);
					vet = vet->prox;
				}
			}
		}
	}

	/*Após o usuário escolher um aeroporto, lista todos os aeroportos que possuem rotasde origem cadastradas, inclusive com os custos totais para cada uma delas*/
	void listaAeroportosOrigem(TipoLista *lista){

		mostraAeroportos(*lista);

		system("cls");
		int numIndice;
		printf("----- Pesquisar Rotas Origem do Aeroporto -----\n");
		printf("Indice do aeroporto:");
		scanf("%d",&numIndice);
		
		TipoApontadorLista auxLista = buscaRotaAerea(*lista,numIndice);
		
		if(auxLista == NULL){
			printf("\n** Aeroporto nao existe no sistema. **\n\n");
		}else{		

			printf("\n---- Rotas Aereas que levam ao aeroporto '%s' ----\n",auxLista->nome);
			// Volta o apontador para a primeira posi��o da Lista
			auxLista = lista->primeiro;
			
			while(auxLista != NULL){
				TipoApontadorVet auxVet = auxLista->primeiro;
				if (auxVet != NULL){
					while(auxVet != NULL){
						if (auxVet->indice == numIndice){
							printf("\t->Indice da Cidade:%d\tCidade:%s\n",auxLista->indice, auxLista->nome);
							break;
						}
						auxVet = auxVet->prox;
					}
				}
				auxLista = auxLista->prox;
			}
		}
	}
	
	/*Com base na informação de um nome de aeroporto, realiza a deleção de um aeroporto dede todas as rotas aéreas de origem/destino vinculadas ao tal*/
	void removeAeroporto(TipoLista *lista){
		TipoApontadorLista auxLista;

		mostraAeroportos(*lista);

		int numIndice;
		printf("Digite o codigo do aeroporto a ser excluido:");
		scanf("%d",&numIndice);

		


	}
	/*Após a escolha de dois aeroportos, realiza a remoção de uma rota aérea;◦Caso os aeroportos não existam, emitir uma mensagem de erro*/
	void removeRotaAerea(TipoLista *lista){
		system("cls");

		if(lista->primeiro != lista->ultimo){

			mostraAeroportos(*lista);

			int numIndice;
			printf("----- Remover Rotas Aerea do Aeroporto -----\n");
			printf("Indice do aeroporto:");
			scanf("%d",&numIndice);
			
			// verifica se o aeroporto existe
			TipoApontadorLista auxLista = buscaRotaAerea(*lista,numIndice),auxLista2;
			TipoApontadorVet auxVet = auxLista->primeiro;
			
			if(auxLista == NULL){
				printf("\n** Aeroporto nao existe no sistema. **\n\n");
			}else if(auxLista->primeiro == NULL){
				printf("\n** Aeroporto nao contem rotas. **\n\n");
			}else{

				int numIndice2;
		
				printf("Rota Aereas a ser removida:");
				scanf("%d",&numIndice2);
				
				// Verifica se o aeroporto a ser removido existe
				auxLista2 = buscaRotaAerea(*lista,numIndice);

				if(auxLista == NULL){
					printf("\n** Aeroporto nao existe no sistema. **\n\n");
				}else{		
					// Caso seja a primeira rota aerea
					if(auxLista->primeiro->indice == numIndice2){
						TipoApontadorVet auxVet2 = auxLista->primeiro;

						auxLista->primeiro = auxVet->prox;
						free(auxVet2);
						return;
					}

					while(auxVet->prox != NULL){
						if(auxVet->prox->indice == numIndice2){
							break;
						}
						auxVet = auxVet->prox;
					}

					if (auxVet->prox == NULL) {
						printf("Nao existe essa rota aerea dentro deste aeroporto\n");
					}else{
						TipoApontadorVet auxVet2 = auxVet->prox;

						auxVet->prox = auxVet->prox->prox;
						free(auxVet2);
					}
				}
			}
		}else{
			printf("\n** Nao ha aeroportos cadastrados no sistema. **\n\n");			
		}
	}
	/*Retorna o somatório de todas as distâncias das rotas aéreas cadastradas*/
	void calculaDistAereas(TipoLista lista){
		
		system("cls");
		double somatorio = 0;
		if(lista.primeiro != lista.ultimo){
			TipoApontadorLista auxLista = lista.primeiro;
			while(auxLista != NULL){
				TipoApontadorVet auxVet = auxLista->primeiro;
				while(auxVet != NULL){
					somatorio += auxVet->custoVoo;
					auxVet = auxVet->prox;
				}
				auxLista = auxLista->prox;
			}

			printf("\nSomatorio de todos os Voos cadastrados:%.2lf",somatorio);
		}else{
			printf("\n** Nao ha aeroportos cadastrados no sistema. **\n\n");
		}
	}

// Fim Codigo das Rotas Aereas


/* Atribui o valor 0 (zero) as posições da matriz de adjacência e configura a lista de adjacênciade 
modo que todas as posições dos vértices apontem para NULL (ou seja, inicialmente não há vizinhança)*/
void inicializaGrafo(TipoLista *lista, double distancia[TAMMAX][TAMMAX], char cidades[TAMMAX][TAMNOME]){

	// Matriz de adjacencia
	for(int i = 0; i < TAMMAX; i++){
		// Limpa matriz
		for(int j = 0; j < TAMMAX; j++){
			distancia[i][j] = 0;
		}

		// Limpa a lista de nomes de cidade
		strcpy(cidades[i],"");
	}

	// Lista de adjacencia
	FListaVazia(lista);
	indice = 1;
}

void menuTerrestre(char cidades[TAMMAX][TAMNOME], double distancia[TAMMAX][TAMMAX]){

	while(true){

		int escolha;

		system("cls");
		printf("----- Menu Terrestre -----\n");
		printf("0 - Voltar.\n");
		printf("1 - Inserir Cidade.\n");
		printf("2 - Inserir Rota.\n");
		printf("3 - Mostrar Cidades Vizinhas.\n");
		printf("4 - Somatorio de todas rotas as cidades.\n");
		printf("Opcao:");
		scanf("%d",&escolha);

		switch(escolha){
			case 0:
				return;
			case 1:
				insereCidade(cidades,distancia);
				break;
			case 2:
				insereRotaTerrestre(cidades,distancia);
				break;
			case 3:
				listaCidadesVizinhas(cidades,distancia);
				break;
			case 4:
				calculaDistTerrestres(cidades,distancia);
				break;
			default:
				printf("Opcao escolhida invalida!\n");
				break;
		}		
	printf("\n\n");
	system("pause");
	}
}

void menuAero(TipoLista *aeroporto){

	while(true){

		int escolha;

		system("cls");
		printf("----- Menu Aero -----\n");
		printf("0 - Voltar.\n");
		printf("1 - Inserir Aeroporto.\n");
		printf("2 - Inserir Rota Aerea.\n");
		printf("3 - Mostrar Aeroportos Destino.\n");
		printf("4 - Mostrar Aeroportos Origem.\n");
		printf("5 - Remover Rota Aerea.\n");
		printf("6 - Remover Aeroporto.\n");
		printf("7 - Somatorio de todas rotas aereas.\n");
		printf("Opcao:");
		scanf("%d",&escolha);

		switch(escolha){
			case 0:
				return;
			case 1:
				insereAeroporto(aeroporto);
				break;
			case 2:
				insereRotaAerea(*aeroporto);
				break;
			case 3:
				listaAeroportosDestino(aeroporto);
				break;
			case 4:
				listaAeroportosOrigem(aeroporto);
				break;
			case 5:
				removeRotaAerea(aeroporto);
				break;
			case 6:
				removeAeroporto(aeroporto);
				break;
			case 7:
				calculaDistAereas(*aeroporto);
				break;
			default:
				printf("Opcao escolhida invalida!\n");
				break;
		}		
		printf("\n\n");
		system("pause");
	}
}

main(){
	TipoLista aeroporto;

	double distanciaTerrestre[TAMMAX][TAMMAX];
	char cidades[TAMMAX][TAMNOME];
	inicializaGrafo(&aeroporto, distanciaTerrestre, cidades);

	while(true){
		
		int escolha;
		
		system("cls");
		printf("----- Menu -----\n");
		printf("1 - Rota Terrestre.\n");
		printf("2 - Rota Aerea.\n");
		printf("3 - Sair.\n");
		printf("Opcao:");
		scanf("%d",&escolha);

		switch(escolha){
			case 1:
				menuTerrestre(cidades,distanciaTerrestre);
				break;
			case 2:
				menuAero(&aeroporto);
				break;
			case 3:
				exit(0);
				break;
			default:
				printf("Opcao escolhida invalida!\n");
				system("pause");
				break;
		}
	}
}
