/*
 *	Licencia Apache, Versión 2.0 con Modificación
 *	
 *	Copyright 2023 Desmon (David)
 *	
 *	Se concede permiso, de forma gratuita, a cualquier persona que obtenga una copia de 
 *	este software y archivos de documentación asociados (el "Software"), para tratar el 
 *	Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, 
 *	modificación, fusión, publicación, distribución, sublicencia y/o venta de copias del 
 *	Software, y para permitir a las personas a quienes se les proporcione el Software 
 *	hacer lo mismo, sujeto a las siguientes condiciones:
 *	
 *	El anterior aviso de copyright y este aviso de permiso se incluirán en todas las 
 *	copias o partes sustanciales del Software.
 *	
 *	EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O 
 *	IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD 
 *	PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN. EN NINGÚN CASO LOS TITULARES DEL 
 *	COPYRIGHT O LOS TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGÚN 
 *	RECLAMO, DAÑO U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE 
 *	OTRA MANERA, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTRO TIPO
 *	DE ACCIONES EN EL SOFTWARE.
 *	
 *	Además, cualquier modificación realizada por terceros se considerará propiedad del 
 *	titular original de los derechos de autor. Los titulares de derechos de autor 
 *	originales no se responsabilizan de las modificaciones realizadas por terceros.
 *	
 *	Queda explícitamente establecido que no es obligatorio especificar ni notificar los 
 *	cambios realizados entre versiones, ni revelar porciones específicas de código 
 *	modificado.
 */


#include "base.h"

#ifdef _WIN32
#ifndef _ExceptionHandler_WIN_
#define _ExceptionHandler_WIN_
LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS *ExceptionInfo) {
    printf("Se ha producido una excepción (código %lx) en la dirección %p\n",
        ExceptionInfo->ExceptionRecord->ExceptionCode,
        ExceptionInfo->ExceptionRecord->ExceptionAddress);
    return EXCEPTION_EXECUTE_HANDLER; // Manejar la excepción
}
#endif
#endif

//int main(int argc, char *argv[])
int main()
{
	
	#ifdef _WIN32
	#ifndef _ExceptionHandler_WIN_
	#define _ExceptionHandler_WIN_
	SetUnhandledExceptionFilter(ExceptionHandler);
	#endif
	#endif

	/*NewObject_String_c(source_code);
	MyFile mi_archivo1;
    open_file(&mi_archivo1, "codigo.bh", READ);
    if (error_open_file(mi_archivo1)) {
        printf("Error al abrir el archivo code.c\n");
        return 1;
    } else if (error_mode_file(mi_archivo1))
    {
        printf("Error al abrir el archivo, el modo no es adecuado.\n");
        return 1;
    }
    //printf("size del archivo: %d\n", mi_archivo1.size);

    // Leer el archivo
    read_file(&mi_archivo1);
    if (error_read_file(mi_archivo1)){
        printf("Error al leer el archivo %d\n", mi_archivo1.data);
    } else {
        mi_archivo1.data [get_size_file(mi_archivo1)] = 0x0;
        //printf("Datos leidos: \n%s\n", get_data_file(mi_archivo1));
		source_code.setStr(&source_code, get_data_file(mi_archivo1), get_size_file(mi_archivo1));
    }

	compile(mi_archivo1.data, get_size_file(mi_archivo1));

	close_file(&mi_archivo1);
	source_code.printStr(&source_code, "\n");*/
	
	compile_file("codigo.bh");

	

	// (source_code.searchChar(&source_code, '\n' ) == 0 && source_code.str[0] != 0) ? puts("final file") :  puts("not final file");

	/*for ( unsigned char *source_code_position = source_code.str; source_code_position < source_code.str+source_code.size; source_code_position++){
		// hacer una copia del puntero y recorrer el archivo caracter a caracter hasta el final
		if (source_code.searchChar(&source_code, '\n' ) == 0 && source_code.str[0] != 0){
			// esta es la ultima linea del archivo
		} else {}*/
		/*if        (source_code.searchChar(source_code_position, '#' ) == 0 && source_code_position == '#'){

		} else if (source_code.searchChar(source_code_position, '%' ) == 0 && source_code_position == '%'){
			
		}
	}*/

	/*NewObject_String_c(my_string);
	my_string.setStr(&my_string, "Hola mundo", 0);
	printf("mi str: ");
	my_string.printStr(&my_string, "\n");
	printf("posicion del primer espacio: %llu\n", my_string.searchChar(&my_string, ' ') );*/


	/*int index = 0, do_help = 0, opt;
	char*shortopts = ":ht:v";

	struct option options[] = {

		{"help",    no_argument, &do_help, 1},
        {"version", no_argument, NULL, 'v'},

	};

	setlocaleU();

	while ((opt =  getopt_long(argc, argv, shortopts, options, NULL)) != -1)
	{
		index += 1;
		printf("%c\n",opt);
		switch (opt)
		{
		case 'h':
			do_help = 1;
			break;
        case 'v':
            printf_color( VERSION_STING_EXEC NAME_COMPILER ": #{FG:cyan}%hhu.%hhu#{FG:reset} \n", VERSION_COMPILER, SUB_VERSION_COMPILER);
			break;


		case ':':
			fprintf(stderr, "Error: El par" A_ACENT "metro \"-" CHAR_FORMAT "/--" STRING_FORMAT "\" requiere un argumento\n", optopt, options[index].name);
			return EXIT_FAILURE;
		case '?':
		default:
			printf_color(ERROR_ARGV);
			return ESRCH;
		}
	}

	if (do_help || ((index == 0) && (opt == -1)))
	{
		printf_color(USAGE_STRING_ARGV "\n\t" HELP_STRING_ARGV "\n");
        printf_color("\t" VERSION_STRING_ARGV "\n");
		return EXIT_SUCCESS;
	}*/


	return EXIT_SUCCESS;
}