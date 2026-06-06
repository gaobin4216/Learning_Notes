# Python 环境管理：编辑器与 IDE 配置详解

## 一、为什么需要编辑器管理 Python 环境？

Python 项目经常面临**多版本共存**和**依赖隔离**的问题：

- 项目 A 需要 Python 3.8 + Django 3.2
- 项目 B 需要 Python 3.12 + FastAPI 0.100
- 机器学习项目需要 Python 3.10 + PyTorch

手动切换环境容易出错，好的编辑器/IDE 能**自动识别、切换、管理**这些环境。

---

## 二、各编辑器/IDE 环境管理能力对比

| 工具 | 环境管理能力 | 自动检测 venv | Conda 支持 | 远程环境 | 学习成本 | 推荐指数 |
|------|------------|--------------|-----------|---------|---------|---------|
| **VS Code** | 强 | 是 | 是 | SSH/WSL/Docker | 低 | ★★★★★ |
| **PyCharm** | 最强 | 是 | 是 | SSH/Docker/WSL | 中 | ★★★★★ |
| **Cursor** | 强（同 VS Code） | 是 | 是 | SSH/WSL/Docker | 低 | ★★★★ |
| **Windsurf** | 强（同 VS Code） | 是 | 是 | SSH/WSL/Docker | 低 | ★★★★ |
| **Sublime Text** | 弱 | 否 | 否 | 否 | 高 | ★★ |
| **Vim/Neovim** | 中（需配置） | 手动 | 手动 | 是 | 高 | ★★★ |
| **Jupyter Lab** | 中 | 否（需手动） | 是 | 否 | 低 | ★★★ |
| **Thonny** | 弱 | 否 | 否 | 否 | 极低 | ★★ |

---

## 三、VS Code：环境管理配置详解（推荐）

### 3.1 必装扩展

```
Ctrl+Shift+X 打开扩展面板，安装以下扩展：
```

| 扩展 | 作用 | 必装 |
|------|------|------|
| **Python** | 微软官方，环境管理核心 | 是 |
| **Pylance** | 类型检查 + 智能补全 | 是 |
| **Python Debugger** | 调试支持 | 是 |
| **Python Environment Manager** | 可视化管理所有环境 | 推荐 |
| **Jupyter** | Notebook 支持 | 按需 |

### 3.2 选择 Python 解释器

**方法一：命令面板（最常用）**

1. 按 `Ctrl+Shift+P` 打开命令面板
2. 输入 `Python: Select Interpreter`
3. 从列表中选择：
   - 系统 Python（如 `Python 3.12.0`）
   - 虚拟环境（如 `.venv`、`venv`）
   - Conda 环境（如 `conda: myenv`）

**方法二：状态栏快捷切换**

- 点击 VS Code **左下角**的 Python 版本号
- 弹出环境列表，直接选择

**方法三：设置文件指定**

`.vscode/settings.json`：

```json
{
    // 指定默认解释器路径
    "python.defaultInterpreterPath": "D:/Python312/python.exe",

    // 针对特定工作区使用虚拟环境
    "python.defaultInterpreterPath": "${workspaceFolder}/.venv/Scripts/python.exe"
}
```

### 3.3 创建虚拟环境

**方法一：命令面板**

1. `Ctrl+Shift+P` → `Python: Create Environment`
2. 选择类型：`Venv` 或 `Conda`
3. 选择 Python 版本
4. VS Code 自动创建并激活

**方法二：终端手动创建**

```bash
# 创建 venv
python -m venv .venv

# Windows 激活
.venv\Scripts\activate

# macOS/Linux 激活
source .venv/bin/activate

# 安装依赖
pip install -r requirements.txt
```

### 3.4 自动激活虚拟环境

VS Code 设置（`Ctrl+,` 打开设置，搜索 `python.terminal`）：

