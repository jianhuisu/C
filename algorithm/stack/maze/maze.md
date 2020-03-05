1 如何标注已经走过的路径 ?
    
    将已经走过的坐标点值标记为 0,1 之外的值(比如2) 代表已经扫描过,当回溯的时候,判断栈顶元素的successor是否=0
    
2 top的最大值取决于什么因素 什么时候top的值会大于1
    
    一次可以对0-3个坐标点进行压栈,但是一次只能对一个坐标出栈,当可选方向数>1时,响应的栈中存储的坐标个数>1
        
3 如何优化stack占用的空间

    使用链表代表数组
        
4 如何控制前进方向的优先选择权 栈的生长方向
(最后入栈的方向是前进时优先选择的方向)
    
    if(p.row + 1 < MAX_ROW && maze[p.row+1][p.col] == 0){
        mark_path(p.row + 1,p.col,p);
    }

    if(p.col + 1 < MAX_COL && maze[p.row][p.col + 1] == 0) {
        mark_path(p.row,p.col + 1,p);
    }
    
    if(p.col - 1 >= 0 && maze[p.row][p.col - 1] == 0) {
        mark_path(p.row,p.col - 1,p);
    }

    if(p.row - 1 >= 0 && maze[p.row - 1][p.col] == 0) {
        mark_path(p.row - 1,p.col,p);
    }
    
通过以上的代码可以得出 当前进时 优先选择上方坐标点 ,其次选择左方 、右方 上方 因为,最后入栈的左边最先出栈
 
5 如何正向打印从起点到终点的路径


