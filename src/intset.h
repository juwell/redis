/*
 * 整数集合
 * 
 * Copyright (c) 2009-2012, Pieter Noordhuis <pcnoordhuis at gmail dot com>
 * Copyright (c) 2009-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __INTSET_H
#define __INTSET_H
#include <stdint.h>

// 整数集合
typedef struct intset {
    // 编码方式
    // 可选值为(在inset.c中定义): INTSET_ENC_INT16, INTSET_ENC_INT32, INTSET_ENC_INT64
    uint32_t encoding;
    // 元素个数
    uint32_t length;
    // 元素内容, 虽然是int8_t类型, 但实际类型是根据encoding值来的
    int8_t contents[];
} intset;

// 创建一个新的整数集合, O(1)
intset *intsetNew(void);
// 将给定元素添加到集合里, O(N)
intset *intsetAdd(intset *is, int64_t value, uint8_t *success);
// 删除给定元素, O(N)
intset *intsetRemove(intset *is, int64_t value, int *success);
// 查找给定元素是否存在
// 因为底层为有序数组, 因此可用二分查找法来进行, 因此O(logN)
uint8_t intsetFind(intset *is, int64_t value);
// 从集合中随机返回一个元素, O(1)
int64_t intsetRandom(intset *is);
// 取出指定索引位上的元素, O(1)
uint8_t intsetGet(intset *is, uint32_t pos, int64_t *value);
// 返回集合中元素的个数, O(1)
uint32_t intsetLen(const intset *is);
// 返回集合占用的内存字节数, O(1)
size_t intsetBlobLen(intset *is);
int intsetValidateIntegrity(const unsigned char *is, size_t size, int deep);

#ifdef REDIS_TEST
int intsetTest(int argc, char *argv[]);
#endif

#endif // __INTSET_H
