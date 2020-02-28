#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// 以下三个源文件只能同时包含一个
//#include "./m_thread_not_safe.c"
//#include "./m_thread_safe_lock.c"
//#include "./m_thread_not_safe_no_lock.c"
#include "./m_thread_safe_semaphore.c"

void main(void){

    //m_thread_not_safe();
    //m_thread_safe_lock();
    //m_thread_not_safe_no_lock();
    m_thread_safe_semaphore();
}


/*

 cpu 空转
 https://cloud.tencent.com/developer/article/1408753

 c多线程
 https://www.cnblogs.com/zzdbullet/p/9526130.html

*/