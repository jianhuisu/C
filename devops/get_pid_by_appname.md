根据应用name获取应用进程pid

    [guangsujiqiang@su-ct7 CLionProjects]$>man pgrep
    1769 nginx
    1966 nginx
    1967 nginx
    1968 nginx
    1969 nginx
    1970 nginx
    1971 nginx
    1972 nginx
    1973 nginx
    [guangsujiqiang@su-ct7 CLionProjects]$>pgrep -lo nginx
    1769 nginx
    [guangsujiqiang@su-ct7 CLionProjects]$>pgrep -ln nginx
    1973 nginx
    [guangsujiqiang@su-ct7 CLionProjects]$>pgrep -l nginx
