#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int comprobar_valor_repetido(int* valores_generados, int tam, int new_val) {
	int ya_generado = 0;
	
	for (int i = 0; i < tam; i++){
		if (valores_generados[i] == new_val)
			ya_generado = 1;
	}
	
	return ya_generado;
}

int main(int argc, char* argv[])
{
	


	int x0 = 303;
	int a = 2061,
		c = 4231,
		m = 1e4;
	
	int xn;
	int* valores_gen;
	
	int num_gen = 0;
	int tipo_generador = 0;
	
	if ((valores_gen = (int *) malloc(2 * m * sizeof(int))) == NULL) {
		fputs("Error reservando memoria para valores generados por generador 1\n",stderr);
  	exit(1);
	}
	
	if (tipo_generador == 0){
		xn = (a*x0 + c) % m;
		
		while (comprobar_valor_repetido(valores_gen, num_gen, xn) == 0) {
			valores_gen[num_gen] = xn;
			num_gen++;
			
			xn = (a*xn + c) % m;
		}
	}

	else if (tipo_generador == 1){
		double x = (a*(double)x0 + c) / m;
		xn = (x-(int)x) * m;

		while (comprobar_valor_repetido(valores_gen, num_gen, xn) == 0) {
			valores_gen[num_gen] = xn;
			num_gen++;
			
			double x = (a*(double)xn + c) / m;
			xn = (x-(int)x) * m;
		}
	}

	else if (tipo_generador == 2){
		double x = (a*(double)x0 + c) / m;
		x = (x-(int)x) * m;
		xn = (int)(x + 0.5);

		while (comprobar_valor_repetido(valores_gen, num_gen, xn) == 0) {
			valores_gen[num_gen] = xn;
			num_gen++;
			
			double x = (a*(double)xn + c) / m;
			x = (x-(int)x) * m;
			xn = (int)(x + 0.5);
		}
	}

	else{
		xn = (int) fmod( (a*x0 + c), m );

		while (comprobar_valor_repetido(valores_gen, num_gen, xn) == 0) {
			valores_gen[num_gen] = xn;
			num_gen++;

			xn = (int) fmod( (a*xn + c), m );
		}
	}

	printf("Periodo del generador: %d\n", num_gen);
	
	free(valores_gen);
	
	return 0;
}