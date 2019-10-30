#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double uniforme() //Genera un número uniformemente distribuido en el
				  //intervalo [0,1) a partir de uno de los generadores
				  //disponibles en C. Lo utiliza el generador de demanda
{
	int t = rand();
	double f = ((double)RAND_MAX+1.0);
	return (double)t/f;
}

float* construye_prop_a(int n) //Construye la tabla de búsqueda de
							   //tamaño n para la distribución de
							   //la demanda del apartado (a).
{
	int i;
	float* temp;
	if ((temp = (float*) malloc(n*sizeof(float))) == NULL)
		{
		 fputs("Error reservando memoria para generador uniforme\n",stderr);
		 exit(1);
		}
	temp[0] = 1.0/n;
	for (i=1;i<n;i++)
		temp[i] = temp[i-1]+1.0/n;
	return temp;
}


float* construye_prop_b(int n) //Construye la tabla de búsqueda de
							   //tamaño n para la distribución de
							   //la demanda del apartado (b).
{
	int i, max;
	float* temp;
	if ((temp = (float*) malloc(n*sizeof(float))) == NULL)
		{
		 fputs("Error reservando memoria para generador proporcional\n",stderr);
		 exit(1);
		}
	max = (n/2)*(n+1);
	temp[0] = n*1.0/max;
	for (i=1;i<n;i++)
		temp[i] = temp[i-1]+(float)(n-i)/max;
	return temp;
}

float* construye_prop_c(int n) //Construye la tabla de búsqueda de
							   //tamaño n para la distribución de
							   //la demanda del apartado (c).
{
	int i, max;
	float* temp;
	if ((temp = (float*) malloc(n*sizeof(float))) == NULL)
		{
		 fputs("Error reservando memoria para generador triangular\n",stderr);
		 exit(1);
		}
	max = n*n/4;
	temp[0] = 0.0;
	for (i=1;i<(n/2);i++)
		temp[i] = temp[i-1]+(float)i/max;
	for (i=(n/2);i<n;i++)
		temp[i] = temp[i-1]+(float)(n-i)/max;
	return temp;
}

int genera_demanda(float* tabla,int tama) // Genera un valor de la 
									  	  // distribución de la demanda codificada en tabla, por el 
										  // método de tablas de búsqueda. 
										  // tama es el tamaño de la tabla, 100 en nuestro caso particular
{
	int i;
	double u = uniforme();
	i = 0;
	while((i<tama) && (u>=tabla[i]))
		i++;
	return i;
}



int main(int argc, char* argv[])
{
	int x = 10,
		y = 5,
		z = 3,
		veces = 10000,
		tabla = 'a';
	
	int demanda, ganancia, s_maxima;
	double ganancia_maxima = 0;
	float* tablabdemanda;

	srand(time(NULL)); //Inicializa el generador de numeros pseudoaleatorios

	if (tabla == 'a')		tablabdemanda = construye_prop_a(100);
	else if (tabla == 'b')	tablabdemanda = construye_prop_b(100);
	else					tablabdemanda = construye_prop_c(100);


	// Ejecutar modelo de Montecarlo
	for (int s = 1; s < 100; s++){
		double sum = 0.0, sum2 = 0.0;
		
		for (int i = 0; i < veces; i++){
			demanda = genera_demanda(tablabdemanda, 100);

			if (s > demanda){
				if (z < (s - demanda) * y)
        			ganancia = demanda * x - z;
        		else
        			ganancia = demanda * x - (s - demanda) * y;
        	}

			else
				ganancia = s*x;

			sum += ganancia;
			sum2 += ganancia*ganancia;
		}
		
		// Obtener ganancia media y desviacion tipica
		double ganancia_esperada = sum/veces,
			   desviacion = sqrt((sum2-veces*ganancia_esperada*ganancia_esperada)/(veces - 1));

		if (ganancia_esperada > ganancia_maxima){
			ganancia_maxima = ganancia_esperada;
			s_maxima = s;
		}

		printf("s: %d, ganancia: %f, desv: %f\n", s, ganancia_esperada, desviacion);
	}

	printf("\nValor de x: %d, valor de y: %d, valor de z: %d, numero de veces: %d, tipo de tabla: %c", x, y, z, veces, tabla);
	printf("\nValor maximo de ganancia: %f || s --> %d\n", ganancia_maxima, s_maxima);
	return 0;
}