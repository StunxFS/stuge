// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_LANG_H
#define STUGE_LANG_H

#define LANGUAGE_OPTIONS_SIZE 2
const char* LANGUAGE_OPTIONS[LANGUAGE_OPTIONS_SIZE];

void LoadLanguage(void);
const char* _(const char* key);

#endif // STUGE_LANG_H
