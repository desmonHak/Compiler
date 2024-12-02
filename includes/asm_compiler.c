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

#ifndef _ASM_COMPILER_C_
#define _ASM_COMPILER_C_
#include "asm_compiler.h"

unsigned char *format_intrucion(unsigned char *format, ...)
{
    /*
     *
     *  Formatea un string(la intruccion) con sus valores
     *
     */

    unsigned char *instrucciones;
    va_list args;
    va_start(args, format);

#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(unsigned char *, format_intrucion)
                    TYPE_DATA_DBG(unsigned char *, "format = %s")
                        TYPE_DATA_DBG(va_list *, "... = %p")
                            END_TYPE_FUNC_DBG,
                format, args);
#endif

    size_t size = (vsnprintf(NULL, 0, format, args) + 1) * sizeof(unsigned char);
    debug_malloc(unsigned char, instrucciones, sizeof(unsigned char) * size);
    vsprintf(instrucciones, format, args);
    va_end(args);
    return instrucciones;
}

void get_tab_by_level()
{
/*
 *
 *  Devuelve una tabulacion con una cantidad especificada
 *  por tab_level
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, get_tab_by_level) "Tab level: %u" END_TYPE_FUNC_DBG, tab_level);
#endif
    if (tab != NULL)
    {
        free(tab);
    }
    tab = (char *)malloc(sizeof(char) * (tab_level + 1));
    memset(tab, '\t', tab_level);
    tab[tab_level] = 0x0;
}

void asm_syscall(ast_t *node, list_c *list, size_t is_last)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, asm_syscall)
                    TYPE_DATA_DBG(ast_t *, "node = %p")
                        TYPE_DATA_DBG(list_c *, "list = %p")
                            TYPE_DATA_DBG(size_t, "is_last = %zu")
                                END_TYPE_FUNC_DBG,
                node, list, is_last);
#endif

    //unsigned char *instrucciones = NULL;
    Instruccion* header;


    // printf("Syscall(%s)\n", node->name);
    // printf("pointer regs -> %p, size list: %lld\n", node->data_almacenada.regs, node->data_almacenada.nombre_valor->size);
    for (unsigned char i = 0; i < node->data_almacenada.nombre_valor->size; i++)
    {
        header = initInstruccion();
        header->type_instruccion = directa;
        name_value *values = (name_value *)(node->data_almacenada.nombre_valor->items[i]);
        if (!strcmp(values->name, "int"))
        {
            header->value.asm_instruccion = format_intrucion(ASM_INTERRUPCION("%s") "\n", values->value.pointer);
            goto exit_not_syscall;
        }
        else if (!strcmp(values->name, "syscall"))
        {
            header->value.asm_instruccion = format_intrucion(ASM_INTERRUPCION_SYSCALL() "\n");
            goto exit_not_syscall;
        }
        else
        {
            switch (compiler_word_arch)
            {
            case 64:
                /*
                size = (snprintf(NULL, 0, ASM_MOV("%s", "%llu"), values->name, values->value.val64) + 1) * sizeof(unsigned char);
                debug_malloc(unsigned char, instrucciones, sizeof(unsigned char) * size);
                sprintf(instrucciones, ASM_MOV("%s", "%llu"), values->name, values->value.val64);
                */
                header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("%s", "%llu"), tab, values->name, values->value.val64);
                // printf("[%d] %s = %llu\n",i, values->name, values->value.val64);
                break;
            case 32:
                /*
                size = (snprintf(NULL, 0, ASM_MOV("%s", "%u"), values->name, values->value.val32) + 1) * sizeof(unsigned char);
                debug_malloc(unsigned char, instrucciones, sizeof(unsigned char) * size);
                sprintf(instrucciones, ASM_MOV("%s", "%u"), values->name, values->value.val32);
                */
                header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("%s", "%" SCNu32), tab, values->name, values->value.val32);
                // printf("[%d] %s = %"SCNu32"\n",i, values->name, values->value.val32);
                break;
            case 16:
                /*
                size = (snprintf(NULL, 0, ASM_MOV("%s", "%hu"), values->name, values->value.val16) + 1) * sizeof(unsigned char);
                debug_malloc(unsigned char, instrucciones, sizeof(unsigned char) * size);
                sprintf(instrucciones, ASM_MOV("%s", "%hu"), values->name, values->value.val16);
                */
                header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("%s", "%u"), tab, values->name, values->value.val16);
                // printf("[%d] %s = %hu\n",i, values->name, values->value.val16);
                break;
            default:
                printf("wtf con esta arquitectura\n");
            }
        }
        printf("%s\n", header->value.asm_instruccion);
        // printf("is_last = %zu\n",is_last);
        list_push(list, header);
    }
    header = initInstruccion();
    header->type_instruccion = directa;
    switch (compiler_word_arch)
    {
    case 64:
        header->value.asm_instruccion = format_intrucion("%s" ASM_INTERRUPCION_SYSCALL() "\n", tab);
        break;
    case 32:
        header->value.asm_instruccion = format_intrucion("%s" ASM_INTERRUPCION("0x%x") "\n", tab, 0x80);
        break;
    case 16:
    
        header->value.asm_instruccion = format_intrucion("%s" ASM_INTERRUPCION("0x%x") "\n", tab, 0x10);
        break;
    }
