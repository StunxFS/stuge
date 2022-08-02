CC := gcc

all: generate_assets_header
	$(CC) src/*.c src/**/*.c libraylib.a -lglfw -lrt -lm -ldl -pthread -o stuge

generate_asset_headers:
	python3 tools/asset2c.py
