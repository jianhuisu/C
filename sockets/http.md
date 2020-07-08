## http协议

客户端与服务器交互完毕后,客户端主动与服务器断开连接.

#### 请求报文

 - 请求行
 - 请求头
 - 请求体
 
例如
    
    GET /1.txt HTTP/1.1
    host: www.baidu.com
    user-agent: ...
    Accept-Language: en,mi
    //空行
    请求体 
    Form Data:
    
#### 响应报文

 - 响应行
 - 响应头
 - 响应体

例如

    HTTP/1.1 200 OK
    Server: Nginx
    Content-Length: 51
    Content-Type: text/plain
    // 空行
    <html>
        hello world
    <html/>