exit_not_syscall:
    list_push(list, header);
    printf("%s\n", header->value.asm_instruccion);
}

void print_list_assembly(list_c *list)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, print_list_assembly)

                    TYPE_DATA_DBG(list_c *, "list = %p")

                        END_TYPE_FUNC_DBG,
                list);
#endif
    for (size_t i = 0; i < list->size; i++)
    {
        Instruccion* instruccion = (Instruccion *)list->items[i];
        switch (instruccion->type_instruccion)
        {
        case directa:
            printf("%s\n", instruccion->value.asm_instruccion);
            break;
        case set_size_stack_frame_var:
            printf("size_stack_frame_var %zu\n", instruccion->value.size_stack_frame_var);
            break;
        default:
            puts("Unknown instruccion");
            printf("%d\n", instruccion->type_instruccion);
            exit(1);
        }
        
    }
}

void stringToHex(const char *input, char *output, size_t size)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, stringToHex)
                    TYPE_DATA_DBG(const char *, "input = %s")
                        TYPE_DATA_DBG(char *, "output = %p")
                            TYPE_DATA_DBG(size_t, "size = %zu")
                                END_TYPE_FUNC_DBG,
                input, output, size);
#endif

    /*
     *
     *  Convierte una cadena string a su formato hex, de tamaño size
     *
     */

    // solo si el string no fue volteado
    while (*input)
    {
        if (*input == '\\')
        {
            if (!(*input))
                puts("stringToHex: No se a finalizado la cadena");
            switch (*(input + 1))
            {
            case '0':
                sprintf(output, "%02x", '\0');
                break;
            case 'r':
                sprintf(output, "%02x", '\r');
                break;
            case 'n':
                sprintf(output, "%02x", '\n');
                break;
            case 't':
                sprintf(output, "%02x", '\t');
                break;
            case '\\':
                sprintf(output, "%02x", '\\');
                break;
            default:
                sprintf(output, "%02x", *(input + 1)); // Convierte el caracter a formato hexadecimal
            }
            input += 2;
        }
        else
        {
            sprintf(output, "%02x", *input); // Convierte el caracter a formato hexadecimal
            input++;
        }

        output += 2; // Avanza dos posiciones en la cadena de salida
    }
    /*printf("%s\n", input);

    for(size_t i = 0; i < size; i++)
    {
        if (*(input + 1) && *(input + 1) == '\\')
        {
            switch (*input)
            {

            case '0':
                sprintf(output, "%02x", '\0');
                break;
            case 'r':
                sprintf(output, "%02x", '\r');
                break;
            case 'n':
                sprintf(output, "%02x", '\n');
                break;
            case 't':
                sprintf(output, "%02x", '\t');
                break;
            case '\\':
                sprintf(output, "%02x", '\\');
                break;
            default:
                sprintf(output, "%02x", *(input)); // Convierte el caracter a formato hexadecimal
            }
            input += 2; // Avanza dos posiciones en la cadena de salida
        }
        else
        {
            sprintf(output, "%02x", *(input)); // Convierte el caracter a formato hexadecimal
            input += 1;                       // Avanza dos posiciones en la cadena de salida
        }
        //printf("%s\n", output);
        output += 2;
    }*/
}

void strrevWithoutNull(char *str, size_t size)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, strrevWithoutNull)
                    TYPE_DATA_DBG(char *, "str = %s")
                        TYPE_DATA_DBG(size_t, "size = %zu")
                            END_TYPE_FUNC_DBG,
                str, size);
