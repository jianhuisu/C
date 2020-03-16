foo=$(bar)
bar=hub

foo1 := $(bar1) foo2
all:
	@echo $(foo)
	@echo "-$(foo1)-"

# $(bar1) 为定义 所以默认为一个空格 输出如下
# [guangsujiqiang@su-ct7 test_make_var]$>make
# hub
# - foo2-
