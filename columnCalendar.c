/*
 * Calendar v0.01
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
 * Compilation:   gcc -Wall -c -MMD -MP -MF"calendar.d" -MT"calendar.d" -o "calendar.o" calendar.c
 *                gcc -o calendar calendar.o
 *
 * Usage:         ./calendar
 *
 */

#include <stdio.h>

void calendar(int);
void head(int,int);
int calcDaysMonth(int,int);
int zeller(int,int);
void dots(int,int);

void dots(int p,int max){
	if(p == max){
		fprintf(stdout,"|  . ");
	} else {
		fprintf(stdout," . ");
	}
}

int zeller(int year, int month){
	int a = (14-month)/12;
	int y = year-a;
	int m = month+12*a-2;
	int day = 1, d;
	d = (day+y+y/4-y/100+y/400+(31*m)/12)%7;
	return d;
}

int calcDaysMonth(int year, int month){
	int days;
	if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
		days=31;
	} else if(month == 2){
		if((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0)){
			days=29;
		} else {
			days=28;
		}
	} else {
		days=30;
	}
	return days;
}

void head(int year, int month){
	char *monthName,*line = "======================";

	switch(month){
	case 1: monthName = "January";break;
	case 2: monthName = "February";break;
	case 3: monthName = "March ";break;
	case 4: monthName = "April";break;
	case 5: monthName = "May";break;
	case 6: monthName = "June";break;
	case 7: monthName = "July";break;
	case 8: monthName = "August";break;
	case 9: monthName = "September";break;
	case 10: monthName = "October";break;
	case 11: monthName = "November";break;
	case 12: monthName = "December";break;
	}
	fprintf(stdout,"\n%-11s%11d\n%s\nMO TU WE TH FR | SA SU\n%s\n",monthName,year,line,line);
}

void calendar(int year){
	for(int month = 1; month <= 12; month++){
		int z;

		head(year,month);

		if(zeller(year,month) == 0){
			z = 6;
		} else {
			z = zeller(year,month)-1;
		}

		for(int p = 0;p<z;p++){
			dots(p,5);
		}

		int monthDays = calcDaysMonth(year,month);

		for(int day = 1;day <=monthDays;day++){
			z++;

			if(z == 6 || z == 13 || z == 20 || z == 27 || z == 34){
				fprintf(stdout,"| %2d ",day);
			} else {
				fprintf(stdout,"%2d ",day);
			}

			if(z % 7 == 0){
				fprintf(stdout,"\n");
			}
		}
		if(z == 29 || z == 30 || z == 31 || z == 32 || z == 33 || z == 34){
			for(int p=z;p<=34;p++){
				dots(p,33);
			}
		}else if(z == 36 || z == 37){
			for(int p=z;p<=41;p++){
				dots(p,40);
			}
		}
		fprintf(stdout,"\n");
	}
}

int main(void) {
	int year;

	fprintf(stdout,"Year: ");
	scanf("%d", &year);
	calendar(year);
}
