# Python 项目结构与模块化

## 一、模块与包

### 模块 = `.py` 文件

```python
# utils.py —— 这就是一个模块
def add(a, b):
    return a + b
```

```python
# main.py —— 在别的模块里导入
import utils
print(utils.add(2, 3))  # 5
```

### 包 = 含 `__init__.py` 的目录

```
mypackage/
├── __init__.py    # 空文件也行，标识这是 Python 包
├── utils.py
└── models.py
```

```python
# 导入包里的模块
from mypackage import utils
from mypackage.utils import add
import mypackage.utils  # 全限定名访问
```

### 导入方式一览

```python
import os                    # 导入模块，用 os.path 访问
import numpy as np           # 重命名
from os.path import join     # 导入指定成员
from . import utils          # 相对导入（同包内）
from .core import Engine     # 相对导入（同包子目录）
from .. import config        # 相对导入（上级包）
```

**推荐绝对导入**（`from mypackage.core import Engine`），清晰不易出错。同包内部可用相对导入（`from . import utils`）。

---

## 二、标准项目结构

### 简单项目（脚本/小工具）

```
myproject/
├── main.py
├── utils.py
├── requirements.txt
└── README.md
```

### 中型项目（推荐模板）

```
myproject/
├── src/
│   └── mypackage/
│       ├── __init__.py
│       ├── core.py
│       ├── utils.py
│       └── models.py
├── tests/
│   ├── __init__.py
│   ├── test_core.py
│   └── test_utils.py
├── .venv/              # 虚拟环境（不提交）
├── requirements.txt
├── .gitignore
└── README.md
```

### 大型项目

```
myproject/
├── src/
│   └── mypackage/
│       ├── __init__.py
│       ├── core/           # 核心逻辑
│       ├── models/         # 数据模型
│       ├── api/            # API 路由/处理
│       ├── utils/          # 工具函数
│       └── config.py
├── tests/
│   ├── unit/
│   ├── integration/
│   └── conftest.py
├── docs/
├── scripts/
├── pyproject.toml
├── .env.example
├── .gitignore
├── Makefile
└── README.md
```

---

## 三、`__init__.py` 的常见用法

```python
# __init__.py

# 1. 空文件——最简单，只标识这是包

# 2. 控制导出（from mypackage import * 时有效）
from .core import Engine
from .models import User

__all__ = ["Engine", "User"]

# 3. 包版本信息
__version__ = "1.0.0"
```

Python 3.3+ 支持 **隐式命名空间包**（没有 `__init__.py` 也能当包用），但显式写 `__init__.py` 仍然是推荐做法——语义清晰。

---

## 四、`__main__.py`：让包可直接运行

```
mypackage/
├── __init__.py
├── __main__.py    # python -m mypackage 时执行这个文件
└── core.py
```

```python
# __main__.py
from .core import main

if __name__ == "__main__":
    main()
```

```bash
python -m mypackage    # 等价于运行 __main__.py
```

---

## 五、配置文件管理

### 方式对比

| 方式 | 适合场景 |
|------|----------|
| `.py` 文件 | 需要逻辑的复杂配置 |
| `.env` + 环境变量 | 敏感信息（密钥、密码） |
| `pyproject.toml` | 项目元数据、工具配置（现代标准） |
| YAML | 结构化、可读性要求高的配置 |

### 推荐：环境变量 + .env

```python
# config.py
import os

DEBUG = os.getenv("DEBUG", "False").lower() == "true"
SECRET_KEY = os.getenv("SECRET_KEY")
DATABASE_URL = os.getenv("DATABASE_URL", "sqlite:///db.sqlite3")
```

```bash
# .env（不提交到 Git）
DEBUG=True
SECRET_KEY=abc123xyz
DATABASE_URL=postgresql://user:pass@localhost/mydb
```

```python
# 用 python-dotenv 自动加载 .env
from dotenv import load_dotenv
load_dotenv()
```

---

## 六、`.gitignore` 必备内容

```gitignore
# Python
__pycache__/
*.py[cod]
*.so
build/
dist/
*.egg-info/

# 虚拟环境
.venv/
venv/

# 环境变量
.env
.env.local

# IDE
.vscode/
.idea/

# 测试
.pytest_cache/
.coverage
htmlcov/
```

---

## 七、模块化原则

1. **单一职责**：一个模块只做一件事
2. **控制导出**：用 `__all__` 明确公共接口
3. **避免循环导入**：A import B 且 B import A → 重构，把共同依赖抽到第三个模块
4. **配置外部化**：密钥、连接串走环境变量，不硬编码
