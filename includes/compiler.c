#ifndef _COMPILER_C_
#define _COMPILER_C_
#include "compiler.h"

void compile(char *src, Size_file src_size){
    puts("Compilando...");
	lexer_t* lexer = init_lexer(src, src_size);
    parser_t* parser = init_parser(lexer);
    print_tokents(init_lexer(src, src_size));
    ast_t*   root = parser_parser(parser);
	token_t* tok = 0;
    printf("%s\n", token_to_str(parser->token));
    

}
void compile_file(name_file name_file_open){
    MyFile soruce_code;
    
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
    puts("Error.");
    if (error_read_file(soruce_code)){
        printf("Error al leer el archivo(%s) %d\n", name_file_open, soruce_code.data);
    } else soruce_code.data [get_size_file(soruce_code)] = 0x0;
    puts("Error.");
	compile(soruce_code.data, get_size_file(soruce_code));
	close_file(&soruce_code);
}

#endif