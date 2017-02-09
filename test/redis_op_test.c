#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "redis_op.h"
#include "make_log.h"

#define TEST_MOUDLE  "test"
#define REDIS_OP_PROC  "redis"

int main(int argc, char *argv[])
{
    int retn = 0;
    //建立连接
    redisContext* conn = NULL;

    conn = rop_connectdb_nopwd("127.0.0.1", "6379");
    if (conn == NULL) {
        //...
        LOG(TEST_MOUDLE, REDIS_OP_PROC, "rop_connect error\n");
        exit(1);
    }

    //set key
    retn = rop_string_set(conn, "FOO", "BAR");
    if (retn == 0) {
        printf("set succ!\n");
    }


    //get key
    char value[128] = {0};
    retn = rop_string_get(conn, "FOO", value);
    if (retn == 0) {
        printf("get %s = %s\n", "FOO", value);
    }

    //断开连接
    rop_disconnect(conn);

	return 0;
}
