[INFO:includes/sintaxis/../structs_data/../debug_c.c:57] [DEBUG INIT]
El archivo(codigo.bh)
Hash code(md5): 9520caee3f1cc8788ab95e6c4a48c52c
Compilando...
<type=TOKEN_ID, 	int_type=0, 	value=_start>
<type=TOKEN_COLON, 	int_type=7, 	value=:>
<type=TOKKEN_MACRO_SYSCALL, 	int_type=1, 	value=#syscall>
<type=TOKEN_LCORCHETES, 	int_type=17, 	value=[>
<type=TOKEN_REGISTRO, 	int_type=19, 	value=eax>
<type=TOKEN_ASIGNACION, 	int_type=13, 	value==>
<type=TOKEN_INT, 	int_type=15, 	value=1>
<type=TOKEN_COMMA, 	int_type=9, 	value=,>
<type=TOKEN_REGISTRO, 	int_type=19, 	value=ebx>
<type=TOKEN_ASIGNACION, 	int_type=13, 	value==>
<type=TOKEN_INT, 	int_type=15, 	value=2>
<type=TOKEN_COMMA, 	int_type=9, 	value=,>
<type=TOKEN_REGISTRO, 	int_type=19, 	value=ecx>
<type=TOKEN_ASIGNACION, 	int_type=13, 	value==>
<type=TOKEN_INT, 	int_type=15, 	value=3>
<type=TOKEN_COMMA, 	int_type=9, 	value=,>
<type=TOKEN_PUNTO, 	int_type=20, 	value=.>
<type=TOKEN_ID, 	int_type=0, 	value=int>
<type=TOKEN_ASIGNACION, 	int_type=13, 	value==>
<type=TOKEN_INT, 	int_type=15, 	value=0x80>
<type=TOKEN_RCORCHETES, 	int_type=18, 	value=]>
<type=TOKEN_ID, 	int_type=0, 	value=_new>
<type=TOKEN_COLON, 	int_type=7, 	value=:>
<type=TOKKEN_MACRO_SYSCALL, 	int_type=1, 	value=#syscall>
<type=TOKEN_LPAREN, 	int_type=3, 	value=(>
<type=TOKEN_INT, 	int_type=15, 	value=1>
<type=TOKEN_COMMA, 	int_type=9, 	value=,>
<type=TOKEN_INT, 	int_type=15, 	value=2>
<type=TOKEN_COMMA, 	int_type=9, 	value=,>
<type=TOKEN_INT, 	int_type=15, 	value=3>
<type=TOKEN_COMMA, 	int_type=9, 	value=,>
<type=TOKEN_RPAREN, 	int_type=4, 	value=)>
<type=TOKKEN_MACRO_SYSCALL, 	int_type=1, 	value=#syscall>
<type=TOKEN_LPAREN, 	int_type=3, 	value=(>
<type=TOKEN_INT, 	int_type=15, 	value=32>
<type=TOKEN_COMMA, 	int_type=9, 	value=,>
<type=TOKEN_INT, 	int_type=15, 	value=333>
<type=TOKEN_COMMA, 	int_type=9, 	value=,>
<type=TOKEN_INT, 	int_type=15, 	value=35>
<type=TOKEN_RPAREN, 	int_type=4, 	value=)>
<type=TOKEN_ID, 	int_type=0, 	value=var>
<type=TOKEN_ASIGNACION, 	int_type=13, 	value==>
<type=TOKEN_STRING_SIMPLE, 	int_type=21, 	value=hola mundo>
<type=TOKEN_ID, 	int_type=0, 	value=var>
<type=TOKEN_ASIGNACION, 	int_type=13, 	value==>
<type=TOKEN_INT, 	int_type=15, 	value=20>
<type=TOKEN_ID, 	int_type=0, 	value=uint8_t>
<type=TOKEN_ID, 	int_type=0, 	value=variable>
<type=TOKEN_ASIGNACION, 	int_type=13, 	value==>
<type=TOKEN_INT, 	int_type=15, 	value=10>
[INFO:includes/sintaxis/parser.c:776]  ast_t * parser_parser_compound( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:757]  ast_t * parser_parser_compound( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:722]  ast_t * parser_parser_expr( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:246]  ast_t * parser_parser_id( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ID, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_COLON, ); 
[INFO:includes/sintaxis/parser.c:190]  ast_t * parser_parser_funtion( unsigned char *  name_id = _start,  parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:722]  ast_t * parser_parser_expr( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:384]  ast_t * parser_parser_macro_syscall( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKKEN_MACRO_SYSCALL, ); 
Token analizado: <type=TOKEN_LCORCHETES, 	int_type=17, 	value=[>
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_LCORCHETES, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_REGISTRO, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ASIGNACION, ); 
[INFO:includes/sintaxis/parser.c:473] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b891828650
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
registro eax = 1
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_COMMA, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_REGISTRO, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ASIGNACION, ); 
[INFO:includes/sintaxis/parser.c:473] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b891828930
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
registro ebx = 2
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_COMMA, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_REGISTRO, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ASIGNACION, ); 
[INFO:includes/sintaxis/parser.c:473] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b891828950
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
registro ecx = 3
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_COMMA, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_PUNTO, ); 
[INFO:includes/sintaxis/parser.c:418] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b891828a50
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ID, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ASIGNACION, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_RCORCHETES, ); 
[INFO:includes/sintaxis/parser.c:722]  ast_t * parser_parser_expr( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:246]  ast_t * parser_parser_id( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ID, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_COLON, ); 
[INFO:includes/sintaxis/parser.c:190]  ast_t * parser_parser_funtion( unsigned char *  name_id = _new,  parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:722]  ast_t * parser_parser_expr( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:384]  ast_t * parser_parser_macro_syscall( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKKEN_MACRO_SYSCALL, ); 
Token analizado: <type=TOKEN_LPAREN, 	int_type=3, 	value=(>
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_LPAREN, ); 
[INFO:includes/sintaxis/parser.c:501] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b891828670
registro numero rax -> value = 1
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_COMMA, ); 
[INFO:includes/sintaxis/parser.c:501] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b891829420
registro numero rbx -> value = 2
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_COMMA, ); 
[INFO:includes/sintaxis/parser.c:501] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b891829300
registro numero rcx -> value = 3
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_COMMA, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_RPAREN, ); 
[INFO:includes/sintaxis/parser.c:722]  ast_t * parser_parser_expr( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:384]  ast_t * parser_parser_macro_syscall( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKKEN_MACRO_SYSCALL, ); 
Token analizado: <type=TOKEN_LPAREN, 	int_type=3, 	value=(>
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_LPAREN, ); 
[INFO:includes/sintaxis/parser.c:501] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b8918296c0
registro numero rax -> value = 32
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_COMMA, ); 
[INFO:includes/sintaxis/parser.c:501] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b891829500
registro numero rbx -> value = 333
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_COMMA, ); 
[INFO:includes/sintaxis/parser.c:501] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b8918295c0
registro numero rcx -> value = 35
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
final de la macro
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_RPAREN, ); 
[INFO:includes/sintaxis/parser.c:722]  ast_t * parser_parser_expr( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:246]  ast_t * parser_parser_id( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ID, ); 
[INFO:includes/sintaxis/parser.c:75]  ast_t * paser_paser_var( unsigned char *  name_id = 000002b891829010,  parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:91] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b891829180
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ASIGNACION, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_STRING_SIMPLE, ); 
[INFO:includes/sintaxis/parser.c:722]  ast_t * parser_parser_expr( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:246]  ast_t * parser_parser_id( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ID, ); 
[INFO:includes/sintaxis/parser.c:75]  ast_t * paser_paser_var( unsigned char *  name_id = 000002b891829020,  parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:91] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b8918298a0
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ASIGNACION, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
[INFO:includes/sintaxis/parser.c:722]  ast_t * parser_parser_expr( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:246]  ast_t * parser_parser_id( parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ID, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ID, ); 
[INFO:includes/sintaxis/parser.c:75]  ast_t * paser_paser_var( unsigned char *  name_id = 000002b891829280,  parser_t *  parser = 000002b891826e50, ); 
[INFO:includes/sintaxis/parser.c:91] [MALLOC]  (name_value*)malloc(576) Variable: data, Tipo: name_value, Puntero: 000002b8918291a0
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_ASIGNACION, ); 
[INFO:includes/sintaxis/parser.c:49]  token_t * parser_eat( parser_t *  parser = 000002b891826e50,  unsigned int  type = TOKEN_INT, ); 
[INFO:includes/sintaxis/parser.c:703]  void print_ast( ast_t *  root = 000002b8918280a0, ); 
Abstract Syntax Tree(size: 6): 
[INFO:includes/sintaxis/parser.c:576]  void print_ast_recursive( ast_t *  node = 000002b8918280a0,  ast_t *  indent = 0,  ast_t *  is_last_child = 1, ); 
|--- Nodo de inicio
[INFO:includes/sintaxis/parser.c:576]  void print_ast_recursive( ast_t *  node = 000002b891827b20,  ast_t *  indent = 1,  ast_t *  is_last_child = 0, ); 
|--- Name funcion: _start
Pointer Node AST: 000002b891827de0
[INFO:includes/sintaxis/parser.c:576]  void print_ast_recursive( ast_t *  node = 000002b891827be0,  ast_t *  indent = 1,  ast_t *  is_last_child = 0, ); 
|--- Name funcion: _new
Pointer Node AST: 000002b891827c60
[INFO:includes/sintaxis/parser.c:576]  void print_ast_recursive( ast_t *  node = 000002b891827fe0,  ast_t *  indent = 1,  ast_t *  is_last_child = 0, ); 
|--- Syscall(syscall)
pointer regs -> 000002b891829680, size list: 3
[0] rax = 32
[1] rbx = 333
[2] rcx = 35
[INFO:includes/sintaxis/parser.c:576]  void print_ast_recursive( ast_t *  node = 000002b891828120,  ast_t *  indent = 1,  ast_t *  is_last_child = 0, ); 
|--- var = <string@'hola mundo'>
[INFO:includes/sintaxis/parser.c:576]  void print_ast_recursive( ast_t *  node = 000002b891828220,  ast_t *  indent = 1,  ast_t *  is_last_child = 0, ); 
|--- var = <64@20>
[INFO:includes/sintaxis/parser.c:576]  void print_ast_recursive( ast_t *  node = 000002b891827ba0,  ast_t *  indent = 1,  ast_t *  is_last_child = 1, ); 
--- variable = <8@10>
[INFO:includes/asm_compiler.c:73]  void get_tab_by_level(Tab level: 0); 
[INFO:includes/asm_compiler.c:301]  list_c* get_list_assembly( ast_t*  node = 000002b8918280a0,  list_c*  list = 000002b891829820,  size_t  is_last = 1, ); 
Nodo de inicio
[INFO:includes/asm_compiler.c:301]  list_c* get_list_assembly( ast_t*  node = 000002b891827b20,  list_c*  list = 000002b891829820,  size_t  is_last = 0, ); 
[INFO:includes/asm_compiler.c:344]  void asm_funncion_etiqueta( ast_t*  node = 000002b891827b20,  list_c*  list = 000002b891829820,  size_t  is_last = 0, ); 
[INFO:includes/asm_compiler.c:49]  unsigned char* format_intrucion( unsigned char*  format = %s%s:,  va_list*  ... = 000000d3563ff958, ); 
[INFO:includes/asm_compiler.c:58] [MALLOC]  (unsigned char*)malloc(8) Variable: instrucciones, Tipo: unsigned char, Puntero: 000002b891828f30
[INFO:includes/asm_compiler.c:73]  void get_tab_by_level(Tab level: 1); 
[INFO:includes/asm_compiler.c:301]  list_c* get_list_assembly( ast_t*  node = 000002b891827be0,  list_c*  list = 000002b891829820,  size_t  is_last = 0, ); 
[INFO:includes/asm_compiler.c:344]  void asm_funncion_etiqueta( ast_t*  node = 000002b891827be0,  list_c*  list = 000002b891829820,  size_t  is_last = 0, ); 
[INFO:includes/asm_compiler.c:49]  unsigned char* format_intrucion( unsigned char*  format = %s%s:,  va_list*  ... = 000000d3563ff958, ); 
[INFO:includes/asm_compiler.c:58] [MALLOC]  (unsigned char*)malloc(7) Variable: instrucciones, Tipo: unsigned char, Puntero: 000002b891828fa0
[INFO:includes/asm_compiler.c:73]  void get_tab_by_level(Tab level: 2); 
[INFO:includes/asm_compiler.c:301]  list_c* get_list_assembly( ast_t*  node = 000002b891827fe0,  list_c*  list = 000002b891829820,  size_t  is_last = 0, ); 
[INFO:includes/asm_compiler.c:89]  void asm_syscall( ast_t*  node = 000002b891827fe0,  list_c*  list = 000002b891829820,  size_t  is_last = 0, ); 
[INFO:includes/asm_compiler.c:49]  unsigned char* format_intrucion( unsigned char*  format = %smov %s, %llu,  va_list*  ... = 000000d3563ff928, ); 
[INFO:includes/asm_compiler.c:58] [MALLOC]  (unsigned char*)malloc(14) Variable: instrucciones, Tipo: unsigned char, Puntero: 000002b891829140
		mov rax, 32
