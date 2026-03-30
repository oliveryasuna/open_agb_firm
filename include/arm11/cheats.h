#pragma once

#include "error_codes.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

Result loadCheats(const char *path);
u32 getCheatCount(void);
const u32 *getCheatData(void);

#ifdef __cplusplus
} // extern "C"
#endif
