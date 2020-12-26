#include<stdio.h>
#include<locale.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#define catalogoProdutos "produtos"

#define quantidadeMaximaDeItensEmUmaGondola 5
#define quantidadeDeGondolas 12

#define carrinho "carrinhoDeCompras"

#define SIZA 300
#define MAX 200

struct usuario{
	int privilegioUsuario;
	char nome[MAX];
	char prontuario[10];
};

struct Produto
{
	int codigoProduto;
	
	char nomeProduto[45];
	char descricaoProduto[100];
	float peso;
	float preco;
	
	int quantidadeEmEstoque;
};

struct Esteira
{
	struct Produto elementosNaEsteira[200];
	int front;
	int rear;
};


/*Modulo Produtos*/

	/*Cadastro De Produtos*/
void headCadastroProduto(void);
int cadastrarProduto(void);

	/*Funções auxiliares*/
int gerarCodigoProduto(void);
int calcularQuantidadeDeElementosNoArquivoProdutos(void);

	/*Busca*/
int buscaBinariaCodigoDeProduto(FILE *enderecoDoArquivoProdutos, int quantidadeDeElementos, int indiceInicial, int codigoProcurado);

	/*Ordenação*/
int inserirElementoNoCatalogoDeProdutos(struct Produto elementoASerIntroduzido);

	/*Funções de visualização de produtos*/
void listarProdutos(void);
void mostrarDadosDoProduto(struct Produto produtoASerExibido);

/*Modulo Usuarios*/

void limpatelaecabecalhocadastramentousuario(void);
void limpatelaecabecalhoalteracaodadosusuario(void);
void limpatelaecabecalhoremocaousuario(void);
void sortstruct(struct usuario elementoInserido);
void gerenciamentousuarios(void);
void cadastramentousuarios(void);
void listarusuarios(void);

/*Modulo Sistemas*/

int sistemaGerenciador(char nomeDeUsuario[], char prontuario[]);
void headSistemaGerenciadorDeSupermercado(void);
void menuMaster(void);
void gerenciarProdutos(void);
void menuGerenciarProdutos(void);

int sistemaCliente(char nomeDeUsuario[], char prontuario[]);
void headSistemaCliente();
void menuMortal(void);

/*Modulo Gerenciamento de Gondolas*/

void gerenciarGondolas(void);	

	/*Micro operações sobre gôndolas*/
int pushFILE(char nomeDoArquivo[], int codigoDoProdutoASerInserido);
int popFILE(char nomeDoArquivo[]);
int topFILE(char nomeDoArquivo[]);
int isEmptyFILE(char nomeDoArquivo[]);
int isFullGondola(char nomeDoArquivo[]);
int quantidadeDeItensNaPilhaFILE(char nomeDoArquivo[]);

	/*Macro operações sobre gôndolas*/
void inserirProdutoEmUmaGondola(char nomeDoArquivoDaGondola[], int numeroDaGondola);
void removerProdutoDeUmaGondola(char nomeDoArquivoDaGondola[], int numeroDaGondola);

	/*Gráficos*/
void headGerenciadorDeGondolas(void);
void displayGondolas(char *todasAsGondolas[]);
void mostrarGondolaCompleta(char nomeDaGondola[]);

/*Modulo Compras*/

void headCompras(void);
void mostrarProdutoVisaoCliente(struct Produto produtoASerExibido);
void mostrarCarrinho(char nomeArquivoCarrinho[]);

void removerProdutoDoCarrinho(void);
void removerDoCarrinhoEAtulizarEstoque(void);

int comprar(void);

/*Modulo Caixa*/

void inicializarEsteira(struct Esteira *enderecoDaEsteira);
void enqueueEsteira(struct Esteira *enderecoDaEsteira, struct Produto produtoASerInserido);
void dequeueEsteira(struct Esteira *enderecoDaEsteira);
int size(struct Esteira *enderecoDaEsteira);
int emptyEsteira(struct Esteira *enderecoDaEsteira);
int moduloParaValoresNegativos(int resultadoRemainder, int valorDoModulo);
void pegarEnderecoParaEntrega(char endereco[]);

void headCaixa(void);
void displayEsteira(struct Esteira *enderecoDaEsteira);
void caixa(char nomeUsuario[], char prontuario[], char endereco[]);
void gerarNotaFiscal(char nomeUsuario[], char prontuario[], char endereco[], float totalCompra, struct Esteira *produtosComprados);

int buscabinaria(FILE *arquivo, int indiceInicial, int tamanho, char nomeLogin[MAX], char prontuarioLogin[MAX]);

int main(){
	
	setlocale(LC_ALL,"Portuguese");
	
	FILE *usuariosdat = NULL;
	
	usuariosdat = fopen("USUARIOS.DAT", "a+b");
	
	struct usuario usr;
	struct usuario usrPrivilegio;
	int quantidadeElementosStruct;
	char nomeLoginDigitado[MAX];
	char prontuarioLoginDigitado[MAX];
	int opcaoDesejada;
	int i;
 
	if (usuariosdat){
		do{
			do{
				system("CLS");
				printf("SISTEMA GERENCIADOR DE SUPERMERCADO\n\n");
				printf("[1] - Realizar login\n");
				printf("[2] - Cadastrar usuário\n");
				printf("[0] - SAIR\n\n");
				printf("Selecione a opção desejada: ");
				fflush(stdin);
				if (scanf("%d", &opcaoDesejada)){
					break;
				}
				printf("\n\nEntrada inválida inserida. Pressione qualquer tecla para tentar novamente");
				getch();
			} while (1);
			
			fseek(usuariosdat, 0L, SEEK_END);
			quantidadeElementosStruct = (ftell(usuariosdat)) / (sizeof(struct usuario));
			
			switch (opcaoDesejada){
				case 1:
					do{
						system("CLS");
						system("color 1F");
						printf("LOGIN (Digite 00 em ambos os campos para voltar ao menu inicial)");
						printf("\n\n%-21s", "NOME DO USUÁRIO: ");
						fflush(stdin);
						strupr(gets(nomeLoginDigitado));
						printf("\n\n\n");
						printf("%-21s", "PRONTUÁRIO DO USUÁRIO: ");
						fflush(stdin);
						strupr(gets(prontuarioLoginDigitado));
						printf("\n\n");
				
						fseek(usuariosdat, 0L, SEEK_END);
						quantidadeElementosStruct = ftell(usuariosdat) / sizeof(struct usuario);
					
						if (((strcmp(nomeLoginDigitado, "00")) != 0) || ((strcmp(prontuarioLoginDigitado, "00")) != 0)){
							if ((buscabinaria(usuariosdat, 0, quantidadeElementosStruct, nomeLoginDigitado, prontuarioLoginDigitado)) == 1){
								for (i=0; i<quantidadeElementosStruct; i++){
									fseek(usuariosdat, (i * sizeof(struct usuario)), SEEK_SET);
									fread(&usrPrivilegio, sizeof(struct usuario), 1, usuariosdat);
									if(((strcmp(usrPrivilegio.nome, nomeLoginDigitado)) == 0) && ((strcmp(usrPrivilegio.prontuario, prontuarioLoginDigitado)) == 0)){
										break;
									}		
								}
								system("color 2F");
								printf("Acesso permitido!\n\n");
								getch();
								system("color 0F");
								if (usrPrivilegio.privilegioUsuario == 1){
									sistemaGerenciador(usrPrivilegio.nome, usrPrivilegio.prontuario);
								}
								else
								{
									sistemaCliente(usrPrivilegio.nome, usrPrivilegio.prontuario);
								}
							}
						else{
							system("color 4F");
							printf("USUÁRIO E/OU PRONTUÁRIO INVÁLIDO");			
							getch();
						}
					}
			
				} while (((strcmp(nomeLoginDigitado, "00")) != 0) || ((strcmp(prontuarioLoginDigitado, "00")) != 0));
				
				break;
				
				case 2:
					system("color 0F");
					cadastramentousuarios();
					break;
				case 0:
					printf("\n\nObrigado por utilizar nosso sistema :)");
					getch();
					break;
				default:
					printf("\n\nOpção inválida! Pressione qualquer tecla para tentar novamente");
					getch();
				}
			} while (opcaoDesejada != 0);
		}
		else{
			system("CLS");
			system("color 04");
			printf("\n\nARQUIVO USUARIOS.DAT INEXISTENTE");
			getch();
			exit(1);
		}
	
	fclose(usuariosdat);
}

int buscabinaria(FILE *arquivo, int indiceInicial, int tamanho, char nomeLogin[MAX], char prontuarioLogin[MAX]){
	
	int usuarioEncontrado = 0;
	int meio;
	struct usuario *procurador = NULL;
	int modTamanhoParNegado = 1;
	int modTamanhoImparNegado = 0;
	
	fclose(arquivo);
	
	arquivo = NULL;
	
	arquivo = fopen("USUARIOS.DAT", "rb");	
	
	procurador = (struct usuario *) malloc (sizeof(struct usuario));
	
	if(!arquivo){
		system("CLS");
		system("color 04");
		printf("\n\nARQUIVO USUARIOS.DAT INEXISTENTE");
		getch();
		exit(1);
	}
	else{
		if(!procurador){
			system("CLS");
			system("color 04");
			printf("\n\nmalloc devolveu NULL!");
			getch();
			exit(2);	
		}
		else{
			if (tamanho > 0){
			
			meio = ((indiceInicial) + ((tamanho)/2));
			
			fseek(arquivo, (long)(meio * sizeof(struct usuario)), SEEK_SET);
			
			fread(procurador, sizeof(struct usuario), 1, arquivo);
			
			if ((strcmp(procurador->nome, nomeLogin) == 0) && ((strcmp(procurador->prontuario, prontuarioLogin)) == 0)){
				usuarioEncontrado = 1;
				return usuarioEncontrado;
			}
			else if ((strcmp(nomeLogin, procurador->nome)) > 0){	
				indiceInicial = meio+1;
				tamanho = ((tamanho/2) - (!(tamanho % 2)));
			}
			else{
				tamanho /= 2;
			}
				
			free(procurador);
				
			return buscabinaria(arquivo, indiceInicial, tamanho, nomeLogin, prontuarioLogin);
				
			}
		}
	}
}

/*Modulo Produtos*/

void headCadastroProduto(void)
{
	system("CLS");
	printf("                                                                            CADASTRO DE PRODUTO\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                                                 Insira os seguintes dados sobre o produto:\n\n");
	
	return;
}

