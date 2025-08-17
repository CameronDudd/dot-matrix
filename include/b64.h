/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef B64_H
#define B64_H

void b64Encode(unsigned char *dst, const unsigned char *src);
void b64Decode(unsigned char *dst, const unsigned char *src);

#endif  // B64_H