#endif
    if (size % 2 != 0)
    {
        fprintf(stderr, "Error: La cadena debe tener un numero par de digitos hexadecimales.\n");
        return;
    }

    // Invertir los pares de caracteres hexadecimales directamente en la cadena de entrada
    for (size_t i = 0; i < size / 2; i += 2)
    {
        char temp = str[i];
        str[i] = str[size - i - 2];
        str[size - i - 2] = temp;

        temp = str[i + 1];
        str[i + 1] = str[size - i - 1];
        str[size - i - 1] = temp;
    }
    printf("%s\n", str);
}
variable *init_variable(name_value *name, size_t offset_stack, status_c status)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(variable *, init_variable)
                    TYPE_DATA_DBG(name_value *, "name = %p")
                        TYPE_DATA_DBG(size_t, "offset_stack = %zu")
                            TYPE_DATA_DBG(status_c, "status = %p")
                                END_TYPE_FUNC_DBG,
                name, offset_stack, status);
#endif
    variable *nueva_variable;
    debug_calloc(variable, nueva_variable, 1, sizeof(variable));
    nueva_variable->name = name;
    nueva_variable->offset_stack = offset_stack;
    nueva_variable->status = status;
    return nueva_variable;
}

void *free_variable(variable *nueva_variable)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void *, free_variable)
                    TYPE_DATA_DBG(variable *, "nueva_variable = %p")
                        END_TYPE_FUNC_DBG,
                nueva_variable);
#endif
    free(nueva_variable);
    return NULL;
}

void incrementarBaseStackPointer(variable *my_variable)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, incrementarBaseStackPointer)
                    TYPE_DATA_DBG(variable *, "my_variable = %p")
                        END_TYPE_FUNC_DBG,
                my_variable);
#endif
    size_t offset_l = size_type_data(my_variable);
    if (my_variable->status.is_offset_negative) my_variable->offset_stack = (frame_actual->status_stack.size_stack += offset_l);
    else my_variable->offset_stack = (frame_actual->status_stack.size_stack -= offset_l);
}

size_t size_type_data(variable *my_variable){
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(size_t, size_type_data)
                    TYPE_DATA_DBG(variable *, "my_variable = %p")
                        END_TYPE_FUNC_DBG,
                my_variable);
#endif
    switch (my_variable->name->type_data)
    {
    case valor_8bits:  return 1;
    case valor_16bits: return 2;
    case valor_32bits: return 4;
    case valor_64bits: return 8;
    case valor_auto:
    case valor_puntero_generico: return compiler_word_arch / 8;
    case valor_string: return strlen(my_variable->name->value.string);
    default:
        printf(__FILE__ " {size_type_data} Type data(%d)\n", my_variable->name->type_data);
        exit(1);
    }
}
void convert_string_to_push_reverse(list_c *list, size_t frame, name_value *value)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, convert_string_to_push_reverse)
                    TYPE_DATA_DBG(list_c *, "list = %p")
                        TYPE_DATA_DBG(size_t, "frame = %zu")
                            TYPE_DATA_DBG(name_value *, "value = %p")
                                END_TYPE_FUNC_DBG,
                list, frame, value);