int cadastrarProduto(void)
{
	setlocale(LC_ALL, "Portuguese");
	
	char confirmacaoDosDados = '\0';
	
	int resultadoDaOperacao = 0;
	
	FILE *enderecoDoArquivoProdutos = NULL;
	
	struct Produto novoProduto;
	
	novoProduto.codigoProduto = -1;
	
	do
	{
		headCadastroProduto();
		printf("                                                                            Nome do Produto: ");
		gets(novoProduto.nomeProduto);
	}while(strlen(novoProduto.nomeProduto) == 0);
	
	headCadastroProduto();
	printf("                                                                           Descrição do produto: ");
	gets(novoProduto.descricaoProduto);
	
	if(strlen(novoProduto.descricaoProduto) == 0)
	{
		strcpy(novoProduto.descricaoProduto, "NÃO HÁ DESCRIÇÃO");
	}
	
	do
	{
		headCadastroProduto();
		printf("                                                                               Peso(g): ");
		fflush(stdin);
	}while(!(scanf("%f", &novoProduto.peso) && (novoProduto.peso >= 0.0)));
	
	do
	{
		headCadastroProduto();
		printf("                                                                               Preço: R$");
		fflush(stdin);
	}while(!(scanf("%f", &novoProduto.preco) && (novoProduto.preco >= 0.0)));
	
	do
	{
		headCadastroProduto();
		printf("                                                                          Quantidade em estroque: ");
		fflush(stdin);
	}while(!(scanf("%d", &novoProduto.quantidadeEmEstoque) && (novoProduto.quantidadeEmEstoque >= 0)));
	
	do
	{
		system("CLS");
		printf("                                                                            CADASTRO DE PRODUTO\n");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                      Confirme os dados do produto para que o cadastro seja concluído:\n\n");
		mostrarDadosDoProduto(novoProduto);
		printf("\n\n");
		printf("                                                                           [1] - Confirmar\n");
		printf("                                                                           [0] - Cancelar cadastro\n\n");
		printf("                                                                                             ");
		fflush(stdin);
	}while(!((confirmacaoDosDados = getchar()) && (confirmacaoDosDados == '1' || confirmacaoDosDados == '0')));
	
	if(confirmacaoDosDados == '0')
	{
		printf("\n\n                                                                             Cadastro cancelado ");
		fflush(stdin);
		getchar();
	}
	else
	{
		novoProduto.codigoProduto = gerarCodigoProduto();
		
		if(novoProduto.codigoProduto != -1)
		{
			if(-1 == inserirElementoNoCatalogoDeProdutos(novoProduto))
			{
				printf("\n\n                                                      Erro encontrado durante o processo de cadastro. Operação cancelada. \n\n");
				fflush(stdin);
				getchar();
			}
			else
			{
				system("CLS");
				printf("                                                                            CADASTRO DE PRODUTO\n");
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf("                                                                           Cadastro concluído :)\n\n");
				mostrarDadosDoProduto(novoProduto);
				printf("\n                                                                                                 ");
				fflush(stdin);
				getchar();
			}
		}
		else
		{
			printf("\n\n                                                      Erro encontrado durante o processo de cadastro. Operação cancelada. \n\n");
			fflush(stdin);
			getchar();
		}
	}
	
	return resultadoDaOperacao;
}

int gerarCodigoProduto(void)
{
	int codigoProduto = -1;
	int quantidadeDeElementosNoArquivo = calcularQuantidadeDeElementosNoArquivoProdutos();
	FILE *enderecoDoArquivoProdutos = NULL;
	
	if(quantidadeDeElementosNoArquivo >= 0)
	{
		if(enderecoDoArquivoProdutos = (fopen(catalogoProdutos, "rb")))
		{
			srand(time(NULL));
		
			do
			{
				codigoProduto = rand();
			}while(-1 != (buscaBinariaCodigoDeProduto(enderecoDoArquivoProdutos, quantidadeDeElementosNoArquivo, 0, codigoProduto)));
			
			fclose(enderecoDoArquivoProdutos);
		}
		else
		{
			printf("\n\n                                                  Erro ao abrir arquivo \"%s\" durante geração de código. :( ", catalogoProdutos);
		}
	}
	
	return codigoProduto;
}

int calcularQuantidadeDeElementosNoArquivoProdutos(void)
{
	int quantidadeDeElementos = -1;
	FILE *enderecoDoArquivoProdutos = NULL;
	
	if(enderecoDoArquivoProdutos = (fopen(catalogoProdutos, "a+b")))
	{
		fseek(enderecoDoArquivoProdutos, 0L, SEEK_END);
		
		quantidadeDeElementos = ((ftell(enderecoDoArquivoProdutos))/(sizeof(struct Produto)));
	
		fclose(enderecoDoArquivoProdutos);
	}
	else
	{
		printf("\n\n                                                  Erro ao abrir arquivo \"%s\" durante cálculo de elementos. :( ", catalogoProdutos);
	}
	
	return quantidadeDeElementos;
}

int buscaBinariaCodigoDeProduto(FILE *enderecoDoArquivoProdutos, int quantidadeDeElementos, int indiceInicial, int codigoProcurado)
{
	int indiceDoCodigoProcurado = -1;
	int indiceMeio;
	int codigoDoElementoNoMeio;
	
	if(quantidadeDeElementos > 0)
	{
		indiceMeio = ((indiceInicial) + (quantidadeDeElementos/2));
		
		fseek(enderecoDoArquivoProdutos, (long)(sizeof(struct Produto) * indiceMeio), SEEK_SET);
		
		fread(&codigoDoElementoNoMeio, (sizeof(codigoDoElementoNoMeio)), 1, enderecoDoArquivoProdutos);
		
		if(codigoDoElementoNoMeio == codigoProcurado)
		{
			indiceDoCodigoProcurado = indiceMeio;
		}
		else
		{
			if(codigoProcurado < codigoDoElementoNoMeio)
			{
				quantidadeDeElementos = (quantidadeDeElementos/2);
			}
			else
			{
				indiceInicial = (indiceMeio + 1);
				
				quantidadeDeElementos = ((quantidadeDeElementos/2) - (!(quantidadeDeElementos % 2)));
			}
			
			indiceDoCodigoProcurado = buscaBinariaCodigoDeProduto(enderecoDoArquivoProdutos, quantidadeDeElementos, indiceInicial, codigoProcurado);
		}
	}
	
	return indiceDoCodigoProcurado;
}

int inserirElementoNoCatalogoDeProdutos(struct Produto elementoASerIntroduzido)
{
	FILE *enderecoDoArquivoProdutos = NULL;

	int quantidadeAtualDeElementosNoArquivo = (calcularQuantidadeDeElementosNoArquivoProdutos());
	
	int indiceDaPosicaoQueDeveReceberONovoElemento = (quantidadeAtualDeElementosNoArquivo);
	
	int controlador;
	
	int codigoDoElementoNaPosicaoDeIndiceControlador;
	
	struct Produto auxiliarDeMovimentacaoDeRegistros;
	
	int resultadoDaInsercao = -1;
	
	if(enderecoDoArquivoProdutos = (fopen(catalogoProdutos, "r+b")))
	{
		controlador = 0;
		
		while(controlador < quantidadeAtualDeElementosNoArquivo)
		{
			fseek(enderecoDoArquivoProdutos, (long)(controlador * (sizeof(struct Produto))), SEEK_SET);
		
			fread(&codigoDoElementoNaPosicaoDeIndiceControlador, sizeof(codigoDoElementoNaPosicaoDeIndiceControlador), 1, enderecoDoArquivoProdutos);
				
			if(elementoASerIntroduzido.codigoProduto <= codigoDoElementoNaPosicaoDeIndiceControlador)
			{
				indiceDaPosicaoQueDeveReceberONovoElemento = controlador;
				
				controlador = quantidadeAtualDeElementosNoArquivo;
			}
			else
			{
				controlador = (controlador + 1);
			}
		}
	
		while(controlador > indiceDaPosicaoQueDeveReceberONovoElemento)
		{
			fseek(enderecoDoArquivoProdutos, (long)((controlador - 1) * (sizeof(struct Produto))), SEEK_SET);
			
			fread(&auxiliarDeMovimentacaoDeRegistros, sizeof(auxiliarDeMovimentacaoDeRegistros), 1, enderecoDoArquivoProdutos);
			
			fseek(enderecoDoArquivoProdutos, (long)(controlador * (sizeof(struct Produto))), SEEK_SET);
			
			fwrite(&auxiliarDeMovimentacaoDeRegistros, sizeof(auxiliarDeMovimentacaoDeRegistros), 1, enderecoDoArquivoProdutos);
			
			controlador = (controlador - 1);
		}
		
		fseek(enderecoDoArquivoProdutos, (long)(indiceDaPosicaoQueDeveReceberONovoElemento * (sizeof(struct Produto))), SEEK_SET);
		
		fwrite(&elementoASerIntroduzido, sizeof(struct Produto), 1, enderecoDoArquivoProdutos);
		
		fclose(enderecoDoArquivoProdutos);
		
		resultadoDaInsercao = 1;
	}
	else
	{
		printf("\n\n                                                     Erro ao abrir arquivo \"%s\" durante inserção. :( ", catalogoProdutos);	
	}
	
	return resultadoDaInsercao;
}

void mostrarDadosDoProduto(struct Produto produtoASerExibido)
{
	if(produtoASerExibido.codigoProduto != -1)
	{
		printf("                                                                        Código: %d\n\n", produtoASerExibido.codigoProduto);
	}
	
	
	printf("                                                                        Nome do produto: %s\n\n", produtoASerExibido.nomeProduto);
	printf("                                                                        Descrição: %s\n\n", produtoASerExibido.descricaoProduto);
	printf("                                                                        Peso: %.2fg\n\n", produtoASerExibido.peso);
	printf("                                                                        Preço: R$%.2f\n\n", produtoASerExibido.preco);
	printf("                                                                        Quantidade em estoque: %d\n", produtoASerExibido.quantidadeEmEstoque);
	
	return;
}

void listarProdutos()
{
	FILE *enderecoDoArquivoProdutos = NULL;
	
	int quantidadeDeProdutosASeremRepresentados = calcularQuantidadeDeElementosNoArquivoProdutos();
	
	struct Produto produtoASerMostrado;
	
	if(quantidadeDeProdutosASeremRepresentados != -1)
	{
		if(quantidadeDeProdutosASeremRepresentados == 0)
		{
			printf("\n\n                                                                      Não há produtos cadastrados :( \n\n");	
		}
		else
		{	
			if(enderecoDoArquivoProdutos = (fopen(catalogoProdutos, "rb")))
			{
				printf("                                                                          Catálogo de Produtos\n\n");
				
				while(quantidadeDeProdutosASeremRepresentados > 0)
				{
					fread(&produtoASerMostrado, sizeof(struct Produto), 1, enderecoDoArquivoProdutos);
					
					mostrarDadosDoProduto(produtoASerMostrado);
					
					printf("\n");
					
					quantidadeDeProdutosASeremRepresentados = (quantidadeDeProdutosASeremRepresentados - 1);
					
					if(quantidadeDeProdutosASeremRepresentados)
					{
						printf("                                                                                     |\n\n");
					}
				}
				
				fclose(enderecoDoArquivoProdutos);
			}
			else
			{
				printf("\n\n                                                     Erro ao abrir arquivo \"%s\" durante listagem. :( ", catalogoProdutos);
			}
		}
	}
	
	return;
}



/*Modulo Usuarios*/

void limpatelaecabecalhocadastramentousuario(void){
	system("CLS");
	printf("CADASTRAMENTO DE USUÁRIOS\n\n");
}

/*
void limpatelaecabecalhoalteracaodadosusuario(void){
	system("CLS");
	printf("ALTERAÇÃO DE USUÁRIOS\n\n");
}

void limpatelaecabecalhoremocaousuario(void){
	system("CLS");
	printf("REMOÇÃO DE USUÁRIOS\n\n");
}
*/

