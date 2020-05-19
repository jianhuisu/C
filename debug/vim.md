## vim 

##### zhe die

    zc
    zo

##### 取消高亮显示

vim编辑器里出现高亮显示，看着很不舒服，取消方式:

    ：noh
    ：/aaa (随便的字母或数字都可)

##### vim选中多行批量缩进

under command mode : `shift+v`选中行, `shift + >`进行缩进

##### 块编辑

使用案例：多行注释

 1. 在`nomal`模式下按下Ctrl+v, 然后选择你要添加的行数（可以直接 行数+G 过去）
 1. 选择好以后按大写的I ,则光标会自动跳转到所选择行的第一行行首，并会进入到insert模式，可以输入你想要插入的内容。比如“#”
 1. 输入完你想要插入的数据后，按下Esc键，则你会发现刚刚你选择的行的行首已经插入了你想要的内容。
 1. 如果你想要删除注释行的“#”，只需要`Ctrl+v`选中多行的“#”，让后按`Delete`键删除即可。

multiple add new character
 
 1. 按一下 【ctrl + V 】，观察编辑器左下角状态栏 显示 Visual Block
 1. 移动光标 ，编辑器出现反白
 1. 按 y 进行复制 ，反白消失
 1. 移动光标，命令模式下 按 【p】 ，粘贴


##### 多窗口编辑

- sp {filename}
- 按一下【ctrl+w】 然后 按 j 向上一个窗口移动光标
- 按一下【ctrl+w】 然后 按 k 向下一个窗口移动光标
- 按一下【ctrl+w】 然后 按 q 退出光标不在的窗口

##### 飞速翻页

命令模式下

- 【ctrl + f】  上一页
- 【ctrl + b】  下一页
-  G            页尾
-  1G           页首
-  nG           第N行

##### 撤销、反撤销

命令模式下

- u 撤销
- ctrl + r 反撤销

##### 内容搜索、替换

###### vim 中可用 :s 命令来替换字符串，具体如下：

- :s/str1/str2/ 替换当前行第一个 str1 为 str2
- :s/str1/str2/g 替换当前行中所有 str1 为 str2
- :m,ns/str1/str2/ 替换第 n 行开始到最后一行中每一行的第一个 str1 为 str2
- :m,ns/str1/str2/g 替换第 n 行开始到最后一行中所有的 str1 为 str2
- (注：m和n 为数字，若m为 .，表示为当前行开始；若n为$，则表示到最后一行结束)
- 如果使用 # 作为分隔符，则中间出现的 / 不会作为分隔符，比如：
- :s#str1/#str2/# 替换当前行第一个 str1/ 为 str2/
- :%s+/oradata/apras/+/user01/apras1+ (使用+ 来 替换 / )： /oradata/apras/替换成/user01/apras1/

###### vim中搜索 /searchstr

##### vim环境自定义

~/.vimrc 是用户自定义的vim环境变量配置，覆盖主文件（/etc/vimrc）中配置

	set autoindent
	set hlsearch
	set nu
	set showmode
	set ruler
	"set bg=dark     “ 代表注释
	syntax on

有时候需要复制vim的文件内容,会连带行号一起复制出来,消除行号

	set nu!

##### windows与linux中的换行符问题

DOS换行`^M$`,俗称CR与LF，Linux 换行 `$`。如果直接把DOS文件上传到 linux时，会因为换行符的问题出现乱码 ，需要手动转换换行符

	[root@iZ2zeh70iv04ct6uk02dscZ machine_su]#yum install dos2unix
	...
	[root@iZ2zeh70iv04ct6uk02dscZ machine_su]# dos2unix -k foo1
	dos2unix: converting file foo1 to Unix format ...

在实际开发中，我们经常windows上进行开发，然后使用git推送代码到远程仓库，有时候会收到 `CR LF`转换的警告，就是这个原因了

在windows的git bash中执行

	admin@admin-PC MINGW64 /d/application/hexo_blog (master)
	$ git config --list | grep autocrlf
	core.autocrlf=true   // 设置git在push转换成lf,pull的时候转换成crlf

##### 撤销 undo 与 反撤销 redo

    undo 命令模式下 undo
    redo 命令模式下 ctrl + r

##### 分屏

水平分屏   
    
    :sp

垂直分屏

    :vsp
