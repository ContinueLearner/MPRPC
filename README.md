# MPRPC - 基于 Protobuf 和 ZooKeeper 的轻量级 C++ RPC 框架

MPRPC 是一个高性能、易用的 C++ 分布式网络框架，旨在帮助开发者快速构建微服务架构。本项目通过对 Protobuf 的二次封装，实现了透明化的远程过程调用，并引入 ZooKeeper 作为服务配置中心，确保了分布式环境下的高可用性。

## 核心特性

* **高效序列化**：利用 Google Protocol Buffers (Protobuf) 实现高效的二进制数据序列化与反序列化。
* **服务注册与发现**：集成 ZooKeeper 客户端，支持服务提供者自动注册地址及调用者动态发现服务。
* **异步日志系统**：内置高性能异步日志模块，支持分级日志记录。
* **配置化管理**：通过配置文件轻松管理 RPC 服务器参数（如 IP、端口）及 ZooKeeper 地址。
* **抽象网络层**：框架底层对网络通信进行了封装，用户仅需关注业务逻辑实现。

## 技术栈

* **编程语言**：C++
* **序列化**：Google Protobuf
* **服务治理**：ZooKeeper
* **构建工具**：CMake

## 目录结构

```bash
.
├── bin/                 # 编译生成的二进制执行文件及测试配置
├── example/             # 框架使用示例（包括服务提供者和服务调用者）
├── lib/                 # 编译生成的静态库文件 (libmprpc.a)
├── src/                 # 框架核心源码
│   ├── include/         # 头文件目录
│   └── ...              # 核心模块实现（RPC提供者、通道、配置处理等）
└── test/                # 针对 Protobuf 等模块的单元测试代码

```

## 核心模块说明

1. **MprpcApplication**：框架的初始化入口，负责读取配置文件并管理全局运行状态。
2. **RpcProvider**：服务发布者模块。它接收 Protobuf 定义的服务对象，将其方法映射到网络端口，并将服务信息同步至 ZooKeeper。
3. **MprpcChannel**：服务调用者模块。通过继承 `google::protobuf::RpcChannel`，实现了将本地 RPC 调用转发为网络数据包的逻辑。
4. **ZkClient**：ZooKeeper 客户端封装，用于处理与集群的连接、节点创建及数据查询。
5. **Logger**：基于单例模式实现的日志系统，保障了系统运行时的监控与调试。

## 快速开始

### 1. 依赖安装

确保系统中已安装以下环境：

* `protobuf` 3.x 或更高版本
* `zookeeper` 及其 C 客户端开发库
* `cmake`

### 2. 编译项目

在根目录下执行：

```bash
cmake .
make

```

### 3. 发布服务（Callee）

参考 `example/callee` 目录，通过 `RpcProvider` 发布您定义的 Protobuf 服务。

### 4. 调用服务（Caller）

参考 `example/caller` 目录，使用 `MprpcChannel` 像调用本地函数一样发起远程请求。
