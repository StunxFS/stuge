# (C) 2022 StunxFS. All rights reserved. Use of this source code is
# governed by an MIT license that can be found in the LICENSE file.

from os import path
import os, sys, sqlite3, subprocess, textwrap

import dearpygui.dearpygui as dpg

VERSION = "0.1.0"

MAKE_PY = path.join('tools', 'make.py')
DB_PATH = path.join("sted", "sted.sqlite")
IS_FIRST_TIME = not path.exists(DB_PATH)

GAME_EXE = path.join("bin", "stuge") + (".exe" if sys.platform == "nt" else "")
GAME_MODIFIED = False
GAME_WAS_MODIFIED = False


def msgbox(title, msg_):
    id = dpg.generate_uuid()
    msg = "\n".join(textwrap.wrap(msg_, 300))
    with dpg.window(label=title,
                    modal=True,
                    show=True,
                    tag=id,
                    autosize=True,
                    no_resize=True,
                    pos=(250, 250),
                    no_close=True):
        dpg.add_text(msg)
        dpg.add_separator()
        dpg.add_button(label="OK",
                       width=400,
                       callback=lambda: dpg.configure_item(id, show=False))


class ProcessResult:

    def __init__(self, out, err, exit_code):
        self.out = out
        self.err = err
        self.exit_code = exit_code


def execute(*args):
    res = subprocess.run(args, capture_output=True, encoding='utf-8')
    stdout = res.stdout.strip() if res.stdout else ""
    stderr = res.stderr.strip() if res.stderr else ""
    return ProcessResult(stdout, stderr, res.returncode)


def build_stuge(from_editor=False):
    global GAME_WAS_MODIFIED
    if GAME_WAS_MODIFIED:
        clean_stuge()
    print(">> make.py build")
    res = execute(sys.executable, MAKE_PY, "build")
    if from_editor and res.exit_code == 0:
        msgbox("Operation completed", "Game built =)")
    else:
        msgbox("Failed to build game", res.err)
    return res.exit_code


def rebuild_stuge(from_editor=False):
    clean_stuge()
    print(">> make.py build")
    res = execute(sys.executable, MAKE_PY, "build")
    if from_editor and res.exit_code == 0:
        msgbox("Operation completed", "Rebuilt game =)")
    else:
        msgbox("Failed to rebuild game", res.err)


def build_and_run_stuge(from_editor=False):
    if build_stuge(from_editor) == 0:
        run_stuge()


def run_stuge():
    if path.exists(GAME_EXE):
        print(">> run game")
        execute("./" + GAME_EXE)
    else:
        msgbox("The game could not be launched", "The binary was not found")


def clean_stuge(from_editor=False):
    print(">> make.py clean")
    res = execute(sys.executable, MAKE_PY, "clean")
    if from_editor and res.exit_code == 0:
        msgbox("Operation completed", "Deleted `.o` files =)")


def insideStugeSRC():
    return path.exists("src") and path.isdir("src") and path.isfile(
        path.join("src", "ow.c"))


class DB:

    def __init__(self):
        self.db = sqlite3.connect(DB_PATH, check_same_thread=False)
        if IS_FIRST_TIME:
            cur = self.db.cursor()
            cur.execute(
                'CREATE TABLE config (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, value TEXT)'
            )
            cur.executemany("INSERT INTO config VALUES(?, ?, ?)",
                            [(0, "GAME_NAME", "stuge"),
                             (1, 'GAME_DEFAULT_WIDTH', '870'),
                             (2, 'GAME_DEFAULT_HEIGHT', '580')])
            self.db.commit()

    def setConfig(self, name, value):
        cur = self.db.cursor()
        if self.existsConfig(name):
            cur.execute(
                f"UPDATE config SET value = '{value}' WHERE name = '{name}'")
        else:
            cur.execute(
                f"INSERT INTO config(name, value) VALUES('{name}','{value}')")
        self.db.commit()

    def getConfigs(self):
        cur = self.db.cursor()
        return cur.execute('SELECT name, value FROM config').fetchall()

    def getConfig(self, name):
        cur = self.db.cursor()
        if x := cur.execute(
                f"SELECT name, value FROM config WHERE name = '{name}'"
        ).fetchone():
            return x[1]
        return None

    def existsConfig(self, name):
        if _ := self.getConfig(name):
            return True
        return False

    def writeConfigHeader(self):
        configs = self.getConfigs()
        with open(path.join("src", "config.h"), "w") as config:
            config.write(
                """// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

// File generated by Sted.
// Please, do not edit this file. Your changes may be overwritten.

#ifndef STUGE_CONFIG_H
#define STUGE_CONFIG_H

""")
            for name, value in configs:
                if value.isdigit():
                    config.write(f"#define {name} {value}\n")
                else:
                    config.write(f'#define {name} "{value}"\n')

            config.write("""
#endif // STUGE_CONFIG_H""")

    def close(self):
        self.db.close()
