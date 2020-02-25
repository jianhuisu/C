## redis的应用场景

### 计数器

INCR和EXPIRE配合来达到只在规定的生存时间内进行计数(counting)的目的

#### 接口限流计数器[http api | 中间件]
    
日常的开放平台API一般常有限流，利用redis的incr命令可以实现一般的限流操作。如限制用户对某接口每分钟请求次数上限1000次
因为没有办法保证用户匀速调用API,所以采用划分时间窗口来计算调用速率

常见的限流算法

 - 令牌桶算法(Token Bucket)  使流量以比较均匀的速度向外发送;允许突发数据的发送
 - 漏桶算法(Leaky Bucket)    不允许突发数据传送 漏桶算法强制一个常量的输出速率而不管输入数据流的突发性

伪码实现漏桶算法(来自yii框架)
    
    getRateLimit()：返回允许的请求的最大数目及时间，例如，[1000, 60] 表示在 60 秒内最多 1000 次的 API 调用。
    loadAllowance()：返回剩余的允许的请求和最后一次速率限制检查时相应的UNIX时间戳数。
    saveAllowance()：保存剩余的允许请求数和当前的UNIX时间戳。    
   
    
    // $window    = 60s  $limit     = 1000
    list($limit, $window) = $user->getRateLimit($request, $action);
    list($allowance, $timestamp) = $user->loadAllowance($request, $action);
    
    $current = time();
    
    $allowance += (int) (($current - $timestamp) * $limit / $window);
    if ($allowance > $limit) {
       $allowance = $limit;
    }
    
    if ($allowance < 1) {
       $user->saveAllowance($request, $action, 0, $current);
       $this->addRateLimitHeaders($response, $limit, 0, $window);
       throw new TooManyRequestsHttpException($this->errorMessage);
    }
    
    $user->saveAllowance($request, $action, $allowance - 1, $current);
    $this->addRateLimitHeaders($response, $limit, $allowance - 1, (int) (($limit - $allowance + 1) * $window / $limit));

个人感觉漏桶与令牌桶最明显的区别是

- 令牌桶输出速率可以变化 , 令牌以恒定速率颁发,可以以任意速度消耗 就像嗑瓜子 不停的磕,累积到一堆以后可以一口吃光(当然：累积时间是有限制的,着要是磕个一年两年谁受的了)
- 漏桶输出速率恒定 ,溢出的请求则拒绝或丢弃 就像嗑瓜子 不停的磕,虽然累积了一堆,但是一口只允许吃N个,多余的都被狗吃了

#### 实现幂等性操作 

为了防止重复消费,撞单,刷单,限制五分钟之内只能有一次付款操作

    $redisKey = "api_name_" + $api;
    $count = $this->redis->incr($redisKey);
    if ($count == 1) {
        $this->redis->expire($redisKey,1);
    }
    if (count > 200) {
        return false;
    }
    
### 缓存

Redis和MongoDB是当下应用最广泛的NoSQL产品，当然如果系统里的写操作居多，也没有必要使用缓存，因此Redis主要用于解决访问性能和并发能力的问题。
高并发系统里有时候单台Redis server不能满足性能需求，Redis 3.0之前的办法是Redis Sentinel，多个节点同时提供服务，并且每个节点都保存全量数据，
Redis 3.0之后引入了Redis Cluster，通过数据分片（Data Sharding）在每个节点上只保留部分数据（总共有16384个slot）来实现高可用。

Redis Cluster采用无中心节点方式实现，客户端直接与redis集群的每个节点连接，客户请求到达节点之后，
使用统一的哈希算法，CRC16(key)%16384，计算出key对应的slot，然后从Redis Cluster定位出具体的server，具体的data sharding，最终将数据返回给用户 。

但由于Redis的事务仅能解决单台server上的ACID问题，对于多台server常见的问题是多个请求针对同一个key的操作一致性问题，需要结合Zookeeper使用分布式锁的机制解决一致性问题和顺序操作问题。

哪些数据适合缓存

- 访问量较大的热点数据
- 生成过程耗时长 比如一些CRM系统中的报表数据,一些业务数据经过复杂分析计算的结果集
- session(hash table) ,完美利用hash算法带来的便利性

缓存穿透/缓存雪崩解决思路

 - 避免缓存集体失效,为缓存随即设置过期时间
 - 当大量缓存穿透到数据库层时,对查询操作进行去重,排队操作
 - 后台单起服务负责更新将要过期的缓存
 - 多级缓存

### 排行榜/带权重的消息队列
     
Scenario 1: The higher the user scores, the higher the ranking. In the same score case, redis uses dictionary sort
            
Scenario 2: User games take the shortest time, ranking ahead
            
Scenario 3: The higher the user’s score, the higher the ranking. If the score is the same, the user who first achieves the score is in front of the ranking.
             
Scenario 2: The shortest time for the user to complete the game is ahead of the queue. If the time for completing the game is the same, the user who reaches the record first is ahead of the queue.    

    We can subtract the time stamp from the same large number MAX (e.g. 5000000000 000). 
    The smaller the time stamp, the greater the difference. 
    So we can change the structure of score to:Fractions +’+ (MAX-timestamp)So we can meet our needs.
    If you use integers as scores, one thing to note is that the largest integer in JS is.
    Therefore, the best score structure is: fraction +’.’+ timestamp, which becomes floating-point number.
    
    Score.timestamp : 
        User1: 100.(Max - 145454565657)
        User2: 100.(Max - 145454565658)
    
change the user’s score composition.
    
    Score.timestamp : 
    User1: 100.145454565657
    User2: 101.145454565657

https://developpaper.com/tips-for-using-redis-to-rank/

### 好友关系
    
    
