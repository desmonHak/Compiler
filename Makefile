NASM=nasm
C=gcc
LEVEL_OPTIMIZACION=3

CFLAGS=	-O$(LEVEL_OPTIMIZACION) -fdiagnostics-color=always -masm=intel -std=c17 \
		-Wno-unused-parameter -Wno-implicit-fallthrough -Wno-type-limits 		\
		-Wno-unused-variable -Wno-pointer-sign -D_ExceptionHandler

C_DEBUG=-D DEBUG_ENABLE -O0 -fdiagnostics-color=always -masm=intel -std=c17 	\
		-ggdb -fno-asynchronous-unwind-tables -Wall -Wextra -Wpedantic			\
		-fno-omit-frame-pointer													\
		-fstack-protector-strong -fno-inline -fno-optimize-sibling-calls		\
		-fdiagnostics-show-option -D_ExceptionHandler

DIR_TARGET=output
TARGET_FILE=compiler
BASE_HEADERS= includes

init: create $(DIR_TARGET)\$(TARGET_FILE).exe  \
	$(DIR_TARGET)\$(TARGET_FILE)_debug
	tree /A /F > tree_files.txt

$(DIR_TARGET)\$(TARGET_FILE).exe: $(BASE_HEADERS)/main.c
	$(C) $(CFLAGS) $^ -o $@

debug: $(DIR_TARGET)\$(TARGET_FILE)_debug
	@echo "$(DIR_TARGET)\$(TARGET_FILE)_debug"

$(DIR_TARGET)\$(TARGET_FILE)_debug: $(BASE_HEADERS)/main.c
	$(C) $(C_DEBUG) $^ -o $@

create:
	@cls
	if not exist $(DIR_TARGET) mkdir $(DIR_TARGET)

clear:
	if exist $(DIR_TARGET)  del /Q /F $(DIR_TARGET)\$(TARGET_FILE).exe
	del /Q /F tree_files.txt

	if exist $(DIR_TARGET) rmdir /Q $(DIR_TARGET)