screencut
=========
Windows下的一个截屏软件。

编译说明
--------
下载源码：
``
git clone https://github.com/neeker/screencut.git
``

进入目录并创建编译目录：
``
cd screencut
mkdir build && cd build && cmake -G "Visual Studio 12" ..
``
然后使用VS2013打开screencut.sln并编译。
*注：如果要支持XP需要给cmake加上`-T v120_xp`选项*

环境要求
--------
* 最低要求cmake的2.8版本
* 编译要求VSC6~VS12


