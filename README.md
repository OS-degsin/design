# design


---
开发手册：OS课程设计    
题目：死锁的检测与解除    
组长：刘嘉源    
组员：庄子晨、熊烨方    

---


# 1 预期界面
##  1.1 主菜单
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908132018582.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzE0NTM5Nw==,size_16,color_FFFFFF,t_70#pic_center)

## 1.2 模拟资源分配界面
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908132052367.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzE0NTM5Nw==,size_16,color_FFFFFF,t_70#pic_center)

# 流程图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200911085635309.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzE0NTM5Nw==,size_16,color_FFFFFF,t_70#pic_center)

# 2 技术模块
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908132525470.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzE0NTM5Nw==,size_16,color_FFFFFF,t_70#pic_center)

## 2.1 死锁检测
### 2.1.1 所有资源数量均为1
使用dfs或bfs，二分染色法，判断是否存在循环等待的环路即可。
### 2.1.2 每种资源数量为若干个
参考课本6.4节，类似银行家算法，用已有资源尝试逐个解锁，最终存在无法解锁的进程，则为死锁进程。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200908132211101.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzE0NTM5Nw==,size_16,color_FFFFFF,t_70#pic_center)

## 2.2 死锁解除
### 2.2.1 撤销死锁进程
直接将所有死锁进程撤销，是最简单的办法。
### 2.2.2 回滚到安全状态
系统通过各种状态进入死锁状态。 操作系统将系统回滚到以前的安全状态。 为此，操作系统需要在每个状态下执行检查指针。
现在，我们陷入死锁，将回滚所有分配以进入之前的安全状态。
