ADT{
    数据项: 
    关系集合: 尾部插入 头部删除 
    相关操作:
    
        void createQueue(Queue * pt);
        
        bool queueIsFull(Queue * pt);
        
        bool queueIsEmpty(Queue * pt);
        
        int getQueueItemsCount(Queue * pt);
        
        bool insertQueueNode(Item book,Queue * pt);
        
        bool deleteQueueNode(Queue * pt);
        
        bool resetQueue(Queue * pt);
      
        void traversal(Queue * pt, void(*pfun)(Item item));
        
}