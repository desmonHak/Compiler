# WL_lib 

-----
WL_lib (Windows & Linux Library) Es una libreria que permite un cierto alto nivel de funciones, para no tener que lidiar con las cabeceras unicas de cada sistema.

Actualmente hemos creado una funcion `open_file` que nos permite abrir archivos independientemente del si el sistema es Linux o Windows, para la tarea, intenamente se usa las funciones de `fileapi.h` con su funcion `CreateFile` para abrir archivos en sistemas Windows, o en caso de ser un sistema linux donde se esta compilando, usar la clasica `fopen`. 

Se espera en un futuro hacer lo mismo con socket's, lo que deberia permitir la facilidad de escribir software multiplataforma que haga uso de estos

----

## I/O para archivos:

### open_file

Para poder abrir un archivo, usamos la funcion `open_file`, esta funcion recibe un puntero a una estructura de tipo `MyFile`. Aqui podemos ver un par de ejemplos:

```C

// Ejemplo 1:
MyFile mi_archivo;    
open_file(&mi_archivo, "archivo.txt", READ);

// Ejemplo 2:
MyFile* mi_archivo = (MyFile*) malloc(sizeof(MyFile));
open_file(mi_archivo,  "archivo.txt", READ);

```

La funcion `open_file` no retorna ningun valor, aparte de la estructura de tipo `MyFile` recibe un valor de tipo `name_file` el cual a de ser el nombre del archivo y un tercer argumento `mode`

```C
void open_file(MyFile*, name_file, mode);
```

### read_file

La funcion `read_file` permite leer el contenido de un archivo. Recibe un puntero de una estructura de tipo `MyFile`, este a de ser el valor que se uso junto a `open_file` con el modo `READ` minimo para poder efectuar la lectura:
```C
void read_file(MyFile*);
```

Ejemplo:

```C

// Ejemplo 1(mi_archivo sin malloc):  
read_file(&mi_archivo);

// Ejemplo 2(mi_archivo con malloc):
read_file(mi_archivo);

```

### get_data_file

Esta funcion permite obtener los datos que se han leeido o se han escrito. recibe un objeto de tipo `MyFile`:

```C
char *get_data_file(MyFile);
```

Ejemplo
```C

printf("Datos del archivo leeido: %s\n", get_data_file(mi_archivo));

```

### close_file

Esta funcion es la encargda de cerrar el archivo tras realizar las operaciones con el mismo. Este recibe un puntero a una esstructura `MyFile`.
```C
void close_file(MyFile *)
```

Ejemplo:
```C

// Ejemplo 1(mi_archivo sin malloc):  
close_file(&mi_archivo);

// Ejemplo 2(mi_archivo con malloc):
close_file(mi_archivo);

```

### write_file

Esta funcion permite escribir datos en un archivo. Recibe un puntero a una estrcutura `MyFile` y un puntero de tipo `const char *` donde se alojen los datos a escribir en el mismo.

```C
void write_file(MyFile *my_file, const char *data);
```

Ejemplo:
```C

const char msg[] = "Hola Mundo\n";

// Ejemplo 1(mi_archivo sin malloc):  
write_file(&mi_archivo, msg);

// Ejemplo 2(mi_archivo con malloc):
write_file(mi_archivo, msg);

```

----