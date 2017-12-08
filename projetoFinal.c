#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

/*
 * UNIVERSIDADE FEDERAL DE GOIÁS - INSTITUTO DE INFORMÁTICA
 * Sistema de controle de transações financeiras
 * Curso: Sistemas de Informação
 * Aluno: Orlando da Cruz Pereira Júnior
 * Matrícula: 201301679
 * 08.12.2017 09:44:50
*/
 
typedef struct endereco{
	char logradouro[100];
	char complemento[100];
	char CEP[50];
	char bairro[50];
	char cidade[50];
	char estado[50];
};

typedef struct Cliente{
	int codigo;
	char nome[100];
	char CNPJ_CPF[14];
	char telefone[11];
	struct endereco este_endereco;
} Cliente;

typedef struct Conta{
	int codigoCliente;
	int agencia;
	int numero;
	struct Cliente este_cliente;
	int saldo;
}Conta;

typedef struct Transacao{
	char tipo[50];
	int valor;
	char data[10];
	struct Conta esta_conta;
	char descricao[100];
} Transacao;

int aux, i, qtd, j, cont, ultimo, agencia, conta, agenciaD, contaD;
int valor, tamanho = 1, tamanhoC = 1, op; 
char temp[50];
char D[10] = "DEBITO";
char C[10] = "CREDITO";

Transacao vetorT[1000];
Conta vetorConta[1000];
Cliente vetor[]; //tamanho do vetor de clientes
struct Cliente cliente;

void cadastrarCliente(char nomeArquivo[]);
void listarClientes(int i);
void buscarCliente(int aux, int tamanho);
void atualizarCliente(int aux, int tamanho);
void excluirCliente(int aux);

void listarTodasAsContas(int aux);
void cadastrarConta(int aux, int tamanho, int tamanhoC);
void listarContas(int aux, int tamanho, int tamanhoC);
void saqueEmConta(int agencia, int conta, int tamanhoC);
void depositoEmConta(int agencia, int conta, int aux, int tamanhoC, int op);
void transferenciaEntreContas(int agencia, int conta, int agenciaD, int contaD, int tamanhoC, int op);
void extratoDeUmaConta(int agencia, int conta, int tamanhoC);

void MensagemSuperior(){
    system("color 5F");//17
    system("mode con:cols=80 lines=25");
    system("cls");
    printf("Universidade Federal de Goias - UFG - Goiania GO\n");
    printf("Instituto de informatica - Programacao Imperativa\n");
    printf("Bacharelado Sistemas de Informacao 2017-2\n");
    printf(" ------------------------------------------------------------------------------ \n");
    Centraliza("SIMULACAO SISTEMA BANCARIO - ITAU UNIBANCO S.A.");
    Centraliza("DEMO Version 1.0 - Itau mais seguranca para voce");
    Centraliza("SAC: 0800 728 0728 Ouvidoria: 0800 570 0011");
    printf("\n");
}

void Centraliza(char Mensagem[]){ //Centraliza as mensagem na tela
    int i;
    for(i = 0; i < ((80 - strlen(Mensagem)) / 2); i++)
        printf(" ");
    printf("%s\n", Mensagem);
}

