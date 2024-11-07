# STEP1：翻墙
    科学上网：https://ikuuu.one/user#
    账号：gaobin4216@gmail.com
    密码：???
# STEP2：申请github账号，安装VScode
# STEP3：安装git
```sudo apt install git  ```
# STEP4：本地配置
```
git config --global user.name "gaobin4216"        //用户名
git config --global user.email gaobin4216@gmail.com //github的油箱
git config --global --unset https.proxy
git config --global --unset http.proxy
git config --global http.proxy 127.0.0.1:7890    //梯子的端口
git config --global https.proxy 127.0.0.1:7890   //梯子的端口
```
# STEP5：git与github绑定
1、在git bash中输入```ssh-keygen -t rsa -C  gaobin4216@gmail.com  ```后连续回车，生成.ssh文件，里面存储的是两个 ssh key 的秘钥，id_rsa.pub 文件里面存储的是公钥，id_rsa 文件里存储的是私钥，不能告诉别人。打开 id_rsa.pub 文件，复制里面的内容。  
2、在github的设置中，添加配置公钥后完成。   
3、在git bash中检查绑定，输入```ssh -T git@github.com```，应该会有Hi开头的提示出现，如果没有输入```yes```回车。

# STEP6：使用
1、git clone  
2、在vscode中打开  
3、暂存、拉取、推送  

--注意：不要每次上传50M以上的文件。