#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#include <locale.h>
#define TAM 50

typedef struct violao
{
	char nome[TAM];			//nome do viol�o
	char tipo_madeira[TAM]; //tipo da madeira do viol�o
	char corda[TAM];		//tipo da corda do viol�o
	float preco;			//pre�o do viol�o
	int ano_fab;			//ano de fabrica��o do viol�o
	int id;					//identificador para a busca do viol�o
} Violao;

int cadastrarViolao(int vID);	  // cadastro de Viol�o
int validarViolao(int id);		  // verifica se o viol�o ja esta cadastrado ou n�o
Violao criarViolao(int id);		  // cria o viol�o
Violao consultarViolao(int id);	  // consultar de viol�es
int editarViolao(Violao att);	  // editar viol�es cadastrados na mem�ria
int alterarViolao(Violao old);	  //editar viol�es cadastrados no arquivo
int excluirViolao(int id); //excluir viol�es

void menu();

//Fun��o main

int main()
{
	setlocale(LC_ALL, "portuguese");
	menu();
}
/************************************/

//Fun��o para cadastrar viol�o
int cadastrarViolao(int vID)
{

	Violao violao = criarViolao(vID);
	FILE *ptrArqViolao;
	ptrArqViolao = fopen("violao.txt", "ab+");
	if (ptrArqViolao == NULL)
		printf("NAO FOI POSSIVEL ABRIR O ARQUIVO\n");

	if (validarViolao(vID) == 0)
	{													  //verifica se o id do viol�o ja esta cadastrado
		fwrite(&violao, sizeof(Violao), 1, ptrArqViolao); //se n�o estiver escreve no arquivo
		fclose(ptrArqViolao);
		return 1;
	}

	else
	{ //se estiver n�o escreve
		fclose(ptrArqViolao);
		return 0;
	}
}

/*****************************************************************/

//Fun��o para verificar se o viol�o j� est� cadastrado ou n�o

int validarViolao(int id)
{
	FILE *ptrArqViolao;
	Violao violao;

	ptrArqViolao = fopen("violao.txt", "rb");
	if (ptrArqViolao == NULL)
		printf("\nN�O FOI POSS�VEL ABRIR O ARQUIVO \n");

	while (!feof(ptrArqViolao))
	{
		fread(&violao, sizeof(Violao), 1, ptrArqViolao);
		if (violao.id == id)
		{
			fclose(ptrArqViolao);
			return 1;
		}
	}
	fclose(ptrArqViolao);
	return 0;
}

/*****************************************************************/

//Cria um novo violao sem id

Violao criarViolao(int id)
{
	Violao novo_violao;
	novo_violao.id = id;

	printf("Insira os dados do Viol�o !");
	printf("\n Id: %d\n", novo_violao.id);
	printf("\n Nome: ");
	scanf("%s", novo_violao.nome);
	printf("\n Tipo de Madeira: ");
	scanf("%s", novo_violao.tipo_madeira);
	printf("\n Corda: ");
	scanf("%s", novo_violao.corda);
	printf("\n Preco: ");
	scanf("%f", &novo_violao.preco);
	printf("\n Ano de F�brica: ");
	scanf("%d", &novo_violao.ano_fab);

	return novo_violao;
}

/*****************************************************************/

//Fun��o de consulta dos viol�es cadastrados

Violao consultarViolao(int id)
{
	Violao violao;
	FILE *ptrArqViolao;
	int violao_encontrado = 0;

	ptrArqViolao = fopen("violao.txt", "rb");
	if (ptrArqViolao == NULL)
	{
		printf("N�O FOI POSS�VEL ABRIR O ARQUIVO, N�O EXISTE VIOL�O CADASTRADO \n");
	}
	while (!feof(ptrArqViolao) && violao_encontrado == 0)
	{
		fread(&violao, sizeof(Violao), 1, ptrArqViolao);
		if (violao.id == id)
			violao_encontrado = 1;
					
	}

	if (violao_encontrado == 1)
		printf("\nNome do viol�o: %s   ID: %d \n Tipo de Madeira: %s \n Corda: %s \n Pre�o: %f \n Ano de fabrica��o: %d \n\n", violao.nome, violao.id, violao.tipo_madeira, violao.corda, violao.preco, violao.ano_fab);
	else
	{
		printf(" ESSE VIOL�O N�O FOI CADASTRADO\n\n");
		fclose(ptrArqViolao);
		
	}

	fclose(ptrArqViolao);
	return violao;
}

