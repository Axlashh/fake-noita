## 南京理工大学22级暑期团队项目

- 项目名称：具有可编程法术系统的闯关游戏
- 团队成员：黄子昕， 贾春欣

以下为开发记录  

---

##### 8月26日

目前完善了暂停页面，在暂停页面可查看各类法杖与法术的信息，不再只能靠经验了

并且完成了地图小方块的编写，现在可以开始自己画地图，多搭建几个平台来战斗了

接下来的重点就是怪物系统，要考虑怪物进攻玩家的策略；再写一下游戏内获得法术与法杖的方式，本项目就基本完成了

##### 8月19日

###### 终于！

法术的部分全部完成，包括十个法术、三根法杖以及在暂停页面自由切换法杖与背包里的法术

qt的update逻辑真的不知道是什么，莫名其妙，一个bug修了我两三个小时，最后还是用贼笨的全局变量勉强实现效果

接下来要完成地图与怪物的部分，地图打算随便画几个平台得了，怪物就到处乱冲

目前法术是用一个基类派生一堆类实现的，法术的发射以及抽取逻辑都使用基类的函数，根据对象的不同属性指向不同逻辑（改了蛮多遍），法杖与人物都类似

暂停菜单是在游戏主界面的类中增加了一个暂停菜单类的成员变量，按下esc就会show()，paintEvent里先画了一层黑色的蒙版，主界面的物理模拟暂停。暂停菜单里有作为坑位的widget类和作为物品被拖动的widget类，来实现背包的效果

总得来说还行，.cpp已经有一千五百行左右了，感觉最后能写两千多行

##### 8月14日

法术的发射与绘图都搞定了，下一步是写出调整法杖与法术的图形界面，方便在游戏中操控

不过现在就写了一个法术的具体属性，法杖的发射逻辑也没怎么测试

现在.cpp文件的行数已经八百行左右了，这个项目还有得搞啊

##### 8月12日

法术模块的基本逻辑写完了，接下来估计还得花一部分时间debug

法术发射的部分主要用了递归去写

不同的法术跟法杖都用了类的继承，结构调了几遍，有时候写完了才发现某个函数可以不用虚函数

接下来得把素材整理一下，处理qt的画图部分，以及不同物体碰撞的逻辑

地图估计要改一下，应该不会写原游戏那种地图了，可能会写类似于混乱大枪战的那种地图，还是注重打怪的部分

##### 8月6日

实现了让人物动起来

##### 8月5日

目前写出了一个box2d的简单应用界面，一个会弹的小球

决定更改项目，做一个仿noita的游戏出来，以下为构思的分目标：

1. 界面模块

- 实现注册、登录账号系统， 利用MySql将数据存储在外部
- 实现分数的个人排行榜、总排行榜  

2. 地图模块

- 实现三个关卡固定大小的地图，每个地图中带有一定的随机属性

- 实现地图中有部分物体可破坏，利用box2d实现简单的物理模拟

3. 法术模块

- 实现有不同属性的法杖，施法时间与可添加法术组件数量有不同

- 法术组件实现两大种类，影响其他组件（如下一个释放的法术范围增大）以及放出法术实体（发射光球）

4. 角色模块

- 实现多种类型的敌人， 出现于不同关卡

##### 8月3日

一开始调试在主程序内调用python函数，调半天最后发现是qt自带的mingw设置有问题，无法调用python，浪费一大堆时间

后面python的opencv库又出bug，突然就报缺dll库，调一个多小时，最后降opencv版本解决的

最后发现mediapipe的手势识别在高速移动情况下很不好，切水果肯定是做不成了，又不知道做啥

今天一天算是浪费了，还花一堆时间，心态炸裂

##### 8月2日

游戏暂时打算只做一个切水果 ~~行数不够就再写一个游戏~~
初步构思了项目的分目标：

1. 界面模块

- 实现注册、登录账号系统， 利用MySql将数据存储在外部
- 实现分数的个人排行榜、总排行榜  

2. 手部识别模块

- 实现获取手部关键点坐标
- 实现不同手势的识别

3. 切水果模块

- 实现难度递增的关卡
- 实现炸弹、血量系统
- 实现刀刃的轨迹
- 实现游戏内菜单，能通过手势控制

##### 7月28日

项目初始化完成，准备开始