#endif

    /*
     *
     *  Convierte una cadena de caracteres como "hola mundo" a una secuencia
     *  de movimientos a la pila en orden inverso:
     *
     *      ; para una CPU de 64bits:
     *      push "do"
     *      push "hola mun" ;  64/8 bytes por movimieno a la pìla
     *
     *      ; para una CPU de 32bits:
     *      push "do"
     *      push " mun"
     *      push "hola"
     *
     *      ; para una CPU de 16bits:
     *      push "do"
     *      push "un"
     *      push " m"
     *      push "la"
     *      push "ho"
     *
     *  De tal manera que se recibe el marco de pila actual y se calcula la direccion
     *  en run time de la pila donde se almacenan los datos.
     *
     */
    if (value->type_data != valor_string)
        return;
    // si el valor no es un string finalizar
    // list_c *list = init_list(sizeof(unsigned char*));
    size_t size_str = strlen(value->value.string);    // tamaño del string
    unsigned char size_word = compiler_word_arch / 8; // tamaño de palabra para el que es destinada la instruccion
    unsigned char *value_str;

    Instruccion* header;

    list_c *list_temp = init_list(sizeof(Instruccion)); // lista termporal
    for (size_t i = size_str; i > 0; i -= size_word)
    {
        header = initInstruccion();
        header->type_instruccion = directa;
        if (i > SIZE_MAX - 0xff)
            break; // al ser un valor unsigned al pasar el 0 pasa a su valor maximo
        char cadenaHex[2 * size_word + 1];
        debug_calloc(unsigned char, value_str, 2 * size_word + 1, sizeof(unsigned char));
        // copiar una cantidad de size_word(16, 32, 64) bytes al nuevo buffer reservado
        memcpy(value_str, value->value.string + (size_str - i), size_word);
        stringToHex(value_str, cadenaHex, size_word);    // convertir el string de caracteres, a un string con su representacion hex
        strrevWithoutNull(cadenaHex, strlen(cadenaHex)); // dara la vuelta a la cadena por ser littel endian
        size_t real_size_hex = strlen(cadenaHex) / 2;
        /*if (i + size_word > size_str)
        {*/
        if (real_size_hex == 1)
        {
            header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("byte   [BASE_STACk-0x%x]", "0x%s ; %s = n %s"), tab, i, cadenaHex, value->name, value->value);
        }
        else if (real_size_hex == 2)
        {
            header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("word  [BASE_STACk-0x%x]", "0x%s ; %s =  %s"), tab, i, cadenaHex, value->name, value->value);
        }
        else if (real_size_hex <= 4)
        {
            header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("dword  [BASE_STACk-0x%x]", "0x%s ; %s =  %s"), tab, i, cadenaHex, value->name, value->value);
        }
        else if (real_size_hex <= 8)
        {
            header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("rax", "0x%s ; %s =  %s\n") "%s" ASM_MOV("  [BASE_STACk-0x%x]", "RAX ; %s =  %s"), tab, cadenaHex, value->name, value->value, tab, i, value->name, value->value);
        }
        else
        {
            puts("error-?");
            exit(1);
        }
        /*}
        else
        {
            instrucciones = format_intrucion("%s" ASM_MOV("SIZE_T_SIZE_OPERATION  [BASE_STACk-0x%x]", "0x%s ; %s = %s"), tab, i, cadenaHex, value->name, value->value);
        }*/

        printf("%lld %s\n", real_size_hex, header->value.asm_instruccion);
        list_push(list_temp, header);
        /*switch (compiler_word_arch)
        {
        case 64:

            break;

        default:
            break;
        }*/
    }

    for (size_t i = list_temp->size - 1; i > 0; --i)
    {
        list_push(list, (Instruccion*)(list_temp->items[i]));
        printf("%zu %s\n", i, ((Instruccion*)list_temp->items[i])->value.asm_instruccion);
    }
    list_push(list, (Instruccion*)(list_temp->items[0]));
    list_temp = free_list(list_temp);
    // return list;
}



void asm_var_create(ast_t *node, list_c *list, size_t is_last)
{
    //unsigned char *instrucciones = NULL;
    Instruccion* header = initInstruccion();
    header->type_instruccion = directa;
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, asm_var_create)
                    TYPE_DATA_DBG(ast_t *, "node = %p")
                        TYPE_DATA_DBG(list_c *, "list = %p")
                            TYPE_DATA_DBG(size_t, "is_last = %zu")
                                END_TYPE_FUNC_DBG,
                node, list, is_last);
