# Python 环境搭建与工具链配置

## 一、Python 安装

### Windows 安装

#### 方式一：官网下载（推荐）

1. 访问 [https://www.python.org/downloads/](https://www.python.org/downloads/)
2. 下载最新稳定版（如 Python 3.12.x）
3. 运行安装程序
4. **重要**：勾选 "Add Python to PATH"
5. 选择 "Install Now" 或自定义安装

```bash
# 验证安装
$ python --version
Python 3.12.2

$ pip --version
pip 24.0 from C:\Python312\Lib\site-packages\pip (python 3.12)
```

#### 方式二：Microsoft Store

1. 打开 Microsoft Store
2. 搜索 "Python 3.12"
3. 点击安装

> 优点：自动更新，配置简单

#### 方式三：Miniconda

```bash
# 下载 Miniconda
# https://docs.conda.io/en/latest/miniconda.html

# 安装后验证
$ conda --version
conda 24.1.2
```

### macOS 安装

```bash
# 方式一：Homebrew（推荐）
$ brew install python@3.12

# 验证
$ python3 --version
Python 3.12.2

# 方式二：官网下载 .pkg 安装包
```

### Linux 安装

```bash
# Ubuntu/Debian
$ sudo apt update
$ sudo apt install python3 python3-pip python3-venv

# CentOS/RHEL
$ sudo yum install python3

# Arch Linux
$ sudo pacman -S python python-pip

# 验证
$ python3 --version
Python 3.12.2
```

---

## 二、多版本管理

### 为什么需要多版本？

- 不同项目可能需要不同的 Python 版本
- 测试代码在多个版本下的兼容性
- 某些库只支持特定版本

### pyenv（Linux/macOS）

```bash
# 安装 pyenv
$ curl https://pyenv.run | bash

# 安装 Python 版本
$ pyenv install 3.11.0
$ pyenv install 3.12.0

# 设置全局版本
$ pyenv global 3.12.0

# 设置项目本地版本
$ pyenv local 3.11.0

# 查看已安装版本
$ pyenv versions
```

### pyenv-win（Windows）

```powershell
# 使用 PowerShell 安装
Invoke-WebRequest -UseBasicParsing -Uri "https://raw.githubusercontent.com/pyenv-win/pyenv-win/master/pyenv-win/install-pyenv-win.ps1" -OutFile "./install-pyenv-win.ps1"; &"./install-pyenv-win.ps1"

# 安装 Python 版本
pyenv install 3.12.0
pyenv install 3.11.0

# 设置全局版本
pyenv global 3.12.0
```

### 直接指定解释器

```bash
# 使用特定版本运行
$ python3.11 script.py
$ python3.12 script.py

# 创建虚拟环境时指定版本
$ python3.11 -m venv .venv
```

---

## 三、VS Code 配置

### 安装 Python 扩展

1. 打开 VS Code
2. 按 `Ctrl+Shift+X` 打开扩展面板
3. 搜索并安装 "Python" 扩展（微软官方）

### 配置 Python 解释器

1. 按 `Ctrl+Shift+P` 打开命令面板
2. 输入 "Python: Select Interpreter"
3. 选择你的 Python 版本或虚拟环境

### 推荐扩展

| 扩展 | 说明 |
|------|------|
| **Python** | 微软官方，必装 |
| **Pylance** | 智能补全、类型检查 |
| **Python Debugger** | 调试支持 |
| **Black Formatter** | 代码格式化 |
| **isort** | import 排序 |
| **Ruff** | 超快的 linter |
| **Jupyter** | Notebook 支持 |

### 工作区配置

`.vscode/settings.json`：

```json
{
    "python.defaultInterpreterPath": "${workspaceFolder}/.venv/Scripts/python.exe",
    "python.linting.enabled": true,
    "python.linting.ruffEnabled": true,
    "python.formatting.provider": "black",
    "editor.formatOnSave": true,
    "python.analysis.typeCheckingMode": "basic",
    "python.testing.pytestEnabled": true,
    "python.testing.pytestArgs": ["tests"],
    "files.exclude": {
        "**/__pycache__": true,
        "**/*.pyc": true,
        ".venv": true
    }
}
```

### 调试配置

`.vscode/launch.json`：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Python: Current File",
            "type": "debugpy",
            "request": "launch",
            "program": "${file}",
            "console": "integratedTerminal",
            "cwd": "${workspaceFolder}"
        },
        {
            "name": "Python: Module",
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

## 四、代码质量工具

### Linter（代码检查）

#### ruff（推荐，超快）

```bash
# 安装
pip install ruff

# 检查代码
ruff check .

# 自动修复
ruff check --fix .

# 格式化
ruff format .
```

`pyproject.toml` 配置：

```toml
[tool.ruff]
line-length = 88
target-version = "py38"

[tool.ruff.lint]
select = ["E", "F", "I", "N", "W", "UP"]
```

#### flake8

```bash
# 安装
pip install flake8

# 检查代码
flake8 src/ tests/
```

### Formatter（代码格式化）

#### black（推荐）

```bash
# 安装
pip install black

# 格式化单个文件
black main.py

# 格式化整个目录
black src/ tests/

# 检查但不修改
black --check src/
```

#### isort（import 排序）

```bash
# 安装
pip install isort

# 排序
isort src/ tests/

# 配合 black 使用
isort --profile black src/
```

### 类型检查

#### mypy

```bash
# 安装
pip install mypy

# 类型检查
mypy src/

# 配置 pyproject.toml
[tool.mypy]
python_version = "3.12"
warn_return_any = true
warn_unused_configs = true
```

### 综合配置

`pyproject.toml`：

```toml
[tool.black]
line-length = 88
target-version = ["py38"]

[tool.isort]
profile = "black"
line_length = 88

[tool.ruff]
line-length = 88
target-version = "py38"

[tool.ruff.lint]
select = ["E", "F", "I", "N", "W", "UP"]

[tool.mypy]
python_version = "3.12"
warn_return_any = true
```

---

## 五、测试工具

### pytest（推荐）

```bash
# 安装
pip install pytest

# 运行测试
pytest

# 运行特定文件
pytest tests/test_core.py

# 显示详细输出
pytest -v

# 显示打印输出
pytest -s

# 运行匹配的测试
pytest -k "test_user"

# 生成覆盖率报告
pytest --cov=src --cov-report=html
```

### 测试文件结构

```
tests/
├── __init__.py
├── conftest.py          # 共享的 fixtures
├── test_core.py
├── test_utils.py
└── test_models.py
```

```python
# conftest.py
import pytest

@pytest.fixture
def sample_user():
    return {"name": "Test User", "email": "test@example.com"}

# test_core.py
def test_create_user(sample_user):
    assert sample_user["name"] == "Test User"
```

### 单元测试 vs 集成测试

```
tests/
├── unit/               # 单元测试（快速，隔离）
│   ├── test_models.py
│   └── test_utils.py
├── integration/        # 集成测试（依赖外部服务）
│   ├── test_api.py
│   └── test_database.py
└── conftest.py
```

---

## 六、完整工具链配置示例

### 项目初始化脚本

```bash
#!/bin/bash
# init_project.sh

# 创建项目目录
mkdir myproject && cd myproject

# 创建虚拟环境
python -m venv .venv
source .venv/bin/activate  # Linux/macOS
# .venv\Scripts\activate   # Windows

# 安装开发依赖
pip install black ruff mypy pytest pytest-cov

# 创建项目结构
mkdir -p src/myproject tests docs
touch src/myproject/__init__.py
touch tests/__init__.py
touch tests/conftest.py

# 创建配置文件
cat > pyproject.toml << EOF
[project]
name = "myproject"
version = "0.1.0"
requires-python = ">=3.8"

[tool.black]
line-length = 88

[tool.ruff]
line-length = 88
select = ["E", "F", "I"]

[tool.pytest.ini_options]
testpaths = ["tests"]
EOF

cat > .gitignore << EOF
__pycache__/
*.pyc
.venv/
.env
EOF

# 初始化 Git
git init
git add .
git commit -m "Initial commit"
```

### Makefile

```makefile
.PHONY: install lint format test clean

install:
	pip install -r requirements.txt
	pip install -r requirements-dev.txt

lint:
	ruff check src/ tests/
	mypy src/

format:
	black src/ tests/
	isort --profile black src/ tests/

test:
	pytest tests/ -v --cov=src

clean:
	find . -type d -name __pycache__ -exec rm -rf {} +
	rm -rf build/ dist/ *.egg-info .pytest_cache .mypy_cache
```

---

## 七、常见问题

### pip 安装权限问题

```bash
# 不要用 sudo pip install
# 使用虚拟环境或 --user 参数
pip install --user requests
```

### 虚拟环境激活失败（Windows PowerShell）

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### Python 命令找不到

```bash
# Windows：检查 PATH 环境变量
# 或使用 python3 命令
$ python3 --version

# 或使用 py launcher（Windows）
$ py --version
$ py -3.12 script.py
```

### 编码问题

```python
# 文件开头添加
# -*- coding: utf-8 -*-

# 或设置环境变量
# Windows
set PYTHONUTF8=1

# Linux/macOS
export PYTHONUTF8=1
```

---

## 八、环境选择总结

| 场景 | 推荐方案 |
|------|----------|
| **Windows 开发** | 官网安装 + VS Code + venv |
| **macOS 开发** | Homebrew + VS Code + venv |
| **Linux 开发** | 系统包管理 + VS Code + venv |
| **数据科学** | Miniconda + Jupyter |
| **多版本管理** | pyenv（Linux/macOS）或 pyenv-win（Windows） |
| **团队协作** | poetry + pyproject.toml |
