#include <stdio.h>
#include "WL_lib.h"

int main()
{

    MyFile mi_archivo;

    open_file(&mi_archivo, "code.c", READ);
    if (error_open_file(mi_archivo))
    {
        printf("Error al abrir el archivo code.c\n");
        return 1;
    }
    else if (error_mode_file(mi_archivo))
    {
        printf("Error al abrir el archivo, el modo no es adecuado.\n");
        return 1;
    }

    printf("size del archivo: %d\n", get_size_file);

    // Leer el archivo
    read_file(&mi_archivo);
    if (error_read_file(mi_archivo))
    {
        printf("Error al leer el archivo %d\n", mi_archivo.data);
    }
    else
    {
        mi_archivo.data[get_size_file(mi_archivo)] = 0x0;
        printf("Datos leidos: \n%s\n", get_data_file(mi_archivo));
    }

    MyFile mi_archivo_cpy;
    open_file(&mi_archivo_cpy, "code1.c", READ | WRITE);
    if (error_open_file(mi_archivo))
    {
        printf("Error al abrir el archivo code1.c\n");
        return 1;
    }
    mi_archivo_cpy.size = get_size_file(mi_archivo);
    printf("size del archivo: %d\n", get_size_file(mi_archivo_cpy));

    write_file(&mi_archivo_cpy, get_data_file(mi_archivo));
    if (error_read_file(mi_archivo_cpy))
    {
        printf("Error al escribir el archivo\n");
    }
    printf("size del archivo: %d\n", get_size_file(mi_archivo_cpy));

    puts("Archivo abierto");
    close_file(&mi_archivo);
    close_file(&mi_archivo_cpy);
    return 0;
}
