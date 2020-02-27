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
- 会话缓存(hash table) ,完美利用hash算法带来的便利性

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

### 分布式锁
        
分布式环境中使用线程来代表分布式锁的竞争者角色稍微有点不恰当了,使用客户端来称呼更合适,以下内容翻译自redis官方    

_SETNX can be used, and was historically used, as a locking primitive. For example, to acquire the lock of the key foo, the client could try the following:_

SETNX可以被用(曾经被)来作锁定原语,例如,要对资源foo进行加锁,客户端可以执行如下操作

    SETNX lock.foo <current Unix time + lock timeout + 1>

_If SETNX returns 1 the client acquired the lock, setting the lock.foo key to the Unix time at which the lock should no longer be considered valid. The client will later use DEL lock.foo in order to release the lock._

如果SETNX返回1代表客户端加锁成功,将锁的值设置为一个时间戳,该时间戳代表超过这个时间以后,该锁可以被释放(可以被加锁客户端释放,也可以被其它客户端释放)

_If SETNX returns 0 the key is already locked by some other client. We can either return to the caller if it's a non blocking lock, or enter a loop retrying to hold the lock until we succeed or some kind of timeout expires._

如果SETNX返回0代表客户端加锁失败,该锁被其它客户端持有使用,当前调用客户端可以选择立即返回或者采取一些合适的方法尝试重新获取锁的使用权.

_When this happens we can't just call DEL against the key to remove the lock and then try to issue a SETNX,
 as there is a race condition here, when multiple clients detected an expired lock and are trying to release it._
 
当其它客户端发现该锁已经过期时,不能仅仅使用`del + setnx`这一组命令去`释放+获取`该锁,因为这里存在竞争条件

_C1 and C2 read lock.foo to check the timestamp, because they both received 0 after executing SETNX, 
as the lock is still held by C3 that crashed after holding the lock._

当客户端C1 C2使用 setnx 获取 lock.foo 锁时,发现这个锁被其它客户端持有(假设 lock.foo 目前仍被一个异常终止的客户端C3持有)
 
    C1 sends DEL lock.foo
    C1 sends SETNX lock.foo and it succeeds
    
    C2 sends DEL lock.foo
    C2 sends SETNX lock.foo and it succeeds
    
_ERROR: both C1 and C2 acquired the lock because of the race condition._

此时C1 C2 两个客户端都以为自己获得了 lock.foo 的持有权,这里就产生了错误.**幸运的是**,我们可以采用以下方式来规避上述问题

    C4 发送 GETSET lock.foo <current Unix timestamp + lock timeout + 1>

_Because of the GETSET semantic, C4 can check if the old value stored at key is still an expired timestamp. If it is, the lock was acquired._

GETSET 命令允许将`get``set`两个原子性操作一次性完成,新值覆盖旧值,并返回旧值,并且GETSET也是是原子性的.

    这是 GETSET 的返回值描述： the old value stored at key, or nil when key did not exist.
        
    127.0.0.1:6379> keys *
    (empty list or set)
    127.0.0.1:6379> getset name 99
    (nil)
    127.0.0.1:6379> get name
    "99"

如果该调用的返回值(一个unix_timestamp)已经过期,那么恭喜C4,获得了 lock.foo 的持有权,如果返回值是 nil,同样恭喜C4获得了 lock.foo 的持有权,此时返回的时间戳不是一个过期时间戳,
那么很不幸C4将deadlock的`unix_timestamp`又延长一些,有意思的是这对于一个deadlock来讲又无关紧要.

如果此时另外一个Client C5调用GETSET,C5的GETSET落后于C4的GETSET,却先于C4返回到caller处,C5就可以知道,它仍然没有获得 lock.foo 的使用权,是继续等待还是另作它想则取决于C5的编写者了.

_In order to make this locking algorithm more robust,_

为了保障锁的使用算法更加`健壮`,
 
_a client holding a lock should always check the timeout didn't expire before unlocking the key with DEL_

锁的持有者必须确保在调用DEL释放锁之前,锁中存储的`unix_timestamp`都不会过期 

_because client failures can be complex, not just crashing but also blocking a lot of time against some operations and trying to issue DEL after a lot of time (when the LOCK is already held by another client)._

造成deadlock的原因有很多种,客户端异常只是其中之一,比如一个试图去`释放`一个因为自己`阻塞了太长时间`而不再属于自己的`lock`的客户端. 

!!!注意!!!:

_The following pattern is discouraged in favor of the Redlock algorithm which is only a bit more complex to implement,but offers better guarantees and is fault tolerant._

 下面这种设计模式并不推荐用来实现redis分布式锁。应该参考`the Redlock algorithm`(https://redis.io/topics/distlock)的实现，这个方法只是复杂一点，但是却能保证更好的使用效果。
 (上面断句应该从`discouraged`与`in favor of`中间)

_We document the old pattern anyway because certain existing implementations link to this page as a reference._

官方文档中标注这种设计模式是因为很多现存的实现方式需要链接这个页面作为参考

_Moreover it is an interesting example of how Redis commands can be used in order to mount programming primitives._
 
而且,这也是一个展示如何使用Redis命令来[装载/挂载]编程原语的有趣的例子.
 
_Anyway even assuming a single-instance locking primitive,starting with 2.6.12 it is possible to create a much simpler locking primitive, equivalent to the one discussed here,_

从2.6.12起可以使用更简单的锁定原语,等价于刚才的实现效果
 
_using the SET command to acquire the lock, and a simple Lua script to release the lock. The pattern is documented in the SET command page._

使用SET加锁,Lua脚本释放锁,这种模式在SET页面(指官方网站中的页面)已经标注.

_That said, SETNX can be used, and was historically used, as a locking primitive._
 
 ... ...  
  
#### redis配合Lua保证操作的原子性

    
EVAL的第一个参数是一段 Lua 5.1 脚本程序。 这段Lua脚本不需要（也不应该）定义函数。它运行在 Redis 服务器中。

EVAL的第二个参数是参数的个数，后面的参数（从第三个参数），表示在脚本中所用到的那些 Redis 键(key)，这些键名参数可以在 Lua 中通过全局变量 KEYS 数组，用 1 为基址的形式访问( KEYS[1] ， KEYS[2] ，以此类推)。

在命令的最后，那些不是键名参数的附加参数 arg [arg …] ，可以在 Lua 中通过全局变量 ARGV 数组访问，访问的形式和 KEYS 变量类似( ARGV[1] 、 ARGV[2] ，诸如此类)。    
    
    127.0.0.1:6379> eval "return {KEYS[1],KEYS[2],ARGV[1],ARGV[2]}" 2 key1 key2 first second1) "key1"2) "key2"3) "first"4) "second"
    
相当于把加锁/释放锁的核心算法封装为一串Lua代码,发送到redis服务端,redis服务端会将该脚本中的一系列操作视为一个整体操作,并保证其调用的原子性,这也是一个不错的解决方案.    

#### 更好的方式 Redlock

官方推荐了一套 Redlock algorithm 算法,可以参考以下,平时在使用的时候,如果并发量比较大,还是建议使用一些成熟分布式锁应用来实现分布式锁的控制,比如ZooKeeper...


























 












