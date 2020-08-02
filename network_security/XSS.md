## XSS攻击

人们经常将跨站脚本攻击（Cross Site Scripting）缩写为CSS，但这会与层叠样式表（Cascading Style Sheets，CSS）的缩写混淆。
因此，有人将跨站脚本攻击缩写为XSS。XSS指插入恶意指令代码到网页，使用户加载并执行攻击者恶意制造的网页程序.

比如网页A有一个form表单.

    <input tyep=text name="my_post" ></input>
    
用户在表单中提交了一段js代码.

    <script>alert("111");</script>
    
那么网页在将`form`提交内容进行反显时,网页就会弹出`alert`框体.

#### XSS攻击的防御

严格验证用户输出,输出用户提交数据前也需要进行验证.禁止用户提交恶意脚本.