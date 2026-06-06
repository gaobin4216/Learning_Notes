# Python 工具链：代码质量与测试

## 一、工具链全景

```
代码格式化  →  black, ruff format
import 排序 →  ruff（替代 isort）
代码检查    →  ruff（替代 flake8）
类型检查    →  mypy
测试        →  pytest
覆盖率      →  pytest-cov
```

现代推荐组合：**ruff + mypy + pytest**，统一用 `pyproject.toml` 配置。

---

## 二、ruff：一站式 Linter + Formatter（推荐）

ruff 用 Rust 编写，比 flake8 快 10-100 倍，同时替代 flake8（检查）、isort（import 排序）、pyflakes 等多个工具。

```bash
pip install ruff

ruff check .           # 检查代码
ruff check --fix .     # 自动修复
ruff format .          # 格式化
ruff format --check .  # 仅检查，不修改
```

### pyproject.toml 配置

```toml
[tool.ruff]
line-length = 88
target-version = "py38"

[tool.ruff.lint]
select = [
    "E",     # pycodestyle errors
    "F",     # pyflakes
    "I",     # isort（import 排序）
    "N",     # pep8-naming
    "W",     # pycodestyle warnings
    "UP",    # pyupgrade（语法现代化）
]
ignore = ["E501"]  # 忽略行太长（交给 formatter 处理）

[tool.ruff.format]
quote-style = "double"
```

### VS Code 集成

安装 **Ruff** 扩展，然后：

```json
// .vscode/settings.json
{
    "[python]": {
        "editor.defaultFormatter": "charliermarsh.ruff",
        "editor.formatOnSave": true,
        "editor.codeActionsOnSave": {
            "source.fixAll.ruff": "explicit",
            "source.organizeImports.ruff": "explicit"
        }
    }
}
```

---

## 三、black：纯格式化工具（备选）

如果不用 ruff format，black 是最流行的格式化工具。它强制统一风格，零配置。

```bash
pip install black
black src/ tests/
black --check --diff src/  # 仅预览差异，不实际修改
```

```toml
# pyproject.toml
[tool.black]
line-length = 88
target-version = ["py38"]
```

---

## 四、mypy：类型检查

```bash
pip install mypy
mypy src/
```

```toml
# pyproject.toml
[tool.mypy]
python_version = "3.12"
warn_return_any = true
warn_unused_configs = true
ignore_missing_imports = true
```

mypy 检查的是**类型注解**：

```python
def add(a: int, b: int) -> int:
    return a + b

add(1, "2")   # mypy 报错：Argument 2 has incompatible type "str"
```

类型注解不会影响运行时行为，但能提前发现大量 bug。

---

## 五、pytest：测试框架

```bash
pip install pytest pytest-cov
```

### 基本使用

```bash
pytest                          # 运行所有测试
pytest tests/test_core.py       # 运行指定文件
pytest -v                       # 详细输出
pytest -k "test_user"           # 运行名称匹配的测试
pytest --cov=src --cov-report=html  # 覆盖率报告
```

### 测试文件结构

```
tests/
├── __init__.py
├── conftest.py          # 共享 fixtures
├── test_core.py
└── test_utils.py
```

```python
# conftest.py —— 共享的测试数据/工具
import pytest

@pytest.fixture
def sample_data():
    return {"name": "Alice", "age": 30}
```

```python
# test_core.py
def test_get_name(sample_data):
    assert sample_data["name"] == "Alice"
```

---

## 六、Makefile：命令简写

把常用命令集中到一个文件，不用每次都敲长命令：

```makefile
.PHONY: install lint format test clean

install:
	pip install -r requirements.txt
	pip install -r requirements-dev.txt

lint:
	ruff check src/ tests/
	mypy src/

format:
	ruff format src/ tests/
	ruff check --fix src/ tests/

test:
	pytest tests/ -v --cov=src

clean:
	find . -type d -name __pycache__ -exec rm -rf {} +
	rm -rf .pytest_cache .mypy_cache .ruff_cache
```

使用：

```bash
make lint     # 一键检查
make format   # 一键格式化
make test     # 一键测试
```

---

## 七、完整 pyproject.toml 汇总

```toml
[project]
name = "myproject"
version = "0.1.0"
requires-python = ">=3.9"

[tool.ruff]
line-length = 88
target-version = "py38"

[tool.ruff.lint]
select = ["E", "F", "I", "N", "W", "UP"]

[tool.mypy]
python_version = "3.12"
warn_return_any = true
ignore_missing_imports = true

[tool.pytest.ini_options]
testpaths = ["tests"]
addopts = "-v --cov=src"
```

这一个文件替代了过去分散的 `setup.cfg`、`.flake8`、`.isort.cfg`、`mypy.ini` 等。

---

## 八、工具速查

| 工具 | 用途 | 命令 |
|------|------|------|
| ruff | 检查 + 格式化（推荐） | `ruff check .` / `ruff format .` |
| black | 纯格式化 | `black src/` |
| mypy | 类型检查 | `mypy src/` |
| pytest | 测试 | `pytest -v` |
| pytest-cov | 覆盖率 | `pytest --cov=src` |