void sortstruct(struct usuario elementoInserido){
	
	int tamanhoVetor;
	FILE *arquivo = NULL;
	struct usuario auxPosicao;
	struct usuario auxTroca;
	int i;
	
	arquivo = fopen("USUARIOS.DAT", "r+b");
	
	if(!arquivo){
		system("CLS");
		system("color 04");
		printf("\n\nARQUIVO USUARIOS.DAT INEXISTENTE");
		getch();
		exit(1);
	}
	else{
		fseek(arquivo, 0L, SEEK_END);
		
		tamanhoVetor = (ftell(arquivo) / sizeof(struct usuario)) + 1;
	
		for (i = tamanhoVetor-1; i > 0; i--){
			
			fseek(arquivo, (long)(i * sizeof(struct usuario)), SEEK_SET);
			
			fread(&elementoInserido, sizeof(struct usuario), 1, arquivo);
			
			fseek(arquivo, (long)((i-1) * sizeof(struct usuario)), SEEK_SET);
			
			fread(&auxPosicao, sizeof(struct usuario), 1, arquivo);
			
			if (((strcmp(elementoInserido.nome, auxPosicao.nome)) <= 0)){
				
				fseek(arquivo, (long)((i-1) * sizeof(struct usuario)), SEEK_SET);
				fwrite(&elementoInserido, sizeof(struct usuario), 1, arquivo);
				fseek(arquivo, (long)(i * sizeof(struct usuario)), SEEK_SET);
				fwrite (&auxPosicao, sizeof(struct usuario), 1, arquivo);
				
			}
			else{
				fseek(arquivo, (long)(i * sizeof(struct usuario)), SEEK_SET);
				fwrite (&elementoInserido, sizeof(struct usuario), 1, arquivo);
				break;
			}
		}
		
		if(tamanhoVetor == 1){
			fwrite (&elementoInserido, sizeof(struct usuario), 1, arquivo);
		}
		
		getch();
	}

	fclose(arquivo);
	
	return;
}

void gerenciarUsuarios(void){
	
	FILE *usuariosdat = NULL;
	int opcaoDesejada;
	int quantidadeElementosStruct;
	
	usuariosdat = fopen("USUARIOS.DAT", "a+b");
	
	if(!usuariosdat){
		system("CLS");
		system("color 04");
		printf("\n\nARQUIVO USUARIOS.DAT INEXISTENTE");
		getch();
		exit(1);
	}
	else{
		do{

			fseek(usuariosdat, 0L, SEEK_END);
			quantidadeElementosStruct = (ftell(usuariosdat)) / (sizeof(struct usuario));
		
			do{
				system("CLS");
				printf("GERENCIAMENTO DE USUÁRIOS\n\n");
				printf("[1] - Cadastrar usuário\n");
				printf("[2] - Listar usuários cadastrados\n");
				printf("[0] - SAIR\n\n");
				printf("Digite a opção desejada: ");
				fflush(stdin);
				if (scanf("%d", &opcaoDesejada)){
					break;
				}
				printf("\n\nEntrada inválida inserida. Pressione qualquer tecla para tentar novamente");
				getch();
			} while (1);
			
			switch(opcaoDesejada){
				case 1:
					cadastramentousuarios();
					break;
				case 2:
					listarusuarios();
					break;
				case 0:
					break;
					return;
				default:
					printf("\n\nOpção inválida. Pressione qualquer tecla para tentar novamente");
					getch();
			}
			
		} while (opcaoDesejada != 0);
	}
	
	fclose(usuariosdat);
	
}

void cadastramentousuarios(void){
	
	FILE *usuariosdat = NULL;
	
	usuariosdat = fopen("USUARIOS.DAT", "rb");
	
	struct usuario usuarioQueSeraCadastrado;
	struct usuario resultadoBuscaSequencial;
	int quantidadeElementosStruct;
	int escolhaPrivilegio;
	char senhaUsuarioMasterDigitada[MAX];
	int i;
	
	if(!usuariosdat){
		system("CLS");
		system("color 04");
		printf("\n\nARQUIVO USUARIOS.DAT INEXISTENTE");
		getch();
		exit(1);
	}
	else{
		
		do{
			fseek(usuariosdat, 0L, SEEK_END);
			quantidadeElementosStruct = (ftell(usuariosdat)) / sizeof(struct usuario);
			
			limpatelaecabecalhocadastramentousuario();
			
			printf("Digite o nome do usuário: ");
			fflush(stdin);
			strupr(gets(usuarioQueSeraCadastrado.nome));
				
			limpatelaecabecalhocadastramentousuario();
			
			printf("Digite o prontuário de %s: ", usuarioQueSeraCadastrado.nome);
			fflush(stdin);
			strupr(gets(usuarioQueSeraCadastrado.prontuario));
			
			for (i=0; i<quantidadeElementosStruct; i++){
				fseek(usuariosdat, (i * sizeof(struct usuario)), SEEK_SET);
				fread(&resultadoBuscaSequencial, sizeof(struct usuario), 1, usuariosdat);
				if ((strcmp(resultadoBuscaSequencial.prontuario, usuarioQueSeraCadastrado.prontuario)) == 0){
					break;
				}
			}
			if (((strcmp(usuarioQueSeraCadastrado.nome, "00")) == 0) && ((strcmp(usuarioQueSeraCadastrado.prontuario, "00")) == 0)){
				printf("\n\nEste nome e prontuário não podem ser cadastrados no sistema");
				getch();
			}
			else if ((strcmp(resultadoBuscaSequencial.prontuario, usuarioQueSeraCadastrado.prontuario)) == 0){	
				printf("\n\nProntuário já cadastrado no sistema. Por favor, digite outro nome de usuário e prontuário");	
				getch();
			}
				
		} while ((strcmp(resultadoBuscaSequencial.prontuario, usuarioQueSeraCadastrado.prontuario)) == 0 || (((strcmp(usuarioQueSeraCadastrado.nome, "00")) == 0) && ((strcmp(usuarioQueSeraCadastrado.prontuario, "00")) == 0)));
		
		fclose (usuariosdat);
		
		usuariosdat = fopen("USUARIOS.DAT", "a+b");
			
		do{
			
			do{
				
				limpatelaecabecalhocadastramentousuario();
			
				printf("0 - Comum");
				printf("\n1 - Master");
				printf("\n\nEscolha o privilégio de %s: ", usuarioQueSeraCadastrado.nome);
				fflush(stdin);
				if (scanf("%d", &escolhaPrivilegio)){
					break;
				}
				printf("\n\nEntrada inválida inserida! Pressione qualquer tecla para tentar novamente");
				getch();
			} while (1);
			if(escolhaPrivilegio == 1){
				do{
					limpatelaecabecalhocadastramentousuario();
					printf("Digite a senha para cadastramento de um usuário master: ");	
					fflush(stdin);
					gets(senhaUsuarioMasterDigitada);
											
					if(strcmp(senhaUsuarioMasterDigitada, "cavalo verde marciano come abacaxi") == 0){
						usuarioQueSeraCadastrado.privilegioUsuario = 1;
						printf("\n\nUsuário master %s cadastrado(a)", usuarioQueSeraCadastrado.nome);
					}
					else{
						printf("\n\nSenha incorreta! Pressione qualquer tecla para tentar novamente");
						getch();
					}
				} while ((strcmp(senhaUsuarioMasterDigitada, "cavalo verde marciano come abacaxi") != 0));				
			}
			else if (escolhaPrivilegio == 0){
				usuarioQueSeraCadastrado.privilegioUsuario = 0;
				printf("\n\nUsuário comum %s cadastrado(a)", usuarioQueSeraCadastrado.nome);
			}
			else{
				printf("\n\nPrivilégio inválido! Pressione qualquer tecla para tentar novamente");
			}
		
			getch();
		
		} while (!((escolhaPrivilegio == 0) || (escolhaPrivilegio == 1)));
			
		fseek(usuariosdat, 0L, SEEK_END);
		
		quantidadeElementosStruct = (ftell(usuariosdat) / sizeof(struct usuario));	
			
		fclose(usuariosdat);
	
		sortstruct(usuarioQueSeraCadastrado);
	
		getch();
	}
}

/*

void alteracaodadosusuarios(){
	
	struct usuario usuarioASerAlterado;
	struct usuario novosDados;
	struct usuario resultadoBuscaArquivo;
	struct usuario resultadoBuscaArquivoRedundanciaDadosCadastramento;
	struct usuario sobrescreverUsuario;
	int indiceUsuarioAlterado;
	FILE *arquivoAlteracao = NULL;
	int quantidadeElementosArquivo = ftell(arquivoAlteracao) / sizeof(struct usuario);
	char confirmadorAlteracao;
	int i=0;
	
	arquivoAlteracao = fopen("TESTE.DAT", "r+b");
	
	if(arquivoAlteracao = fopen("TESTE.DAT", "r+b")){
		system("CLS");
		printf("ALTERAÇÃO DE USUÁRIOS\n\n");
		printf("Digite o nome do usuário o qual se deseja alterar os dados: ");
		fflush(stdin);
		strupr(gets(usuarioASerAlterado.nome));
		system("CLS");
		printf("ALTERAÇÃO DE USUÁRIOS\n\n");
		printf("Digite o prontuário do usuário o qual se deseja alterar os dados: ");		
		fflush(stdin);
		strupr(gets(usuarioASerAlterado.prontuario));
		fseek(arquivoAlteracao, 0L, SEEK_END);
		quantidadeElementosArquivo = (ftell(arquivoAlteracao)) /  sizeof(struct usuario);
	
		if((buscabinaria(arquivoAlteracao, 0, quantidadeElementosArquivo, usuarioASerAlterado.nome, usuarioASerAlterado.prontuario)) == 1){
			
			arquivoAlteracao = fopen("TESTE.DAT", "r+b");
			
			printf("\n\nQuantidadeElementosArquivo: %d", quantidadeElementosArquivo);
			getch();
				
			for (indiceUsuarioAlterado = 0; indiceUsuarioAlterado < quantidadeElementosArquivo; indiceUsuarioAlterado++){
				fseek(arquivoAlteracao, (long)(indiceUsuarioAlterado * sizeof(struct usuario)), SEEK_SET);
				fread(&resultadoBuscaArquivo, sizeof(struct usuario), 1, arquivoAlteracao);
				printf("\n\nresultadoBusca.nome: %s", resultadoBuscaArquivo.nome);
				printf("\nresultadoBusca.prontuario: %s", resultadoBuscaArquivo.prontuario);
				printf("\nresultadoBusca.privilegio: %d", resultadoBuscaArquivo.privilegioUsuario);
				printf("\n\nindiceUsuarioAlterado = %d", indiceUsuarioAlterado);
				getch();
				if (((strcmp(resultadoBuscaArquivo.nome, usuarioASerAlterado.nome)) == 0) && ((strcmp(resultadoBuscaArquivo.prontuario, usuarioASerAlterado.prontuario)) == 0)){
					break;
				}
			}	
			
			do{
				system("CLS");
				printf("ALTERAÇÃO DE USUÁRIOS\n\n");
				printf("Digite o novo nome para o registro de %s: ", usuarioASerAlterado.nome);
				fflush(stdin);
				strupr(gets(novosDados.nome));
				system("CLS");
				printf("ALTERAÇÃO DE USUÁRIOS\n\n");
				printf("Digite o novo prontuário para o registro de %s: ", usuarioASerAlterado.nome);
				fflush(stdin);
				strupr(gets(novosDados.prontuario));
				/*
				do{
					system("CLS");
					printf("ALTERAÇÃO DE USUÁRIOS\n\n");
					printf("Digite o novo privilégio para o registro de %s: ", usuarioASerAlterado.nome);
					fflush(stdin);
					if (scanf("%d", &novosDados.privilegioUsuario)){
						break;
					}
					printf("\n\nEntrada inválida inserida. Pressione qualquer tecla para tentar novamente");
					getch();
				} while (1);
				*/
				
				/*
				system("CLS");
				printf("ALTERAÇÃO DE USUÁRIOS\n\n");
				printf("Nome atual: %s", usuarioASerAlterado.nome);
				printf("\nNovo nome: %s", novosDados.nome);
		
				printf("\n\nProntuário atual: %s", usuarioASerAlterado.prontuario);
				printf("\nNovo prontuário: %s", novosDados.prontuario);
				*/
				
				/*
				printf("\n\nNovo privilégio: %d", novosDados.privilegioUsuario);
				if(novosDados.privilegioUsuario == 1){
					printf(" (Master)");
				}
				else{
					printf(" (Comum)");
				}
				*/
				
				/*				
				novosDados.privilegioUsuario = resultadoBuscaArquivo.privilegioUsuario;
				
				printf("\n\nDeseja continuar? (S/N): ");
				fflush(stdin);
				scanf("%c", &confirmadorAlteracao);
					
				for (i = 0; i<quantidadeElementosArquivo; i++){
					fseek(arquivoAlteracao, (long)(i * sizeof(struct usuario)), SEEK_SET);
					fread (&resultadoBuscaArquivoRedundanciaDadosCadastramento, sizeof(struct usuario), 1, arquivoAlteracao);
					if ((strcmp(novosDados.prontuario, resultadoBuscaArquivoRedundanciaDadosCadastramento.prontuario)) == 0){
						printf("\n\nJá existe um usuário cadastrado com este prontuário");
						getch();
						break;
					}
				}
			
				if (((novosDados.privilegioUsuario != 0) && (novosDados.privilegioUsuario != 1))){
					printf("\n\nPrivilégio inválido inserido. Tente novamente!");
					getch();	
				}
			
			} while (((strcmp(novosDados.prontuario, resultadoBuscaArquivoRedundanciaDadosCadastramento.prontuario)) == 0) || ((novosDados.privilegioUsuario != 0) && (novosDados.privilegioUsuario != 1))); 
			
			
			if(confirmadorAlteracao == 'S'){
				
				for (indiceUsuarioAlterado; indiceUsuarioAlterado < quantidadeElementosArquivo - 1; indiceUsuarioAlterado++){
					fseek(arquivoAlteracao, (long)((indiceUsuarioAlterado+1) * sizeof(struct usuario)), SEEK_SET);
					fread(&sobrescreverUsuario, sizeof(struct usuario), 1, arquivoAlteracao);
					fseek(arquivoAlteracao, (long)((indiceUsuarioAlterado) * sizeof(struct usuario)), SEEK_SET);
					fwrite(&sobrescreverUsuario, sizeof(struct usuario), 1, arquivoAlteracao);
					printf("\n\nindiceUsuarioAlterado = %d", indiceUsuarioAlterado); //teste
				}
				
				fseek(arquivoAlteracao, (long)((quantidadeElementosArquivo-1) * sizeof(struct usuario)), SEEK_SET);
				fwrite(&novosDados, sizeof(struct usuario), 1, arquivoAlteracao);
				
				printf("\n\nnovosDados.nome: %s", novosDados.nome); //TESTE 
				printf("\nnovosDados.prontuario: %s", novosDados.prontuario); //TESTE 
				printf("\nnovosDados.privilegio: %s", novosDados.privilegioUsuario); //TESTE
				
				sortstruct(novosDados);
				
				printf("\n\nOs dados do usuário foram alterados com sucesso!");
				getch();
				
			}
		}
		else{
			printf("\n\nO usuário procurado não existe no sistema!");
			getch();
		}
	}
	else{
		system("CLS");
		system("color 04");
		printf("\n\nARQUIVO USUARIOS.DAT INEXISTENTE");
		getch();
		exit(1);
	}
	return;
}
*/

