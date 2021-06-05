#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#include <locale.h>
#define TAM 50

typedef struct violao
{
	char nome[TAM];			//nome do violão
	char tipo_madeira[TAM]; //tipo da madeira do violão
	char corda[TAM];		//tipo da corda do violão
	float preco;			//preço do violão
	int ano_fab;			//ano de fabricação do violão
	int id;					//identificador para a busca do violão
} Violao;

int cadastrarViolao(int vID);	  // cadastro de Violão
int validarViolao(int id);		  // verifica se o violão ja esta cadastrado ou não
Violao criarViolao(int id);		  // cria o violão
Violao consultarViolao(int id);	  // consultar de violões
int editarViolao(Violao att);	  // editar violões cadastrados na memória
int alterarViolao(Violao old);	  //editar violões cadastrados no arquivo
int excluirViolao(Violao del); //excluir violões

void menu();

//Função main

int main()
{
	setlocale(LC_ALL, "portuguese");
	menu();
}
/************************************/

//Função para cadastrar violão
int cadastrarViolao(int vID)
{

	Violao violao = criarViolao(vID);
	FILE *ptrArqViolao;
	ptrArqViolao = fopen("violao.txt", "ab+");
	if (ptrArqViolao == NULL)
		printf("NAO FOI POSSIVEL ABRIR O ARQUIVO\n");

	if (validarViolao(vID) == 0)
	{													  //verifica se o id do violão ja esta cadastrado
		fwrite(&violao, sizeof(Violao), 1, ptrArqViolao); //se não estiver escreve no arquivo
		fclose(ptrArqViolao);
		return 1;
	}

	else
	{ //se estiver não escreve
		fclose(ptrArqViolao);
		return 0;
	}
}

/*****************************************************************/

//Função para verificar se o violão já está cadastrado ou não

int validarViolao(int id)
{
	FILE *ptrArqViolao;
	Violao violao;

	ptrArqViolao = fopen("violao.txt", "rb");
	if (ptrArqViolao == NULL)
		printf("\nNÃO FOI POSSÍVEL ABRIR O ARQUIVO \n");

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

	printf("Insira os dados do Violão !");
	printf("\n Id: %d\n", novo_violao.id);
	printf("\n Nome: ");
	scanf("%s", novo_violao.nome);
	printf("\n Tipo de Madeira: ");
	scanf("%s", novo_violao.tipo_madeira);
	printf("\n Corda: ");
	scanf("%s", novo_violao.corda);
	printf("\n Preco: ");
	scanf("%f", &novo_violao.preco);
	printf("\n Ano de Fábrica: ");
	scanf("%d", &novo_violao.ano_fab);

	return novo_violao;
}

/*****************************************************************/

//Função de consulta dos violões cadastrados

Violao consultarViolao(int id)
{
	Violao violao;
	FILE *ptrArqViolao;
	char violao_encontrado = 0;

	ptrArqViolao = fopen("violao.txt", "rb");
	if (ptrArqViolao == NULL)
	{
		printf("NÃO FOI POSSÍVEL ABRIR O ARQUIVO, NÃO EXISTE VIOLÃO CADASTRADO \n");
	}
	while (!feof(ptrArqViolao) && !violao_encontrado)
	{
		fread(&violao, sizeof(Violao), 1, ptrArqViolao);
		if (violao.id == id)
			violao_encontrado = 1;
	}

	if (violao_encontrado)
		printf("Nome do violão: %s   ID: %s \n Tipo de Madeira: %s \n Corda: %s \n Preço: %f \n Ano de fabricação: %d \n\n", violao.nome, violao.id, violao.tipo_madeira, violao.corda, violao.preco, violao.ano_fab);
	else
	{
		printf(" ESSE VIOLÃO NÃO ESTA CADASTRADO\n\n");
		fclose(ptrArqViolao);
		
	}

	fclose(ptrArqViolao);
	return violao;
}

/*****************************************************************/
//Essa função solicita o campo a ser alterado pelo usuario

