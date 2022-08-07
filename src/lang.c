// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "toml/toml.h"

#include "game.h"
#include "lang.h"
#include "utils.h"

#include "data/langs_english.h"
#include "data/langs_spanish.h"

const char* _(const char* key) {
    if (toml_key_exists(gGame.lang_txt, key)) {
        toml_datum_t res = toml_string_in(gGame.lang_txt, key);
        if (res.ok) {
            return res.u.s;
        }
        return "<lang-key-with-null-value>";
    }
    return "<lang-key-not-found>";
}

void LoadLanguage(void) {
    char errbuf[200];
    switch (gGame.lang) {
        case GL_English: {
            gGame.lang_txt = toml_parse(&LANGS_ENGLISH[0], errbuf, sizeof(errbuf));
        }; break;

        case GL_Spanish: {
            gGame.lang_txt = toml_parse(&LANGS_SPANISH[0], errbuf, sizeof(errbuf));
        }; break;
    }
    if (gGame.lang_txt == NULL) {
        RuntimeError(TextFormat("cannot parse language file: %s", &errbuf[0]));
    }
}

char* GL2String(GameLanguage gl) {
    switch (gl) {
        case GL_English: return "ENGLISH";
        case GL_Spanish: return "SPANISH";
    }
    return "unknown language";
}
