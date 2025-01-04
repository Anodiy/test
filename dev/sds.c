#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 模拟 SDS 的结构
typedef struct {
    int len;      // 当前字符串长度
    int alloc;    // 已分配的总容量
    char buf[];   // 实际字符串内容
} sdshdr;

// 创建 SDS
sdshdr* sds_new(const char* init) {
    int init_len = strlen(init);
    sdshdr* sds = (sdshdr*)malloc(sizeof(sdshdr) + init_len + 1);
    sds->len = init_len;
    sds->alloc = init_len;
    memcpy(sds->buf, init, init_len + 1); // 包括 '\0'
    return sds;
}

// 扩容 SDS
sdshdr* sds_append(sdshdr* sds, const char* append) {
    int append_len = strlen(append);
    int new_len = sds->len + append_len;

    // 判断是否需要扩容
    if (new_len > sds->alloc) {
        sds->alloc = (new_len < 1024) ? (new_len * 2) : (new_len + 1024);
        sds = (sdshdr*)realloc(sds, sizeof(sdshdr) + sds->alloc + 1);
    }

    // 追加字符串
    memcpy(sds->buf + sds->len, append, append_len + 1);
    sds->len = new_len;
    return sds;
}

// 释放 SDS
void sds_free(sdshdr* sds) {
    free(sds);
}

int main() {
    // 传统 C 字符串操作
    char* cstr = (char*)malloc(16);  // 初始分配 16 字节
    strcpy(cstr, "Hello");
    printf("C String: %s\n", cstr);

    // 动态扩容模拟
    strcat(cstr, " World!"); // 手动处理内存，可能会导致溢出
    printf("C String After Append: %s\n", cstr);
    free(cstr);

    // SDS 操作
    sdshdr* sds = sds_new("Hello");
    printf("SDS String: %s\n", sds->buf);

    // 自动扩容
    sds = sds_append(sds, " World!");
    printf("SDS String After Append: %s\n", sds->buf);

    // 释放 SDS
    sds_free(sds);
    return 0;
}
