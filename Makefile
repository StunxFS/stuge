CC := gcc
EXE_NAME := stuge

CFILES := `find . -iname '*.c'`

all: generate_asset_headers
	$(CC) src/data/*.o $(CFILES) libraylib.a -Ithirdparty -I/usr/include/libxml2 -I/usr/include/lua5.3 -lxml2 -llua5.3 -lglfw -lrt -lm -ldl -pthread -o $(EXE_NAME)

generate_asset_headers:
	python3 tools/asset2c.py
