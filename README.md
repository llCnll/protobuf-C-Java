# protobuf-C-Java

## 简要
protobuf, http  
为什么要使用protobuf, 因为更轻更快, 跨语言  

C/C++作为客户端  
Java作为服务端, 使用SpringBoot  

## 需求
简单讲下, 毕竟是项目中运用前的小demo.  

客户端有很多的点, 要发送给web服务端, 服务端进行接收再进行回调(回调就属于其他项目了, 这里并未设计)  

## protobuf
定义点类型, 在定义点云类型. 详情请见protobuf官网
```java
syntax = "proto3";
package cn.chennan.server.proto;

message Point3f {
	float x = 1;
	float y = 2;
	float z = 3;
}

message PointCloud {
    int32 total = 1;
	repeated Point3f map_points = 2;
}
```

## 客户端

### CMakeLists
具体详见CMakeLists, 挑需要注意的地方讲讲
- 涉及到protobuf, `find_package(Protobuf REQUIRED`, 没有protobuf, 需要进行安装
- 因为protobuf, 所以在编译的时候需要把protobuf相关类库加载, 那几条关于protobuf的都是.
- 涉及到http, 所以需要添加`find_package(CURL REQUIRED)`, 没有curl需要进行安装.
- 因为curl, 所以在编译的时候需要加参数 `-lcurl`

### 主程序
基本没啥讲的, 看一眼就懂  
需要注意的是, 需要protobuf的请求头 `m_header = curl_slist_append( m_header, "Content-Type: application/x-protobuf" );`  


`point_cloud.SerializeToString(&sReq)` 就是protobuf的api, 将对象序列化. 用这个进行传输  
`resp.ParseFromString(sResp)` 反序列化.

## 服务端

### Maven
```xml
<dependency>
    <groupId>com.google.protobuf</groupId>
    <artifactId>protobuf-java</artifactId>
    <version>3.8.0</version>
</dependency>
```
### 编译protobuf
Java需要手动编译, 我是在 server/src/main 下打开的终端.  
-I : protobuf 文件所在目录
-java_out : 输出到哪里  
最后一个参数 : protobuf 文件名
```shell script
~/protobuf-C-Java/Server/src/main$ protoc -I=resources/cn/chennan/server --java_out=java http.proto
```
### HttpController
跟正常web服务一样, @RequestMapping@REsponseBody  
主要用到的是流, 所以需要`request.getInputStream()`  
然后就如出一辙了, 使用 `parseFrom` 反序列化.  
看最后是否需要返回内容, 需要的话, 就把String改成void, 把注释打开照着写即可.

## 最后
最后的最后, 是我用了一天的时间摸索的... 主要确实没有相关文档, 既跨语言, 有需要http. 希望此文档对你有所帮助~