int main(){
	char opcao[10], opcaoC1[10], opcaoT1[10];

	//limpa codigos
	for(i=0; i<10; i++){
		vetor[i].codigo = NULL;
	}
	
	while(strcmp(opcao, "S")){
		
		MensagemSuperior();
		
		printf(" ##############################################################################\n");
	    printf(" |   Digite um comando para prosseguir:                                       |\n");
	    printf(" |   C - Gerenciar Clientes                                                   |\n");
	    printf(" |   T - Gerenciar Contas                                                     |\n");
	    printf(" |   S - Sair                                                                 |\n");
	    printf(" ##############################################################################\n");
	    printf("  Digite a opcao escolhida: \n");
		scanf("%s",opcao);
		
		if( strcmp(opcao, "C") == 0){
			MensagemSuperior();
			printf("================ Gerenciar Clientes ================\n");
			printf("Digite um comando para prosseguir\n");
			printf("C - Cadastrar um cliente\n");
			printf("L - Listar todos os clientes cadastrados\n");
			printf("B - Buscar cliente ja cadastrado\n");
			printf("A - atualizar um cliente cadastrado\n");
			printf("E - Excluir um cliente cadastrado\n");
			scanf("%s",opcaoC1);
			
			if( strcmp(opcaoC1, "C") == 0){
				MensagemSuperior();
				printf("C - Cadastrar um cliente\n");
				cadastrarCliente("Clientes.txt");
				tamanho++;
			}
			if( strcmp(opcaoC1, "L") == 0){
				
				printf("L - Listar todos os clientes cadastrados\n");
				//tamanho = 3; // sem dados preenchidos apague esta linha
				listarClientes(tamanho);
	
			}
			if( strcmp(opcaoC1, "B") == 0){
				MensagemSuperior();
				printf("Escolha o criterio da pesquisa\n");
				printf("1 - Nome\n");
				printf("2 - Codigo\n");
				printf("3 - CPF ou CNPJ\n");
				scanf("%d",&aux);
				buscarCliente(aux, tamanho);
	
			}
			if( strcmp(opcaoC1, "A") == 0){
				MensagemSuperior();
				printf("Atualizar cliente - Escolha um criterio para atualizacao\n");
				printf("1 - Nome\n");
				printf("2 - Codigo\n");
				printf("3 - CPF ou CNPJ\n");
				scanf("%d",&aux);
				atualizarCliente(aux, tamanho);
	
			}
			if( strcmp(opcaoC1, "E") == 0){
				MensagemSuperior();
				printf("Excluir cliente - Escolha um criterio para exclusao\n");
				printf("1 - Nome\n");
				printf("2 - Codigo\n");
				printf("3 - CPF ou CNPJ\n");
				scanf("%d",&aux);
				excluirCliente(aux);
				tamanho = tamanho - 1;
			}
		}
		if( strcmp(opcao, "T") == 0){
			MensagemSuperior();
			printf("================ Gerenciar Contas ================\n");
			printf("Digite um comando para prosseguir\n");
			printf("R - Listagem de todas as contas cadastradas.\n");
			printf("C - Cadastrar uma conta para um cliente.\n");
			printf("L - Listar todas as contas de um cliente.\n");
			printf("S - Realizar um saque de uma conta.\n");
			printf("D - Realizar um deposito em uma conta.\n");
			printf("T - Realizar transferencias entre contas.\n");
			printf("E - Exibir extrato de uma conta.\n");
			scanf("%s",opcaoT1);
			
			if( strcmp(opcaoT1, "R") == 0){
				MensagemSuperior();
				printf("R - Listagem de todas as contas cadastradas.\n");
				listarTodasAsContas(tamanhoC);
			}
			if( strcmp(opcaoT1, "C") == 0){
				MensagemSuperior();
				printf("C - Cadastrar uma conta para um cliente.\n");
				printf("Escolha o criterio da pesquisa\n");
				printf("1 - Nome\n");
				printf("2 - Codigo\n");
				printf("3 - CPF ou CNPJ\n");
				scanf("%d",&aux);
				cadastrarConta(aux, tamanho, tamanhoC);
				tamanhoC++;
			}
			if( strcmp(opcaoT1, "L") == 0){
				MensagemSuperior();
				printf("L - Listar todas as contas de um cliente.\n");//FALTOU ACABAR ESTA PARTE
				printf("Escolha o criterio da pesquisa\n");
				printf("1 - Nome\n");
				printf("2 - Codigo\n");
				printf("3 - CPF ou CNPJ\n");
				scanf("%d",&aux);
				listarContas(aux, tamanho, tamanhoC);
			}
			if( strcmp(opcaoT1, "S") == 0){
				MensagemSuperior();
				printf("################# Saque em conta #################\n");
				printf("Digite a agencia:");
				scanf("%d",&agencia);
				printf("Digite o numero da conta:");
				scanf("%d",&conta);
								
				saqueEmConta(agencia, conta, tamanhoC);
			}
			if( strcmp(opcaoT1, "D") == 0){
				MensagemSuperior();
				printf("################# Deposito em conta #################\n");
				printf("Digite a agencia:");
				scanf("%d",&agencia);
				printf("Digite o numero da conta:");
				scanf("%d",&conta);
				printf("Digite o valor:");
				scanf("%d",&aux);
				depositoEmConta(agencia, conta, aux, tamanhoC, op=0);
				
			}
			if( strcmp(opcaoT1, "T") == 0){
				MensagemSuperior();
				printf("################# Transferencia entre contas #################\n");
				printf("Informe os dados da conta de origem\n");
				printf("Digite a agencia:");
				scanf("%d",&agencia);
				printf("Digite o numero da conta:");
				scanf("%d",&conta);
				printf("Informe os dados da conta de destino:\n");
				printf("Digite a agencia:");
				scanf("%d",&agenciaD);
				printf("Digite o numero da conta:");
				scanf("%d",&contaD);
				saqueEmConta(agencia, conta, tamanhoC);
				depositoEmConta(agenciaD, contaD, aux, tamanhoC, op=1);
				//transferenciaEntreContas(agencia, conta, agenciaD, contaD);
			}
			if( strcmp(opcaoT1, "E") == 0){
				MensagemSuperior();
				printf("################# Extrato da conta #################\n");
				printf("Digite a agencia:");
				scanf("%d",&agencia);
				printf("Digite o numero da conta:");
				scanf("%d",&conta);
				extratoDeUmaConta(agencia, conta, tamanhoC);
			}
				
		}
		if( strcmp(opcao, "S") == 0){
			MensagemSuperior();
			printf("Sair\n");
		}
		
	}
	return 0;
}

