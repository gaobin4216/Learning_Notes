# STEP1：翻墙
    科学上网：https://ikuuu.one/user#
    账号：gaobin4216@gmail.com
    密码：???
# STEP2：申请github账号，安装VScode
# STEP3：安装git
# STEP4：git与github绑定
1、在git bash中输入```ssh-keygen -t rsa -C  gaobin4216@gmail.com  ```后连续回车，在C盘用户目录下生成.ssh文件，里面存储的是两个 ssh key 的秘钥，id_rsa.pub 文件里面存储的是公钥，id_rsa 文件里存储的是私钥，不能告诉别人。打开 id_rsa.pub 文件，复制里面的内容。  
2、在github的设置中，添加配置公钥后完成。   
3、在git bash中检查绑定，输入```ssh -T git@github.com```，应该会有Hi开头的提示出现，如果没有输入```yes```回车。
# STEP5：本地配置
在git bash中：
```
git config --global user.name "gaobin4216"        //用户名，标识提交者的名字
git config --global user.email gaobin4216@gmail.com //github的邮箱，标识提交者的邮箱
git config --global --unset https.proxy   //取消代理
git config --global --unset http.proxy
git config --global http.proxy 127.0.0.1:10080    //设置，梯子的端口
git config --global https.proxy 127.0.0.1:10080   //设置梯子的端口
```
# STEP6：使用
1、git clone  
2、在vscode中打开  
3、拉取、暂存、提交、同步  