/*
void remocaousuarios(){
	
	struct usuario usuarioASerRemovido;
	struct usuario resultadoBuscaArquivo;
	struct usuario sobrescreverUsuario;
	int indiceUsuarioRemovido;
	FILE *arquivoParaRemocao = NULL;
	int quantidadeElementosArquivo;
	char confirmadorRemocao;
	
	if(arquivoParaRemocao = fopen("TESTE.DAT", "r+b")){
		system("CLS");
		printf("REMOÇÃO DE USUÁRIOS\n\n");
		printf("Digite o nome do usuário o qual se deseja alterar os dados: ");
		fflush(stdin);
		strupr(gets(usuarioASerRemovido.nome));
		system("CLS");
		printf("REMOÇÃO DE USUÁRIOS\n\n");
		printf("Digite o prontuário do usuário o qual se deseja alterar os dados: ");		
		fflush(stdin);	
		strupr(gets(usuarioASerRemovido.prontuario));
		fseek(arquivoParaRemocao, 0L, SEEK_END);
		quantidadeElementosArquivo = (ftell(arquivoParaRemocao)) /  sizeof(struct usuario);
		if ((buscabinaria(arquivoParaRemocao, 0, quantidadeElementosArquivo, usuarioASerRemovido.nome, usuarioASerRemovido.prontuario)) == 1){
			for (indiceUsuarioRemovido = 0; indiceUsuarioRemovido < quantidadeElementosArquivo; indiceUsuarioRemovido++){
				fseek(arquivoParaRemocao, (long)(indiceUsuarioRemovido * sizeof(struct usuario)), SEEK_SET);
				fread(&resultadoBuscaArquivo, sizeof(struct usuario), 1, arquivoParaRemocao);
				if (((strcmp(resultadoBuscaArquivo.nome, usuarioASerRemovido.nome)) == 0) && ((strcmp(resultadoBuscaArquivo.prontuario, usuarioASerRemovido.prontuario)) == 0)){
					break;
				}
			}
			system("CLS");
			printf("REMOÇÃO DE USUÁRIOS\n\n");
			
			printf("Nome: %s", usuarioASerRemovido.nome);
			printf("\nProntuário: %s", usuarioASerRemovido.prontuario);
			
			printf("\n\nDeseja continuar? (S/N): ");
			fflush(stdin);
			scanf("%c", &confirmadorRemocao);
			
			if (confirmadorRemocao == 'S'){
				printf("\n\nENTREI NO IF"); //teste
				getch();
				for (indiceUsuarioRemovido; indiceUsuarioRemovido < quantidadeElementosArquivo - 1; indiceUsuarioRemovido++){
					fseek(arquivoParaRemocao, (long)((indiceUsuarioRemovido+1) * sizeof(struct usuario)), SEEK_SET);
					fread(&sobrescreverUsuario, sizeof(struct usuario), 1, arquivoParaRemocao);
					printf("\n\nsobrescreverUsuario.nome = %s", sobrescreverUsuario.nome);
					printf("\nsobrescreverUsuario.prontuario = %s", sobrescreverUsuario.prontuario);
					printf("\nsobrescreverUsuario.privilegio = %d", sobrescreverUsuario.privilegioUsuario);
					getch();
					fseek(arquivoParaRemocao, (long)(indiceUsuarioRemovido * sizeof(struct usuario)), SEEK_SET);
					fwrite(&sobrescreverUsuario, sizeof(struct usuario), 1, arquivoParaRemocao);
					fseek(arquivoParaRemocao, (long)(indiceUsuarioRemovido * sizeof(struct usuario)), SEEK_SET);
					fread(&sobrescreverUsuario, sizeof(struct usuario), 1, arquivoParaRemocao);
					printf("\n\nsobrescreverUsuario.nome = %s", sobrescreverUsuario.nome);
					printf("\nsobrescreverUsuario.prontuario = %s", sobrescreverUsuario.prontuario);
					printf("\nsobrescreverUsuario.privilegio = %d", sobrescreverUsuario.privilegioUsuario);
					getch();
				}
			}
			
			fseek(arquivoParaRemocao, 0L, SEEK_SET);
			truncate("TESTE.DAT", (quantidadeElementosArquivo-1) * sizeof(struct usuario));
			
		}
		else{
			printf("\n\nO usuário procurado não existe no sistema!");
			getch();
		}
	}
	else{
		system("CLS");
		system("color 04");
		printf("\n\nARQUIVO USUARIOS.DAT INEXISTENTE");
		getch();
		exit(1);
	}
}

*/

void listarusuarios(void){
	
	int i;
	
	struct usuario usuariosArquivo;
	int quantidadeElementosArquivo;
	FILE *arquivoQualquer = NULL;
	
	arquivoQualquer = fopen("USUARIOS.DAT", "rb");
	
	if(!arquivoQualquer){
		system("color 04");
		printf("\n\nARQUIVO USUARIOS.DAT INEXISTENTE");
		getch();
		exit(1);
	}
	else{
		fseek(arquivoQualquer, 0L, SEEK_END);
		quantidadeElementosArquivo = (ftell(arquivoQualquer) / sizeof(struct usuario));
				
		system("CLS");
		printf("USUÁRIOS CADASTRADOS NO ARQUIVO\n\n");
		printf("%-50s%-13s%-13s", "Nome", "Prontuário", "Privilégio");
		for (i=0; i<quantidadeElementosArquivo; i++){ 
		
			fseek(arquivoQualquer, i*(sizeof(struct usuario)), SEEK_SET);
			fread(&usuariosArquivo, sizeof(struct usuario), 1, arquivoQualquer);
			printf("\n\n%-50s", usuariosArquivo.nome);
			printf("%-13s", usuariosArquivo.prontuario);
			if (usuariosArquivo.privilegioUsuario == 1)
				printf("%-13s", "Master");
			else
				printf("%-13s", "Comum");
				
		}
		
		fclose(arquivoQualquer);
	}
	
	getch();
}

int sistemaGerenciador(char nomeDeUsuario[], char prontuario[])
{
	setlocale(LC_ALL, "Portuguese");	
	
	char opcao = '\0';
	
	char enderecoParaEntrega[100];
	
	while(opcao != '0')
	{
		do
		{
			headSistemaGerenciadorDeSupermercado();
			menuMaster();
		}while(!(scanf("%c", &opcao)));
		
		switch(opcao)
		{
			case '1':
				gerenciarGondolas();
			break;
			case '2':
				gerenciarUsuarios();
			break;
			case '3':
				gerenciarProdutos();
			break;
			case '4':
				comprar();
			break;
			case '5':
				pegarEnderecoParaEntrega(enderecoParaEntrega);
			break;
			case '6':
				caixa(nomeDeUsuario, prontuario, enderecoParaEntrega);
			break;
		}
	}
	
	remove(carrinho);
	
	return 0;
}

int sistemaCliente(char nomeDeUsuario[], char prontuario[])
{
	setlocale(LC_ALL, "Portuguese");	
	
	char opcao = '\0';
	
	char enderecoParaEntrega[100];
	
	while(opcao != '0')
	{
		do
		{
			headSistemaCliente();
			menuMortal();
		}while(!(scanf("%c", &opcao)));
		
		switch(opcao)
		{
			case '1':
				comprar();
			break;
			case '2':
				pegarEnderecoParaEntrega(enderecoParaEntrega);
			break;
			case '3':
				caixa(nomeDeUsuario, prontuario, enderecoParaEntrega);
			break;
		}
	}
	
	remove(carrinho);
	
	return 0;
}

