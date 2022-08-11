CC := gcc
EXE_NAME := stuge

all: generate_asset_headers
	$(CC) src/**/**.o src/**.c src/**/**.c thirdparty/**/**.c libraylib.a -Ithirdparty -I/usr/include/libxml2 -I/usr/include/lua5.3 -lxml2 -llua5.3 -lglfw -lrt -lm -ldl -pthread -o $(EXE_NAME)

generate_asset_headers:
	python3 tools/asset2c.py
