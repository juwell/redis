/*
 * ѹ���б�
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

#ifndef _ZIPLIST_H
#define _ZIPLIST_H

#define ZIPLIST_HEAD 0
#define ZIPLIST_TAIL 1

/* Each entry in the ziplist is either a string or an integer. */
typedef struct {
    /* When string is used, it is provided with the length (slen). */
    unsigned char *sval;
    unsigned int slen;
    /* When integer is used, 'sval' is NULL, and lval holds the value. */
    long long lval;
} ziplistEntry;

// ����һ���µ�ѹ���б�, O(1)
unsigned char *ziplistNew(void);
unsigned char *ziplistMerge(unsigned char **first, unsigned char **second);
// ����һ����������ֵ���½ڵ�, ��������½ڵ���ӵ�ѹ���б�ı�ͷ���β, ƽ��O(N), �O(N*N)
unsigned char *ziplistPush(unsigned char *zl, unsigned char *s, unsigned int slen, int where);
// ����ѹ���б���������ϵĽڵ�, O(N)
unsigned char *ziplistIndex(unsigned char *zl, int index);
// ���ظ����ڵ����һ���ڵ�, O(1)
unsigned char *ziplistNext(unsigned char *zl, unsigned char *p);
// ���ظ����ڵ����һ���ڵ�, O(1)
unsigned char *ziplistPrev(unsigned char *zl, unsigned char *p);
// ��ȡ�����ڵ��������ֵ, O(1)
unsigned int ziplistGet(unsigned char *p, unsigned char **sval, unsigned int *slen, long long *lval);
// ����������ֵ���½ڵ���뵽�����ڵ�, ƽ��O(N), �O(N*N)
unsigned char *ziplistInsert(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen);
// ��ѹ���б���ɾ�������ڵ�, ƽ��O(N), �O(N*N)
unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p);
// ɾ��ѹ���б��ڸ��������ϵ���������ڵ�, ƽ��O(N), �O(N*N)
unsigned char *ziplistDeleteRange(unsigned char *zl, int index, unsigned int num);
unsigned char *ziplistReplace(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen);
unsigned int ziplistCompare(unsigned char *p, unsigned char *s, unsigned int slen);
// ��ѹ���б��в��Ҳ����ذ����˸���ֵ�Ľڵ�
// ��Ϊ�ڵ��ֵ������һ���ֽ�����, ���Լ��ڵ�ֵ�͸���ֵ�Ƿ���ͬ�ĸ��Ӷ�ΪO(N)
// ���������б�ĸ��Ӷ�ΪO(N*N)
unsigned char *ziplistFind(unsigned char *zl, unsigned char *p, unsigned char *vstr, unsigned int vlen, unsigned int skip);
// ����ѹ���б�Ŀǰ�����Ľڵ�����, �ڵ���С��65535ʱΪO(1), ����65535ʱΪO(N)
unsigned int ziplistLen(unsigned char *zl);
// ����ѹ���б�Ŀǰռ�õ��ڴ��ֽ���, O(1)
size_t ziplistBlobLen(unsigned char *zl);
void ziplistRepr(unsigned char *zl);
typedef int (*ziplistValidateEntryCB)(unsigned char* p, void* userdata);
int ziplistValidateIntegrity(unsigned char *zl, size_t size, int deep,
                             ziplistValidateEntryCB entry_cb, void *cb_userdata);
void ziplistRandomPair(unsigned char *zl, unsigned long total_count, ziplistEntry *key, ziplistEntry *val);
void ziplistRandomPairs(unsigned char *zl, unsigned int count, ziplistEntry *keys, ziplistEntry *vals);
unsigned int ziplistRandomPairsUnique(unsigned char *zl, unsigned int count, ziplistEntry *keys, ziplistEntry *vals);

#ifdef REDIS_TEST
int ziplistTest(int argc, char *argv[]);
#endif

#endif /* _ZIPLIST_H */