/*****************************************************************/
//Essa fun��o solicita o campo a ser alterado pelo usuario

int editarViolao(Violao old)
{

	FILE *ptrArqViolao;
	int op;

	printf("\n-----Escolha a op��o que deseja alterar:-----\n");
	printf("\n 1: Alterar Nome");
	printf("\n 2: Alterar o Tipo de Madeira");
	printf("\n 3: Alterar Tipo de Corda");
	printf("\n 4: Alterar Pre�o");
	printf("\n 5: Alterar Ano de Fabrica��o");
	printf("\n\n\n Digite o numero correspondente a opcao: ");
	scanf("%d", &op);
	system("cls");

	switch (op)
	{
	case 1:
		printf("Digite um novo nome: ");
		scanf("%s", old.nome);
		alterarViolao(old);
		printf("Nome do viol�o: %s   ID: %d \n Tipo de Madeira: %s \n Corda: %s \n Pre�o: %f \n Ano de fabrica��o: %d \n\n", old.nome, old.id, old.tipo_madeira, old.corda, old.preco, old.ano_fab);
		break;

	case 2:
		printf("Digite um novo tipo de madeira: ");
		scanf("%s", old.tipo_madeira);
		alterarViolao(old);
		printf("Nome do viol�o: %s   ID: %d \n Tipo de Madeira: %s \n Corda: %s \n Pre�o: %f \n Ano de fabrica��o: %d \n\n", old.nome, old.id, old.tipo_madeira, old.corda, old.preco, old.ano_fab);
		break;

	case 3:
		printf("Digite um novo tipo de corda: ");
		scanf("%s", old.corda);
		alterarViolao(old);
		printf("Nome do viol�o: %s   ID: %d \n Tipo de Madeira: %s \n Corda: %s \n Pre�o: %f \n Ano de fabrica��o: %d \n\n", old.nome, old.id, old.tipo_madeira, old.corda, old.preco, old.ano_fab);

		break;

	case 4:

		printf("Digite um novo pre�o: ");
		scanf("%f", &old.preco);
		alterarViolao(old);
		printf("Nome do viol�o: %s   ID: %d \n Tipo de Madeira: %s \n Corda: %s \n Pre�o: %f \n Ano de fabrica��o: %d \n\n", old.nome, old.id, old.tipo_madeira, old.corda, old.preco, old.ano_fab);

		break;

	case 5:

		printf("Digite um novo ano de fabrica��o: ");
		scanf("%d", &old.ano_fab);
		alterarViolao(old);
		printf("Nome do viol�o: %s   ID: %d \n Tipo de Madeira: %s \n Corda: %s \n Pre�o: %f \n Ano de fabrica��o: %d \n\n", old.nome, old.id, old.tipo_madeira, old.corda, old.preco, old.ano_fab);

		break;

	default:
		printf("ERRO!! OP��O N�O ENCONTRADA, POR FAVOR INSIRA UMA OP��O VALIDA \n");
		system("pause");
		break;
	}
}

