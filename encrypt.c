/*
 * Encrypt v0.01
 * Copyleft - 2014  Javier Dominguez Gomez
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
 * Compilation:   gcc -Wall -c -MMD -MP -MF"encrypt.d" -MT"encrypt.d" -o "encrypt.o" encrypt.c
 *                gcc -o encrypt encrypt.o -lcrypt
 *
 * Usage:         ./encrypt
 *
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <crypt.h>

int main(void) {
	unsigned long seed[2];
	char salt[] = "$1$3xe26505";
	const char * const seedchars = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char *password;
	int i;

	seed[0] = time(NULL);
	seed[1] = getpid() ^ (seed[0] >> 14 & 0x30000);

	for (i = 0; i < 8; i++) {
		salt[3 + i] = seedchars[(seed[i / 5] >> (i % 5) * 6) & 0x3f];
	}

	password = crypt(getpass("String to encrypt: "), salt);

	puts(password);
	return 0;
}
