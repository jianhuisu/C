未显式指定key的过期时间,该key默认永久存储

ttl demo_key

In Redis 2.6 or older the command returns -1 if the key does not exist or if the key exist but has no associated expire.

Starting with Redis 2.8 the return value in case of error changed:
- The command returns -2 if the key does not exist.
- The command returns -1 if the key exists but has no associated expire.

EXPIRE demo_key integer_expire_seconds_num
expire demo_key 10  // expire 10 seconds

    redis> SET mykey "Hello"
    "OK"
    redis> EXPIRE mykey 10
    (integer) 1
    redis> TTL mykey
    (integer) 10
    redis>

## zset

    127.0.0.1:6379[1]> zadd page_rank 10 google.com
    (integer) 0
    127.0.0.1:6379[1]> zadd page_rank 7 baidu.com
    (integer) 1
    127.0.0.1:6379[1]> zadd page_rank 9 bing.com
    (integer) 1
    127.0.0.1:6379[1]> zrange page_rank 0 -1 
    1) "baidu.com"
    2) "bing.com"
    3) "google.com"
    127.0.0.1:6379[1]> zrange page_rank 0 -1 withscores
    1) "baidu.com"
    2) "7"
    3) "bing.com"
    4) "9"
    5) "google.com"
    6) "10"
    127.0.0.1:6379[1]> zcount page_bank
    (error) ERR wrong number of arguments for 'zcount' command
    127.0.0.1:6379[1]> zcount page_bank 0 10
    (integer) 0
    127.0.0.1:6379[1]> zcount page_bank 1 10
    (integer) 0
    127.0.0.1:6379[1]> 
    127.0.0.1:6379[1]> 
    127.0.0.1:6379[1]> 
    127.0.0.1:6379[1]> 
    127.0.0.1:6379[1]> zadd page_rank 10 alibaba.com
    (integer) 1
    127.0.0.1:6379[1]> zrange page_rank 0 -1
    1) "baidu.com"
    2) "bing.com"
    3) "alibaba.com"
    4) "google.com"
    127.0.0.1:6379[1]> 
    127.0.0.1:6379[1]> ZREVRANK page_rank google.com
    (integer) 0
    127.0.0.1:6379[1]> ZREVRANK page_rank baidu.com
    (integer) 3
    127.0.0.1:6379[1]> zrevrank page_rank alibaba.com
    (integer) 1
    127.0.0.1:6379[1]> zrevrank page_rank google.com
    (integer) 0
    127.0.0.1:6379[1]> zscore page_rank bing.com
    "9"
    127.0.0.1:6379[1]> 
    127.0.0.1:6379[1]> zrank page_rank
    (error) ERR wrong number of arguments for 'zrank' command
    127.0.0.1:6379[1]> zrank page_rank google.com
    (integer) 3
    127.0.0.1:6379[1]> zrank page_rank alibaba.com
    (integer) 2
    127.0.0.1:6379[1]> zrank page_rank bing.com
    (integer) 1
    127.0.0.1:6379[1]> zrank page_rank baidu.com
    (integer) 0
