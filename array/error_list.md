## 常见错误

`error: variable-sized object may not be initialized`

error code block 

    void merge(int start,int mid,int end)
    {
    
        int n1 = mid - start + 1;
        int n2 = end - mid;
        
        int left[n1] = {11};  
        int right[n2] = {9};
        // ...    
    }
    
right code block

    void merge(int start, int mid, int end)
    {
        int n1 = mid - start + 1;
        int n2 = end - mid;
        int left[n1], right[n2];
        int i, j, k;
    }
    
动态声明数组时不能使用`{}`这种方式初始化.