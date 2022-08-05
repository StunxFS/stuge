// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_UTILS_H
#define STUGE_UTILS_H

#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

void RuntimeError(const char* msg);

#endif // STUGE_UTILS_H
