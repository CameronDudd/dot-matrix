/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "b64.h"

#define PADDING '='

static const unsigned char _b64EncodeTable[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                                                'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                                's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

static const unsigned char _b64DecodeTable[] = {
    ['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,  ['E'] = 4,  ['F'] = 5,  ['G'] = 6,  ['H'] = 7,  ['I'] = 8,  ['J'] = 9,  ['K'] = 10, ['L'] = 11, ['M'] = 12,
    ['N'] = 13, ['O'] = 14, ['P'] = 15, ['Q'] = 16, ['R'] = 17, ['S'] = 18, ['T'] = 19, ['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23, ['Y'] = 24, ['Z'] = 25,
    ['a'] = 26, ['b'] = 27, ['c'] = 28, ['d'] = 29, ['e'] = 30, ['f'] = 31, ['g'] = 32, ['h'] = 33, ['i'] = 34, ['j'] = 35, ['k'] = 36, ['l'] = 37, ['m'] = 38,
    ['n'] = 39, ['o'] = 40, ['p'] = 41, ['q'] = 42, ['r'] = 43, ['s'] = 44, ['t'] = 45, ['u'] = 46, ['v'] = 47, ['w'] = 48, ['x'] = 49, ['y'] = 50, ['z'] = 51,
    ['0'] = 52, ['1'] = 53, ['2'] = 54, ['3'] = 55, ['4'] = 56, ['5'] = 57, ['6'] = 58, ['7'] = 59, ['8'] = 60, ['9'] = 61, ['+'] = 62, ['/'] = 63};

void b64Encode(unsigned char *dst, const unsigned char *src) {
  const unsigned char *end = src;
  while (*end) {
    ++end;
  }
  while ((end - src) >= 3) {
    *dst++ = _b64EncodeTable[src[0] >> 2];
    *dst++ = _b64EncodeTable[((src[0] & 0x03) << 4) | (src[1] >> 4)];
    *dst++ = _b64EncodeTable[((src[1] & 0x0F) << 2) | (src[2] >> 6)];
    *dst++ = _b64EncodeTable[src[2] & 0x3F];
    src += 3;
  }
  if (end - src) {
    *dst++ = _b64EncodeTable[src[0] >> 2];
    if ((end - src) == 1) {
      *dst++ = _b64EncodeTable[(src[0] & 0x03) << 4];
      *dst++ = PADDING;
    } else {
      *dst++ = _b64EncodeTable[((src[0] & 0x03) << 4) | (src[1] >> 4)];
      *dst++ = _b64EncodeTable[((src[1] & 0x0F) << 2)];
    }
    *dst++ = PADDING;
  }
}

void b64Decode(unsigned char *dst, const unsigned char *src) {
  while (*src) {
    unsigned char b0 = _b64DecodeTable[src[0]];
    unsigned char b1 = _b64DecodeTable[src[1]];
    unsigned char b2 = (src[2] == '=') ? 0 : _b64DecodeTable[src[2]];
    unsigned char b3 = (src[3] == '=') ? 0 : _b64DecodeTable[src[3]];
    *dst++           = (b0 << 2) | (b1 >> 4);
    *dst++           = (b1 << 4) | (b2 >> 2);
    *dst++           = (b2 << 6) | b3;
    src += 4;
    if ((src[0] == '\0') || (src[1] == '\0')) {
      break;
    }
  }
}