#endif
    // printf("Size stack frame: %zu\n", stack_frame.total_size_stack_frame);
    printf("Size stack frame: %zu\n", frame_actual->status_stack.size_stack);

    for (unsigned char i = 0; i < node->data_almacenada.nombre_valor->size; i++)
    {
        printHashTable(frame_actual->status_stack.variables);
        variable *nueva_variable;
        name_value *var = (name_value *)(node->data_almacenada.nombre_valor->items[i]);

        // list_push(stack_frame.stack_frame_var, var); // guardar la variable en el stack
        if (!containsKey(frame_actual->status_stack.variables, var->name))
        {
            // si la variable no existe se declara en el frame actual
            nueva_variable = init_variable(
                var,
                frame_actual->status_stack.size_stack,
                (status_c){
                    .is_local = 1,          // decir que sera una variable local
                    .is_offset_negative = 1 // (offset negativo = 1)
                });
            // poner en la tabla hash la nueva variable
            incrementarBaseStackPointer(nueva_variable);
            put(frame_actual->status_stack.variables, var->name, nueva_variable);
        }
        else
        {
            // si la variable ya fue declarada anteriormente, se cambiara su valor
            variable *old_variable = (variable *)get(frame_actual->status_stack.variables, var->name);
            name_value *var_old = old_variable->name; // obtener el antiguo nombre de variable


            nueva_variable = init_variable( // crea la nueva variable
                var,
                frame_actual->status_stack.size_stack,
                (status_c){
                    .is_local = 1,          // decir que sera una variable local
                    .is_offset_negative = 1 // (offset negativo = 1)
                });
            // nueva_variable = removeFromHashTable(frame_actual->status_stack.variables, var->name);
            
            updateValue(frame_actual->status_stack.variables, var->name, nueva_variable); // actualzar la tabla hash con el nuevo valor
            // despues de actualizar los valores, volvemos a obtener la variable pero actualizada
            nueva_variable = (variable *)get(frame_actual->status_stack.variables, var->name);

            if(var_old->type_data == var->type_data){ // comparar si la anterior declaracion y la nueva son del mismo tipo
                // alterar el antiguo valor con el nuevo
                if (nueva_variable->status.is_local){
                    if (nueva_variable->status.is_offset_negative){
                        if (var->type_data >= 0 && var->type_data < 4)
                            nueva_variable->offset_stack += (var->type_data+1)*2;
                    } else {
                        if (var->type_data >= 0 && var->type_data < 4)
                            nueva_variable->offset_stack -= (var->type_data+1)*2;
                    }   
                } else {
                    puts("variables no locales, no implementadas.");
                }
            } else {
                /*
                 *
                 *  Si se le esta dando otro valor a la variable ya existente, con otro tipo de dato,
                 *  se reservara memoria dinamica para futuras reasignaciones de tipos de datos variables.
                 * 
                 */
                    /*if (nueva_variable->status.is_offset_negative){
                        if (var->type_data >= 0 && var->type_data < 4)
                            nueva_variable->offset_stack += (var->type_data+1) - (old_variable->name->type_data+1);
                    } else {
                        if (var->type_data >= 0 && var->type_data < 4)
                            nueva_variable->offset_stack -= (var->type_data+1 - (old_variable->name->type_data+1));
                    }  */
                //size_t offset_l = size_type_data(old_variable);
                printf("--> %zu %zu %zu %zu\n", old_variable->offset_stack, nueva_variable->offset_stack, size_type_data(old_variable), frame_actual->status_stack.size_stack);
                nueva_variable->offset_stack = old_variable->offset_stack - size_type_data(old_variable);
                nueva_variable->offset_stack += size_type_data(nueva_variable);
                //frame_actual->status_stack.size_stack = nueva_variable->offset_stack;
                frame_actual->status_stack.size_stack += size_type_data(nueva_variable);
                frame_actual->status_stack.size_stack -= size_type_data(old_variable);
                printf("--> %zu %zu %zu %zu\n", old_variable->offset_stack, nueva_variable->offset_stack, size_type_data(old_variable), frame_actual->status_stack.size_stack);
            }
            

            old_variable = free_variable(old_variable);                                   // liberar la antigua variable y poner la nueva
            if (nueva_variable == NULL)
            {
                puts("[hash-table] error");
                exit(1);
            }
        }

        switch (nueva_variable->name->type_data)
        {
        case valor_8bits:
            printf("<8@%hhu>\n", var->value.val8);
            // stack_frame.total_size_stack_frame += 1; // 1byte
            // instrucciones = format_intrucion("%s" ASM_MOV("byte  [BASE_STACk-0x%x]", "%" PRIu64 " ; %s"), tab, stack_frame.total_size_stack_frame, var->value.val8, var->name);

            header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("byte   [BASE_STACk-0x%x]", "%" PRIu64 " ; %s"), tab, nueva_variable->offset_stack, var->value.val8, var->name);
            break;
        case valor_16bits:
            printf("<16@%hu>\n", var->value.val16);
            // stack_frame.total_size_stack_frame += 2; // 2byte

            // instrucciones = format_intrucion("%s" ASM_MOV("word  [BASE_STACk-0x%x]", "%u ; %s"), tab, stack_frame.total_size_stack_frame, var->value.val16, var->name);
            header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("word  [BASE_STACk-0x%x]", "%u ; %s"), tab, nueva_variable->offset_stack, var->value.val16, var->name);
            break;
        case valor_32bits:
            printf("<32@%" SCNu32 ">\n", var->value.val32);
            // stack_frame.total_size_stack_frame += 4; // 4byte

            // instrucciones = format_intrucion("%s" ASM_MOV("dword [BASE_STACk-0x%x]", "%" SCNu32 "  ; %s"), tab, stack_frame.total_size_stack_frame, var->value.val32, var->name);
            header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("dword  [BASE_STACk-0x%x]", "%" SCNu32 "  ; %s"), tab, nueva_variable->offset_stack, var->value.val32, var->name);
            break;
        case valor_64bits:
            printf("<64@%" PRIu64 ">\n", var->value.val64);
            // stack_frame.total_size_stack_frame += 8; // 8byte

            // instrucciones = format_intrucion("%s" ASM_MOV("qword [BASE_STACk-0x%x]", "%" PRIu64 " ; %s"), tab, stack_frame.total_size_stack_frame, var->value.val64, var->name);
            header->value.asm_instruccion = format_intrucion("%s" ASM_MOV("qword  [BASE_STACk-0x%x]", "%" PRIu64 " ; %s"), tab, nueva_variable->offset_stack, var->value.val64, var->name);
            break;
        case valor_puntero_generico:
            printf("<pointer@%p>\n", var->value.pointer);
            // stack_frame.total_size_stack_frame += (compiler_word_arch / 8); // el tamaño de palabra al que se compila pero en byte

            break;
        case valor_string:
            // stack_frame.total_size_stack_frame += (compiler_word_arch/8); // el tamaño de palabra al que se compila pero en byte
            // convert_string_to_push_reverse(list, stack_frame.total_size_stack_frame, var);
            // stack_frame.total_size_stack_frame += strlen(var->value.string);
            convert_string_to_push_reverse(list, nueva_variable->offset_stack, var);

            printf("<string@'%s'>\n", var->value.string);
            break;
        default:
            printf(__FILE__ " Type data(%d)\n", node->type);
            break;
        }
    }
    // si se creo unanueva instruccion añadirlo
    if (header->value.asm_instruccion != NULL)
        list_push(list, header);

    
}

