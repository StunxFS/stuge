CC := gcc

all: generate_asset_headers
	$(CC) src/*.c src/**/*.c libraylib.a -I/usr/include/lua5.3 -llua5.3 -lglfw -lrt -lm -ldl -pthread -o stuge

generate_asset_headers:
	python3 tools/asset2c.py