void cadastrarCliente(char nomeArquivo[]) {
    FILE *arquivo;

    arquivo = fopen(nomeArquivo, "a");
    if(arquivo == NULL) {
        printf("Ocorreram problemas ao salvar o arquivo.");
        return;
    }
	
	aux = 0;
	for(i=1; aux<=tamanho; i++){
		if(vetor[i].codigo == NULL){
			vetor[i].codigo = i;
			printf("\nNome do cliente:");
			scanf("%s",vetor[i].nome);
			printf("CPF/CNPJ:");
			scanf("%s",vetor[i].CNPJ_CPF);
			printf("Telefone:");
			scanf("%s",vetor[i].telefone);
			printf("Logradouro:");
			scanf("%s",vetor[i].este_endereco.logradouro);
			printf("Complemento:");
			scanf("%s",vetor[i].este_endereco.logradouro);
			printf("CEP:");
			scanf("%s",vetor[i].este_endereco.CEP);
			printf("Bairro:");
			scanf("%s",vetor[i].este_endereco.bairro);
			printf("Cidade:");
			scanf("%s",vetor[i].este_endereco.cidade);
			printf("Estado:");
			scanf("%s",vetor[i].este_endereco.estado);
			
			//salvando no arquivo
			fprintf(arquivo, "\n%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;",
			//fprintf(arquivo, "\n%d;%s;",
		    	vetor[i].codigo,	
				vetor[i].nome,
				vetor[i].CNPJ_CPF, 
				vetor[i].telefone, 
				vetor[i].este_endereco.logradouro, 
				vetor[i].este_endereco.logradouro, 
				vetor[i].este_endereco.CEP, 
				vetor[i].este_endereco.bairro, 
				vetor[i].este_endereco.cidade, 
				vetor[i].este_endereco.estado
			);
			Centraliza("\nSALVO COM SUCESSO!\n");
			aux = tamanho + 1;
			system("pause");
		}
		aux++;
	}
    
    //CODIGO DE AMOSTRAGEM
    for(i=1; i<=tamanho; i++){
		printf("%d %s\n", i, vetor[i].nome);
	}
    printf("\nArquivo salvo com sucesso......\n\n");
    //FINAL CODIGO DE AMOSTRAGEM
    
    fclose(arquivo);
}

void listarClientes(int tamanho){
	MensagemSuperior();
	printf("\n------------------ Clientes cadastrados -----------------\n");
	//aux = 0;
	cont = 0;
	for(aux=0; aux<10; aux++){
		if(vetor[aux].codigo == NULL){
			cont++;
		}	
		else{
			//rotina de ordenação
			qtd = tamanho; //tamanho do vetor
			for(i = 1; i < qtd; i++){
		    	for (j = 0; j < qtd -1 ; j++){
		        	if(strcmp(vetor[j].nome , vetor[j+1].nome) > 0){   
			            strcpy(temp, vetor[j].nome);
			            strcpy(vetor[j].nome, vetor[j+1].nome);
			            strcpy(vetor[j+1].nome,temp);                               
		         	}
		         }
			}
			
		}
	}
	
	//imprimindo em tela
	for(i=1; i<tamanho; i++){
		//if(vetor[i].codigo == NULL){
		printf("Codigo: %d ", vetor[i].codigo);
		printf("Nome: %s ", vetor[i].nome);
		printf("CPF/CNPJ: %s ",vetor[i].CNPJ_CPF);
		printf("\nTelefone: %s ",vetor[i].telefone);
		printf("Logradouro: %s ",vetor[i].este_endereco.logradouro);
		printf("\nComplemento: %s ",vetor[i].este_endereco.complemento);
		printf("CEP: %s ",vetor[i].este_endereco.CEP);
		printf("Bairro: %s ",vetor[i].este_endereco.bairro);
		printf("\nCidade: %s ",vetor[i].este_endereco.cidade);
		printf("Estado: %s \n",vetor[i].este_endereco.estado);
		printf("---------------------------------------------------------\n");
	}
	
	system("pause");
}

