# 虚拟网卡的配置
![](Hyper-V_1.png)
这里介绍一些术语
- **网络适配器**就是网卡，硬件网卡就是你电脑上用来连接网线的那个设备。Hyper‑V 给虚拟机提供一块软件实现的网卡，虚拟机里的操作系统会把它当作一块有线网卡来用
- **`Default Switch`** 是 Hyper‑V 自带的默认虚拟交换机。选它以后，虚拟机通常会自动拿到 IP 地址，再通过 Windows 的网络连接上网。这个共享上网的方式叫 **NAT**。
>你选 `Default Switch` 后，Windows 会为这个虚拟网络提供两项服务：
>1. **DHCP** 给虚拟机分配一个内部 IP，并告诉它默认网关在哪里。
>2. **NAT** 把虚拟机发出的上网请求经由笔记本的 Wi‑Fi 或有线网络转发出去。
>所以你的笔记本可以同时有两套地址。比如家里的路由器给 Windows 分配 `192.168.1.20`，Windows 再给虚拟机分配 `172.24.128.10`。这两个地址属于不同的网络。
- **WSL** 全称是 _Windows Subsystem for Linux_，即 **适用于 Linux 的 Windows 子系统**。它让你在 Windows 里直接使用 Ubuntu 等 Linux 发行版的终端和工具，比如 Bash、`apt` 和 Git。
- **WSL 2** 是 WSL 目前默认使用的架构。早期的 **WSL 1** 通过转换层处理 Linux 程序发给系统的请求。**WSL 2** 则在 Windows 自动管理的轻量虚拟机里运行真正的 Linux 内核，因此能兼容更多 Linux 软件。
截图里的 **`WSL (Hyper-V firewall)`** 是 Windows 为 WSL 2 管理的虚拟网络。你现在是用 Hyper‑V 向导单独创建一台虚拟机，想让它正常联网就选 **`Default Switch`**。选 `WSL (Hyper-V firewall)`，就是把**这台虚拟机自己的网卡接到 Windows 为 WSL 2 创建的内部 NAT 网络**。
# 加载`iso`镜像安装操作系统
右键创建好的虚拟机，点击设置
![](Hyper-V_2.png)
找到**SCSI控制器**，点击**DVD 驱动器**，然后点击**添加**
![](Hyper-V_3.png)
然后点击**镜像文件**，点击**浏览**，找到Ubuntu操作系统的镜像文件，选择之后点击确定
![](Hyper-V_4.png)
然后在这个地方把DVD驱动器的位置调整到第一位。
然后启动这个虚拟机，这时候就会进入Ubuntu的安装程序