void asm_set_entry_point(ast_t *node, list_c *list, size_t is_last)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(list_c *, asm_set_entry_point)
                    TYPE_DATA_DBG(ast_t *, "node = %p")
                        TYPE_DATA_DBG(list_c *, "list = %p")
                            TYPE_DATA_DBG(size_t, "is_last = %zu")
                                END_TYPE_FUNC_DBG,
                node, list, is_last);
#endif
    entry_point = (node->name);
    Instruccion* header = initInstruccion();
    header->type_instruccion = directa;
    header->value.asm_instruccion = format_intrucion("%s" ASM_DEFINE("ENTRY_POINT", "%s"), tab, entry_point);
    list_push(list, header);
}

void asm_set_word_size(ast_t *node, list_c *list, size_t is_last)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(list_c *, asm_set_word_size)
                    TYPE_DATA_DBG(ast_t *, "node = %p")
                        TYPE_DATA_DBG(list_c *, "list = %p")
                            TYPE_DATA_DBG(size_t, "is_last = %zu")
                                END_TYPE_FUNC_DBG,
                node, list, is_last);
#endif
    entry_point = (node->name);
    Instruccion* header = initInstruccion();
    header->type_instruccion = directa;
    header->value.asm_instruccion = format_intrucion("%s" ASM_DEFINE("COMPILER_WORD_ARCh", "%hhu"), tab, compiler_word_arch);
    list_push(list, header);
}

list_c *get_list_assembly(ast_t *node, list_c *list, size_t is_last)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(list_c *, get_list_assembly)
                    TYPE_DATA_DBG(ast_t *, "node = %p")
                        TYPE_DATA_DBG(list_c *, "list = %p")
                            TYPE_DATA_DBG(size_t, "is_last = %zu")
                                END_TYPE_FUNC_DBG,
                node, list, is_last);
