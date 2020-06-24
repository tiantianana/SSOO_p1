#include <stdio.h>	/*Header file for system call printf*/
#include <sys/types.h>	/*Header file for system call fstat*/
#include <sys/stat.h>
#include <fcntl.h>	/*Header file for system call fcntl*/
#include <dirent.h> 	/*Header file for system call opendir, closedir,readdir...*/
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	DIR *dir;		// Creamos una variable directorio 
	char buf[PATH_MAX] = {0};// Creamos una variable de tipo char que es el buffer, que reserva un espacio de 4096 bytes en la memoria 
	struct dirent *obj;	// Variable tipo struc dirent, almacena caracteristicas de los subdirectorios/ficheros
	int id_fichero;		// Va almacenando el descriptor de cada fichero abierto en el while
	off_t size;		// Almacena el tamaño del fichero, devuelto por lseek


	if (argc > 1){ 	// Si el numero de argumentos es mayor que uno, te devuelve un error
                perror("no se encuentra en el directorio actual");
                exit(-1);
	}

	// Si nos pasan un solo argumento, obtenemos el directorio actual con la funcion getcwd

	getcwd(buf, PATH_MAX);	// le pasamos el buffer y el tamaño de este
	dir = opendir(buf);	// Abrimos el directorio
	
	while((obj=readdir(dir)) != NULL) {	// En cada iteracion del while, obj almacena la informacion de la siguiente entrada del 'stream' del directorio actual. 
		if(obj->d_type==DT_REG) {	// Solo abrimos los ficheros de tipo regular
			id_fichero = open(obj->d_name, O_RDONLY);	// Abrimos el fichero dejando su descriptor en id_fichero
			size = lseek(id_fichero, 0, SEEK_END);	// Desplazamos hasta el final el puntero de la descripcion del fichero, sin offset, 
								// de modo que lseek devuelve los bytes que hay desde el inicio del fichero 
								// hasta el puntero (el tamaño total del fichero)
			printf("%s\t%ld\n", obj->d_name, size);	// Imprimimos el nombre (campo d_name de la estructura dirent) y el tamaño obtenido con lseek.
			close(id_fichero);	//Cerramos el fichero.
		}	
	}

	closedir(dir);	//cerramos el directorio (actual)

	return 0;
}
