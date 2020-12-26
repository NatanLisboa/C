#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

int MMC (int v[], int quantidade_elementos);

int main(){
	
	setlocale(LC_ALL,"Portuguese");
	
	char controlador;
	int n;
	int *vetor = NULL;
	int i;
	int j;
	int entradas_validas;
	
	do{
		do{
			system("CLS");
			printf("MMC de vários números\n\n");
			printf("Digite a quantidade de números para cálculo do MMC entre eles: ");
			fflush(stdin);
			if (((scanf("%d", &n)) && (n>0)))
				break;
			printf("\n\nEntrada inválida inserida. Pressione qualquer tecla para tentar novamente.");
			getch();
		} while (1);
		
		vetor = malloc(sizeof (int) * n);
		
		entradas_validas = 0;
		for (i=0; i<n; i++){
			
			system("CLS");
			printf("MMC de vários números\n\n");
		
			for (j=0; j<entradas_validas; j++){
				if (j==0)
					printf("Digite o %dº número (maior que 0): %d", j+1, vetor[j]);				
				else
					printf("\nDigite o %dº número (maior que 0): %d", j+1, vetor[j]);
			}	
				
			if (i == 0)
				printf("Digite o %dº número (maior que 0): ", i+1);
			else
				printf("\nDigite o %dº número (maior que 0): ", i+1);
			fflush(stdin);
			if (!(scanf("%d", &vetor[i]) && (vetor[i] > 0))){
				printf("\n\nEntrada inválida inserida. Pressione qualquer tecla para tentar novamente");
				getch();
				i--;
				continue;
			}
			
			entradas_validas++;

		}
			
		printf("\n\nMMC(");
		for (i=0; i<n; i++){
			if (i < n-1)
				printf("%d,", vetor[i]);
			else
				printf("%d) = ", vetor[i]);
		}
		printf("%d", MMC(vetor, n));
		getch();
		
		free (vetor);
		
		printf("\n\nDeseja fazer outra operação (S para \"sim\" e qualquer tecla para \"não\"): ");
		fflush(stdin);
		scanf("%c", &controlador);
		
	} while ((controlador == 'S') || (controlador == 's'));
	
	system("CLS");
	printf("\n\nObrigado por utilizar o programa :)");
	getch();
	return (0);
	
}

int MMC (int v[], int quantidade_elementos){
	
	int i;
	int divisor_primo=2;
	int numeros_iguais_a_um=0;
	int numeros_divisiveis;
	int divisores;
	int mmc=1;
	
	for (i = 0; i < quantidade_elementos; i++)
		if (v[i] == 1)
			numeros_iguais_a_um++;
	
	while (numeros_iguais_a_um < quantidade_elementos){
		
		numeros_divisiveis = 0;
		
		for (i = 0; i < quantidade_elementos; i++){
			if (v[i] % divisor_primo == 0){
				v[i] /= divisor_primo;
				numeros_divisiveis++;
			}
		}
		
		if (numeros_divisiveis > 0)
			mmc *= divisor_primo;
		else
			do{
				divisor_primo++;
				divisores=0;
				for (i=1; i<=divisor_primo; i++)
					if (divisor_primo % i == 0)
						divisores++;
			}while (divisores != 2);
		
		numeros_iguais_a_um=0;
		
		for (i = 0; i < quantidade_elementos; i++)
			if (v[i] == 1)
				numeros_iguais_a_um++;
	}
	
	return mmc;
	
}
