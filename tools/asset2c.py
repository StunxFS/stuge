# (C) 2022 StunxFS. All rights reserved. Use of this source code is
# governed by an MIT license that can be found in the LICENSE file.

# Script used to embed the assets in the final binary.

import os, glob

ASSETS = glob.glob("assets/**/*.*")

for asset in ASSETS:
    with open(asset, "rb") as f:
        bytes = f.read()
        final_name = os.path.splitext(asset)[0].replace(os.path.sep, "_")
        print(f"[asset2c] generating header for '{asset}' (result: 'src/data/{final_name}.h')")
        with open(os.path.join("src", "data", final_name + ".h"), "w") as fn:
            fn.write("// File generated by 'tools/asset2c.py'\n")
            fn.write("// Please, do not edit this file. Your changes may be overwritten.\n\n")
            fn.write(f"static char {final_name.upper()}[{len(bytes)}] = {{\n\t")
            line_len = 0
            for i,b in enumerate(bytes):
                if line_len > 80:
                    fn.write("\n\t")
                    line_len = 8
                if i == len(bytes) - 1:
                    fn.write(f"{b}\n")
                    line_len+=len(str(b))
                else:
                    fn.write(f"{b}, ")
                    line_len +=len(str(b))+2
            fn.write("};")