void headSistemaCliente()
{
	system("CLS");
	printf("                                                                          SUPERMERCADO VAZIO\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	
	return;	
}

void gerenciarProdutos(void)
{
	char opcao = '\0';
	
	while(opcao != '0')
	{
		do
		{
			headSistemaGerenciadorDeSupermercado();
			menuGerenciarProdutos();
		}while(!(scanf("%c", &opcao)));
		
		switch(opcao)
		{
			case '1':
				cadastrarProduto();
			break;
			case '2':
				headSistemaGerenciadorDeSupermercado();
				
				listarProdutos();
				
				printf("                                                                                                      ");
				fflush(stdin);
				getchar();
				
			break;
		}
	}
		
	return;
}

void headSistemaGerenciadorDeSupermercado(void)
{
	system("CLS");
	printf("                                                                   SISTEMA GERENCIADOR SUPERMERCADO VAZIO\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	
	return;
}

void menuMaster(void)
{
	printf("                                                                       [1] - Gerenciar Gôndolas\n");
	printf("                                                                       [2] - Gerenciar Usuários\n");
	printf("                                                                       [3] - Gerenciar Produtos\n");
	printf("                                                                       [4] - Comprar\n");
	printf("                                                                       [5] - Entregas em Domicílio\n");
	printf("                                                                       [6] - Caixa/PDV\n");
	printf("                                                                       [0] - Sair\n");
	printf("                                                                                                   ");
	fflush(stdin);
	
	return;
}

void menuMortal(void)
{
	printf("                                                                       [1] - Comprar\n");
	printf("                                                                       [2] - Entregas em Domicílio\n");
	printf("                                                                       [3] - Caixa/PDV\n");
	printf("                                                                       [0] - Sair\n");
	printf("                                                                                                   ");
	fflush(stdin);
	
	return;
}

void menuGerenciarProdutos(void)
{
	printf("                                                                       [1] - Cadastrar Produtos\n");
	printf("                                                                       [2] - Listar todos os produtos\n");
	printf("                                                                       [0] - Sair\n");
	printf("                                                                                                   ");
	fflush(stdin);
	
	return;
}

/*Modulo Gerenciamento de Gondolas*/

void gerenciarGondolas(void)
{	
	char *gondolas[quantidadeDeGondolas] = {"gondola1", "gondola2", "gondola3", "gondola4", "gondola5", "gondola6", "gondola7", "gondola8", "gondola9", "gondola10", "gondola 11", "gondola 12"};
	int numeroDaGondola = -1;
	char opcao;
	
	while(numeroDaGondola != 0)
	{
		do
		{
			headGerenciadorDeGondolas();
			displayGondolas(gondolas);
			printf("\n\n                                                   Insira o número da gôndola que deve ser operada ou 0 para voltar: ");
			fflush(stdin);
		}while(!(scanf("%d", &numeroDaGondola)));
		
		if((numeroDaGondola >= 1 && numeroDaGondola <= quantidadeDeGondolas))
		{
			opcao = '\0';
			
			while(opcao != '0')
			{
				do
				{
					headGerenciadorDeGondolas();
					printf("                                                                             Gôndola %d\n\n", numeroDaGondola);
			
					mostrarGondolaCompleta(gondolas[(numeroDaGondola - 1)]);
			
					printf("\n\n");
					printf("                                                                         [1] - Inserir Produto\n");
					printf("                                                                         [2] - Remover Produto\n");
					printf("                                                                         [0] - Voltar\n");
					printf("                                                                                          ");
					fflush(stdin);
				}while(!(scanf("%c", &opcao)));
		
				switch(opcao)
				{
					case '1':
						if(!isFullGondola(gondolas[(numeroDaGondola - 1)]))
						{
							inserirProdutoEmUmaGondola(gondolas[(numeroDaGondola - 1)], numeroDaGondola);
						}
						else
						{
							printf("\n\n                                                                           GÔNDOLA CHEIA :) ");
							
							fflush(stdin);
							getchar();
						}
					break;
					case '2':
						if(!isEmptyFILE(gondolas[(numeroDaGondola - 1)]))
						{
							removerProdutoDeUmaGondola(gondolas[(numeroDaGondola - 1)], numeroDaGondola);
						}
						else
						{
							printf("\n\n                                                                           GÔNDOLA VAZIA :( ");
							
							fflush(stdin);
							getchar();
						}
					break;
				}
			}
		}
	}
	
	return;
}

int pushFILE(char nomeDoArquivo[], int codigoDoProdutoASerInserido)
{
	FILE *enderecoDoArquivoPilha = NULL;
	int ocorrenciaDeErro = 1;
	
	if(enderecoDoArquivoPilha = (fopen(nomeDoArquivo, "ab+")))
	{
		fwrite(&codigoDoProdutoASerInserido, sizeof(codigoDoProdutoASerInserido), 1, enderecoDoArquivoPilha);
	
		fclose(enderecoDoArquivoPilha);
		
		ocorrenciaDeErro = 0;	
	}
	else
	{
		printf("\n\n                                                  Erro ao abrir arquivo \"%s\" durante procedimento de push. :( ", nomeDoArquivo);
	
		fflush(stdin);
		getchar();
	}
	
	return ocorrenciaDeErro;
}

int popFILE(char nomeDoArquivo[])
{
	int ocorrenciaDeErro = 1;
	int quantidadeDeItens = quantidadeDeItensNaPilhaFILE(nomeDoArquivo);
	
	if(quantidadeDeItens >= 0)
	{	
		truncate(nomeDoArquivo, ((quantidadeDeItens - 1) * (sizeof(int))));
		
		ocorrenciaDeErro = 0;
	}
	
	return ocorrenciaDeErro;
}

int topFILE(char nomeDoArquivo[])
{
	FILE *enderecoDoArquivo = NULL;
	int codigoDoProdutoNoTopo = - 1;
	
	if(enderecoDoArquivo = (fopen(nomeDoArquivo, "rb")))
	{
		fseek(enderecoDoArquivo, (long)(-(sizeof(int))), SEEK_END);
		
		fread(&codigoDoProdutoNoTopo, (sizeof(codigoDoProdutoNoTopo)), 1, enderecoDoArquivo);
		
		fclose(enderecoDoArquivo);
	}
	else
	{
		printf("\n\n                                      Erro de abertura arquivo \"%s\" durante procedimento \"topFILE\" :( ", nomeDoArquivo);
	
		fflush(stdin);
		getchar();
	}
	
	return codigoDoProdutoNoTopo;
}

int isEmptyFILE(char nomeDoArquivo[])
{
	return (quantidadeDeItensNaPilhaFILE(nomeDoArquivo) == 0);	
}

int isFullGondola(char nomeDoArquivo[])
{
	return(quantidadeDeItensNaPilhaFILE(nomeDoArquivo) == quantidadeMaximaDeItensEmUmaGondola);	
}

int quantidadeDeItensNaPilhaFILE(char nomeDoArquivo[])
{
	int quantidadeDeItens = -1;
	FILE *enderecoDoArquivoPilha = NULL;
	
	if(enderecoDoArquivoPilha = (fopen(nomeDoArquivo, "ab+")))
	{
		fseek(enderecoDoArquivoPilha, 0L, SEEK_END);
		
		quantidadeDeItens = (ftell(enderecoDoArquivoPilha)/sizeof(int));
	
		fclose(enderecoDoArquivoPilha);
	}
	else
	{
		printf("\n\n                                                  Erro ao abrir arquivo \"%s\" durante cálculo de itens. :( ", nomeDoArquivo);
		
		fflush(stdin);
		getchar();	
	}
	
	return quantidadeDeItens;
}

void inserirProdutoEmUmaGondola(char nomeDoArquivoDaGondola[], int numeroDaGondola)
{
	FILE *enderecoDeUmArquivo = NULL;
	int quantidadeDeItensNoCatalogoProdutos = calcularQuantidadeDeElementosNoArquivoProdutos();
	int codigoProdutoASerInserido;
	int fatorDeSaltoParaLocalizacaoDoProduto;
	struct Produto produtoASerInserido;
	char confirmacaoDeInsercao;
	
	if(quantidadeDeItensNoCatalogoProdutos > 0)
	{
		do
		{
			headGerenciadorDeGondolas();
			
			listarProdutos();
			
			printf("\n\n                                                       Insira o código do produto que deve ser inserido ou -1 para voltar: ");
			
			fflush(stdin);
		}while(!(scanf("%d", &codigoProdutoASerInserido)));
		
		if(codigoProdutoASerInserido != -1)
		{
			if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb+")))
			{
				fatorDeSaltoParaLocalizacaoDoProduto = buscaBinariaCodigoDeProduto(enderecoDeUmArquivo, quantidadeDeItensNoCatalogoProdutos, 0, codigoProdutoASerInserido);
				
				if(fatorDeSaltoParaLocalizacaoDoProduto != -1)
				{
					fseek(enderecoDeUmArquivo, (fatorDeSaltoParaLocalizacaoDoProduto * (sizeof(struct Produto))), SEEK_SET);
					
					fread(&produtoASerInserido, sizeof(struct Produto), 1, enderecoDeUmArquivo);
					
					fclose(enderecoDeUmArquivo);
					
					if(produtoASerInserido.quantidadeEmEstoque > 0)
					{
					
						do
						{
							headGerenciadorDeGondolas();
							
							printf("                                                                 Deseja inserir o seguinte produto?:\n\n");
							
							mostrarDadosDoProduto(produtoASerInserido);
							
							printf("\n\n");
							printf("                                                                         [1] - Confirmar\n");
							printf("                                                                         [0] - Cancelar\n");
							printf("                                                                                         ");
							fflush(stdin);
						}while(!(scanf("%c", &confirmacaoDeInsercao)));
						
						if(confirmacaoDeInsercao == '1')
						{
							if(0 == pushFILE(nomeDoArquivoDaGondola, produtoASerInserido.codigoProduto))
							{	
								/*Atualizando quantidade em estoque*/
								
								if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "r+b")))
								{
									produtoASerInserido.quantidadeEmEstoque = (produtoASerInserido.quantidadeEmEstoque - 1); 
									
									fseek(enderecoDeUmArquivo, (fatorDeSaltoParaLocalizacaoDoProduto * (sizeof(struct Produto))), SEEK_SET);
									
									fwrite(&produtoASerInserido, sizeof(produtoASerInserido), 1, enderecoDeUmArquivo);
									
									fclose(enderecoDeUmArquivo);
									
									printf("\n\n                                                                         Inserção concluída :) ");
								}
								else
								{
									printf("\n\n                                              Erro ao abrir arquivo \"%s\" durante a atualização de estoque. :( ", catalogoProdutos);
								}
							}
							else
							{
								printf("\n\n                            Erro durante procedimento de \"Push\" de produto em gôndola, pós confirmação. :( ");
							}
						}
						else
						{
							printf("\n\n                                                                         Operação cancelada ;) ");
						}	
					}
					else
					{
						printf("\n\n                                                                            NÃO HÁ QUANTIDADE EM ESTOQUE PARA ESSE PRODUTO :( ");
					}
					
					fflush(stdin);
					getchar();
				}
				else
				{
					fclose(enderecoDeUmArquivo);
					
					printf("\n\n                                                                            PRODUTO NÃO ENCONTRADO ");	
					
					fflush(stdin);
					getchar();
				}
			}
			else
			{
				printf("\n\n                                              Erro ao abrir arquivo \"%s\" durante inserção de produto em gôndola. :( ", catalogoProdutos);
			
				fflush(stdin);
				getchar();	
			}
		}
	}
	else
	{
		printf("\n\n                                                Não há produtos registrados para inserção. !!!V A Z I O!!! :( :( :( :( ");		
	
		fflush(stdin);
		getchar();	
	}
	
	
	return;
}