```json
{
    // 打开终端时自动激活虚拟环境
    "python.terminal.activateEnvironment": true,

    // 自动激活的环境（推荐设为 "on" 始终激活）
    "python.terminal.activateEnvInCurrentTerminal": "on"
}
```

### 3.5 多环境管理工作区配置

`.vscode/settings.json`（完整示例）：

```json
{
    // ===== 环境配置 =====
    "python.defaultInterpreterPath": "${workspaceFolder}/.venv/Scripts/python.exe",
    "python.terminal.activateEnvironment": true,
    "python.terminal.activateEnvInCurrentTerminal": "on",

    // ===== 代码质量 =====
    "python.linting.enabled": true,
    "python.linting.pylintEnabled": true,
    "python.linting.pylintArgs": [
        "--load-plugins", "pylint_django",
        "--django-settings-module", "myproject.settings"
    ],
    "python.analysis.typeCheckingMode": "basic",
    "python.analysis.autoSearchPaths": true,
    "python.analysis.extraPaths": ["./src"],

    // ===== 格式化 =====
    "[python]": {
        "editor.defaultFormatter": "ms-python.black-formatter",
        "editor.formatOnSave": true
    },
    "black-formatter.args": ["--line-length", "88"],

    // ===== 测试 =====
    "python.testing.pytestEnabled": true,
    "python.testing.pytestArgs": ["tests"],

    // ===== 文件排除 =====
    "files.exclude": {
        "**/__pycache__": true,
        "**/*.pyc": true,
        "**/.venv": true
    }
}
```

### 3.6 VS Code 环境检测机制

VS Code 按以下优先级自动检测 Python 环境：

```
1. 当前工作区的 .venv/ 或 venv/ 目录
2. python.defaultInterpreterPath 设置
3. 系统 PATH 中的 python
4. Conda 环境列表
5. pyenv 安装的版本
```

---

## 四、PyCharm：环境管理配置详解

### 4.1 创建项目时配置环境

1. `File` → `New Project`
2. 在 `Python Interpreter` 选项中选择：
   - `Virtualenv Environment` → `New environment`
   - `Conda Environment` → `New environment`
   - `System Interpreter` → 使用系统 Python
3. 选择 Python 版本
4. 勾选 `Inherit global site-packages`（如需继承全局包）

### 4.2 为已有项目配置环境

1. `File` → `Settings` → `Project: xxx` → `Python Interpreter`
2. 点击齿轮图标 → `Add Interpreter`
3. 选择类型：

| 选项 | 说明 |
|------|------|
| **Virtualenv Environment** | 创建/使用 venv |
| **Conda Environment** | 创建/使用 conda 环境 |
| **System Interpreter** | 直接使用系统 Python |
| **SSH Interpreter** | 远程服务器 Python |
| **Docker** | Docker 容器中的 Python |
| **WSL** | Windows Subsystem for Linux |

### 4.3 PyCharm Conda 环境配置

```
File → Settings → Project → Python Interpreter → Add Interpreter → Conda Environment
```

**创建新环境：**

```
- 选择 Conda 可执行文件：D:\Anaconda3\condabin\conda.bat
- 环境名称：myproject_env
- Python 版本：3.12
- 勾选 "Make available to all projects"（可选）
```

**使用已有环境：**

```
- 选择 "Use existing environment"
- 从下拉列表选择已有 conda 环境
```

### 4.4 PyCharm venv 配置

```
File → Settings → Project → Python Interpreter → Add Interpreter → Virtualenv Environment
```

| 配置项 | 推荐值 |
|--------|--------|
| **New environment** | 选择此项创建新环境 |
| **Location** | 项目目录下 `.venv` |
| **Base interpreter** | 选择 Python 版本 |
| **Inherit global packages** | 勾选（继承全局已装的包） |
| **Make available to all projects** | 不勾选（环境隔离） |

### 4.5 PyCharm 终端自动激活

PyCharm 默认会自动在终端中激活项目虚拟环境。如未生效：

