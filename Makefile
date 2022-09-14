CC := clang
CFLAGS := -Wall

sources := $(wildcard src/*.c)
outputs = $(wildcard build/*.o)

.PHONY: bootstrap
bootstrap:
	mkdir build\

.PHONY: sources $(sources)
sources: $(sources)

$(sources):
	@printf "\e[34mBuilding: $@\e[0m\n"
	@$(CC) $@ -c -o build/$(@:src/%.c=%.o) $(CFLAGS)
	@printf "\e[32m$@ built!\n\e[0m"

build/edithor.exe: $(sources)
	$(CC) $(outputs) -o build\$(program_name).exe -Wall $(CFLAGS)

.PHONY: build
build: build/edithor.exe

.PHONY: clean
clean:
	rm build/*.o -f
	rm build/*.exe -f


run:
	.\build\edithor.exe
