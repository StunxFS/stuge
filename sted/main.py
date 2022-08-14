# (C) 2022 StunxFS. All rights reserved. Use of this source code is
# governed by an MIT license that can be found in the LICENSE file.

import dearpygui.dearpygui as dpg

import sted

DB = sted.DB()


def game_editor_status(status):
    dpg.set_value("label_status", status)
    dpg.configure_item("ide_status", show=True)


def game_hidden_editor_status():
    dpg.set_value("label_status", "")
    dpg.configure_item("ide_status", show=False)


def game_modified():
    if not sted.GAME_MODIFIED:
        sted.GAME_MODIFIED = True
        dpg.configure_item("game_modified", show=True)


def build_cb():
    game_editor_status("Building game...")
    sted.build_stuge(True)
    game_hidden_editor_status()


def rebuild_cb():
    game_editor_status("Rebuilding game...")
    sted.rebuild_stuge(True)
    game_hidden_editor_status()


def build_and_run_cb():
    game_editor_status("Building and running game...")
    sted.build_and_run_stuge(True)
    game_hidden_editor_status()


def run_cb():
    game_editor_status("Running game...")
    sted.run_stuge()
    game_hidden_editor_status()


def clean_cb():
    game_editor_status("Cleaning...")
    sted.clean_stuge(True)
    game_hidden_editor_status()


def game_name_cb():
    DB.setConfig("GAME_NAME", dpg.get_value("game_name"))
    game_modified()


def game_default_width_cb():
    DB.setConfig("GAME_DEFAULT_WIDTH", dpg.get_value("game_default_width"))
    game_modified()


def game_default_height_cb():
    DB.setConfig("GAME_DEFAULT_HEIGHT", dpg.get_value("game_default_height"))
    game_modified()


def save_cb():
    sted.GAME_MODIFIED = False
    sted.GAME_WAS_MODIFIED = True
    DB.writeConfigHeader()
    dpg.configure_item("game_modified", show=False)


dpg.create_context()

with dpg.window(tag="MainWindow"):
    if sted.insideStugeSRC():
        with dpg.group(horizontal=True):
            dpg.add_text(f"Sted v{sted.VERSION} |")
            dpg.add_button(label="Build", callback=build_cb)
            dpg.add_button(label="Rebuild", callback=rebuild_cb)
            dpg.add_button(label="Build and run", callback=build_and_run_cb)
            dpg.add_button(label="Run", callback=run_cb)
            dpg.add_button(label="Clean .o files", callback=clean_cb)
            with dpg.group(tag="ide_status", show=False, horizontal=True):
                dpg.add_text("|")
                dpg.add_text("", tag="label_status")
            with dpg.group(tag="game_modified", show=False, horizontal=True):
                dpg.add_text("|")
                dpg.add_text("Game modified")
                dpg.add_button(label="Save", callback=save_cb)
        with dpg.tab_bar():
            with dpg.tab(label="Game"):
                with dpg.group(horizontal=True):
                    dpg.add_text("Game name:")
                    dpg.add_input_text(tag="game_name",
                                       default_value=DB.getConfig("GAME_NAME"),
                                       hint="Enter a name",
                                       callback=game_name_cb)
                with dpg.group(horizontal=True):
                    dpg.add_text("Game default width:")
                    dpg.add_input_int(tag="game_default_width",
                                      default_value=int(
                                          DB.getConfig("GAME_DEFAULT_WIDTH")),
                                      callback=game_default_width_cb)
                with dpg.group(horizontal=True):
                    dpg.add_text("Game default height:")
                    dpg.add_input_int(tag="game_default_height",
                                      default_value=int(
                                          DB.getConfig("GAME_DEFAULT_HEIGHT")),
                                      callback=game_default_height_cb)
            with dpg.tab(label="About"):
                dpg.add_text("Sted - The Stuge editor")
                dpg.add_text(f"Version: {sted.VERSION}")
                dpg.add_text("")
                dpg.add_text(
                    "Sted is the official and easy-to-use editor for the Stuge engine."
                )
                dpg.add_text("Developed in Python3 with DearPyGui.")
                dpg.add_text("")
                dpg.add_text(
                    "Any problem, please report it here: https://github.com/StunxFS/stuge"
                )
                dpg.add_text("")
                dpg.add_text(
                    "Copyright (C) 2022 StunxFS. All rights reserved.")
    else:
        sted.msgbox("Cannot initialize Sted", "Stuge source code not found")

dpg.create_viewport(title='Sted - The Stuge editor', width=870, height=570)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.set_primary_window("MainWindow", True)

dpg.start_dearpygui()
dpg.destroy_context()

DB.close()