```
File → Settings → Tools → Terminal → Shell path
```

确保 shell 路径正确（Windows 下推荐使用 PowerShell 或 Git Bash）。

### 4.6 PyCharm requirements.txt 管理

```
# PyCharm 可以自动从 requirements.txt 安装依赖
# 当打开项目时，检测到 requirements.txt 会提示安装

# 手动安装：
Tools → Sync Python Requirements

# 导出当前环境的依赖：
Terminal 中执行：pip freeze > requirements.txt
```

---

## 五、Conda 环境管理详解

### 5.1 Conda vs venv 对比

| 特性 | venv | Conda |
|------|------|-------|
| **管理范围** | 仅 Python 包 | Python + 非 Python 依赖 |
| **Python 版本** | 使用系统已安装的 | 可安装任意 Python 版本 |
| **包来源** | PyPI (pip) | conda-forge + PyPI |
| **适用场景** | 纯 Python 项目 | 数据科学、跨语言依赖 |
| **速度** | 快 | 较慢（依赖解析） |
| **占用空间** | 小 | 大 |

### 5.2 Conda 常用命令

```bash
# 创建环境
conda create -n myenv python=3.12

# 激活环境
conda activate myenv

# 退出环境
conda deactivate

# 列出所有环境
conda env list

# 安装包
conda install numpy pandas

# 从 conda-forge 安装
conda install -c conda-forge matplotlib

# 导出环境
conda env export > environment.yml

# 从 yml 文件创建环境
conda env create -f environment.yml

# 删除环境
conda env remove -n myenv
```

### 5.3 Conda environment.yml 示例

```yaml
name: myproject
channels:
  - conda-forge
  - defaults
dependencies:
  - python=3.12
  - numpy=1.26
  - pandas=2.1
  - matplotlib=3.8
  - pip:
    - some-pip-only-package==1.0.0
```

---

## 六、Cursor / Windsurf（VS Code 分支）

Cursor 和 Windsurf 都基于 VS Code，环境管理操作**完全相同**：

1. `Ctrl+Shift+P` → `Python: Select Interpreter`
2. 选择虚拟环境或 Conda 环境
3. 配置文件同样使用 `.vscode/settings.json`

> Cursor 和 Windsurf 的优势在于 AI 辅助编程，环境管理能力与 VS Code 一致。

---

## 七、Vim / Neovim 环境管理

适合终端用户，需要手动配置。

### 7.1 使用 pyenv 管理 Python 版本

```bash
# 安装 pyenv（Windows 使用 pyenv-win）
# https://github.com/pyenv-win/pyenv-win

# 安装 Python 版本
pyenv install 3.12.0
pyenv install 3.10.13

# 设置全局默认版本
pyenv global 3.12.0

# 为项目设置本地版本（在项目目录下执行）
pyenv local 3.10.13
```

### 7.2 Vim 中指定 Python 路径

```vim
" .vimrc 或 init.vim
let g:python3_host_prog = '/path/to/.venv/bin/python'
```

### 7.3 Neovim + LSP 配置（使用 pyright）

```lua
-- init.lua
require('lspconfig').pyright.setup {
  settings = {
    python = {
      pythonPath = vim.fn.getcwd() .. '/.venv/bin/python',
      analysis = {
        typeCheckingMode = "basic",
        autoSearchPaths = true,
      }
    }
  }
}
```

---

## 八、Jupyter 环境管理

### 8.1 在虚拟环境中使用 Jupyter

```bash
# 激活虚拟环境
source .venv/bin/activate  # 或 .venv\Scripts\activate

# 安装 ipykernel
pip install ipykernel

# 将虚拟环境注册为 Jupyter 内核
python -m ipykernel install --user --name=myproject --display-name "My Project (Python 3.12)"
```

### 8.2 管理 Jupyter 内核

```bash
# 列出所有内核
jupyter kernelspec list

# 删除内核
jupyter kernelspec uninstall myproject
```

