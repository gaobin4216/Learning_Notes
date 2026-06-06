# 编辑器如何对接 Python 环境

## 一、核心关系：编辑器只是个"调用者"

**编辑器本身不执行 Python 代码。** VS Code、PyCharm 都是高级文本编辑器。当你点"运行"，编辑器在背后做的事就是：

```
编辑器 → 调出终端 → 执行：python.exe your_file.py
```

同样，代码补全、类型检查、调试——都是编辑器调用 **python.exe**（或基于 python.exe 的语言服务器）来完成的。

所以编辑器唯一需要知道的就是：**用哪个 python.exe？**

---

## 二、解释器选择：编辑器的核心能力

### 2.1 编辑器会扫描哪些 python.exe？

当你在 VS Code 里按 `Ctrl+Shift+P` → `Python: Select Interpreter`，它会按优先级扫描：

```
1. 项目目录下的 .venv/ 或 venv/（自动检测到）
2. python.defaultInterpreterPath 指定的路径
3. 系统 PATH 环境变量里的 python
4. Conda 管理的所有环境
5. pyenv 安装的版本
```

选中的解释器路径会写入 `.vscode/settings.json`：

```json
{
    "python.defaultInterpreterPath": "${workspaceFolder}/.venv/Scripts/python.exe"
}
```

### 2.2 选了解释器后，编辑器用它做什么？

| 功能 | 实际调用 |
|------|----------|
| 运行代码 | `python.exe your_file.py` |
| 调试 | `python.exe -m debugpy your_file.py` |
| 代码补全/类型检查 | Pylance 语言服务器（背后用 python.exe 分析代码） |
| 终端打开 | 自动执行 activate 脚本，让终端里的 `python` 指向项目环境 |
| 测试 | `python.exe -m pytest tests/` |

**一句话**：选了解释器后，编辑器的所有 Python 相关功能都围绕这个 python.exe 工作。

---

## 三、VS Code 配置详解（推荐）

### 3.1 必装扩展

| 扩展 | 作用 |
|------|------|
| **Python**（微软官方） | 环境管理核心，必装 |
| **Pylance** | 类型检查 + 智能补全，通常随 Python 自动安装 |
| **Python Debugger** | 调试支持 |
| **Jupyter**（按需） | Notebook 支持 |

### 3.2 选择解释器的三种方式

**方式一：命令面板**
`Ctrl+Shift+P` → `Python: Select Interpreter` → 从列表中选择

**方式二：状态栏快捷切换**
点击 VS Code 左下角的 Python 版本号（如 `3.12.0 (.venv)`），直接弹出环境列表

**方式三：手动指定路径**
```json
// .vscode/settings.json
{
    "python.defaultInterpreterPath": "D:/myproject/.venv/Scripts/python.exe"
}
```

### 3.3 终端自动激活虚拟环境

```json
{
    "python.terminal.activateEnvironment": true,
    "python.terminal.activateEnvInCurrentTerminal": "on"
}
```

配置后，每次在 VS Code 中打开新终端，会自动执行 `.venv/Scripts/activate`。终端提示符会显示 `(.venv)`，之后直接 `pip install` 就装到项目环境里。

### 3.4 完整工作区配置

```json
// .vscode/settings.json
{
    // ===== 环境 =====
    "python.defaultInterpreterPath": "${workspaceFolder}/.venv/Scripts/python.exe",
    "python.terminal.activateEnvironment": true,
    "python.terminal.activateEnvInCurrentTerminal": "on",

    // ===== 代码质量 =====
    "python.analysis.typeCheckingMode": "basic",
    "python.analysis.autoSearchPaths": true,
    "python.analysis.extraPaths": ["./src"],

    // ===== 格式化 =====
    "[python]": {
        "editor.defaultFormatter": "ms-python.black-formatter",
        "editor.formatOnSave": true
    },

    // ===== 测试 =====
    "python.testing.pytestEnabled": true,
    "python.testing.pytestArgs": ["tests"],

    // ===== 隐藏不必要的文件 =====
    "files.exclude": {
        "**/__pycache__": true,
        "**/*.pyc": true,
        "**/.venv": true
    }
}
```

### 3.5 调试配置

```json
// .vscode/launch.json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Python: 当前文件",
            "type": "debugpy",
            "request": "launch",
            "program": "${file}",
            "console": "integratedTerminal",
            "cwd": "${workspaceFolder}"
        },
        {
            "name": "Python: 模块",
            "type": "debugpy",
            "request": "launch",
            "module": "mypackage",
            "console": "integratedTerminal",
            "cwd": "${workspaceFolder}"
        }
    ]
}
```

---

## 四、PyCharm 配置详解

### 4.1 项目解释器

PyCharm 在创建项目或配置已有项目时设置解释器：

- `File` → `Settings` → `Project: xxx` → `Python Interpreter`
- 点击齿轮 → `Add Interpreter`

支持的类型：

| 类型 | 说明 |
|------|------|
| Virtualenv Environment | 创建/使用 venv |
| Conda Environment | 创建/使用 conda 环境 |
| System Interpreter | 直接用系统安装的 python.exe |
| SSH Interpreter | 远程服务器上的 Python |
| Docker | 容器中的 Python |
| WSL | Windows Subsystem for Linux |

### 4.2 VS Code vs PyCharm 对比

| | VS Code | PyCharm |
|------|---------|---------|
| 启动速度 | 快 | 较慢 |
| 内存占用 | 小 | 大 |
| 开箱即用 | 需装扩展 | 开箱即用 |
| 重构能力 | 基础 | 强大（安全重命名、提取方法等） |
| 价格 | 免费 | Community 免费 / Pro 付费 |
| 适用 | 通用开发、多语言 | 专业 Python、大型项目 |

**建议**：大部分场景 VS Code 够用；做大型 Python 项目（Django/Flask + 数据库 + 前端）可以考虑 PyCharm Pro。

---

## 五、其他编辑器简述

### Cursor / Windsurf

基于 VS Code，环境管理的操作**完全一样**（`Ctrl+Shift+P` → `Python: Select Interpreter`）。

### Jupyter Lab/Notebook

Jupyter 有自己独立的内核（kernel）机制。要让虚拟环境在 Jupyter 中可用：

```bash
.venv\Scripts\activate
pip install ipykernel
python -m ipykernel install --user --name=myproject --display-name "My Project (Python 3.12)"
```

之后在 Jupyter 界面选择对应的 kernel 即可。

---

## 六、常见问题排查

### Q1：VS Code 检测不到刚创建的 .venv？

- 确认 `.venv/Scripts/python.exe`（或 `.venv/bin/python`）文件存在
- `Ctrl+Shift+P` → `Python: Select Interpreter` → `Enter interpreter path...` → 手动浏览到 python.exe

### Q2：终端里虚拟环境没自动激活？

检查两个设置是否开启：
```json
"python.terminal.activateEnvironment": true,
"python.terminal.activateEnvInCurrentTerminal": "on"
```
如果用了 PowerShell 报执行策略错误：
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### Q3：pip install 装到了错误的地方？

先看当前用的哪个 pip：
```bash
pip --version    # 输出会显示 pip 所属的 python 路径
```
如果路径不对，说明虚拟环境没激活。直接指定绝对路径来装：
```bash
.venv\Scripts\pip install requests    # Windows
.venv/bin/pip install requests        # Unix
```

### Q4：PyCharm 里改了代码但运行结果没变？

检查运行配置（Run Configuration）里的 ` Python interpreter` 是否指向你预期的环境——可能跑的是另一个 python.exe。
