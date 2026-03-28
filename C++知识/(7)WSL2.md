# wsl2 + vscode + github

- 在windows上vscode安装wsl插件，然后远程连接，sudo apt 安装gcc和cmake
- clash代理启用TNU模式，Clash TUN 在 Windows 内核做了全局流量接管，而 WSL 所有流量必须经过 Windows，所以 WSL 自动 “共享” 了 Windows 的代理、路由与 SSH 行为
- 然后再告诉Git你是谁，就可使用github了
   git config --global user.name "gaobin"
   git config --global user.email "gaobin4216@gmail.com"
- 你在 WSL 里敲 git pull、git push、ssh git@github.com 时，流量不是直接从你家宽带连 GitHub，而是 → 先走 Windows Clash 代理 → 再到 GitHub。