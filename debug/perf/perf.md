## perf

perf 工具是 Linux 内核提供一个非常强大的动态跟踪工具，perf top 指令可用于实时分析正在执行程序的性能问题。
与 callgrind、xdebug、xhprof 等工具不同，perf 无需修改代码导出 profile 结果文件。

    perf top -p [进程ID]