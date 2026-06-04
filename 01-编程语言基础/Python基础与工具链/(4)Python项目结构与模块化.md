# Python 项目结构与模块化

## 一、Python 模块与包

### 模块（Module）

一个 `.py` 文件就是一个模块。

```python
# math_utils.py
def add(a, b):
    return a + b

def multiply(a, b):
    return a * b
```

```python
# main.py
import math_utils

result = math_utils.add(2, 3)  # 5
```

### 包（Package）

包含 `__init__.py` 文件的目录就是包。

```
myproject/
├── mypackage/
│   ├── __init__.py      # 包标识文件
│   ├── utils.py
│   └── models.py
└── main.py
```

```python
# __init__.py
from .utils import helper
from .models import User
```

```python
# main.py
from mypackage import helper, User
```

### 导入方式

```python
# 导入整个模块
import os
os.path.join("a", "b")

# 导入模块并重命名
import numpy as np
np.array([1, 2, 3])

# 导入模块中的特定成员
from os.path import join, exists
join("a", "b")

# 导入所有成员（不推荐，容易命名冲突）
from os import *
```

---

## 二、标准项目结构

### 简单项目

```
myproject/
├── main.py              # 程序入口
├── utils.py             # 工具函数
├── config.py            # 配置文件
├── requirements.txt     # 依赖列表
└── README.md            # 项目说明
```

### 中型项目

```
myproject/
├── src/                 # 源代码目录
│   └── mypackage/
│       ├── __init__.py
│       ├── core.py      # 核心功能
│       ├── utils.py     # 工具函数
│       └── models.py    # 数据模型
├── tests/               # 测试目录
│   ├── __init__.py
│   ├── test_core.py
│   └── test_utils.py
├── docs/                # 文档
├── data/                # 数据文件
├── scripts/             # 脚本
├── requirements.txt     # 依赖
├── setup.py             # 打包配置
├── .gitignore           # Git 忽略规则
└── README.md            # 项目说明
```

### 大型项目（推荐）

```
myproject/
├── src/
│   └── mypackage/
│       ├── __init__.py
│       ├── core/
│       │   ├── __init__.py
│       │   ├── engine.py
│       │   └── processor.py
│       ├── models/
│       │   ├── __init__.py
│       │   ├── user.py
│       │   └── product.py
│       ├── api/
│       │   ├── __init__.py
│       │   ├── routes.py
│       │   └── handlers.py
│       ├── utils/
│       │   ├── __init__.py
│       │   ├── helpers.py
│       │   └── validators.py
│       └── config.py
├── tests/
│   ├── unit/
│   ├── integration/
│   └── conftest.py
├── docs/
├── scripts/
├── pyproject.toml       # 项目配置（现代标准）
├── poetry.lock          # 依赖锁定
├── .env                 # 环境变量（不提交）
├── .env.example         # 环境变量示例
├── .gitignore
├── Makefile             # 常用命令
└── README.md
```

---

## 三、`__init__.py` 的作用

### 基本作用

1. 标识目录为 Python 包
2. 控制包的导入行为

### 常见用法

```python
# __init__.py

# 空文件（最简单）
```

```python
# __init__.py

# 导出公共接口
from .core import Engine
from .models import User, Product

__all__ = ["Engine", "User", "Product"]
```

```python
# __init__.py

# 版本信息
__version__ = "1.0.0"
__author__ = "Your Name"
```

### 包级别初始化

```python
# __init__.py

import logging

# 配置包级别的日志
logging.getLogger(__name__).addHandler(logging.NullHandler())

# 初始化数据库连接
db = init_database()
```

---

## 四、Python 路径与导入

### `sys.path`

Python 查找模块的路径列表：

```python
import sys
print(sys.path)

# 输出类似：
# ['', '/usr/lib/python3.11', '/usr/lib/python3.11/lib-dynload', ...]
```

### 相对导入 vs 绝对导入

```python
# 绝对导入（推荐）
from mypackage.core import Engine
from mypackage.models import User

# 相对导入（同包内使用）
from . import utils           # 当前包的 utils
from .core import Engine      # 当前包的 core.Engine
from .. import config         # 上级包的 config
```

