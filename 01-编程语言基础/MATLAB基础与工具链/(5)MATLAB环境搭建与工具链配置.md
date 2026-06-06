# MATLAB 环境搭建与工具链配置

## 一、MATLAB 安装

### 获取许可证

| 方式 | 说明 | 适用人群 |
|------|------|----------|
| **校园许可证** | 学校统一购买，学生免费使用 | 在校学生 |
| **学生版** | MathWorks 提供低价学生版 | 在校学生 |
| **学术版** | 高校教师、研究人员优惠价 | 高校教师 |
| **商业版** | 按年付费 | 企业用户 |
| **MATLAB Online** | 有许可证即可在线使用，无需安装 | 所有许可证持有者 |

> **学生建议**：先问学校是否有校园许可证，很多大学都提供免费的 MATLAB 使用权限。

### 安装步骤

1. 注册 [MathWorks 账号](https://www.mathworks.com/mwaccount/)
2. 下载 [MATLAB 安装程序](https://www.mathworks.com/downloads/)
3. 运行安装程序，登录 MathWorks 账号
4. 选择许可证
5. **选择需要的工具箱**（可以后续再添加）
6. 选择安装路径
7. 等待安装完成（通常需要 30 分钟到 1 小时）

### 安装路径建议

| 平台 | 默认路径 |
|------|----------|
| Windows | `C:\Program Files\MATLAB\R2024a` |
| macOS | `/Applications/MATLAB_R2024a.app` |
| Linux | `/usr/local/MATLAB/R2024a` |

> **注意**：安装路径不要包含中文或空格，可能导致某些功能异常。

### 安装后添加工具箱

如果安装时没有选择某些工具箱，后续可以补充安装：

```
MATLAB → 主页 → 附加功能 → 获取附加功能
```

---

## 二、MATLAB 基本配置

### 设置默认工作目录

每次启动 MATLAB 时，默认的工作目录（Current Folder）决定了文件的读写位置。

设置方法：`主页 → 预设 → 常规 → 初始工作文件夹`

建议设置为你的项目根目录，比如 `D:\MATLAB_Projects`。

### 编辑器配置

`主页 → 预设 → 编辑器/调试器`：

| 配置项 | 建议值 | 说明 |
|--------|--------|------|
| 缩进 | 4 空格 | 统一代码风格 |
| 自动保存 | 开启 | 防止意外丢失 |
| 行号 | 显示 | 方便调试定位 |
| 自动换行 | 关闭 | 保持代码整洁 |
| 代码折叠 | 开启 | 折叠长函数，便于浏览 |

### 代码风格建议

| 元素 | 命名规范 | 示例 |
|------|----------|------|
| 变量名 | 小写 + 下划线 | `my_variable` |
| 函数名 | 小写 + 下划线 | `load_data` |
| 类名 | 驼峰命名 | `MyClass` |
| 常量 | 全大写 + 下划线 | `MAX_ITERATIONS` |
| 文件名 | 与函数名一致 | `load_data.m` |

---

## 三、VS Code 配置（可选）

如果偏好 VS Code 编辑代码，需要做以下配置：

### 1. 安装 VS Code

访问 [https://code.visualstudio.com/](https://code.visualstudio.com/) 下载安装。

### 2. 安装 MATLAB 扩展

按 `Ctrl+Shift+X`，搜索 `MATLAB`，安装 MathWorks 官方扩展。

### 3. 配置 MATLAB 路径

创建 `.vscode/settings.json`：

```json
{
    "matlab.matlabpath": "C:/Program Files/MATLAB/R2024a/bin/matlab.exe",
    "matlab.linting.enabled": true,
    "matlab.linting.RunCodeAnalysis": true,
    "matlab.editor.enableVariableHighlighting": true
}
```

> **注意**：`matlab.matlabpath` 需要改成你实际安装的 MATLAB 路径。

---

## 四、常用命令速查

### 环境与变量管理

| 命令 | 功能 |
|------|------|
| `clc` | 清空命令窗口（不清除变量） |
| `clear` | 清除工作区所有变量 |
| `clear var1 var2` | 清除指定变量 |
| `clear all` | 清除所有变量、函数、MEX 文件 |
| `close all` | 关闭所有图形窗口 |
| `who` | 列出工作区变量名 |
| `whos` | 列出工作区变量的详细信息（大小、类型） |

### 帮助与文档

| 命令 | 功能 |
|------|------|
| `help func` | 查看函数的简要帮助 |
| `doc func` | 打开函数的完整文档 |
| `type func` | 显示函数的源代码 |
| `which func` | 显示函数文件的路径 |
| `lookfor keyword` | 在所有函数帮助中搜索关键词 |

### 路径管理

| 命令 | 功能 |
|------|------|
| `path` | 查看当前搜索路径 |
| `addpath('dir')` | 添加目录到搜索路径 |
| `addpath(genpath('dir'))` | 递归添加目录及子目录 |
| `rmpath('dir')` | 移除目录 |
| `savepath` | 永久保存路径修改 |
| `restoredefaultpath` | 恢复默认路径 |

### 版本与工具箱

| 命令 | 功能 |
|------|------|
| `ver` | 显示 MATLAB 版本和已安装工具箱 |
| `license('test', 'toolbox_name')` | 检查工具箱是否可用 |
| `toolboxdir('toolbox_name')` | 查看工具箱安装路径 |

---

## 五、数据导入导出

MATLAB 支持多种数据格式的读写：

### 常用数据格式

```matlab
% CSV 文件
data = readtable('data.csv');          % 读取为表格
writetable(data, 'output.csv');        % 写入 CSV

% Excel 文件
data = readtable('data.xlsx');         % 读取
writetable(data, 'output.xlsx');       % 写入

% MAT 文件（MATLAB 原生格式，保存工作区变量）
save('workspace.mat', 'var1', 'var2'); % 保存指定变量
load('workspace.mat');                 % 加载

% 文本文件
data = load('data.txt');               % 纯数值文本

% 图片
img = imread('photo.png');             % 读取图片
imwrite(img, 'output.png');            % 保存图片
```

### 格式选择建议

| 格式 | 适用场景 | 说明 |
|------|----------|------|
| `.mat` | MATLAB 变量存储 | 保留变量名和类型，读写最快 |
| `.csv` | 与其他工具交换数据 | 通用格式，Excel 可直接打开 |
| `.xlsx` | 与 Excel 交互 | 支持多 Sheet、格式保留 |
| `.txt` | 纯数值数据 | 简单，无格式信息 |

---

## 六、绘图基础

### 基本二维图

```matlab
x = 0:0.01:2*pi;

figure;
plot(x, sin(x), 'b-', 'LineWidth', 1.5);   % 蓝色实线
hold on;                                      % 保持当前图形
plot(x, cos(x), 'r--', 'LineWidth', 1.5);   % 红色虚线
xlabel('x');                                  % X 轴标签
ylabel('y');                                  % Y 轴标签
legend('sin(x)', 'cos(x)');                   % 图例
title('三角函数');                             % 标题
grid on;                                      % 显示网格
```

### 子图

```matlab
figure;
subplot(2, 1, 1);        % 2 行 1 列，第 1 个
plot(x, sin(x));
title('sin(x)');

subplot(2, 1, 2);        % 2 行 1 列，第 2 个
plot(x, cos(x));
title('cos(x)');
```

### 保存图形

```matlab
saveas(gcf, 'figure.png');                    % 保存为 PNG
exportgraphics(gcf, 'figure.pdf');            % 高质量 PDF 导出
exportgraphics(gcf, 'figure.png', 'Resolution', 300);  % 指定分辨率
```

---

## 七、常见问题排查

### 许可证过期

- 登录 MathWorks 账号续期
- 或联系学校/单位的 MATLAB 管理员
- 检查系统时间是否正确

### 工具箱函数找不到

```matlab
ver                           % 检查是否安装了该工具箱
which funcname                % 检查函数是否在搜索路径中
restoredefaultpath;           % 重置搜索路径
rehash toolboxcache;          % 刷新工具箱缓存
```

### MATLAB 启动慢

- 减少 `startup.m` 中的初始化操作
- 关闭不需要的工具箱
- 清理搜索路径中不必要的目录
- 检查网络连接（某些工具箱启动时会联网验证）

### 内存不足

```matlab
whos                          % 查看变量占用内存
clear large_var               % 清除不需要的大变量
pack                          % 整理内存碎片（旧版本）
```

### 函数名与文件名不一致

MATLAB 要求函数文件名必须与函数名一致。如果 `myfunc.m` 中定义的函数名是 `other_func`，MATLAB 会使用文件名 `myfunc` 来调用，而不是函数定义中的名字。
