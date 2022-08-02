CC := gcc

all: generate_assets_header
	$(CC) src/*.c src/toml/*.c libraylib.a -lglfw -lrt -lm -ldl -pthread -o stuge

generate_assets_header:
	python3 tools/asset2c.py
