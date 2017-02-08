#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <hiredis.h>

int main(int argc, char *argv[])
{
    
    redisContext *c;
    redisReply *reply;

    //创建一个服务器句柄
    c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    //执行一个指令
    reply = redisCommand(c, "SET %s %s", "itcast", "nihao");
    if (reply == NULL) {
        printf("redisCommand set error\n");
        exit(1);
    }
    if (strcmp(reply->str, "OK") == 0) {
        printf("set itcast nihao  ok\n");
    }
    freeReplyObject(reply);
	printf("hehehe!");
	//执行get指令
	reply = redisCommand(c, "GET %s", "itcast");
    if (reply == NULL) {
        printf("redisCommand get error\n");
        exit(1);
    }
    printf("get itcast = %s\n", reply->str);
    freeReplyObject(reply);

    //释放服务器句柄
    redisFree(c);

        return 0;
}
