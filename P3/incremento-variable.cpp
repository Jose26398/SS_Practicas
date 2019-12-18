#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <iostream>
#include <time.h>

using namespace std;

#define libre 0
#define ocupado 1



float generallegada(float tlleg){
	float u = random(); // o también rand() en lugar de random()
	u = (u/(RAND_MAX+1.0)); //RAND_MAX es una constante del sistema
	return (-tlleg*log(1-u));
}



float generaservicio(float tserv){
	float u = random(); // o también rand() en lugar de random()
	u = (u/(RAND_MAX+1.0)); //RAND_MAX es una constante del sistema
	return (-tserv*log(1-u));
}


int main(int argc, char *argv[])
{
	float total_a_atender;
	float tlleg;
	float tserv;

	if (argc != 4)
	{
		printf("\n\nFormato Argumentos -> <numero_servidores total_a_atender tlleg tserv>\n\n");
		exit(1);
	}
	sscanf(argv[1],"%f",&total_a_atender);
	sscanf(argv[2],"%f",&tlleg);
	sscanf(argv[3],"%f",&tserv);

	// for (int i = 0; i < 150; ++i){	

	int infinito = 10e6; 	//tiempo en que ocurren cosas que sabemos no pueden ocurrir
	int atendidos = 0; 	//al principio no hay nadie ya atendido
	float inicio_ocio = 0; 	//marcará el momento en que el servidor empieza a estar ocioso
	float acum_cola = 0;	//acumulador de número de clientes en cola por el tiempo en que están en
	                	//dicha cola. El cliente que está siendo atendido NO está en cola
	float reloj = 0; 	//marca el valor del tiempo simulado, inicialmente cero
	int servidor = libre;	//inicialmente el servidor no está atendiendo a nadie
	int encola = 0;		//no hay nadie en cola todavía
	float tiempo_llegada = reloj + generallegada(tlleg); 	//en ese tiempo llegará el primer cliente
	float tiempo_salida = infinito;
	float tultsuc = 0;
	float ocio = 0;


	clock_t ini = clock();
	while (atendidos < total_a_atender)
	{
		reloj = min(tiempo_llegada,tiempo_salida); //una función que calcula el mı́nimo
		if (reloj == tiempo_llegada)//si estamos en el instante en que llega alguien
		{
			tiempo_llegada = reloj + generallegada(tlleg);  //determinamos cuando llegará el siguiente cliente
			if (servidor == libre) //si el servidor está ocioso
			{ 
				servidor = ocupado; //deja de estarlo
				tiempo_salida = reloj + generaservicio(tserv);  //determinamos cuando saldrá ese cliente que acaba de llegar
				ocio += reloj - inicio_ocio; //acumulamos el ocio hasta este momento
			}
			else //el servidor está ocupado
			{
				acum_cola += (reloj - tultsuc) * encola; //acumulamos el número de clientes en cola por el tiempo en que han estado en cola
				tultsuc = reloj; //para saber en qué momento cambió el tamaño de la cola, en este caso aumentó en uno más
				encola++;  //hay un cliente más en cola
			}
		}

		if (reloj == tiempo_salida) //si estamos en el instante en que se va alguien
		{
			atendidos++; //se ha atendido a un cliente más
			if (encola > 0) //si quedan clientes en cola
			{
				acum_cola += (reloj - tultsuc) * encola; // acumulamos el número de clientes en cola por el tiempo en que han estado en cola
				tultsuc = reloj; //para saber en qué momento cambió el tamaño de la cola, en este caso disminuyó en uno
				encola--; //hay un cliente menos en cola
				tiempo_salida = reloj + generaservicio(tserv);  //determinamos cuando saldrá ese cliente que acaba de entrar
			}
			else //no quedan clientes en cola
			{
				servidor = libre; //el servidor se queda ocioso por falta de clientes
				inicio_ocio = reloj; //marcamos cuando empieza a estar ocioso
				tiempo_salida = infinito; //nadie puede salir puesto que nadie hay
			}
		}
	}
	clock_t fin = clock();
	
	float porcent_ocio = ocio*100/reloj; //calculamos el porcentaje de tiempo de ocio del servidor
	printf("Porcentaje de tiempo ocioso: %f\n", porcent_ocio);
	
	float media_encola = acum_cola/reloj; //calculamos el número medio de clientes en cola
	printf("Número medio de clientes en cola: %f\n", media_encola);
	
	double tiempo = (double)(fin-ini) / (double)CLOCKS_PER_SEC;
	printf("Tiempo de ejecución: %g segundos\n", tiempo);
// }

}