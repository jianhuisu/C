## 跨站请求伪造

`CSRF（Cross-site request forgery）`攻击者盗用了你的身份，以你的名义发送恶意请求

攻击模式:要完成一次CSRF攻击，受害者必须依次完成两个步骤

 1. 登录受信任网站A，并在本地生成Cookie.
 2. 在不登出站点A的情况下，访问危险网站B.站点B中包含了伪造的可以请求站点A的恶意请求,此时可以利用A在浏览器中缓存的`cookie`.

例子

站点A的服务端验证代码:
    
    转账API: http://www.myBank.com/Transfer.php
    <?php
    　　　　session_start();
    　　　　if (isset($_POST['toBankId'] &&　isset($_POST['money']))
    　　　　{
    　　　　    buy_stocks($_POST['toBankId'],　$_POST['money']);
    　　　　}
    　　?>

危险网站B的`js`伪造请求表单.
    
    <html>
    　　<head>
    　　　　<script type="text/javascript">
    　　　　　　function steal()
    　　　　　　{
              　　　　 iframe = document.frames["steal"];
    　　     　　      iframe.document.Submit("transfer");
    　　　　　　}
    　　　　</script>
    　　</head>
    
    　　<body onload="steal()">
    　　　　<iframe name="steal" display="none">
    　　　　　　<form method="POST" name="transfer"　action="http://www.myBank.com/Transfer.php">
    　　　　　　　　<input type="hidden" name="toBankId" value="11">
    　　　　　　　　<input type="hidden" name="money" value="1000">
    　　　　　　</form>
    　　　　</iframe>
    　　</body>
    </html>
    
如果用户点击了恶意网站B的连接,那么自己的存款将会被转移.CSRF攻击是利用了受站点A信任的cookie,从而绕过身份验证机制.
(因为平时为了保证站点30天内登陆状态,会将一些身份认证信息存储在cookie中).

#### CSRF的防御

客户端页面增加伪随机数
服务端核对令牌：
    
step.1  服务端在cookie中存储一个随机值. 
    
    <?php
        $value = “DefenseSCRF”;
        setcookie(”key”, $value, time()+3600);
    ?>
    
step.2 对该cookie值进行信息摘要,例如使用`md5()`算法加密.这个算法是防御csrf的核心部分.如果你的算法暴露了,那么恶意网站就可以使用js在客户端
实现一套同样的算法.这意味着`B`,可以根据你cookie里面存储的加密前的`原始串`进而得出模拟表单中的`hash value`.
       
    <?php
    　　$hash = md5($_COOKIE['key']);
    ?>
    <form method=”POST” action=”transfer.php”>
        <input type=”text” name=”toBankId”>
        <input type=”text” name=”money”>
        <input type=”hidden” name=”hash” value=”<?=$hash;?>”>
        <input type=”submit” name=”submit” value=”Submit”>
    </form>

step.3  站点A的服务端对cookie中的加密前的原始串应用生成`表单hash value`时同样的算法,验证表单中的hash值是否为自己颁发的.加密过程隐藏在服务端,客户端难以伪造. 

    <?php
    
        $hash = md5($_COOKIE['key']);
    　　 if($_POST['hash'] == $hash) {
    　　  doJob();
        } else {
            return error("csrf验证失败");
    　　 }
    ?>