int editarViolao(Violao old)
{

	FILE *ptrArqViolao;
	int op;

	printf("\n-----Escolha a opção que deseja alterar:-----\n");
	printf("\n 1: Alterar Nome");
	printf("\n 2: Alterar o Tipo de Madeira");
	printf("\n 3: Alterar Tipo de Corda");
	printf("\n 4: Alterar Preço");
	printf("\n 5: Alterar Ano de Fabricação");
	printf("\n\n\n Digite o numero correspondente a opcao: ");
	scanf("%d", &op);
	system("cls");

	switch (op)
	{
	case 1:
		printf("Digite um novo nome: ");
		scanf("%s", old.nome);
		alterarViolao(old);
		printf("Nome do violão: %s   ID: %s \n Tipo de Madeira: %s \n Corda: %s \n Preço: %f \n Ano de fabricação: %d \n\n", old.nome, old.id, old.tipo_madeira, old.corda, old.preco, old.ano_fab);
		break;

	case 2:
		printf("Digite um novo tipo de madeira: ");
		scanf("%s", old.tipo_madeira);
		alterarViolao(old);
		printf("Nome do violão: %s   ID: %s \n Tipo de Madeira: %s \n Corda: %s \n Preço: %f \n Ano de fabricação: %d \n\n", old.nome, old.id, old.tipo_madeira, old.corda, old.preco, old.ano_fab);
		break;

	case 3:
		printf("Digite um novo tipo de corda: ");
		scanf("%s", old.corda);
		alterarViolao(old);
		printf("Nome do violão: %s   ID: %s \n Tipo de Madeira: %s \n Corda: %s \n Preço: %f \n Ano de fabricação: %d \n\n", old.nome, old.id, old.tipo_madeira, old.corda, old.preco, old.ano_fab);

		break;

	case 4:

		printf("Digite um novo preço: ");
		scanf("%f", &old.preco);
		alterarViolao(old);
		printf("Nome do violão: %s   ID: %s \n Tipo de Madeira: %s \n Corda: %s \n Preço: %f \n Ano de fabricação: %d \n\n", old.nome, old.id, old.tipo_madeira, old.corda, old.preco, old.ano_fab);

		break;

	case 5:

		printf("Digite um novo ano de fabricação: ");
		scanf("%d", &old.ano_fab);
		alterarViolao(old);
		printf("Nome do violão: %s   ID: %s \n Tipo de Madeira: %s \n Corda: %s \n Preço: %f \n Ano de fabricação: %d \n\n", old.nome, old.id, old.tipo_madeira, old.corda, old.preco, old.ano_fab);

		break;

	default:
		printf("ERRO!! OPÇÃO NÃO ENCONTRADA, POR FAVOR INSIRA UMA OPÇÃO VALIDA \n");
		system("pause");
		break;
	}
}

/*****************************************************************/
//Essa função altera a variavel do tipo Violão encontrada no arquivo
int alterarViolao(Violao att)
{
	Violao violao_old;
	char violao_encontrado = 0;
	unsigned int nReg = 0;
	FILE *ptrArqViolao;

	if ((ptrArqViolao = fopen("violao.txt", "rb+")) == NULL)
		printf("\nNÃO FOI POSSÍVEL ABRIR O ARQUIVO\n");

	while (!feof(ptrArqViolao) && !violao_encontrado)
	{
		fread(&violao_old, sizeof(violao_old), 1, ptrArqViolao);
		nReg++;
		if (violao_old.id == att.id)
			;
		violao_encontrado = 1;
	}

	fseek(ptrArqViolao, ((nReg - 1) * sizeof(att)), SEEK_SET);
	int codViolao = fwrite(&att, sizeof(att), 1, ptrArqViolao);
}

/*****************************************************************/

//Função para excluir violões
int excluirViolao(Violao del)
{

	FILE *ptrArqViolao = fopen("violao.txt", "ab+");
	FILE *newptrArqViolao = fopen("newViolao.txt", "wb+");
	int id;

	scanf("%d", &id);

	while (!feof(ptrArqViolao))
	{
		fread(&del, sizeof(del), 1, ptrArqViolao);
		if (id == del.id)
		{
			fwrite(&del, sizeof(del), 1, newptrArqViolao);
		}
	}
	fclose(newptrArqViolao);
	fclose(newptrArqViolao);
	remove("newViolao.txt");
	rename("newViolao.txt", "violao.txt");
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
	printf("\n\n->Ao cadastrar: O preço do produto deve se utilizar ',' (vírgula), pois está no formato pt-BR\n");
	printf("\n---------------------------------------------------------------------------------------------------\t\n");
	printf("\n 1: Cadastrar Violão");
	printf("\n 2: Consultar Violão");
	printf("\n 3: Alterar Dados do Violão");
	printf("\n 4: Excluir Registro do Violão");
	printf("\n 0: Sair");
	printf("\n\n\n Digite o numero correspondente a opcao: ");
	scanf("%d", &op);
	system("cls");

	switch (op)
	{
	case 1:
		printf("\n-----Cadastrar Violão-----\n");
		printf("\nDigite o ID do Violão:\t");
		scanf("%d", &vID);
		cadastrarViolao(vID);
		break;

	case 2:
		printf("\n-----Consultar Cadastro do Violão-----\n");
		printf("\nDigite o ID do Violão:\t");
		scanf("%d", &vID);
		consultarViolao(vID);
		break;

	case 3:
		printf("\n-----Alterar Dados do Violão-----\n");
		printf("\nDigite o ID do Violão:\t");
		scanf("%d", &vID);
		editarViolao(consultarViolao(vID));
		break;

	case 4:
		printf("\n-----Excluir Registro do Violão-----\n");
		printf("\nDigite o ID do Violão:\t");
		scanf("%d", &vID);
		excluirViolao(consultarViolao(vID));
		break;

	case 0:
		exit(1);
		break;

	default:
		printf("ERRO!! OPÇÃO NÃO ENCONTRADA, POR FAVOR INSIRA UMA OPÇÃO VALIDA \n");
		system("pause");
		break;
	}
	menu();
}