void removerProdutoDeUmaGondola(char nomeDoArquivoDaGondola[], int numeroDaGondola)
{
	FILE *enderecoDeUmArquivo = NULL;
	int codigoDoProdutoASerRemovido;
	int fatorDeSaltoParaLocalizacaoDeUmProduto;
	struct Produto produtoASerRemovido;
	
	char confirmacaoDeRemocao = '\0';
	
	if(enderecoDeUmArquivo = (fopen(nomeDoArquivoDaGondola, "rb")))
	{
		fseek(enderecoDeUmArquivo, -((long)(sizeof(int))), SEEK_END);
		
		fread(&codigoDoProdutoASerRemovido, sizeof(int), 1, enderecoDeUmArquivo);
		
		fclose(enderecoDeUmArquivo);
		
		if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb+")))
		{
			fatorDeSaltoParaLocalizacaoDeUmProduto = buscaBinariaCodigoDeProduto(enderecoDeUmArquivo, calcularQuantidadeDeElementosNoArquivoProdutos(), 0, codigoDoProdutoASerRemovido);
			
			if(fatorDeSaltoParaLocalizacaoDeUmProduto != -1)
			{
				fseek(enderecoDeUmArquivo, (long)(fatorDeSaltoParaLocalizacaoDeUmProduto * (sizeof(struct Produto))), SEEK_SET);
				
				fread(&produtoASerRemovido, sizeof(struct Produto), 1, enderecoDeUmArquivo);
				
				fclose(enderecoDeUmArquivo);
				
				do
				{
					headGerenciadorDeGondolas();
					printf("                                                                             Gôndola %d\n\n", numeroDaGondola);
					
					mostrarDadosDoProduto(produtoASerRemovido);
					
					printf("\n\n\n\n                                                       Tem certeza que deseja remover este produto da gôndola?: \n\n");
					printf("                                                                            [1] - Confirmar\n");
					printf("                                                                            [0] - Cancelar\n");
					printf("                                                                                         ");
					fflush(stdin);
					confirmacaoDeRemocao = getchar();
				}while(confirmacaoDeRemocao != '0' && confirmacaoDeRemocao != '1');
				
				if(confirmacaoDeRemocao == '1')
				{
					if(0 == popFILE(nomeDoArquivoDaGondola))
					{
						if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb+")))
						{	
							fseek(enderecoDeUmArquivo, (long)(fatorDeSaltoParaLocalizacaoDeUmProduto * (sizeof(struct Produto))), SEEK_SET);
							
							produtoASerRemovido.quantidadeEmEstoque = (produtoASerRemovido.quantidadeEmEstoque + 1);
							
							fwrite(&produtoASerRemovido, sizeof(struct Produto), 1, enderecoDeUmArquivo);
							
							fclose(enderecoDeUmArquivo);
							
							printf("\n\n                                                                       Remoção concluída :) :) ");							
						}
						else
						{
							printf("\n\n                Erro ao abrir arquivo \"%s\" durante processo de atulização de estoque pós remoção de produto de uma gôndola. :( ", catalogoProdutos);
						}
					}
					else
					{
						printf("\n\n                                                  Erro durante procedimento de \"Pop\". Esta operação foi cancelada :( ");	
					}
				}
				else
				{
					printf("\n\n                                                                    Operação de remoção cancelada :( ");	
				}
				
				fflush(stdin);
				getchar();
			}
			else
			{
				fclose(enderecoDeUmArquivo);
				
				printf("\n\n                                           PRODUTO DE CÓDIGO %d NO TOPO DA GÔNDOLA NÃO ENCONTRADO ", codigoDoProdutoASerRemovido);	
					
				fflush(stdin);
				getchar();
			}
		}
		else
		{
			printf("\n\n                       Erro ao abrir arquivo \"%s\" durante processo de busca do elemento no topo da gôndola para remoção. :( ", catalogoProdutos);
			
			fflush(stdin);
			getchar();
		}	
	}
	else
	{
		printf("\n\n                           Erro ao abrir arquivo \"%s\" durante processo de recuperação do elemento no topo da gôndola. :( ", nomeDoArquivoDaGondola);	
		
		fflush(stdin);
		getchar();
	}
	
	return;
}

