#pragma once

#include <vector>
#include <cstdint>

using namespace std;

/// 8-bit unsigned integer
typedef uint8_t u8;
/// 16-bit unsgined integer
typedef uint16_t u16;
/// 32-bit unsigned integer
typedef uint32_t u32;
/// 64-bit unsigned integer
typedef uint64_t u64;

/// Block size constant container
namespace BlockSize
{
    typedef u32 BLOCK_128;
    typedef u64 BLOCK_256;
}; // namespace BlockWordSize

/// Abstract block cipher interface
template<class T> class CipherInterface
{
    virtual size_t block_size() { return sizeof(T); }
};

template<class T> static inline size_t block_byte_size() { return sizeof(T) * 4; }
