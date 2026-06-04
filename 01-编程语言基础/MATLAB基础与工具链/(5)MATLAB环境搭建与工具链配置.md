# MATLAB 环境搭建与工具链配置

## 一、MATLAB 安装

### 获取许可证

| 方式 | 说明 |
|------|------|
| **学校/单位** | 很多高校有校园许可证，免费使用 |
| **学生版** | MathWorks 提供低价学生版 |
| **个人版** | 商业购买 |
| **MATLAB Online** | 有许可证即可在线使用，无需安装 |

### 安装步骤

1. 注册 [MathWorks 账号](https://www.mathworks.com/mwaccount/)
2. 下载 [MATLAB 安装程序](https://www.mathworks.com/downloads/)
3. 运行安装程序，登录账号
4. 选择许可证和需要的工具箱
5. 选择安装路径，完成安装

### 安装路径建议

- Windows：`C:\Program Files\MATLAB\R2024a`（默认）
- macOS：`/Applications/MATLAB_R2024a.app`
- Linux：`/usr/local/MATLAB/R2024a`

---

## 二、MATLAB 基本配置

### 设置默认工作目录

`主页 → 预设 → 常规 → 初始工作文件夹`

### 编辑器配置

`主页 → 预设 → 编辑器/调试器`：
- 缩进：4 空格
- 自动保存：开启
- 行号：显示

### 代码格式化习惯

- 变量名：小写 + 下划线，如 `my_variable`
- 函数名：小写 + 下划线，如 `load_data`
- 常量：全大写，如 `MAX_ITER`
- 每个函数文件开头写帮助注释

---

## 三、VS Code 配置（可选）

如果偏好 VS Code 编辑代码：

1. 安装 VS Code
2. 安装扩展 `MATLAB`（MathWorks 官方）
3. 配置 MATLAB 路径：

```json
// .vscode/settings.json
{
    "matlab.matlabpath": "C:/Program Files/MATLAB/R2024a/bin/matlab.exe",
    "matlab.linting.enabled": true
}
```

---

## 四、常用命令速查

| 命令 | 功能 |
|------|------|
| `clc` | 清空命令窗口 |
| `clear` | 清除工作区变量 |
| `clear all` | 清除所有变量和函数 |
| `close all` | 关闭所有图形窗口 |
| `who` / `whos` | 查看工作区变量 |
| `help func` | 查看函数帮助 |
| `doc func` | 打开函数文档 |
| `type func` | 显示函数源码 |
| `which func` | 显示函数文件路径 |
| `ver` | 显示版本和已安装工具箱 |
| `addpath` | 添加搜索路径 |
| `savepath` | 保存路径修改 |

---

## 五、数据导入导出

### 常用数据格式

```matlab
% CSV
data = readtable('data.csv');
writetable(data, 'output.csv');

% Excel
data = readtable('data.xlsx');
writetable(data, 'output.xlsx');

% MAT 文件（MATLAB 原生格式）
save('workspace.mat', 'var1', 'var2');
load('workspace.mat');

% 文本文件
data = load('data.txt');

% 图片
img = imread('photo.png');
imwrite(img, 'output.png');
```

---

## 六、绘图基础

```matlab
% 基本二维图
x = 0:0.01:2*pi;
figure;
plot(x, sin(x), 'b-', 'LineWidth', 1.5);
hold on;
plot(x, cos(x), 'r--');
xlabel('x');
ylabel('y');
legend('sin(x)', 'cos(x)');
title('三角函数');
grid on;

% 子图
figure;
subplot(2, 1, 1); plot(x, sin(x)); title('sin');
subplot(2, 1, 2); plot(x, cos(x)); title('cos');

% 保存图片
saveas(gcf, 'figure.png');
exportgraphics(gcf, 'figure.pdf');  % 高质量导出
```

---

## 七、常见问题

### 许可证过期

- 登录 MathWorks 账号续期
- 或联系学校/单位管理员

### 工具箱函数找不到

```matlab
ver                           % 检查是否安装了该工具箱
restoredefaultpath;           % 重置路径
rehash toolboxcache;          % 刷新工具箱缓存
```

### MATLAB 启动慢

- 减少 `startup.m` 中的初始化操作
- 关闭不需要的工具箱
- 清理路径中不必要的目录