void headGerenciadorDeGondolas(void)
{
	system("CLS");
	printf("                                                                         GERENCIAR GÔNDOLAS\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	
	return;
}

void displayGondolas(char *todasAsGondolas[])
{
	int controlador = 0;
	FILE *enderecoDoArquivoGenerico = NULL;
	struct Produto produtoNoTopoDaGondola;
	int quantidadeDeItensNoCatalogoProdutos = calcularQuantidadeDeElementosNoArquivoProdutos();
	int codigoProduto;
	int fatorDeSaltoParaBuscaDeProduto;

	while(controlador < quantidadeDeGondolas)
	{
		if((controlador) % 3 == 0)
		{
			printf("\n  |-----------------------------------------------------|-----------------------------------------------------|-----------------------------------------------------|\n");
			printf("  | ");
		}
		
		printf("G%-3d| ", (controlador + 1));
			
		if(quantidadeDeItensNaPilhaFILE(todasAsGondolas[controlador]) == 0)
		{
			printf("%-46s", "GÔNDOLA VAZIA");
			
			printf("| ");
			
			controlador = (controlador + 1);
		}
		else
		{
			if(enderecoDoArquivoGenerico = (fopen(todasAsGondolas[controlador], "rb")))
			{
				fseek(enderecoDoArquivoGenerico, (long)(-(sizeof(int))), SEEK_END);
				
				fread(&codigoProduto, sizeof(fatorDeSaltoParaBuscaDeProduto), 1, enderecoDoArquivoGenerico);
				
				fclose(enderecoDoArquivoGenerico);			
			
				if(enderecoDoArquivoGenerico = (fopen(catalogoProdutos, "rb")))
				{
					fatorDeSaltoParaBuscaDeProduto = buscaBinariaCodigoDeProduto(enderecoDoArquivoGenerico, quantidadeDeItensNoCatalogoProdutos, 0, codigoProduto);
					
					if(fatorDeSaltoParaBuscaDeProduto != -1)
					{
						fseek(enderecoDoArquivoGenerico, (long)((sizeof(struct Produto)) * (fatorDeSaltoParaBuscaDeProduto)), SEEK_SET);
						
						fread(&produtoNoTopoDaGondola, sizeof(struct Produto), 1,enderecoDoArquivoGenerico);
						
						printf("%-38s R$%-5.2f", produtoNoTopoDaGondola.nomeProduto, produtoNoTopoDaGondola.preco);
					}
					else
					{
						printf("%-46s", "PRODUTO NÃO ENCONTRADO :(");
					}
					
					fclose(enderecoDoArquivoGenerico);
					
					printf("| ");
					
					controlador = (controlador + 1);
				}
				else
				{
					printf("\n\n                                                  Erro ao abrir arquivo \"%s\" durante display de gôndolas. :( ", catalogoProdutos);
					
					controlador = (quantidadeDeGondolas + 1);
				}
			}
			else
			{
				printf("\n\n                                                  Erro ao abrir arquivo \"%s\" durante display de gôndolas. :( ", todasAsGondolas[controlador]);
			
				controlador = (quantidadeDeGondolas + 1);
			}		
		}
	}
	
	if(controlador == quantidadeDeGondolas && (quantidadeDeGondolas % 3 != 0))
	{
		do
		{
			printf("                                           | ");
			
			controlador = (controlador + 1);
		}while(controlador % 3 != 0);
	}
	
	printf("\n");
	
	printf("  |-----------------------------------------------------|-----------------------------------------------------|-----------------------------------------------------|\n");
		
	printf("\n");	
	
	return;
}

void mostrarGondolaCompleta(char nomeDaGondola[])
{	
	FILE *enderecoDeUmArquivo = NULL;
	int quantidadeDeProdutosNoCatalogo;
	int quantidadeDeElementosASeremExibidos = quantidadeDeItensNaPilhaFILE(nomeDaGondola);
	int fatorDeSaltoParaLocalizacaoDeProduto;
	int codigoProduto;
	struct Produto produtoASerExibido;
	
	if(quantidadeDeElementosASeremExibidos > 0)
	{	
		printf("                                                                                             Quantidade de produtos nesta gôndola: %d", quantidadeDeElementosASeremExibidos);
	
		while(quantidadeDeElementosASeremExibidos > 0)
		{
			printf("\n\n");
			
			quantidadeDeElementosASeremExibidos = (quantidadeDeElementosASeremExibidos - 1);
			
			if(enderecoDeUmArquivo = (fopen(nomeDaGondola, "rb")))
			{
				fseek(enderecoDeUmArquivo, (quantidadeDeElementosASeremExibidos * (sizeof(int))), SEEK_SET);
				
				fread(&codigoProduto, sizeof(codigoProduto), 1, enderecoDeUmArquivo);
				
				fclose(enderecoDeUmArquivo);
				
				if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb")))
				{
					quantidadeDeProdutosNoCatalogo = calcularQuantidadeDeElementosNoArquivoProdutos();
					
					fatorDeSaltoParaLocalizacaoDeProduto = buscaBinariaCodigoDeProduto(enderecoDeUmArquivo, quantidadeDeProdutosNoCatalogo, 0, codigoProduto);
					
					if(fatorDeSaltoParaLocalizacaoDeProduto != -1)
					{
						fseek(enderecoDeUmArquivo, ((fatorDeSaltoParaLocalizacaoDeProduto) * (sizeof(struct Produto))), SEEK_SET);
						
						fread(&produtoASerExibido, (sizeof(struct Produto)), 1, enderecoDeUmArquivo);
						
						mostrarDadosDoProduto(produtoASerExibido);
					}
					else
					{
						printf("                                                                            PRODUTO NÃO ENCONTRADO ");	
						
						fflush(stdin);
						getchar();	
					}
					
					fclose(enderecoDeUmArquivo);
				}
				else
				{
					quantidadeDeElementosASeremExibidos = -1;
					
					printf("\n\n                                        Erro ao abrir arquivo \"%s\" durante procedimento de exibição de elementos. :( ", catalogoProdutos);	
					
					fflush(stdin);
					getchar();
				}
			}
			else
			{
				quantidadeDeElementosASeremExibidos = -1;
				
				printf("\n\n                                        Erro ao abrir arquivo \"%s\" durante procedimento de exibição de elementos. :( ", nomeDaGondola);	
				
				fflush(stdin);
				getchar();
			}	
		}
	}
	else
	{
		printf("                                                                            GÔNDOLA VAZIA ");	
	}
	
	return;
}

/*Modulo Compras*/

int comprar(void)
{
	setlocale(LC_ALL, "Portuguese");
	
	char *gondolas[quantidadeDeGondolas] = {"gondola1", "gondola2", "gondola3", "gondola4", "gondola5", "gondola6", "gondola7", "gondola8", "gondola9", "gondola10", "gondola 11", "gondola 12"};
	FILE *enderecoDeUmArquivo = NULL;
	struct Produto produtoEscolhido;
	int codigoDoProdutoEscolhido;
	int numeroDaGondola = -1;
	int indiceDaPosicaoDoElementoProcurado;
	char confirmacaoDeEscolha;
	char escolhaDeOperacaoSobreCarrinho;
	
	while(numeroDaGondola != 0)
	{
		do
		{
			headCompras();
			displayGondolas(gondolas);
			printf("                                                       Insira o número da gôndola onde o produto escolhido está, ou:\n\n");
			printf("                                                                     [-2] - Visualizar Carrinho de Compras\n");
			printf("                                                                     [ 0] - Voltar\n\n");
			printf("                                                                                                ");
			fflush(stdin);
		}while(!(scanf("%d", &numeroDaGondola) && (numeroDaGondola >= 0 && numeroDaGondola <= quantidadeDeGondolas) || (numeroDaGondola == -2)));
		
		if(numeroDaGondola != 0)
		{
			if(numeroDaGondola != -2)
			{
				if(!isEmptyFILE(gondolas[(numeroDaGondola - 1)]))
				{
					if(-1 != (codigoDoProdutoEscolhido = (topFILE(gondolas[(numeroDaGondola - 1)]))))
					{					
						if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb")))
						{
							indiceDaPosicaoDoElementoProcurado = buscaBinariaCodigoDeProduto(enderecoDeUmArquivo, calcularQuantidadeDeElementosNoArquivoProdutos(), 0, codigoDoProdutoEscolhido);
							
							if(indiceDaPosicaoDoElementoProcurado != -1)
							{
								fseek(enderecoDeUmArquivo, (long)((indiceDaPosicaoDoElementoProcurado) * (sizeof(struct Produto))), SEEK_SET);
							
								fread(&produtoEscolhido, (sizeof(struct Produto)), 1, enderecoDeUmArquivo);
								
								fclose(enderecoDeUmArquivo);
								
								do
								{
									headCompras();
									printf("\n\n");
									mostrarProdutoVisaoCliente(produtoEscolhido);
									printf("                                                                   Deseja inserir esse item no carrinho?\n\n");
									printf("                                                                            [1] - Confirmar\n");
									printf("                                                                            [0] - Cancelar cadastro\n\n");
									printf("                                                                                             ");
									fflush(stdin);
									confirmacaoDeEscolha = getchar();
								}while(confirmacaoDeEscolha != '1' && confirmacaoDeEscolha != '0');
								
								if(confirmacaoDeEscolha == '1')
								{
									pushFILE(carrinho, codigoDoProdutoEscolhido);
									
									popFILE(gondolas[(numeroDaGondola - 1)]);
								}	
							}	
							else
							{
								fclose(enderecoDeUmArquivo);
						
								printf("\n\n                                                                            PRODUTO NÃO ENCONTRADO NO CATÁLOGO");	
							
								fflush(stdin);
								getchar();
							}
						}
						else
						{
							printf("\n\n                                         Erro ao abrir arquivo \"%s\" durante busca de código de produto no processo de compras. :( ", catalogoProdutos);
						}	
					}
				}
				else
				{
					printf("\n\n                                                                           GÔNDOLA VAZIA :( ");
					
					fflush(stdin);
					getchar();
				}
			}
			else
			{
				do
				{
					headCompras();
					mostrarCarrinho(carrinho);
					
					printf("                                                                            [1] - Remover Item do carrinho\n");
					printf("                                                                            [0] - Voltar\n\n");
					printf("                                                                                            ");
					fflush(stdin);
					escolhaDeOperacaoSobreCarrinho = getchar();
				}while(!(escolhaDeOperacaoSobreCarrinho == '0' || (escolhaDeOperacaoSobreCarrinho == '1' && (quantidadeDeItensNaPilhaFILE(carrinho) > 0))));
				
				if(escolhaDeOperacaoSobreCarrinho == '1')
				{
					removerProdutoDoCarrinho();
				}
			}
		}	
	}
		
	return 0;
}

void removerDoCarrinhoEAtulizarEstoque(void)
{
	FILE *enderecoDeUmArquivo = NULL;
	int codigoDoProdutoASerRemovido;
	int fatorDeSaltoParaLocalizacaoDeUmProduto;
	struct Produto produtoASerRemovido;
	
	if(enderecoDeUmArquivo = (fopen(carrinho, "rb")))
	{
		fseek(enderecoDeUmArquivo, -((long)(sizeof(int))), SEEK_END);
		
		fread(&codigoDoProdutoASerRemovido, sizeof(int), 1, enderecoDeUmArquivo);
		
		fclose(enderecoDeUmArquivo);
		
		if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb+")))
		{
			fatorDeSaltoParaLocalizacaoDeUmProduto = buscaBinariaCodigoDeProduto(enderecoDeUmArquivo, calcularQuantidadeDeElementosNoArquivoProdutos(), 0, codigoDoProdutoASerRemovido);
			
			if(fatorDeSaltoParaLocalizacaoDeUmProduto != -1)
			{
				fseek(enderecoDeUmArquivo, (long)(fatorDeSaltoParaLocalizacaoDeUmProduto * (sizeof(struct Produto))), SEEK_SET);
				
				fread(&produtoASerRemovido, sizeof(struct Produto), 1, enderecoDeUmArquivo);
				
				fclose(enderecoDeUmArquivo);
				
				if(0 == popFILE(carrinho))
				{
					if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb+")))
					{	
						fseek(enderecoDeUmArquivo, (long)(fatorDeSaltoParaLocalizacaoDeUmProduto * (sizeof(struct Produto))), SEEK_SET);
							
						produtoASerRemovido.quantidadeEmEstoque = (produtoASerRemovido.quantidadeEmEstoque + 1);
						
						fwrite(&produtoASerRemovido, sizeof(struct Produto), 1, enderecoDeUmArquivo);
						
						fclose(enderecoDeUmArquivo);
							
						printf("\n\n                                                                       Remoção concluída :) :) ");							
					}
					else
					{
						printf("\n\n                Erro ao abrir arquivo \"%s\" durante processo de atulização de estoque pós remoção de produto do carrinho :( ", catalogoProdutos);
					}
				}
				else
				{
					printf("\n\n                                                  Erro durante procedimento de \"Pop\". Esta operação foi cancelada :( ");	
				}
			}
			else
			{
				fclose(enderecoDeUmArquivo);
				
				printf("\n\n                                           PRODUTO DE CÓDIGO %d NO TOPO DO CARRINHO NÃO ENCONTRADO ", codigoDoProdutoASerRemovido);	
					
				fflush(stdin);
				getchar();
			}
		}
		else
		{
			printf("\n\n                       Erro ao abrir arquivo \"%s\" durante processo de busca do elemento no topo do carrinho para remoção. :( ", catalogoProdutos);
			
			fflush(stdin);
			getchar();
		}	
	}
	else
	{
		printf("\n\n                           Erro ao abrir arquivo \"%s\" durante processo de recuperação do elemento no topo do carrinho. :( ", carrinho);	
		
		fflush(stdin);
		getchar();
	}
	
	return;
}


void removerProdutoDoCarrinho(void)
{
	FILE *enderecoDeUmArquivo = NULL;
	int codigoDoProdutoASerRemovido;
	int fatorDeSaltoParaLocalizacaoDeUmProduto;
	struct Produto produtoASerRemovido;
	
	char confirmacaoDeRemocao = '\0';
	
	if(enderecoDeUmArquivo = (fopen(carrinho, "rb")))
	{
		fseek(enderecoDeUmArquivo, -((long)(sizeof(int))), SEEK_END);
		
		fread(&codigoDoProdutoASerRemovido, sizeof(int), 1, enderecoDeUmArquivo);
		
		fclose(enderecoDeUmArquivo);
		
		if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb+")))
		{
			fatorDeSaltoParaLocalizacaoDeUmProduto = buscaBinariaCodigoDeProduto(enderecoDeUmArquivo, calcularQuantidadeDeElementosNoArquivoProdutos(), 0, codigoDoProdutoASerRemovido);
			
			if(fatorDeSaltoParaLocalizacaoDeUmProduto != -1)
			{
				fseek(enderecoDeUmArquivo, (long)(fatorDeSaltoParaLocalizacaoDeUmProduto * (sizeof(struct Produto))), SEEK_SET);
				
				fread(&produtoASerRemovido, sizeof(struct Produto), 1, enderecoDeUmArquivo);
				
				fclose(enderecoDeUmArquivo);
				
				do
				{
					headCompras();
					
					mostrarProdutoVisaoCliente(produtoASerRemovido);
					
					printf("\n\n\n\n                                                       Tem certeza que deseja remover este produto do carrinho?: \n\n");
					printf("                                                                            [1] - Confirmar\n");
					printf("                                                                            [0] - Cancelar\n");
					printf("                                                                                         ");
					fflush(stdin);
					confirmacaoDeRemocao = getchar();
				}while(confirmacaoDeRemocao != '0' && confirmacaoDeRemocao != '1');
				
				if(confirmacaoDeRemocao == '1')
				{
					if(0 == popFILE(carrinho))
					{
						if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb+")))
						{	
							fseek(enderecoDeUmArquivo, (long)(fatorDeSaltoParaLocalizacaoDeUmProduto * (sizeof(struct Produto))), SEEK_SET);
							
							produtoASerRemovido.quantidadeEmEstoque = (produtoASerRemovido.quantidadeEmEstoque + 1);
							
							fwrite(&produtoASerRemovido, sizeof(struct Produto), 1, enderecoDeUmArquivo);
							
							fclose(enderecoDeUmArquivo);
							
							printf("\n\n                                                                       Remoção concluída :) :) ");							
						}
						else
						{
							printf("\n\n                Erro ao abrir arquivo \"%s\" durante processo de atulização de estoque pós remoção de produto do carrinho :( ", catalogoProdutos);
						}
					}
					else
					{
						printf("\n\n                                                  Erro durante procedimento de \"Pop\". Esta operação foi cancelada :( ");	
					}
				}
				else
				{
					printf("\n\n                                                                    Operação de remoção cancelada :( ");	
				}
				
				fflush(stdin);
				getchar();
			}
			else
			{
				fclose(enderecoDeUmArquivo);
				
				printf("\n\n                                           PRODUTO DE CÓDIGO %d NO TOPO DO CARRINHO NÃO ENCONTRADO ", codigoDoProdutoASerRemovido);	
					
				fflush(stdin);
				getchar();
			}
		}
		else
		{
			printf("\n\n                       Erro ao abrir arquivo \"%s\" durante processo de busca do elemento no topo do carrinho para remoção. :( ", catalogoProdutos);
			
			fflush(stdin);
			getchar();
		}	
	}
	else
	{
		printf("\n\n                           Erro ao abrir arquivo \"%s\" durante processo de recuperação do elemento no topo do carrinho. :( ", carrinho);	
		
		fflush(stdin);
		getchar();
	}
	
	return;
}

void headCompras(void)
{
	system("CLS");
	printf("                                                                                COMPRAS\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                                                           Carrinho de Compras\n\n");
	
	return;
}

void mostrarProdutoVisaoCliente(struct Produto produtoASerExibido)
{
	printf("                                                                        Nome do produto: %s\n\n", produtoASerExibido.nomeProduto);
	printf("                                                                        Descrição: %s\n\n", produtoASerExibido.descricaoProduto);
	printf("                                                                        Peso: %.2fg\n\n", produtoASerExibido.peso);
	printf("                                                                        Preço: R$%.2f\n\n", produtoASerExibido.preco);
	
	return;
}

void mostrarCarrinho(char nomeArquivoCarrinho[])
{	
	FILE *enderecoDeUmArquivo = NULL;
	int quantidadeDeProdutosNoCatalogo;
	int quantidadeDeElementosASeremExibidos = quantidadeDeItensNaPilhaFILE(nomeArquivoCarrinho);
	int fatorDeSaltoParaLocalizacaoDeProduto;
	int codigoProduto;
	struct Produto produtoASerExibido;
	
	if(quantidadeDeElementosASeremExibidos > 0)
	{	
		printf("                                                                                             Quantidade de produtos: %d", quantidadeDeElementosASeremExibidos);
	
		while(quantidadeDeElementosASeremExibidos > 0)
		{
			printf("\n\n");
			
			quantidadeDeElementosASeremExibidos = (quantidadeDeElementosASeremExibidos - 1);
			
			if(enderecoDeUmArquivo = (fopen(nomeArquivoCarrinho, "rb")))
			{
				fseek(enderecoDeUmArquivo, (quantidadeDeElementosASeremExibidos * (sizeof(int))), SEEK_SET);
				
				fread(&codigoProduto, sizeof(codigoProduto), 1, enderecoDeUmArquivo);
				
				fclose(enderecoDeUmArquivo);
				
				if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb")))
				{
					quantidadeDeProdutosNoCatalogo = calcularQuantidadeDeElementosNoArquivoProdutos();
					
					fatorDeSaltoParaLocalizacaoDeProduto = buscaBinariaCodigoDeProduto(enderecoDeUmArquivo, quantidadeDeProdutosNoCatalogo, 0, codigoProduto);
					
					if(fatorDeSaltoParaLocalizacaoDeProduto != -1)
					{
						fseek(enderecoDeUmArquivo, ((fatorDeSaltoParaLocalizacaoDeProduto) * (sizeof(struct Produto))), SEEK_SET);
						
						fread(&produtoASerExibido, (sizeof(struct Produto)), 1, enderecoDeUmArquivo);
						
						mostrarProdutoVisaoCliente(produtoASerExibido);
					}
					else
					{
						printf("                                                                            PRODUTO NÃO ENCONTRADO ");	
						
						fflush(stdin);
						getchar();	
					}
					
					fclose(enderecoDeUmArquivo);
				}
				else
				{
					quantidadeDeElementosASeremExibidos = -1;
					
					printf("\n\n                                        Erro ao abrir arquivo \"%s\" durante procedimento de exibição de elementos. :( ", catalogoProdutos);	
					
					fflush(stdin);
					getchar();
				}
			}
			else
			{
				quantidadeDeElementosASeremExibidos = -1;
				
				printf("\n\n                                        Erro ao abrir arquivo \"%s\" durante procedimento de exibição de elementos. :( ", nomeArquivoCarrinho);	
				
				fflush(stdin);
				getchar();
			}	
		}
	}
	else
	{
		printf("\n\n                                                                        Carrinho !!!VAZIO!!! :'( \n\n");	
	}
	
	return;
}

void inicializarEsteira(struct Esteira *enderecoDaEsteira)
{
	enderecoDaEsteira->front = -1;
	
	enderecoDaEsteira->rear = -1;
}

void enqueueEsteira(struct Esteira *enderecoDaEsteira, struct Produto produtoASerInserido)
{	
	enderecoDaEsteira->front = enderecoDaEsteira->front + ( emptyEsteira(enderecoDaEsteira) );

	enderecoDaEsteira->rear = ( ( enderecoDaEsteira->rear + 1 ) % SIZA);
	
	enderecoDaEsteira->elementosNaEsteira[enderecoDaEsteira->rear] = produtoASerInserido;
	
	return; 
}

void dequeueEsteira(struct Esteira *enderecoDaEsteira)
{
	if(size(enderecoDaEsteira) == 1)
	{
		inicializarEsteira(enderecoDaEsteira);
	}
	else
	{
		enderecoDaEsteira->front = ( ( enderecoDaEsteira->front + 1 ) % SIZA );
	}
	
	return;
}

int size(struct Esteira *enderecoDaEsteira)
{
	int quantidadeDeElementos;
	int auxiliarParaCalculoDeModulo;
	
	if(emptyEsteira(enderecoDaEsteira))
	{
		quantidadeDeElementos = 0;
	}
	else
	{
		quantidadeDeElementos = ( ( moduloParaValoresNegativos( ( ( ( enderecoDaEsteira->rear - enderecoDaEsteira->front ) % SIZA ) ), SIZA) ) + 1 );
	}
	
	return quantidadeDeElementos;
}

int emptyEsteira(struct Esteira *enderecoDaEsteira)
{
	return (enderecoDaEsteira->rear == -1);
}

int moduloParaValoresNegativos(int resultadoRemainder, int valorDoModulo)
{
	while(resultadoRemainder < 0)
	{
		resultadoRemainder = resultadoRemainder + valorDoModulo;
	}
	
	return resultadoRemainder;
}

void displayEsteira(struct Esteira *enderecoDaEsteira)
{
	int quantidadeDeElementosJaEscritosNaTela;
	int quantidadeDeElementos;
	
	if(emptyEsteira(enderecoDaEsteira))
	{
		printf("                                                                            Esteira vazia\n\n");
	}
	else
	{
		quantidadeDeElementosJaEscritosNaTela = 0;
		quantidadeDeElementos = size(enderecoDaEsteira);
		
		while(quantidadeDeElementosJaEscritosNaTela < quantidadeDeElementos)
		{
			mostrarProdutoVisaoCliente(enderecoDaEsteira->elementosNaEsteira[(enderecoDaEsteira->front + quantidadeDeElementosJaEscritosNaTela) % SIZA]);
			
			printf("\n\n");
			
			quantidadeDeElementosJaEscritosNaTela = quantidadeDeElementosJaEscritosNaTela + 1;
		}
		
		printf("\n\n");
	}
	
	return;
}

void headCaixa(void)
{
	system("CLS");
	printf("                                                                                CAIXA\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	
	
	return;
}


void pegarEnderecoParaEntrega(char endereco[])
{
	system("CLS");
	printf("                                                                          SUPERMERCADO VAZIO\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                                                   Insira o endereço para entrega: ");
	fflush(stdin);
	gets(endereco);
	
	return;
}



void caixa(char nomeUsuario[], char prontuario[],char endereco[])
{
	FILE *enderecoDeUmArquivo = NULL;
	int fatorDeSaltoParaLocalizacaoDeProduto;
	int quantidadeDeProdutosNoCatalogo;
	int codigoProduto;
	struct Esteira esteiraDeProdutos;
	struct Produto produtoASerExibido;
	float subtotalDaCompra = 0.0;
	int quantidadeDeElementosNoCarrinho = quantidadeDeItensNaPilhaFILE(carrinho);
	char confirmarCompraDeProduto = '1';
	
	headCaixa();
	
	if(quantidadeDeElementosNoCarrinho > 0)
	{
		inicializarEsteira(&esteiraDeProdutos);
		
		while(quantidadeDeElementosNoCarrinho > 0 && confirmarCompraDeProduto != '0')
		{	
			if(enderecoDeUmArquivo = (fopen(carrinho, "rb")))
			{
				fseek(enderecoDeUmArquivo, (long)(-sizeof(int)), SEEK_END);
				
				fread(&codigoProduto, sizeof(codigoProduto), 1, enderecoDeUmArquivo);
				
				fclose(enderecoDeUmArquivo);
				
				if(enderecoDeUmArquivo = (fopen(catalogoProdutos, "rb")))
				{
					quantidadeDeProdutosNoCatalogo = calcularQuantidadeDeElementosNoArquivoProdutos();
					
					fatorDeSaltoParaLocalizacaoDeProduto = buscaBinariaCodigoDeProduto(enderecoDeUmArquivo, quantidadeDeProdutosNoCatalogo, 0, codigoProduto);
					
					if(fatorDeSaltoParaLocalizacaoDeProduto != -1)
					{
						fseek(enderecoDeUmArquivo, ((fatorDeSaltoParaLocalizacaoDeProduto) * (sizeof(struct Produto))), SEEK_SET);
						
						fread(&produtoASerExibido, (sizeof(struct Produto)), 1, enderecoDeUmArquivo);
					}
					else
					{
						printf("                                                                            PRODUTO NÃO ENCONTRADO ");	
						
						fflush(stdin);
						getchar();	
					}
					
					fclose(enderecoDeUmArquivo);
				}
				else
				{
					
					printf("\n\n                                        Erro ao abrir arquivo \"%s\" durante procedimento de exibição de elementos. :( ", catalogoProdutos);	
					
					fflush(stdin);
					getchar();
				}
			}
			else
			{
				printf("\n\n                                        Erro ao abrir arquivo \"%s\" durante procedimento de exibição de elementos. :( ", carrinho);	
				
				fflush(stdin);
				getchar();
			}
			
			do
			{
				headCaixa();
				printf("                                                                               ESTEIRA\n\n");
				displayEsteira(&esteiraDeProdutos);
				printf("                                                                                                         Subtotal: R$%.2f\n\n", subtotalDaCompra);
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n\n");
				
				mostrarProdutoVisaoCliente(produtoASerExibido);
				
				printf("                                                                      Inserir produto na esteira? \n\n");
				printf("                                                                          [1] - Confimar\n");
				printf("                                                                          [2] - Cancelar\n");
				printf("                                                                          [0] - Cancelar toda compra\n");
				printf("                                                                                          ");
				fflush(stdin);
				confirmarCompraDeProduto = getchar();
			}while(confirmarCompraDeProduto < '0' || confirmarCompraDeProduto > '2');
		
			if(confirmarCompraDeProduto != '0')
			{
				if(confirmarCompraDeProduto == '1')
				{
					enqueueEsteira(&esteiraDeProdutos, produtoASerExibido);
					
					popFILE(carrinho);				
					
					subtotalDaCompra = (subtotalDaCompra + produtoASerExibido.preco);
				}
				else
				{
					removerDoCarrinhoEAtulizarEstoque();
				}
			}
			else
			{
				while(size(&esteiraDeProdutos) > 0)
				{
					pushFILE(carrinho, esteiraDeProdutos.elementosNaEsteira[esteiraDeProdutos.front].codigoProduto);
					
					dequeueEsteira(&esteiraDeProdutos);			
				}
				
				while(quantidadeDeItensNaPilhaFILE(carrinho) > 0)
				{
					removerDoCarrinhoEAtulizarEstoque();
				}
				
				remove(carrinho);
				
				headCaixa();
				printf("\n\n                                                                           Compra cancelada :(\n\n");
				
				fflush(stdin);
				getchar();
			}
			
			quantidadeDeElementosNoCarrinho = quantidadeDeItensNaPilhaFILE(carrinho);
		}
		
		if(confirmarCompraDeProduto != '0' && ((size(&esteiraDeProdutos) > 0)))
		{
			do
			{
				headCaixa();
				printf("                                                                               ESTEIRA\n\n");
				displayEsteira(&esteiraDeProdutos);
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				
				printf("\n                                                                         Valor total: R$%.2f\n\n", subtotalDaCompra);
				
				printf("                                                                  Concluir compra e efetuar pagamento?\n\n");
				printf("                                                                           [1] - Confimar\n");
				printf("                                                                           [0] - Cancelar\n");
				printf("                                                                                          ");
				fflush(stdin);
				confirmarCompraDeProduto = getchar();
			}while(confirmarCompraDeProduto < '0' || confirmarCompraDeProduto > '1');
			
			if(confirmarCompraDeProduto == '1')
			{
				gerarNotaFiscal(nomeUsuario, prontuario, endereco, subtotalDaCompra, &esteiraDeProdutos);
			}
			else
			{
				while(size(&esteiraDeProdutos) > 0)
				{
					pushFILE(carrinho, esteiraDeProdutos.elementosNaEsteira[esteiraDeProdutos.front].codigoProduto);
					
					dequeueEsteira(&esteiraDeProdutos);			
				}
				
				while(quantidadeDeItensNaPilhaFILE(carrinho) > 0)
				{
					removerDoCarrinhoEAtulizarEstoque();
				}
				
				remove(carrinho);
				
				headCaixa();
				printf("\n\n                                                                           Compra cancelada :(\n\n");
				
				fflush(stdin);
				getchar();
			}	
		}
	}	
	else
	{
		printf("\n\n                                                                         Seu carrinho está vazio :( ");
		fflush(stdin);
		getchar();
	}
	
	return;
}

void gerarNotaFiscal(char nomeUsuario[], char prontuario[], char endereco[], float totalCompra, struct Esteira *produtosComprados)
{
	int controlador = 1;
	struct Produto produto;
	
	system("CLS");
	printf("                                                                          SUPERMERCADO VAZIO\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                                                              NOTA FISCAL ^-^\n\n");
	printf("                     Nome: %-40s        Prontuário: %-40s Endereço: %-60s\n\n\n\n", nomeUsuario, prontuario, endereco);
	printf("          Item                     Código                     Nome                            Descrição                             Peso(g)           Preço\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
	
	while(size(produtosComprados) > 0)
	{
		produto = produtosComprados->elementosNaEsteira[produtosComprados->front];
		
		printf("      %7d                 %10d               %-30s  %-44s %5.2f           R$%.2f\n\n", controlador++, produto.codigoProduto, produto.nomeProduto, produto.descricaoProduto, produto.peso, produto.preco);
		
		dequeueEsteira(produtosComprados);
	}
	
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
	
	fflush(stdin);
	getchar();
	
	return;
}