void buscarCliente(int aux, int tamanho){
	//printf("\nInforme o nome do cliente:\n");
	//printf("\naux = %d\n",aux);
	if( aux == 1 ){
		printf("Informe o nome:");
		scanf("%s",temp);
		qtd = 0;
		
		for(i=0; i<tamanho; i++){ //3 é o tamanho do vetor
			if( strcmp(temp, vetor[i].nome) == 0){
				printf("\nCliente encontrado de nome: %s\n", vetor[i].nome);
				printf("\nCodigo: %d \n", vetor[i].codigo);
				printf("Nome: %s\n", vetor[i].nome);
				printf("CPF/CNPJ: %s\n",vetor[i].CNPJ_CPF);
				printf("Telefone: %s\n",vetor[i].telefone);
				printf("Logradouro: %s\n",vetor[i].este_endereco.logradouro);
				printf("Complemento: %s\n",vetor[i].este_endereco.logradouro);
				printf("CEP: %s\n",vetor[i].este_endereco.CEP);
				printf("Bairro: %s\n",vetor[i].este_endereco.bairro);
				printf("Cidade: %s\n",vetor[i].este_endereco.cidade);
				printf("Estado: %s\n",vetor[i].este_endereco.estado);
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
		
	}
	if( aux == 2 ){
		printf("Informe o codigo:");
		scanf("%d",&j);
		qtd = 0;
		
		for(i=0; i<3; i++){ //3 é o tamanho do vetor
			if( j == vetor[i].codigo ){
				printf("\nCliente encontrado de nome: %s\n", vetor[i].nome);
				printf("\nCodigo: %d \n", vetor[i].codigo);
				printf("Nome: %s\n", vetor[i].nome);
				printf("CPF/CNPJ: %s\n",vetor[i].CNPJ_CPF);
				printf("Telefone: %s\n",vetor[i].telefone);
				printf("Logradouro: %s\n",vetor[i].este_endereco.logradouro);
				printf("Complemento: %s\n",vetor[i].este_endereco.logradouro);
				printf("CEP: %s\n",vetor[i].este_endereco.CEP);
				printf("Bairro: %s\n",vetor[i].este_endereco.bairro);
				printf("Cidade: %s\n",vetor[i].este_endereco.cidade);
				printf("Estado: %s\n",vetor[i].este_endereco.estado);
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
	}
	if( aux == 3 ){
		printf("Informe o CPF ou CNPJ:");
		scanf("%s",temp);
		qtd = 0;
		
		for(i=0; i<3; i++){ //3 é o tamanho do vetor
			if( strcmp(temp, vetor[i].CNPJ_CPF) == 0){
				printf("\nCliente encontrado de nome: %s\n", vetor[i].nome);
				printf("\nCodigo: %d\n", vetor[i].codigo);
				printf("Nome: %s\n", vetor[i].nome);
				printf("CPF/CNPJ: %s\n",vetor[i].CNPJ_CPF);
				printf("Telefone: %s\n",vetor[i].telefone);
				printf("Logradouro: %s\n",vetor[i].este_endereco.logradouro);
				printf("Complemento: %s\n",vetor[i].este_endereco.logradouro);
				printf("CEP: %s\n",vetor[i].este_endereco.CEP);
				printf("Bairro: %s\n",vetor[i].este_endereco.bairro);
				printf("Cidade: %s\n",vetor[i].este_endereco.cidade);
				printf("Estado: %s\n",vetor[i].este_endereco.estado);
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
	}
	system("pause");
}

void atualizarCliente(int aux, int tamanho){
	//printf("\nInforme o nome do cliente:\n");
	//printf("\naux = %d\n",aux);
	if( aux == 1 ){
		printf("Informe o nome:");
		scanf("%s",temp);
		qtd = 0;
		
		for(i=0; i<tamanho; i++){ //3 é o tamanho do vetor
			if( strcmp(temp, vetor[i].nome) == 0){
				MensagemSuperior();
				printf("\nCliente encontrado de nome: %s\n", vetor[i].nome);
				
				printf("\nAgora informe os dados do cliente novamente!\n");
				
				printf("Codigo do cliente:");
				scanf("%d",&vetor[i].codigo);
				while(vetor[i].codigo == NULL){ //verifica se o dado é nulo
					printf("Codigo do cliente:");
					scanf("%d",&vetor[i].codigo);
				}
				
				printf("Nome:");
				scanf("%s",vetor[i].nome);
				while(vetor[i].nome == NULL){ //verifica se o dado é nulo
					printf("Nome:");
					scanf("%s",vetor[i].nome);
				}
				
				
				printf("CPF/CNPJ:");
				scanf("%s",vetor[i].CNPJ_CPF);
				while(vetor[i].CNPJ_CPF == NULL){ //verifica se o dado é nulo
					printf("CPF/CNPJ:");
					scanf("%s",vetor[i].CNPJ_CPF);
				}
				
				printf("Telefone:");
				scanf("%s",vetor[i].telefone);
				while(vetor[i].telefone == NULL){ //verifica se o dado é nulo
					printf("Telefone:");
					scanf("%s",vetor[i].telefone);
				}
				
				printf("Logradouro:");
				scanf("%s",vetor[i].este_endereco.logradouro);
				while(vetor[i].este_endereco.logradouro == NULL){ //verifica se o dado é nulo
					printf("Logradouro:");
					scanf("%s",vetor[i].este_endereco.logradouro);
				}
				
				printf("Complemento:");
				scanf("%s",vetor[i].este_endereco.logradouro);
				while(vetor[i].nome == NULL){ //verifica se o dado é nulo
					printf("Complemento:");
					scanf("%s",vetor[i].este_endereco.logradouro);
				}
				
				printf("CEP:");
				scanf("%s",vetor[i].este_endereco.CEP);
				while(vetor[i].este_endereco.CEP == NULL){ //verifica se o dado é nulo
					printf("CEP:");
					scanf("%s",vetor[i].este_endereco.CEP);
				}
				
				printf("Bairro:");
				scanf("%s",vetor[i].este_endereco.bairro);
				while(vetor[i].este_endereco.bairro == NULL){ //verifica se o dado é nulo
					printf("Bairro:");
					scanf("%s",vetor[i].este_endereco.bairro);
				}
				
				printf("Cidade:");
				scanf("%s",vetor[i].este_endereco.cidade);
				while(vetor[i].este_endereco.cidade == NULL){ //verifica se o dado é nulo
					printf("Cidade:");
					scanf("%s",vetor[i].este_endereco.cidade);
				}
				
				printf("Estado:");
				scanf("%s",vetor[i].este_endereco.estado);
				while(vetor[i].este_endereco.estado == NULL){ //verifica se o dado é nulo
					printf("Estado:");
					scanf("%s",vetor[i].este_endereco.estado);
				}
				
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
		
	}
	if( aux == 2 ){
		printf("Informe o codigo:");
		scanf("%d",&j);
		qtd = 0;
		
		for(i=0; i<3; i++){ //3 é o tamanho do vetor
			if( j == vetor[i].codigo ){
				MensagemSuperior();
				printf("\nCliente encontrado de nome: %s\n", vetor[i].nome);
				
				printf("\nAgora informe os dados do cliente novamente!\n");
				
				printf("Codigo do cliente:");
				scanf("%d",&vetor[i].codigo);
				while(vetor[i].codigo == NULL){ //verifica se o dado é nulo
					printf("Codigo do cliente:");
					scanf("%d",&vetor[i].codigo);
				}
				
				printf("Nome:");
				scanf("%s",vetor[i].nome);
				while(vetor[i].nome == NULL){ //verifica se o dado é nulo
					printf("Nome:");
					scanf("%s",vetor[i].nome);
				}
				
				
				printf("CPF/CNPJ:");
				scanf("%s",vetor[i].CNPJ_CPF);
				while(vetor[i].CNPJ_CPF == NULL){ //verifica se o dado é nulo
					printf("CPF/CNPJ:");
					scanf("%s",vetor[i].CNPJ_CPF);
				}
				
				printf("Telefone:");
				scanf("%s",vetor[i].telefone);
				while(vetor[i].telefone == NULL){ //verifica se o dado é nulo
					printf("Telefone:");
					scanf("%s",vetor[i].telefone);
				}
				
				printf("Logradouro:");
				scanf("%s",vetor[i].este_endereco.logradouro);
				while(vetor[i].este_endereco.logradouro == NULL){ //verifica se o dado é nulo
					printf("Logradouro:");
					scanf("%s",vetor[i].este_endereco.logradouro);
				}
				
				printf("Complemento:");
				scanf("%s",vetor[i].este_endereco.logradouro);
				while(vetor[i].nome == NULL){ //verifica se o dado é nulo
					printf("Complemento:");
					scanf("%s",vetor[i].este_endereco.logradouro);
				}
				
				printf("CEP:");
				scanf("%s",vetor[i].este_endereco.CEP);
				while(vetor[i].este_endereco.CEP == NULL){ //verifica se o dado é nulo
					printf("CEP:");
					scanf("%s",vetor[i].este_endereco.CEP);
				}
				
				printf("Bairro:");
				scanf("%s",vetor[i].este_endereco.bairro);
				while(vetor[i].este_endereco.bairro == NULL){ //verifica se o dado é nulo
					printf("Bairro:");
					scanf("%s",vetor[i].este_endereco.bairro);
				}
				
				printf("Cidade:");
				scanf("%s",vetor[i].este_endereco.cidade);
				while(vetor[i].este_endereco.cidade == NULL){ //verifica se o dado é nulo
					printf("Cidade:");
					scanf("%s",vetor[i].este_endereco.cidade);
				}
				
				printf("Estado:");
				scanf("%s",vetor[i].este_endereco.estado);
				while(vetor[i].este_endereco.estado == NULL){ //verifica se o dado é nulo
					printf("Estado:");
					scanf("%s",vetor[i].este_endereco.estado);
				}
				
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
	}
	if( aux == 3 ){
		printf("Informe o CPF ou CNPJ:");
		scanf("%s",temp);
		qtd = 0;
		
		for(i=0; i<3; i++){ //3 é o tamanho do vetor
			if( strcmp(temp, vetor[i].CNPJ_CPF) == 0){
				MensagemSuperior();
				printf("\nCliente encontrado de nome: %s\n", vetor[i].nome);
				
				printf("\nAgora informe os dados do cliente novamente!\n");
				
				printf("Codigo do cliente:");
				scanf("%d",&vetor[i].codigo);
				while(vetor[i].codigo == NULL){ //verifica se o dado é nulo
					printf("Codigo do cliente:");
					scanf("%d",&vetor[i].codigo);
				}
				
				printf("Nome:");
				scanf("%s",vetor[i].nome);
				while(vetor[i].nome == NULL){ //verifica se o dado é nulo
					printf("Nome:");
					scanf("%s",vetor[i].nome);
				}
				
				
				printf("CPF/CNPJ:");
				scanf("%s",vetor[i].CNPJ_CPF);
				while(vetor[i].CNPJ_CPF == NULL){ //verifica se o dado é nulo
					printf("CPF/CNPJ:");
					scanf("%s",vetor[i].CNPJ_CPF);
				}
				
				printf("Telefone:");
				scanf("%s",vetor[i].telefone);
				while(vetor[i].telefone == NULL){ //verifica se o dado é nulo
					printf("Telefone:");
					scanf("%s",vetor[i].telefone);
				}
				
				printf("Logradouro:");
				scanf("%s",vetor[i].este_endereco.logradouro);
				while(vetor[i].este_endereco.logradouro == NULL){ //verifica se o dado é nulo
					printf("Logradouro:");
					scanf("%s",vetor[i].este_endereco.logradouro);
				}
				
				printf("Complemento:");
				scanf("%s",vetor[i].este_endereco.logradouro);
				while(vetor[i].nome == NULL){ //verifica se o dado é nulo
					printf("Complemento:");
					scanf("%s",vetor[i].este_endereco.logradouro);
				}
				
				printf("CEP:");
				scanf("%s",vetor[i].este_endereco.CEP);
				while(vetor[i].este_endereco.CEP == NULL){ //verifica se o dado é nulo
					printf("CEP:");
					scanf("%s",vetor[i].este_endereco.CEP);
				}
				
				printf("Bairro:");
				scanf("%s",vetor[i].este_endereco.bairro);
				while(vetor[i].este_endereco.bairro == NULL){ //verifica se o dado é nulo
					printf("Bairro:");
					scanf("%s",vetor[i].este_endereco.bairro);
				}
				
				printf("Cidade:");
				scanf("%s",vetor[i].este_endereco.cidade);
				while(vetor[i].este_endereco.cidade == NULL){ //verifica se o dado é nulo
					printf("Cidade:");
					scanf("%s",vetor[i].este_endereco.cidade);
				}
				
				printf("Estado:");
				scanf("%s",vetor[i].este_endereco.estado);
				while(vetor[i].este_endereco.estado == NULL){ //verifica se o dado é nulo
					printf("Estado:");
					scanf("%s",vetor[i].este_endereco.estado);
				}
				
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
	}
	system("pause");
}

void excluirCliente(int aux){

	if( aux == 1 ){
		printf("Informe o nome:");
		scanf("%s",temp);
		qtd = 0;
		
		for(i=0; i<3; i++){ //3 é o tamanho do vetor
			if( strcmp(temp, vetor[i].nome) == 0){
				printf("Cliente encontrado de nome: %s\n", vetor[i].nome);
				printf("\nCodigo: %d \n", vetor[i].codigo);
				printf("Nome: %s\n", vetor[i].nome);
				printf("CPF/CNPJ: %s\n",vetor[i].CNPJ_CPF);
				printf("Telefone: %s\n",vetor[i].telefone);
				printf("Logradouro: %s\n",vetor[i].este_endereco.logradouro);
				printf("Complemento: %s\n",vetor[i].este_endereco.complemento);
				printf("CEP: %s\n",vetor[i].este_endereco.CEP);
				printf("Bairro: %s\n",vetor[i].este_endereco.bairro);
				printf("Cidade: %s\n",vetor[i].este_endereco.cidade);
				printf("Estado: %s\n",vetor[i].este_endereco.estado);
				printf("confirma exclusao? 1 - Sim / 2 - Nao\n");
				scanf("%d",&j);
				
				if(j == 1){
				strcpy(vetor[i].nome, "Excluido");
				}
				
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
		
	}
	if( aux == 2 ){
		printf("Informe o codigo:");
		scanf("%s",temp);
		qtd = 0;
		
		for(i=0; i<3; i++){ //3 é o tamanho do vetor
			if( strcmp(temp, vetor[i].nome) == 0){
				printf("\nCliente encontrado de nome: %s\n", vetor[i].nome);
				printf("\nCodigo: %d \n", vetor[i].codigo);
				printf("Nome: %s\n", vetor[i].nome);
				printf("CPF/CNPJ: %s\n",vetor[i].CNPJ_CPF);
				printf("Telefone: %s\n",vetor[i].telefone);
				printf("Logradouro: %s\n",vetor[i].este_endereco.logradouro);
				printf("Complemento: %s\n",vetor[i].este_endereco.complemento);
				printf("CEP: %s\n",vetor[i].este_endereco.CEP);
				printf("Bairro: %s\n",vetor[i].este_endereco.bairro);
				printf("Cidade: %s\n",vetor[i].este_endereco.cidade);
				printf("Estado: %s\n",vetor[i].este_endereco.estado);
				printf("\nconfirma exclusao? 1 - Sim / 2 - Nao\n");
				scanf("%d",&j);
				
				if(j == 1){
				strcpy(vetor[i].nome, "Excluido");
				}
				
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
		
		
	}
	if( aux == 3 ){
		printf("Informe o CPF ou CNPJ:");
		scanf("%s",temp);
		qtd = 0;
		
		for(i=0; i<3; i++){ //3 é o tamanho do vetor
			if( strcmp(temp, vetor[i].CNPJ_CPF) == 0){
				printf("\nCliente encontrado de nome: %s\n", vetor[i].nome);
				printf("\nCodigo: %d \n", vetor[i].codigo);
				printf("Nome: %s\n", vetor[i].nome);
				printf("CPF/CNPJ: %s\n",vetor[i].CNPJ_CPF);
				printf("Telefone: %s\n",vetor[i].telefone);
				printf("Logradouro: %s\n",vetor[i].este_endereco.logradouro);
				printf("Complemento: %s\n",vetor[i].este_endereco.complemento);
				printf("CEP: %s\n",vetor[i].este_endereco.CEP);
				printf("Bairro: %s\n",vetor[i].este_endereco.bairro);
				printf("Cidade: %s\n",vetor[i].este_endereco.cidade);
				printf("Estado: %s\n",vetor[i].este_endereco.estado);
				printf("\nconfirma exclusao? 1 - Sim / 2 - Nao\n");
				scanf("%d",&j);
				
				if(j == 1){
				strcpy(vetor[i].nome, "Excluido");
				}
				
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
	}
	system("pause");
}

void listarTodasAsContas(int tamanhoC){
	printf("------------ Listando contas ----------------\n");
	qtd = 0;
	for(i=1; i<tamanhoC; i++){
		for(j=0; j<tamanhoC; j++){
			if(vetor[i].codigo == vetorConta[j].codigoCliente){
				printf("Codigo cliente: %d Nome: %s\n", vetor[i].codigo, 
														vetor[i].nome);
				printf("Agencia: %d Numero: %d Saldo: %d C.Conta:%d\n", vetorConta[j].agencia, 
															 vetorConta[j].numero,
															 vetorConta[j].saldo,
															 vetorConta[j].codigoCliente);
				qtd = 1;
			}
						
		}
		printf("---------------------------------------------\n");
	}
	if(qtd == 0){
		Centraliza("NENHUMA CONTA ENCONTRADA!");
	}
	system("pause");
}

void cadastrarConta(int aux, int tamanho, int tamanhoC){
	FILE *arquivo;

    arquivo = fopen("Contas.txt", "a");
    if(arquivo == NULL) {
        printf("Ocorreram problemas ao salvar o arquivo.");
        return;
    }
	
	MensagemSuperior();
	printf("\n ################# cadastrando contas #################\n");
	//printf("\nInforme o nome do cliente:\n");
	//printf("\naux = %d\n",aux);
	if( aux == 1 ){
		printf("Informe o nome:");
		scanf("%s",temp);
		qtd = 0;
		
		for(i=1; i<tamanho; i++){ //3 é o tamanho do vetor
			if( strcmp(temp, vetor[i].nome) == 0){

				printf("\nCliente encontrado de nome: %s ", vetor[i].nome);
				printf("Codigo: %d ", vetor[i].codigo);
				
				for(cont=0; cont<tamanhoC; cont++){//procura a ultima posição vazia do vetor contas
					if( vetorConta[cont].numero == NULL ){
						vetorConta[cont].codigoCliente = vetor[i].codigo;
						printf("\nDigite a agencia:");
						scanf("%d",&vetorConta[cont].agencia);
						printf("Digite o numero:");
						scanf("%d",&vetorConta[cont].numero);
						printf("Digite o saldo:");
						scanf("%d",&vetorConta[cont].saldo);
					
						cont = 3; //finalizar o loop
						
						//salvando em arquivo
						fprintf(arquivo, "\n%d;%d;%d;%d;",
						//fprintf(arquivo, "\n%d;%s;",
					    	&vetorConta[cont].codigoCliente,	
							&vetorConta[cont].agencia,
							&vetorConta[cont].numero,
							&vetorConta[cont].saldo 
						);
					}
				}
				
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
		
	}
	if( aux == 2 ){
		printf("Informe o codigo:");
		scanf("%d",&j);
		qtd = 0;
		
		for(i=0; i<tamanho; i++){ //3 é o tamanho do vetor
			if( j == vetor[i].codigo ){
				printf("\nCliente encontrado de nome: %s ", vetor[i].nome);
				printf("Codigo: %d ", vetor[i].codigo);
				
				for(cont=0; cont<3; cont++){//procura a ultima posição vazia do vetor contas
					if( vetorConta[cont].numero == NULL ){
						vetorConta[cont].codigoCliente = vetor[i].codigo;
						printf("\nDigite a agencia:");
						scanf("%d",&vetorConta[cont].agencia);
						printf("Digite o numero:");
						scanf("%d",&vetorConta[cont].numero);
						printf("Digite o saldo:");
						scanf("%d",&vetorConta[cont].saldo);
					
						cont = 3; //finalizar o loop
						
						//salvando em arquivo
						fprintf(arquivo, "\n%d;%d;%d;%d;",
						//fprintf(arquivo, "\n%d;%s;",
					    	vetorConta[cont].codigoCliente,	
							vetorConta[cont].agencia,
							vetorConta[cont].numero,
							vetorConta[cont].saldo 
						);
					}
				}

				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
	}
	if( aux == 3 ){
		printf("Informe o CPF ou CNPJ:");
		scanf("%s",temp);
		qtd = 0;
		
		for(i=0; i<tamanho; i++){ //3 é o tamanho do vetor
			if( strcmp(temp, vetor[i].CNPJ_CPF) == 0){
				printf("\nCliente encontrado de nome: %s ", vetor[i].nome);
				printf("Codigo: %d ", vetor[i].codigo);
				
				for(cont=0; cont<3; cont++){//procura a ultima posição vazia do vetor contas
					if( vetorConta[cont].numero == NULL ){
						vetorConta[cont].codigoCliente = vetor[i].codigo;
						printf("\nDigite a agencia:\n");
						scanf("%d",&vetorConta[cont].agencia);
						printf("Digite o numero:\n");
						scanf("%d",&vetorConta[cont].numero);
						printf("Digite o saldo:\n");
						scanf("%d",&vetorConta[cont].saldo);
					
						cont = 3; //finalizar o loop
						
						//salvando em arquivo
						fprintf(arquivo, "\n%d;%d;%d;%d;",
						//fprintf(arquivo, "\n%d;%s;",
					    	vetorConta[cont].codigoCliente,	
							vetorConta[cont].agencia,
							vetorConta[cont].numero,
							vetorConta[cont].saldo 
						);
					}
				}
				
				qtd = 1;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
			
		}
	}
	fclose(arquivo);
	system("pause");
}

void listarContas(int aux, int tamanho, int tamanhoC){
	MensagemSuperior();
	printf("------------------ Listando contas ----------------------\n");
	if( aux == 1 ){
		printf("Informe o nome do cliente\n");
		scanf("%s",&temp);
		qtd = 0;
		
		for(i=1; i<tamanho; i++){
			for(j=0; j<tamanhoC; j++){
				if( strcmp(temp, vetorConta[j].este_cliente.nome) == 0){
					printf("Codigo cliente: %d Nome: %s\n", vetor[i].codigo, 
															vetor[i].nome);
					printf("Agencia: %d Numero: %d Saldo: %d CC:%d\n", vetorConta[j].agencia, 
																 vetorConta[j].numero,
																 vetorConta[j].saldo,
																 vetorConta[j].codigoCliente);
				}			
				qtd++;
			}
		}
		
		
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhuma conta encontrada!\n");
		}
	}
	if( aux == 2 ){
		printf("Informe o codigo do cliente\n");
		scanf("%d",&op);
		qtd = 0;
		
		for(i=1; i<tamanho; i++){
			for(j=0; j<tamanhoC; j++){
				if(vetor[i].codigo == vetorConta[j].codigoCliente){
					printf("Codigo cliente: %d Nome: %s\n", vetor[i].codigo, 
															vetor[i].nome);
					printf("Agencia: %d Numero: %d Saldo: %d CC:%d\n", vetorConta[j].agencia, 
																 vetorConta[j].numero,
																 vetorConta[j].saldo,
																 vetorConta[j].codigoCliente);
				}			
				qtd++;
			}
		}
		
		
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhuma conta encontrada!\n");
		}
	}
	if( aux == 3 ){
		printf("Informe o CPF ou CNPJ\n");
		scanf("%s",temp);
		qtd = 0;
		
		for(i=1; i<tamanho; i++){
			for(j=0; j<tamanhoC; j++){
				if( strcmp(temp, vetorConta[j].este_cliente.CNPJ_CPF) == 0){
					printf("Codigo cliente: %d Nome: %s\n", vetor[i].codigo, 
															vetor[i].nome);
					printf("Agencia: %d Numero: %d Saldo: %d CC:%d\n", vetorConta[j].agencia, 
																 vetorConta[j].numero,
																 vetorConta[j].saldo,
																 vetorConta[j].codigoCliente);
				}			
				qtd++;
			}
		}
		if(qtd == 0){// i igual ao tamanho do vetor
			printf("\nNenhum cliente encontrado!\n");
		}
	}
	printf("---------------------------------------------------------\n");
	system("pause");
}

void saqueEmConta(int agencia, int conta, int tamanhoC){
	for(i=0; i<tamanhoC; i++){
		if(vetorConta[i].agencia == agencia && vetorConta[i].numero == conta){
			printf("Digite o valor:");
			scanf("%d",&aux);
			
			while( aux > vetorConta[i].saldo){
				printf("Saldo em conta abaixo do valor requerido\n");
				printf("Saldo em conta: %d Valor requerido: %d\n", vetorConta[i].saldo, aux);
				printf("Digite o valor que deseja sacar novamente:\n");
				scanf("%d",&aux);
			}
			printf("Digite a descricao da operacao:");
			scanf("%s",vetorT[i].descricao);
			vetorConta[i].saldo = vetorConta[i].saldo - aux;
			printf("O saldo agora e: R$%d\n", vetorConta[i].saldo);
			
			//Registrando dados na transação
			strcpy(vetorT[i].tipo, D); //setar DEBITO	
			char dateStr [9];
		    _strdate(dateStr);
			strcpy(vetorT[i].data, dateStr); 
			vetorT[i].valor = aux;
		}				
	}
	//return aux;
	system("pause");
}

void depositoEmConta(int agencia, int conta, int aux, int tamanhoC, int op){
	for(i=0; i<tamanhoC; i++){
		if( op == 0){
			if(vetorConta[i].agencia == agencia && vetorConta[i].numero == conta){
				
				printf("Digite a descricao da operacao:");
				scanf("%s",vetorT[i].descricao);
				vetorConta[i].saldo = vetorConta[i].saldo + aux;
				printf("O saldo agora e: R$%d\n", vetorConta[i].saldo);
				
				//Registrando dados na transação
				strcpy(vetorT[i].tipo, C); //setar CREDITO
				char dateStr [9];
			    _strdate(dateStr);
				strcpy(vetorT[i].data, dateStr); 
				vetorT[i].valor = aux;
			}
		}
		if( op == 1){
			if(vetorConta[i].agencia == agencia && vetorConta[i].numero == conta){
				vetorConta[i].saldo = vetorConta[i].saldo + aux;
				
				//Registrando dados na transação
				strcpy(vetorT[i].tipo, C); //setar CREDITO
				char dateStr [9];
			    _strdate(dateStr);
				strcpy(vetorT[i].data, dateStr); 
				vetorT[i].valor = aux;
			}
			
		}
	}
	system("pause");
}

void extratoDeUmaConta(int agencia, int conta, int tamanhoC){
	for(i=0; i<tamanhoC; i++){
		if(vetorConta[i].agencia == agencia && vetorConta[i].numero == conta){
			printf("\nNumero da agencia: %d ", vetorConta[i].agencia);
			printf("\nNumero da conta: %d ", vetorConta[i].numero);
			printf("\nSaldo: %d\n\n", vetorConta[i].saldo);
		
		}				
	}
	system("pause");
}