### `__main__.py`

当包被直接运行时执行的文件：

```
mypackage/
├── __init__.py
├── __main__.py    # python -m mypackage 时执行
└── core.py
```

```python
# __main__.py
from .core import main

if __name__ == "__main__":
    main()
```

```bash
# 直接运行包
$ python -m mypackage
```

---

## 五、配置文件管理

### 配置文件方式对比

| 方式 | 优点 | 缺点 |
|------|------|------|
| **Python 文件** | 支持逻辑、类型安全 | 不便非程序员编辑 |
| **JSON** | 广泛支持 | 不支持注释 |
| **YAML** | 可读性好 | 依赖第三方库 |
| **TOML** | Python 标准 | 较新 |
| **环境变量** | 安全、灵活 | 不便管理大量配置 |

### 推荐方式：环境变量 + 配置文件

```python
# config.py
import os
from pathlib import Path

# 基础配置
BASE_DIR = Path(__file__).parent
DEBUG = os.getenv("DEBUG", "False").lower() == "true"
SECRET_KEY = os.getenv("SECRET_KEY", "default-secret-key")

# 数据库配置
DATABASE_URL = os.getenv("DATABASE_URL", "sqlite:///db.sqlite3")

# API 配置
API_KEY = os.getenv("API_KEY")
API_TIMEOUT = int(os.getenv("API_TIMEOUT", "30"))
```

```
# .env（不提交到 Git）
DEBUG=True
SECRET_KEY=my-secret-key-123
DATABASE_URL=postgresql://user:pass@localhost/mydb
API_KEY=abc123
```

```python
# 使用 python-dotenv 加载 .env 文件
from dotenv import load_dotenv
load_dotenv()
```

### `.gitignore` 配置

```gitignore
# Python
__pycache__/
*.py[cod]
*$py.class
*.so
.Python
build/
dist/
*.egg-info/
.eggs/

# 虚拟环境
.venv/
venv/
ENV/

# 环境变量
.env
.env.local

# IDE
.vscode/
.idea/
*.swp
*.swo

# 测试
.coverage
htmlcov/
.pytest_cache/

# 系统文件
.DS_Store
Thumbs.db
```

---

## 六、Makefile 常用命令

```makefile
# Makefile

.PHONY: install test lint format run clean

# 安装依赖
install:
	pip install -r requirements.txt

# 安装开发依赖
install-dev:
	pip install -r requirements-dev.txt

# 运行测试
test:
	pytest tests/ -v

# 代码检查
lint:
	flake8 src/ tests/
	mypy src/

# 代码格式化
format:
	black src/ tests/
	isort src/ tests/

# 运行程序
run:
	python -m mypackage

# 清理临时文件
clean:
	find . -type d -name __pycache__ -exec rm -rf {} +
	find . -type f -name "*.pyc" -delete
	rm -rf build/ dist/ *.egg-info

# 构建包
build:
	python -m build
```

---

## 七、发布自己的包

### 使用 poetry 发布

```bash
# 1. 初始化项目
poetry init

# 2. 配置 pyproject.toml
# 3. 构建
poetry build

# 4. 发布到 PyPI
poetry publish
```

### 使用 setuptools 发布

```python
# setup.py
from setuptools import setup, find_packages

setup(
    name="mypackage",
    version="1.0.0",
    author="Your Name",
    author_email="your.email@example.com",
    description="A short description",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    url="https://github.com/username/mypackage",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    python_requires=">=3.8",
    install_requires=[
        "requests>=2.28.0",
    ],
)
```

```bash
# 构建
python setup.py sdist bdist_wheel

# 上传到 PyPI
twine upload dist/*
```

---

## 八、模块化最佳实践

1. **单一职责**：每个模块只负责一个功能
2. **明确接口**：通过 `__all__` 控制导出
3. **避免循环导入**：合理组织模块依赖关系
4. **使用相对导入**：同包内使用相对导入
5. **配置外部化**：敏感信息使用环境变量
6. **文档字符串**：为模块和函数添加 docstring
