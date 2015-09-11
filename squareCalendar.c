/*
 * squareCalendar v0.01
 * Copyleft - 2015  Javier Dominguez Gomez
 * Written by Javier Dominguez Gomez <jdg@member.fsf.org>
 * GnuPG Key: 6ECD1616
 * Madrid, Spain
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Compilation:   gcc -Wall -c -MMD -MP -MF"squareCalendar.d" -MT"squareCalendar.d" -o "squareCalendar.o" squareCalendar.c
 *                gcc -o squareCalendar squareCalendar.o
 *
 * Usage:         ./squareCalendar
 *
 */

#include <stdio.h>
#include <stdlib.h>

void trimestre(int,int,int);
void semana (int,int,int,int,int,int);
void cabecera(int,int,int);
int calcularDiasMes(int,int);
int zeller(int,int);
void puntos(int,int);

void puntos(int p,int max){
	if(p == max){
		fprintf(stdout,"|  . ");
	} else {
		fprintf(stdout," . ");
	}
}

int zeller(int ano, int mes){
	int a = (14-mes)/12;
	int y = ano-a;
	int m = mes+12*a-2;
	int dia = 1, d;
	d = (dia+y+y/4-y/100+y/400+(31*m)/12)%7;
	return d;
}

int calcularDiasMes(int ano, int mes){
	int dias;
	if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
		dias=31;
	} else if(mes == 2){
		if((ano % 4 == 0) && (ano % 100 != 0 || ano % 400 == 0)){
			dias=29;
		} else {
			dias=28;
		}
	} else {
		dias=30;
	}
	return dias;
}

void cabecera(int ano,int min,int max){
	char *nombreMes, *linea = "======================", *diasSemana = "LU MA MI JU VI | SA DO";

	fprintf(stdout,"\n");
	for(int mes = min; mes <= max; mes++){
		switch(mes){
			case 1: nombreMes = "Enero";break;
			case 2: nombreMes = "Febrero";break;
			case 3: nombreMes = "Marzo";break;
			case 4: nombreMes = "Abril";break;
			case 5: nombreMes = "Mayo";break;
			case 6: nombreMes = "Junio";break;
			case 7: nombreMes = "Julio";break;
			case 8: nombreMes = "Agosto";break;
			case 9: nombreMes = "Septiembre";break;
			case 10: nombreMes = "Octubre";break;
			case 11: nombreMes = "Nomviembre";break;
			case 12: nombreMes = "Diciembre";break;
		}
		fprintf(stdout,"%-11s%11d   ",nombreMes,ano);

		if(mes % 3 == 0){
			fprintf(stdout,"\n");
		}
	}
	fprintf(stdout,"%s   %s   %s\n",linea,linea,linea);
	fprintf(stdout,"%s   %s   %s\n",diasSemana,diasSemana,diasSemana);
	fprintf(stdout,"%s   %s   %s\n",linea,linea,linea);
}

void semana(int numSemana,int min,int max,int ano,int mesMin,int mesMax){
	int z;

	for(int mes = mesMin; mes <= mesMax; mes++){
		if(zeller(ano,mes) == 0){
			z = 6;
		} else {
			z = zeller(ano,mes)-1;
		}

		if(numSemana == 1){
			for(int p = 0;p<z;p++){
				puntos(p,5);
			}
		}

		int diasMes = calcularDiasMes(ano,mes);

		for(int dia = 1;dia <=diasMes;dia++){
			z++;
			if(z <= max && z >= min){
				if(z == 6 || z == 13 || z == 20 || z == 27 || z == 34){
					fprintf(stdout,"| %2d ",dia);
				} else if(z == 36 && (mes == 2 || mes == 5 || mes == 8 || mes == 11)){
					fprintf(stdout,"%-23s%2d "," ",dia);
				} else if(z == 36 && (mes == 3 || mes == 6 || mes == 9 || mes == 12)){
					fprintf(stdout,"%-46s%2d "," ",dia);
				} else {
					fprintf(stdout,"%2d ",dia);
				}
			}
		}

		if((z == 29 || z == 30 || z == 31 || z == 32 || z == 33 || z == 34) && numSemana == 5){
			for(int p=z;p<=34;p++){
				puntos(p,33);
			}
		} else if((z == 36 || z == 37) && numSemana == 6){
			for(int p=z;p<=41;p++){
				puntos(p,40);
			}
		}

		if(mes % 3 == 0){
			fprintf(stdout,"\n");
		} else {
			fprintf(stdout,"  ");
		}
	}
}

void trimestre(int ano,int mesMin,int mesMax){
	cabecera(ano,mesMin,mesMax);
	semana(1,1,7,ano,mesMin,mesMax);
	semana(2,8,14,ano,mesMin,mesMax);
	semana(3,15,21,ano,mesMin,mesMax);
	semana(4,22,28,ano,mesMin,mesMax);
	semana(5,29,35,ano,mesMin,mesMax);
	semana(6,36,42,ano,mesMin,mesMax);
}

int main(void) {
	system("clear");
	fprintf(stdout,"Year (1..3000)? ");
	scanf("%d", &ano);

	if(ano >= 1 && ano <= 3000){
		trimestre(ano,1,3);
		trimestre(ano,4,6);
		trimestre(ano,7,9);
		trimestre(ano,10,12);
	} else {
		fprintf(stderr,"Error: wrong year.\n");
	}
}
