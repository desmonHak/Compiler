NASM=nasm
C=gcc -g -masm=intel -std=c17 -Wall -Wextra -Wno-implicit-fallthrough -Wno-unused-variable -Wno-pointer-sign -Werror
C_DEBUG=$(C) -D DEBUG_ENABLE
DIR_TARGET=output
TARGET_FILE=compiler
BASE_HEADERS= includes

init: create compiler
	tree /A /F > tree_files.txt

compiler: 
	$(C_DEBUG) $(BASE_HEADERS)/main.c -o $(DIR_TARGET)\$(TARGET_FILE).exe

create:
	@cls
	if not exist $(DIR_TARGET) mkdir $(DIR_TARGET)

clear:
	if exist $(DIR_TARGET)  del /Q /F $(DIR_TARGET)\$(TARGET_FILE).exe
	del /Q /F tree_files.txt

	if exist $(DIR_TARGET) rmdir /Q $(DIR_TARGET)