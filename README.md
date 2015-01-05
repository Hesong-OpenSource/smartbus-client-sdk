# 概述

**smartbus** 是和声(广州)的实时媒体流程服务器IPSC专用的消息总线。

该消息总线是一个 Client-Service 结构的局域网消息总线体系。
其中，smartbus服务与IPSC服务运行在同一台服务器上。消息中线的客户端可以通过本SDK的提供的客户端共享/动态库文件，连接到服务器，并与服务器通信，进行消息收发。

本SDK主要提供 IPSC Smartbus 客户端共享/动态库。

其客户端使用 C 语言开发，如果开发者要使用其它语言进行调用，请在该 C 库的基础上开发。我们在其它开源项目中也提供或者准备提供某些常见语言的 IPSC Smartbus 客户端封装。

# 目录结构

* include C语言头文件
* lib 该目录下放置了客户端共享/动态库文件。不同操作系统的库文件放在不同的子目录中

# 基本概念

## 拓扑结构

IPSC Smartbus 网络的结构是 *多中心的放射型* 结构。每个 Smartbus 服务器都是网络中的一个中心，客户端连接到服务器，并通过服务器向其它客户端发送消息。服务器之间可相互连通，客户端可利用这一特性将消息发送到其它服务器上的客户端。

## 连接方式

IPSC Smartbus 提供 IPC（跨进程通信）和NET（网络通信）两种连接方式。

IPC方式具有较高的效率和可靠性。但是客户端与服务器必须处于同一服务器上。

NET方式通过UDP通信，它要求局域网具有高可靠性和高带宽。

## Smartbus 节点标识

在 IPSC Smartbus 体系中，每个服务器或客户端进程都被视为一个节点，节点标识用3个元素表示，它们分别是：
* Node：节点编号。该编号在整个体系中唯一。
* Client：客户端。节点中的客户端。每个节点都可以为多个客户端提供连接。
* Type：类型。

## API 参考

目前只有从 .h 文件生成的 doxygen 手册。

您可以直接阅读头文件的注释，或者使用 doxygen 生成文档：

```sh
cd doxygen
./doxygen
```

输出目录在 `doxygen/output`
