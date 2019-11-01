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


struct ordenado{
	float acum;
	int pos;
};


ordenado* construye_prop_c_ordenado(int n) //Construye la tabla de búsqueda de
							   //tamaño n para la distribución de
							   //la demanda del apartado (c).
{
	int i, max;
	ordenado* temp;
	if ((temp = (ordenado*) malloc(n*sizeof(ordenado))) == NULL)
		{
		 fputs("Error reservando memoria para generador triangular\n",stderr);
		 exit(1);
		}

	// Al ser funcion triangular, los valores 49-51, 48-52, ... ,tienen las mismas
	// probabilidades, asi que solo tendremos que sumarselos a la acumulada uno a uno.
	max = n*n/4;
	int j = 1;
	temp[0].acum = (float)(n/2)/max;
	temp[0].pos = n/2;

	for (i=(n/2)-1; i>=0; i--){
		temp[j].acum = temp[j-1].acum+(float)i/max;
		temp[j].pos = i;

		temp[j+1].acum = temp[j].acum+(float)(n-i)/max;
		temp[j+1].pos = n-i;
		
		j+=2;
	}

	return temp;
}


int genera_demanda_ordenado(ordenado* tabla,int tama)
{
	int i;
	double u = uniforme();
	i = 0;
	
	while((i<tama) && (u>=tabla[i].acum))
		i++;
	
	return tabla[i].pos;
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


int genera_demanda_binaria(float* tabla,int tama) {
	int i;
	double u = uniforme();
	
	int a = 0, b = tama - 1;
	bool encontrado = false;
	
	while (a <= b && !encontrado) {
		i = (int) (a + b)/2;
		
		if (u < tabla[i]) {
			if (i == 0)
				encontrado = true;
			else if (tabla[i - 1] <= u)
				encontrado = true;
			else
				b = i - 1;
		}
		else
			a = i + 1;
	}
	return i;
}

int genera_demanda_a_mejorado(float* tabla, int tama){
	double u = uniforme();
	return (int)(u*100);
}



int main(int argc, char* argv[])
{
	int x = 10,
		y = 5,
		veces = 1000000,
		mejora = 3;

	char tabla = 'a';
	
	int demanda, ganancia, s_maxima;
	float* tablabdemanda;
	ordenado* tablabdemanda_ord;

	srand(time(NULL)); //Inicializa el generador de numeros pseudoaleatorios

	if (tabla == 'a')		tablabdemanda = construye_prop_a(100);
	else if (tabla == 'b')	tablabdemanda = construye_prop_b(100);
	else					tablabdemanda = construye_prop_c(100);


	clock_t ini = clock();
	for (int i = 0; i < veces; ++i)
		demanda = genera_demanda(tablabdemanda, 100);
	clock_t fin = clock();


	if (mejora == 1)	tablabdemanda_ord = construye_prop_c_ordenado(100);
	clock_t ini_mej = clock();
	
	for (int i = 0; i < veces; i++){
		if (mejora == 1)
			demanda = genera_demanda_ordenado(tablabdemanda_ord, 100);
		else if (mejora == 2)
			demanda = genera_demanda_binaria(tablabdemanda, 100);
		else if (mejora == 3)
			demanda = genera_demanda_a_mejorado(tablabdemanda, 100);
		else{
			printf("No existe esa mejora\n");
			exit(0);
		}
	}

	clock_t fin_mej = clock();
	double tiempo = (double)(fin-ini) / (double)CLOCKS_PER_SEC;
	double tiempo_mej = (double)(fin_mej-ini_mej) / (double)CLOCKS_PER_SEC;

	printf("\nTiempo en generar demanda sin mejora: %g segundos\n", tiempo);
	printf("Mejora %d aplicada para la tabla %c\n", mejora, tabla);
	printf("Tiempo en generar demanda con mejora: %g segundos\n\n", tiempo_mej);
	return 0;
}