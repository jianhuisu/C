## 跨站请求伪造

`CSRF（Cross-site request forgery）`攻击者盗用了你的身份，以你的名义发送恶意请求

攻击模式:要完成一次CSRF攻击，受害者必须依次完成两个步骤

 1. 登录受信任网站A，并在本地生成Cookie.
 2. 在不登出站点A的情况下，访问危险网站B.站点B中包含了伪造的可以请求站点A的恶意请求,此时可以利用A在浏览器中缓存的`cookie`.

Example.1

攻击情景

原文中Alice是受害者，她使用的一个银行网站`http://unsafe/`存在`session fixation`漏洞，`Mallory`是攻击者，他想盗窃`Alice`的银行中的存款，而`Alice`会点击`Mallory`发给她的网页连接（原因可能是Alice认识Mallory，或者她自己的安全意识不强）.

攻击步骤:

 1. `Hacker:Mallory`访问 `http://unsafe/` 并获得了一个会话`ID（session_id）`，例如服务器返回的形式是：`Set-Cookie: session_id=0D6441FEA4496C2`
 2. `Hacker:Mallory`给`user:Alice`发了一个邮件："我行推出了一项新服务，率先体验请点击：`http://unsafe/?SID=0D6441FEA4496C2`"
 3. `user:Alice`点击并登录了.
 4. 因为服务器的会话ID不改变，现在`Hacker:Mallory`点击 `http://unsafe/?session_id= I_WILL_KNOW_THE_SID`后，他就拥有了`user:Alice`的身份.可以为所欲为了.

防御:

应用自动为每个活跃的用户的会话生成一个 `CSRF「令牌」`.**该令牌用于验证 `经过身份验证的用户` 是否是 `向应用程序发出请求的用户`**.
无论何时，当您在应用程序中定义`HTML`表单时，都应该在表单中包含一个隐藏的`CSRF`标记字段，以便服务端CSRF过滤器可以验证表单中的CSRF令牌是否与会话`session_id`中存储的令牌相同,即使邮件中提前伪造了表单以及盗用了你的身份凭证`session_id`.但是他并不能伪造一个随即的的`CSRF令牌`.所以可以有效的预防上边的情况.除非你的终端被完全劫持.

根据上述实例,开发过程中两个关键的注意事项:

 - 登陆成功以后要更新session_id,验证session_id格式是否合法.
 - 接受到敏感操作时,不单单要验证身份凭证,同时也要验证`经过身份验证的用户`是否是 `向应用程序发出请求的用户`.否则`session_id`暴露就等于登陆权限完全暴露.

#### 其它场景

攻击情景1：最简单：服务器接收任何会话ID.过程如下:

 1. `Hacker:Mallory`发现`http://unsafe/`接收任何会话ID，而且会话ID通过URL地址的查询参数携带到服务器，服务器不做检查
 2. `Hacker:Mallory`给`User:Alice`发送一个电子邮件，他可能假装是银行在宣传自己的新业务，例如，“我行推出了一项新服务，率先体验请点击：`http://unsafe/?SID=  I_WILL_KNOW_THE_SID, I_WILL_KNOW_THE_SID`是`Hacker:Mallory`选定的一个会话ID。
 3. `User:Alice`被吸引了，点击了 `http://unsafe/?SID= I_WILL_KNOW_THE_SID`，像往常一样，输入了自己的帐号和口令从而登录到银行网站。
 4. 因为服务器的会话ID不改变，现在`Hacker:Mallory`点击 `http://unsafe/?SID= I_WILL_KNOW_THE_SID`后，他就拥有了`User:Alice`的身份。可以为所欲为了。

攻击场景2：跨站cookie(cross-site cooking).利用浏览器的漏洞，即使 `http://good` 很安全，但是，由于浏览器管理`cookie`的漏洞，
使恶意网站 `http://evil/` 能够向浏览器发送`http://good `的cookie`。过程如下：

 1. `Hacker:Mallory`给`User:Alice`发送一个邮件"有个有趣的网站：`http://evil` 很好玩，不妨试试"
 2. `User:Alice`访问了这个链接，这个网站将一个会话ID取值为`I_WILL_KNOW_THE_SID` 的`http://good/` 域的`cookie`设置到浏览器中。
 3. `Hacker:Mallory`又给`User:Alice`发了个邮件：“我行推出了一项新服务，率先体验请点击：`http://good/`”
 4. 如果`User:Alice`登录了，`Hacker:Mallory`就可以利用这个ID了



