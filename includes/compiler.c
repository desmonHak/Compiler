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

#ifndef _COMPILER_C_
#define _COMPILER_C_
#include "compiler.h"

void compile(char *src, Size_file src_size){
    puts("Compilando...");
	lexer_t*    lexer  = init_lexer(src, src_size);
    parser_t*   parser = init_parser(lexer);
    print_tokents(init_lexer(src, src_size));
    ast_t*      root  = parser_parser(parser);  
    print_ast(root);
    print_list_assembly(convert_assembly(root));
}
void compile_file(name_file name_file_open){
    /*MyFile soruce_code;
    
    open_file(&soruce_code, name_file_open, READ);
    if (error_open_file(soruce_code)) {
        printf("Error al abrir el archivo %s\n", name_file_open);
        return;
    } else if (error_mode_file(soruce_code))
    {
        printf("Error al abrir el archivo %s, el modo no es adecuado.\n", name_file_open);
        return;
    }


    // Leer el archivo
    read_file(&soruce_code);

    if (error_read_file(soruce_code)){
        printf("Error al leer el archivo(%s) %s\n", name_file_open, soruce_code.data);
    } else soruce_code.data [get_size_file(soruce_code)] = 0x0;
    
	compile(soruce_code.data, get_size_file(soruce_code));
	close_file(&soruce_code);*/

    printf("El archivo(%s)\n", name_file_open);
    unsigned char text[] = 
        "%entry_point _start\n"
        "%word_size 32"
        "_start:" 
        "#syscall[ \
            eax = 1, \
            ebx = 2, \
            ecx = 3,  \
            .int = 0x80 \
        ]" \
        "_new:"
        "#syscall(1,2,3, )" 
        "%syscall(32,333,35)"
        "var = 'holaaaaaaa mundo\\0'"
        "var = 20"
        "uint8_t variable = 10"
        ;

    /*
    implementar un call para llamar a funciones con stdcall o fastcall
    cambiar punto de entrada a Start
    gcc -shared -fPIC -e Start output.obj -o output.exe
    */

    #include "crypt/md5.h"
    unsigned char hash[16];
    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, text, strlen(text));
    MD5_Final(hash, &md5);

    printf("Hash code(md5): ");
    for(int i = 0; i < 16; i++){
        printf("%2.2x", hash[i]);
    }
    puts("");

    compile(text, sizeof(text));
}

#endif