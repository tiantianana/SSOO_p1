#include <stdio.h>		/* Header file for system call printf */
#include <unistd.h>		/* Header file for system call gtcwd */
#include <sys/types.h>		/* Header file for system calls opendir, readdir y closedir */
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    DIR *dir;	
    char buf[PATH_MAX] = {0};	// Reservamos los Bytes de PATH_MAX con un  buffer
    struct dirent *obj;	// Objeto de tipo dirent

    if (argc == 1) {             // Si pasamos un solo parametro, es decir, el comando myls solo.
        getcwd(buf, PATH_MAX);   // Utilizamos la funcion getcwd, con los parametros buf y pathmax (4096), constante que determina el tamaño maximo que puede llegar a tener la ruta del directorio actual (esta funcion elimina el contenido del buffer que no se utilice).
        dir = opendir(buf);      // Abrimos el directorio actual. Almacenamos en dir el puntero del flujo del directorio.
    }
    
    else {
	    dir = opendir(argv[1]);
    }
   
    if(dir == NULL) {        // Si el directorio no existe, o no podemos abrirlo, devolvemos -1
        printf("Error: No se puede abrir el directorio (o no existe).\n");
        exit(-1);
    }

    while ((obj = readdir(dir)) != NULL) {	// Dejamos en obj el puntero del flujo (tipo dirent struct) del directorio
        printf("%s\n", obj->d_name);  //Casting. Mostramos el atributo 'nombre' del subdirectorio apuntado.
    }
    
    closedir(dir);
    return 0;
}
