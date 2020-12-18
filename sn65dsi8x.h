#ifndef SN65DSI8X_H
#define SN65DSI8X_H

#include <linux/slab.h>

#define REGISTER_0x09                   0x09
#define REGISTER_0x0A                   0x0A
#define REGISTER_0x0B                   0x0B
#define REGISTER_0x0D                   0x0D
#define REGISTER_0x10                   0x10
#define REGISTER_0x11                   0x11
#define REGISTER_0x12                   0x12
#define REGISTER_0x13                   0x13
#define REGISTER_0x18                   0x18
#define REGISTER_0x19                   0x19
#define REGISTER_0x1A                   0x1A
#define REGISTER_0x1B                   0x1B
#define REGISTER_0x20                   0x20
#define REGISTER_0x21                   0x21
#define REGISTER_0x22                   0x22
#define REGISTER_0x23                   0x23
#define REGISTER_0x24                   0x24
#define REGISTER_0x25                   0x25
#define REGISTER_0x26                   0x26
#define REGISTER_0x27                   0x27
#define REGISTER_0x28                   0x28
#define REGISTER_0x29                   0x29
#define REGISTER_0x2A                   0x2A
#define REGISTER_0x2B                   0x2B
#define REGISTER_0x2C                   0x2C
#define REGISTER_0x2D                   0x2D
#define REGISTER_0x2E                   0x2E
#define REGISTER_0x2F                   0x2F
#define REGISTER_0x30                   0x30
#define REGISTER_0x31                   0x31
#define REGISTER_0x32                   0x32
#define REGISTER_0x33                   0x33
#define REGISTER_0x34                   0x34
#define REGISTER_0x35                   0x35
#define REGISTER_0x36                   0x36
#define REGISTER_0x37                   0x37
#define REGISTER_0x38                   0x38
#define REGISTER_0x39                   0x39
#define REGISTER_0x3A                   0x3A
#define REGISTER_0x3B                   0x3B
#define REGISTER_0x3C                   0x3C
#define REGISTER_0x3D                   0x3D
#define REGISTER_0x3E                   0x3E

#define VALUE_REGISTER_0x09              0x00
#define VALUE_REGISTER_0x0A              0x03
#define VALUE_REGISTER_0x0B              0x28
#define VALUE_REGISTER_0x0D              0x00
#define VALUE_REGISTER_0x10              0x26
#define VALUE_REGISTER_0x11              0x00
#define VALUE_REGISTER_0x12              0x36
#define VALUE_REGISTER_0x13              0x00
#define VALUE_REGISTER_0x18              0x6c
#define VALUE_REGISTER_0x19              0x00
#define VALUE_REGISTER_0x1A              0x03
#define VALUE_REGISTER_0x1B              0x00
#define VALUE_REGISTER_0x20              0xc0
#define VALUE_REGISTER_0x21              0x03
#define VALUE_REGISTER_0x22              0x00
#define VALUE_REGISTER_0x23              0x00
#define VALUE_REGISTER_0x24              0xd0
#define VALUE_REGISTER_0x25              0x02
#define VALUE_REGISTER_0x26              0x00
#define VALUE_REGISTER_0x27              0x00
#define VALUE_REGISTER_0x28              0x21
#define VALUE_REGISTER_0x29              0x00
#define VALUE_REGISTER_0x2A              0x00
#define VALUE_REGISTER_0x2B              0x00
#define VALUE_REGISTER_0x2C              0x0c
#define VALUE_REGISTER_0x2D              0x00
#define VALUE_REGISTER_0x2E              0x00
#define VALUE_REGISTER_0x2F              0x00
#define VALUE_REGISTER_0x30              0x02
#define VALUE_REGISTER_0x31              0x00
#define VALUE_REGISTER_0x32              0x00
#define VALUE_REGISTER_0x33              0x00
#define VALUE_REGISTER_0x34              0x10
#define VALUE_REGISTER_0x35              0x00
#define VALUE_REGISTER_0x36              0x05
#define VALUE_REGISTER_0x37              0x00
#define VALUE_REGISTER_0x38              0x10
#define VALUE_REGISTER_0x39              0x00
#define VALUE_REGISTER_0x3A              0x1f
#define VALUE_REGISTER_0x3B              0x00
#define VALUE_REGISTER_0x3C              0x10
#define VALUE_REGISTER_0x3D              0x00
#define VALUE_REGISTER_0x3E              0x00

struct sn65dsi8x_params_t {
    u8 reg;
    u8 value;
};

struct sn65dsi8x_params_t sn65dsi8x_parameters[] = {
    {REGISTER_0x09, VALUE_REGISTER_0x09},
    {REGISTER_0x0A, VALUE_REGISTER_0x0A},
    {REGISTER_0x0B, VALUE_REGISTER_0x0B},
    {REGISTER_0x0D, VALUE_REGISTER_0x0D},
    {REGISTER_0x10, VALUE_REGISTER_0x10},
    {REGISTER_0x11, VALUE_REGISTER_0x11},
    {REGISTER_0x12, VALUE_REGISTER_0x12},
    {REGISTER_0x13, VALUE_REGISTER_0x13},
    {REGISTER_0x18, VALUE_REGISTER_0x18},
    {REGISTER_0x19, VALUE_REGISTER_0x19},
    {REGISTER_0x1A, VALUE_REGISTER_0x1A},
    {REGISTER_0x1B, VALUE_REGISTER_0x1B},
    {REGISTER_0x20, VALUE_REGISTER_0x20},
    {REGISTER_0x21, VALUE_REGISTER_0x21},
    {REGISTER_0x22, VALUE_REGISTER_0x22},
    {REGISTER_0x23, VALUE_REGISTER_0x23},
    {REGISTER_0x24, VALUE_REGISTER_0x24},
    {REGISTER_0x25, VALUE_REGISTER_0x25},
    {REGISTER_0x26, VALUE_REGISTER_0x26},
    {REGISTER_0x27, VALUE_REGISTER_0x27},
    {REGISTER_0x28, VALUE_REGISTER_0x28},
    {REGISTER_0x29, VALUE_REGISTER_0x29},
    {REGISTER_0x2A, VALUE_REGISTER_0x2A},
    {REGISTER_0x2B, VALUE_REGISTER_0x2B},
    {REGISTER_0x2C, VALUE_REGISTER_0x2C},
    {REGISTER_0x2D, VALUE_REGISTER_0x2D},
    {REGISTER_0x2E, VALUE_REGISTER_0x2E},
    {REGISTER_0x2F, VALUE_REGISTER_0x2F},
    {REGISTER_0x30, VALUE_REGISTER_0x30},
    {REGISTER_0x31, VALUE_REGISTER_0x31},
    {REGISTER_0x32, VALUE_REGISTER_0x32},
    {REGISTER_0x33, VALUE_REGISTER_0x33},
    {REGISTER_0x34, VALUE_REGISTER_0x34},
    {REGISTER_0x35, VALUE_REGISTER_0x35},
    {REGISTER_0x36, VALUE_REGISTER_0x36},
    {REGISTER_0x37, VALUE_REGISTER_0x37},
    {REGISTER_0x38, VALUE_REGISTER_0x38},
    {REGISTER_0x39, VALUE_REGISTER_0x39},
    {REGISTER_0x3A, VALUE_REGISTER_0x3A},
    {REGISTER_0x3B, VALUE_REGISTER_0x3B},
    {REGISTER_0x3C, VALUE_REGISTER_0x3C},
    {REGISTER_0x3D, VALUE_REGISTER_0x3D},
    {REGISTER_0x3E, VALUE_REGISTER_0x3E}
};

#endif