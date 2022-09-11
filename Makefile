compiler := clang
program_name := edithor
requirements := hal colors utils
files := build\colors.o build\hal.o build\utils.o

bootstrap:
	mkdir build\

utils: src/utils.c
	$(compiler) src\utils.c -c -o build\utils.o

hal: src/hal.c
	$(compiler) src\hal.c -c -o build\hal.o

colors: src/colors.c
	$(compiler) src\colors.c -c -o build\colors.o

main: src/main.c $(requirements)
	$(compiler) src\main.c $(files) -o build\$(program_name).exe -Wall $(CFLAGS)

build: main 

run:
	.\build\edithor.exe
