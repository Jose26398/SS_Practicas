#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <iostream>
#include <iomanip>


using namespace std;

float a11;
float a12;
float a21;
float a22;

float x;
float y;
float dt;

const int numeq = 2;
float t;
float tinic;
float tfin;

float f[2];
float oldestado[2];
float estado[2];

float incr;


void salida(float t){
	cout << std::fixed << std::setprecision(2) << "Depredadores: " << estado[1] << "\t\t"
											   << "Presas: " 	   << estado[0] << "\t\t"
											   << "Tiempo: " 	   << t << "\n";
}


void fijar_parametros(){
	dt = 0.1;

	tinic = 0;
	tfin = 100;
}


void derivacion(float est[numeq], float f[numeq], float tt){
	// específico para el modelo considerado
	f[0] = a11*est[0] - a12*est[0]*est[1];
	f[1] = a21*est[0]*est[1] - a22*est[1];
}


void one_step_runge_kutta(float inp[numeq], float out[numeq], float tt, float hh){
	float k[numeq][4];

	for (int i=0; i < numeq; i++)
		out[i] = inp[i]; 
	float time = tt;
	
	for (int j=0; j < 4; j++) {
		derivacion(out, f, time);
		for (int i=0; i < numeq; i++)
			k[i][j] = f[i];
		
		if (j < 2) {incr = hh/2;}
		else {incr = hh;}
		
		time = tt + incr;
		for (int i=0; i < numeq; i++)
			out[i] = inp[i] + k[i][j]*incr;
	}

	for (int i=0; i < numeq; i++)
		out[i] = inp[i] + hh/6  *  (k[i][0] + 2*k[i][1] + 2*k[i][2] + k[i][3]);
}


void one_step_euler(float inp[numeq], float out[numeq], float tt, float hh){
	derivacion(inp, f, tt);
	for (int i=0; i < numeq; i++)
		out[i] = inp[i] + hh*f[i];
}


void integracion(){
	do{
		salida(t);
		oldestado[0] = estado[0];
		oldestado[1] = estado[1];
		one-step-runge-kutta(oldestado, estado, t, dt); //sustituir por one-step-runge-kutta o por one-step-euler
		t += dt;
	} while(t < tfin);
}


int main(int argc, char *argv[]){
	if(argc == 7){
		sscanf(argv[1], "%f", &a11);
		sscanf(argv[2], "%f", &a12);
		sscanf(argv[3], "%f", &a21);
		sscanf(argv[4], "%f", &a22);
		sscanf(argv[5], "%f", &estado[1]);
		sscanf(argv[6], "%f", &estado[0]);
	}else{
		printf("\nArgumentos: <a11> <a12> <a21> <a22> <x_inicial> <y_inicial>");
		exit(1);
	}

	fijar_parametros();
	t = tinic;
	integracion();
}
