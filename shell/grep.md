## grep

正则表达式与指令输入时的 通配符要区别对待，一般一些功能有限的工具(`ls`) 需要搭配支持正则表达式的工具使用

	cat script.sh | grep -A2 -B2 'show_*'
	grep -n -A2 -B2 'show_val' script.sh
	cat script.sh | grep -i 'show_*'

`grep -v stdin`反选这一功能在查看配置文件时,忽略注释非常实用

	grep -v '#' /etc/my.cnf

反选

	cat script.sh | grep 'show[^a-b]'

行首、行尾

	cat script.sh | grep '^$'
	cat script.sh | grep '^a.*b$'

限定字符重复范围

	cat script.sh | grep 'o\{1,3\}'


#### egrep 或 grep -E

	egrep -n 'gd|good' script.sh
	egrep -n 'gg?ood' script.sh
	egrep -n 'gg+ood' script.sh
	egrep -n 'name(sujianhui|zhaojianwei)' script.sh
	egrep -n 'name(sujianhui|zhaojianwei)?' script.sh
	egrep '(vmx|svm)' /proc/cpuinfo
	egrep -v '(;|^$)' www.conf // 预览一些配置文件时非常实用
