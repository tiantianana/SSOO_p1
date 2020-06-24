#include <stdio.h>		/* Header file for printf */
#include <sys/types.h>		/* Header file for system call  open */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>		/* Header file for system calls read, write y close */
#include <stdlib.h>
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	/*If the number of arguments is less than two (argv[0] -> program, argv[|] -> file to be shown) we print the error and return -1*/

	if(argc < 2)
	{
		printf("Not enough arguments\n");
		return -1;
	}

	int id_fichero;
        char buff[BUFFER_SIZE] = {0}; // Reservamos 1024 Bytes de memoria para el buffer, que inicializamos a 0
	ssize_t size;

	id_fichero = open(argv[1], O_RDONLY);	/*Abrimos el fichero pasado en el argumento 1 con la opcion de apertura
					       	'read only' (solo lectura). El descriptor del fichero se guarda en id_fichero: */
	if(id_fichero < 0){	/* Si el descriptor del fichero es menor que cero (-1), implica que ha habido un
				   error en su apertura por lo que imprimimos un mensaje de error y salimos del programa: */
		perror("open");
		exit(-1);
	}

	size = read(id_fichero, buff, BUFFER_SIZE); 	/* Leemos el fichero, dejando la información leida en el espacio reservado
							   del buffer y el numero de bytes leidos en la variable 'size'*/

	write(STDOUT_FILENO, buff, size);	/* Escribimos en la constante STDOUT_FILENO la parte leida del fichero (que se
						   corresponde con los 'size' bytes del buffer 'buf'). 
						 * Esta proporciona el flujo de salida estandar (imprime por pantalla los bytes 
						 * que acabamos de leer). */
	
	while(size == BUFFER_SIZE){ // Si la parte leida ocupa todo el buffer, aun quedan bytes por leer 
                size = read(id_fichero, buff, BUFFER_SIZE); /* La operacion de lectura comienza en el ultimo desplazamiento 
							       del fichero, el cual aumenta segun los bytes leidos. */
                write(STDOUT_FILENO, buff, size); // Sobreescribimos en la constante de salida estandar cada parte que leemos del fichero
                 }
	
	close(id_fichero);
	return 0;
}