### 8.3 VS Code 中的 Jupyter 环境

VS Code 的 Jupyter 扩展会自动检测已注册的内核，也可以在 Notebook 右上角直接选择 Python 环境。

---

## 九、多版本 Python 管理

### 9.1 Windows：pyenv-win

```bash
# 安装（PowerShell）
pip install pyenv-win --target %USERPROFILE%\.pyenv

# 或使用 Git
git clone https://github.com/pyenv-win/pyenv-win.git %USERPROFILE%\.pyenv

# 添加到环境变量
set PYENV=%USERPROFILE%\.pyenv
set PATH=%PYENV%\bin;%PYENV%\shims;%PATH%

# 使用
pyenv install 3.12.0
pyenv install 3.10.13
pyenv global 3.12.0
```

### 9.2 macOS/Linux：pyenv

```bash
# 安装
curl https://pyenv.run | bash

# 添加到 shell 配置（~/.bashrc 或 ~/.zshrc）
export PYENV_ROOT="$HOME/.pyenv"
export PATH="$PYENV_ROOT/bin:$PATH"
eval "$(pyenv init -)"

# 使用
pyenv install 3.12.0
pyenv global 3.12.0
```

### 9.3 Windows：官方多版本安装

Windows 也可以直接安装多个 Python 版本，使用 `py` 启动器切换：

```bash
# 列出已安装版本
py --list

# 使用指定版本运行
py -3.12 script.py
py -3.10 script.py

# 使用指定版本创建虚拟环境
py -3.12 -m venv .venv
```

---

## 十、推荐配置方案

### 方案一：VS Code + venv（轻量开发）

```
适合：Web 开发、脚本编写、日常开发

配置步骤：
1. 安装 VS Code + Python 扩展
2. 项目目录下 python -m venv .venv
3. Ctrl+Shift+P → Python: Select Interpreter → 选择 .venv
4. 配置 .vscode/settings.json（参考 3.5 节）
```

### 方案二：PyCharm + venv（专业开发）

```
适合：大型项目、团队协作、需要强大重构

配置步骤：
1. New Project → Virtualenv Environment → 创建 .venv
2. File → Settings → Python Interpreter 管理依赖
3. Tools → Sync Python Requirements 同步 requirements.txt
```

### 方案三：VS Code + Conda（数据科学）

```
适合：数据分析、机器学习、科学计算

配置步骤：
1. 安装 Anaconda 或 Miniconda
2. conda create -n myproject python=3.12 numpy pandas
3. VS Code → Python: Select Interpreter → Conda: myproject
4. 配置 Jupyter 内核
```

---

## 十一、常见问题排查

### Q1：VS Code 检测不到虚拟环境

```bash
# 检查虚拟环境是否存在
ls .venv/Scripts/python.exe  # Windows
ls .venv/bin/python           # macOS/Linux

# 如不存在，重新创建
python -m venv .venv

# 在 VS Code 中重新选择解释器
# Ctrl+Shift+P → Python: Select Interpreter → 手动输入路径
```

### Q2：终端中虚拟环境未自动激活

```json
// VS Code settings.json
{
    "python.terminal.activateEnvironment": true,
    "python.terminal.activateEnvInCurrentTerminal": "on"
}
```

如果使用 PowerShell 且遇到执行策略错误：

```bash
# 以管理员身份运行 PowerShell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### Q3：PyCharm 终端不显示虚拟环境名

```
File → Settings → Tools → Terminal → Shell path
改为：powershell.exe 或 bash.exe
```

### Q4：pip install 安装到了错误的环境

```bash
# 检查当前 pip 对应的 Python
pip --version

# 确保使用虚拟环境中的 pip
.venv/Scripts/pip install package_name  # Windows
.venv/bin/pip install package_name      # macOS/Linux

# 或先激活环境再安装
source .venv/bin/activate
pip install package_name
```
