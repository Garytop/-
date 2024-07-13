# FreewayNet
> 大一小学期作业
> 将图像特定区域的RGB值，转换为该区域的权值，求起点到终点的最短路径

## 测试数据规模
1. 565 * 241，2065个点
2. 485 * 401，2970个点
3. 165 * 2001，4990个点

## 本项目基于Linux Ubuntu-22.04 开发
开发环境安装：

``` bash
apt install g++ libgflags-dev autoconf automake libtool libgoogle-glog-dev libpng-dev gdb valgrind make
```

## 本地测试
本地测试在终端中输入
``` bash
make
```
来编译本地判分器，test中的测试为最终测试

输入：
```bash
make clean
```
可清空之前编译出的文件

