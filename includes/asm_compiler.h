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

#ifndef _ASM_COMPILER_H_
#define _ASM_COMPILER_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "./sintaxis/ast.h"
#include "x86/assembly.h"
#include "./structs_data/hash-table.h" // structs_data/hash-table.h !=  structs_data_C/hash-table.h

static char resb_stack[] = "%s" ASM_SUB("TOP_STACk", "%zu") "\n";
static char *instruccion_resb_stack = NULL;
static uint16_t tab_level = 0; // nivel de tabulacion
static char *tab = NULL;       // puntero a las tabulaciones
/*typedef struct stack_frame_c
{
    size_t total_size_stack_frame; // tamaño total de todo el frame
    list_c* stack_frame_var;       // variables almacenadas en el frame
                                   // los datos de la lista enlazada son de tipo
                                   // name_value
} stack_frame_c;
static stack_frame_c stack_frame = {
    .stack_frame_var = NULL,
    .total_size_stack_frame = 0
};*/

typedef struct stack_frame_c
{
    unsigned char *name_frame; // nombre del frame
    struct
    {
        size_t size_stack;    // tamaño del stack
        HashTable *variables; // tabla de hash que contiene las variables(struct variable)
    } status_stack;
} stack_frame_c;
typedef struct status_c
{
    uint8_t is_local : 1;           // si la variable es local y depende del frame 1
                                    // si la variable es estatica 0
    uint8_t is_offset_negative : 1; // 1 si a ebp se le resta offset_stack
                                    // 0 si se le suma
} status_c;
typedef struct variable
{
    size_t offset_stack; /*
                          * en el caso de mov [ebp-8], offset_stack valdria -8
                          */
    status_c status;
    name_value *name; // nombre de la variable y su valor
} variable;

// puntero al stack frame actual
static HashTable *stack_frame = NULL;      // contiene todos los stack frames
static stack_frame_c *frame_actual = NULL; // tiene el frame actual y es añadido a la tabla hash

typedef struct Instruccion {
    enum {
        directa, // supone que la instruccion es una instruccion constante
                 // en asm
        set_size_stack_frame_var // supone un sub esp, <tamaño a reservar en el stack>
    } type_instruccion;

    union {
        char *asm_instruccion;       // instruccion asm directa
        size_t size_stack_frame_var; // tamaño reservado en el stack
    } value;
} Instruccion;

list_c *get_list_assembly(ast_t *node, list_c *list, size_t is_last);
void asm_funncion_etiqueta(ast_t *node, list_c *list, size_t is_last);
void print_list_assembly(list_c *list);
void asm_syscall(ast_t *node, list_c *list, size_t is_last);
unsigned char *format_intrucion(unsigned char *format, ...);
list_c *convert_assembly(ast_t *ast);
void convert_string_to_push_reverse(list_c *list, size_t frame, name_value *value);
size_t size_type_data(variable *my_variable);
stack_frame_c *init_frame(unsigned char *name_frame);
Instruccion* initInstruccion();
#include "asm_compiler.c"
#endif