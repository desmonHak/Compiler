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
        "#syscall[ \
            eax = 1, \
            ebx = 2, \
            ecx = 3,  \
            .int = 0x80 \
        ]" \
        "#syscall(1,2,3, )" 
        "#syscall(32,333,35)";
    compile(text, sizeof(text));
}

#endif