/*****************************************************************/
//Essa fun��o altera a variavel do tipo Viol�o encontrada no arquivo
int alterarViolao(Violao att)
{
	Violao violao_old;
	int violao_encontrado = 0;
	unsigned int nReg = 0;
	FILE *ptrArqViolao;

	if ((ptrArqViolao = fopen("violao.txt", "rb+")) == NULL)
		printf("\nN�O FOI POSS�VEL ABRIR O ARQUIVO\n");

	while (!feof(ptrArqViolao) && violao_encontrado == 0)
	{
		fread(&violao_old, sizeof(violao_old), 1, ptrArqViolao);
		nReg++;
		if (violao_old.id == att.id){
		violao_encontrado = 1;
		violao_old = att;
		}
	}

	fseek(ptrArqViolao, ((nReg - 1) * sizeof(Violao)), SEEK_SET);
	int codViolao = fwrite(&violao_old, sizeof(Violao), 1, ptrArqViolao);
	printf("\n Viol�o Registrado \n");
	system("pause");
	fclose(ptrArqViolao);
}

/*****************************************************************/

//Fun��o para excluir viol�es
int excluirViolao(int id)
{
	Violao violao;
	FILE *ptrArqViolao;
	FILE *newptrArqViolao;

	ptrArqViolao = fopen("violao.txt", "rb");
	newptrArqViolao = fopen("newViolao.txt", "ab");
	if (ptrArqViolao == NULL)
	{
		printf("N�O FOI POSS�VEL ABRIR O ARQUIVO, N�O EXISTE VIOL�O CADASTRADO \n");
	}
	while (!feof(ptrArqViolao) )
	{
		fread(&violao, sizeof(Violao), 1, ptrArqViolao);
	    if(violao.id != id){
		
	    fwrite(&violao, sizeof(Violao), 1, newptrArqViolao);
	}
					
	}
	
	fclose(newptrArqViolao);
	fclose(ptrArqViolao);
    remove("violao.txt");
	rename("newViolao.txt", "violao.txt"); 
	return violao.id;
}




/*****************************************************************/

void menu()
{

	Violao violao;
	int vID;
	int op, n;
	system("cls");

	printf("\n-----------------------------------------------------------------------------------------------------\t");
	printf("\n\t\t\t\t\t   SISTEMA DE REGISTRO \n");
	printf("\n\t\t\t\t\t     GIANNINI	 STORE  \n");
	printf("\n\n->Ao cadastrar: O pre�o do produto deve se utilizar ',' (v�rgula), pois est� no formato pt-BR\n");
	printf("\n---------------------------------------------------------------------------------------------------\t\n");
	printf("\n 1: Cadastrar Viol�o");
	printf("\n 2: Consultar Viol�o");
	printf("\n 3: Alterar Dados do Viol�o");
	printf("\n 4: Excluir Registro do Viol�o");
	printf("\n 0: Sair");
	printf("\n\n\n Digite o numero correspondente a opcao: ");
	scanf("%d", &op);
	system("cls");

	switch (op)
	{
	case 1:
		printf("\n-----Cadastrar Viol�o-----\n");
		printf("\nDigite o ID do Viol�o:\t");
		scanf("%d", &vID);
		cadastrarViolao(vID);
		system("pause");
		break;

	case 2:
		printf("\n-----Consultar Cadastro do Viol�o-----\n");
		printf("\nDigite o ID do Viol�o:\t");
		scanf("%d", &vID);
		consultarViolao(vID);
		system("pause");
		break;

	case 3:
		printf("\n-----Alterar Dados do Viol�o-----\n");
		printf("\nDigite o ID do Viol�o:\t");
		scanf("%d", &vID);
		editarViolao(consultarViolao(vID));
		system("pause");
		break;

	case 4:
		printf("\n-----Excluir Registro do Viol�o-----\n");
		printf("\nDigite o ID do Viol�o:\t");
		scanf("%d", &vID);
		excluirViolao(consultarViolao(vID).id);
		system("pause");
		break;

	case 0:
		exit(1);
		break;

	default:
		printf("ERRO!! OP��O N�O ENCONTRADA, POR FAVOR INSIRA UMA OP��O VALIDA \n");
		system("pause");
		break;
	}
	menu();
}