[INFO:includes/asm_compiler.c:49]  unsigned char* format_intrucion( unsigned char*  format = %smov %s, %llu,  va_list*  ... = 000000d3563ff928, ); 
[INFO:includes/asm_compiler.c:58] [MALLOC]  (unsigned char*)malloc(15) Variable: instrucciones, Tipo: unsigned char, Puntero: 000002b891829440
		mov rbx, 333
[INFO:includes/asm_compiler.c:49]  unsigned char* format_intrucion( unsigned char*  format = %smov %s, %llu,  va_list*  ... = 000000d3563ff928, ); 
[INFO:includes/asm_compiler.c:58] [MALLOC]  (unsigned char*)malloc(14) Variable: instrucciones, Tipo: unsigned char, Puntero: 000002b891829840
		mov rcx, 35
[INFO:includes/asm_compiler.c:49]  unsigned char* format_intrucion( unsigned char*  format = %ssyscall
,  va_list*  ... = 000000d3563ff928, ); 
[INFO:includes/asm_compiler.c:58] [MALLOC]  (unsigned char*)malloc(11) Variable: instrucciones, Tipo: unsigned char, Puntero: 000002b8918291c0
		syscall

[INFO:includes/asm_compiler.c:301]  list_c* get_list_assembly( ast_t*  node = 000002b891828120,  list_c*  list = 000002b891829820,  size_t  is_last = 0, ); 
[INFO:includes/asm_compiler.c:244]  void asm_var_create( ast_t*  node = 000002b891828120,  list_c*  list = 000002b891829820,  size_t  is_last = 0, ); 
Size stack frame: 0
var = [INFO:includes/asm_compiler.c:220] [CALLOC] (unsigned char*)calloc(17, 1) Variable: value_str, Tipo: unsigned char, Puntero: 000002b8918291e0
[INFO:includes/asm_compiler.c:49]  unsigned char* format_intrucion( unsigned char*  format = %smov SIZE_T_SIZE_OPERATION  [BASE_STACk-0x%x], %s ; %s,  va_list*  ... = 000000d3563ff838, ); 
[INFO:includes/asm_compiler.c:58] [MALLOC]  (unsigned char*)malloc(66) Variable: instrucciones, Tipo: unsigned char, Puntero: 000002b89182a0a0
		mov SIZE_T_SIZE_OPERATION  [BASE_STACk-0x0], (ù?VÓ ; hola mundo
[INFO:includes/asm_compiler.c:220] [CALLOC] (unsigned char*)calloc(17, 1) Variable: value_str, Tipo: unsigned char, Puntero: 000002b891829520
[INFO:includes/asm_compiler.c:49]  unsigned char* format_intrucion( unsigned char*  format = %smov SIZE_T_SIZE_OPERATION  [BASE_STACk-0x%x], %s ; %s,  va_list*  ... = 000000d3563ff838, ); 
[INFO:includes/asm_compiler.c:58] [MALLOC]  (unsigned char*)malloc(66) Variable: instrucciones, Tipo: unsigned char, Puntero: 000002b891829a60
		mov SIZE_T_SIZE_OPERATION  [BASE_STACk-0x0], (ù?VÓ ; hola mundo
<string@'hola mundo'>
[INFO:includes/asm_compiler.c:301]  list_c* get_list_assembly( ast_t*  node = 000002b891828220,  list_c*  list = 000002b891829820,  size_t  is_last = 0, ); 
[INFO:includes/asm_compiler.c:244]  void asm_var_create( ast_t*  node = 000002b891828220,  list_c*  list = 000002b891829820,  size_t  is_last = 0, ); 
Size stack frame: 10
var = <64@20>
[INFO:includes/asm_compiler.c:49]  unsigned char* format_intrucion( unsigned char*  format = %smov qword [BASE_STACk-0x%x], %llu ; %s,  va_list*  ... = 000000d3563ff928, ); 
[INFO:includes/asm_compiler.c:58] [MALLOC]  (unsigned char*)malloc(40) Variable: instrucciones, Tipo: unsigned char, Puntero: 000002b89182a180
[INFO:includes/asm_compiler.c:301]  list_c* get_list_assembly( ast_t*  node = 000002b891827ba0,  list_c*  list = 000002b891829820,  size_t  is_last = 1, ); 
[INFO:includes/asm_compiler.c:244]  void asm_var_create( ast_t*  node = 000002b891827ba0,  list_c*  list = 000002b891829820,  size_t  is_last = 1, ); 
Size stack frame: 18
variable = <8@10>
[INFO:includes/asm_compiler.c:49]  unsigned char* format_intrucion( unsigned char*  format = %smov byte  [BASE_STACk-0x%x], %llu ; %s,  va_list*  ... = 000000d3563ff928, ); 
[INFO:includes/asm_compiler.c:58] [MALLOC]  (unsigned char*)malloc(45) Variable: instrucciones, Tipo: unsigned char, Puntero: 000002b891827c20
[INFO:includes/asm_compiler.c:165]  void print_list_assembly( list_c*  list = 000002b891829820, ); 
%include "base.asm"

_start:
	_new:
		mov rax, 32
		mov rbx, 333
		mov rcx, 35
		syscall

		mov qword [BASE_STACk-0x12], 20 ; var
		mov byte  [BASE_STACk-0x13], 10 ; variable
