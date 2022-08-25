// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_UTILS_H
#define STUGE_UTILS_H

#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

#define FRAME 60
#define FRAMES(count) ((count) * FRAME)

#if _WIN32
    #define PATH_SEPARATOR "\\"
#else
    #define PATH_SEPARATOR "/"
#endif

void RuntimeError(const char* msg);

char* UserHomeDir(void);

char* TextDup(const char* str);
void* MemDup(const void* ptr, int size);

#endif // STUGE_UTILS_H
