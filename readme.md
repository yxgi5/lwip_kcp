#Kcpecho编译和使用#

修改了Common.mk和Filelists.mk
针对不同的部分采用不同的gcc参数编译。添加了特定库的链接选项。
差异直接比较原始文件。反正现在能编译通过。


使用之前要source setup-tapif
程序挂了就source relauch.sh


contrib/ports/unix/
* 1. udp_client 和 minimal 是 udp echo
* 2. telnet 192.168.0.2 7 和 minimal 是 tcp echo
* 3. kcp_client 和 kcpecho 是 kcp echo