#endif
    if (node == NULL)
    {
        return list;
    }

    switch (node->type)
    {
    case AST_NOOP:
        break;
    case AST_VAR:
        asm_var_create(node, list, is_last);
        break;
    case AST_INIT:
        puts("Nodo de inicio");
        break;
    case AST_COMPOUND:
        printf("Compound(%s)\n", node->name);
        break;
    case AST_FUNC_ETIQUETA:
        asm_funncion_etiqueta(node, list, is_last);
        break;
    case AST_SYSCALL:
        asm_syscall(node, list, is_last);
        break;
    case AST_ENTRY_POINT:
        asm_set_entry_point(node, list, is_last);
        break;
    case AST_WORD_SIZE:
        asm_set_word_size(node, list, is_last);
        break;
    default:
        printf(__FILE__ " Unknown Node Type: %i\n", node->type);
        print_ast(node);
        exit(1);
    }

    // Recorrer los hijos del nodo recursivamente
    for (size_t i = 0; i < node->children->size; i++)
    {
        get_list_assembly(node->children->items[i], list, (i == node->children->size - 1));
    }
    return list;
}

void asm_funncion_etiqueta(ast_t *node, list_c *list, size_t is_last)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, asm_funncion_etiqueta)
                    TYPE_DATA_DBG(ast_t *, "node = %p")
                        TYPE_DATA_DBG(list_c *, "list = %p")
                            TYPE_DATA_DBG(size_t, "is_last = %zu")
                                END_TYPE_FUNC_DBG,
                node, list, is_last);
#endif

    Instruccion* header = initInstruccion();
    header->type_instruccion = directa;
    header->value.asm_instruccion = format_intrucion("%s%s:", tab, node->name);
    list_push(list, header);
    tab_level++;
    get_tab_by_level();

    //if (frame_actual != NULL) free(frame_actual); // liberar el antiguo grame
    if (frame_actual == NULL) {

    } else {
    header = initInstruccion();
    header->type_instruccion = set_size_stack_frame_var;
    header->value.size_stack_frame_var = frame_actual->status_stack.size_stack;
    list_push(list, header);
        /*instruccion_resb_stack = format_intrucion(resb_stack, tab, frame_actual->status_stack.size_stack);
        list_push(list, instruccion_resb_stack);*/
    }
    frame_actual = init_frame(node->name); // reservar memoria para el nuevo frame
    put(stack_frame, node->name, frame_actual);

}

stack_frame_c *init_frame(unsigned char *name_frame)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(stack_frame_c *, init_frame)
                    TYPE_DATA_DBG(unsigned char *, "name_frame = %s")
                                END_TYPE_FUNC_DBG,
                name_frame);
#endif
    stack_frame_c *frame;
    debug_calloc(stack_frame_c, frame, 1, sizeof(stack_frame_c));

    frame->name_frame = name_frame;
    frame->status_stack.variables = createHashTable(256); // crear tabla de hash

    return frame;
}

Instruccion* initInstruccion(){
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(Instruccion *, initInstruccion)
            END_TYPE_FUNC_DBG);
#endif
    Instruccion* instruccion = NULL;
    debug_calloc(Instruccion, instruccion, 1, sizeof(Instruccion))
    return instruccion;
}

list_c *convert_assembly(ast_t *ast)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(list_c *, convert_assembly)
                    TYPE_DATA_DBG(ast_t *, "ast = %p")
                                END_TYPE_FUNC_DBG,
                ast);
#endif
    // lista donde se almacenara instrucciones asm
    list_c *list = (list_c *)init_list(sizeof(Instruccion));
    Instruccion* header = initInstruccion();
    header->type_instruccion = directa;
    header->value.asm_instruccion = malloc(sizeof(char) * (strlen("%include \"base.asm\"\n") + 1));
    strcpy(header->value.asm_instruccion, "%include \"base.asm\"\n");

    list_push(list, header);
    /*
    stack_frame.stack_frame_var = (list_c *)init_list(sizeof(name_value)); // inicializar la lista enlazada del stack frame
    stack_frame.total_size_stack_frame = compiler_word_arch / 8;
    */

    // ajustar en un futuro a un tamaño adecuado
    stack_frame = createHashTable(512);    // tabla hash donde se almacenan variables
    frame_actual = init_frame(NULL);
    put(stack_frame, "init", frame_actual);

    get_tab_by_level();

    if (stack_frame != NULL) free(stack_frame);
    stack_frame = createHashTable(512);    // tabla hash donde se almacenan todos los stack frames

    return get_list_assembly(ast, list, 1);
}

#endif