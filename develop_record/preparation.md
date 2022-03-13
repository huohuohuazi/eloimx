# Preparation
## 1.
准备阶段，选择一些第三方库
~~~
embree3     # for ray tracing               demo3
fmt         # for format string             demo4
glm         # for vector and matrix         demo1 for vector, demo5 for rand
stb         # for generate a picture        demo2
~~~
关于库Release 和 Debug  
fmt库使用了cmake进行编译，可以得到两个库 fmt.lib 和 fmtd.lib 分别对应release 和 debug版本
在cmake build时，需要使用如下命令
~~~shell
cmake --build . --config Release
~~~
才能生成release版本的库（自己生成的demo库），在链接时，fmt.lib必须和release版本的demo库进行链接才能成功，否则会有运行时库不匹配的报错；或者链接fmtd.lib
## 2.
~~~c++
typedef ... ... ; 记得加分号;
~~~
## 3.
还是尽量不要写类外的inline 函数

## 4.
2.25日
~~~
todo
sampler.h
Intersection.h
~~~

## 5.
3.3日
~~~
编写pathTracer，先解决线性代数坐标系变换问题
~~~

## 6.
3.11日
~~~
-   如果声名实现分离，那么不要写inline，会触发连接错误
-   看一下构造函数的内部调用，在一个带参数的构造函数中调用了没带参数的构造函数，发现没有效果
~~~

## 7.
3.12
~~~
-   format里就不要用花括号了
-   先把向光源采样跳过了，这个太暗了，先写后面的
~~~

## 8.
3.13
~~~c++
elxSpectrum bsdfWeight = bsdf->sample(bRec, rRec.sampler->sample2D(), bsdfPdf);
~~~
pathTracer中，上面函数计算出的$bsdfWeight = \frac{bsdf*cos(\theta)}{pdf(\omega_o)}$, 在diffuse中，该值直接等于表面的reflectance，因此直接返回texture的eval值
~~~c++
throughput *= bsdfWeight;
Li += throughput * value_ * miWeight(bsdfPdf, lumPdf);
~~~
上面的miWeight会返回一个$[0,1]$之间的值，作为重要性采样的调整，目前按照1计算
目前抗锯齿还没有做, 直接光照估计也加上去了，会亮一些(但是只会采样第一个加入场景的光源)
有bug，目前来看采样是不对称的
破案了，已经debug了，出现了两个问题
-   一个是生成frame时没有考虑到0向量就进行标准化，会导致出现nan
-   一个是因为坐标系的不同，mitsuba是z轴系，因此在cos采样时直接抄代码导致了问题