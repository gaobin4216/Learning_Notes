# 包管理与虚拟环境：pip、conda 与 venv

## 一、为什么需要包管理？

### 包管理解决的问题

| 问题 | 说明 |
|------|------|
| **依赖管理** | 自动安装和管理第三方库 |
| **版本控制** | 指定和锁定包版本 |
| **环境隔离** | 不同项目使用不同版本的包 |
| **可复现性** | 确保团队和部署环境一致 |

### Python 包生态

```
Python 标准库（自带）
    ↓
第三方包（PyPI：Python Package Index）
    ↓
pip（包管理器）下载安装
```

> **PyPI**（Python Package Index）是 Python 官方的第三方包仓库，截至 2024 年有超过 50 万个包。

---

## 二、pip：Python 包管理器

### 什么是 pip？

pip（Pip Installs Packages）是 Python 官方的包管理工具，用于从 PyPI 安装和管理第三方包。

### 基本使用

```bash
# 安装包
pip install requests

# 安装指定版本
pip install requests==2.31.0

# 安装最低版本
pip install requests>=2.28.0

# 升级包
pip install --upgrade requests

# 卸载包
pip install uninstall requests

# 查看已安装的包
pip list

# 查看包信息
pip show requests

# 搜索包（已弃用，建议直接访问 PyPI 网站）
pip search requests
```

### requirements.txt

管理项目依赖的标准方式：

```txt
# requirements.txt
requests==2.31.0
flask>=3.0.0
numpy~=1.24.0
pandas
```

```bash
# 从文件安装所有依赖
pip install -r requirements.txt

# 导出当前环境的依赖
pip freeze > requirements.txt
```

### 版本说明符

| 符号 | 含义 | 示例 |
|------|------|------|
| `==` | 精确版本 | `requests==2.31.0` |
| `>=` | 最低版本 | `requests>=2.28.0` |
| `<=` | 最高版本 | `requests<=2.31.0` |
| `!=` | 排除版本 | `requests!=2.29.0` |
| `~=` | 兼容版本 | `requests~=2.31.0`（等价于 >=2.31.0, <2.32.0） |

### pip 配置

```bash
# 使用国内镜像源（加速下载）
pip install requests -i https://pypi.tuna.tsinghua.edu.cn/simple

# 永久配置镜像源
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
```

**常用国内镜像源**：

| 镜像 | 地址 |
|------|------|
| 清华 | https://pypi.tuna.tsinghua.edu.cn/simple |
| 阿里云 | https://mirrors.aliyun.com/pypi/simple |
| 中科大 | https://pypi.mirrors.ustc.edu.cn/simple |
| 豆瓣 | https://pypi.douban.com/simple |

---

## 三、venv：标准库虚拟环境

### 为什么需要虚拟环境？

```
问题场景：
项目 A 需要 requests==2.28.0
项目 B 需要 requests==2.31.0
→ 版本冲突！
```

虚拟环境为每个项目创建独立的 Python 环境，互不干扰。

### venv 基本使用

```bash
# 创建虚拟环境
python -m venv myenv

# 激活虚拟环境（Windows）
myenv\Scripts\activate

# 激活虚拟环境（Linux/macOS）
source myenv/bin/activate

# 退出虚拟环境
deactivate

# 查看当前使用的 Python
which python    # Linux/macOS
where python    # Windows
```

### 虚拟环境目录结构

```
myenv/
├── bin/            # Linux/macOS 可执行文件
│   ├── python
│   ├── pip
│   └── activate
├── Scripts/        # Windows 可执行文件
│   ├── python.exe
│   ├── pip.exe
│   └── activate.bat
├── lib/            # 安装的包
└── pyvenv.cfg      # 配置文件
```

### 最佳实践

```bash
# 1. 创建项目目录
mkdir myproject && cd myproject

# 2. 创建虚拟环境
python -m venv .venv

# 3. 激活虚拟环境
.venv\Scripts\activate  # Windows

# 4. 安装依赖
pip install requests flask

# 5. 导出依赖
pip freeze > requirements.txt

# 6. 提交到 Git（忽略虚拟环境目录）
echo ".venv/" >> .gitignore
```

---

## 四、conda：跨平台包与环境管理

### 什么是 conda？

conda 是一个跨平台的包管理和环境管理系统，由 Anaconda 公司开发。

### conda vs pip

| 特性 | pip | conda |
|------|-----|-------|
| **包来源** | PyPI | Anaconda 仓库 |
| **环境管理** | 需配合 venv | 内置 |
| **非 Python 包** | 不支持 | 支持（C/C++ 库） |
| **依赖解析** | 较弱 | 强大 |
| **适用场景** | 通用 Python 开发 | 数据科学、机器学习 |
| **安装体积** | 小 | 大（Anaconda 约 3GB） |

### Miniconda vs Anaconda

| 发行版 | 大小 | 包数量 | 适合场景 |
|--------|------|--------|----------|
| **Miniconda** | ~80MB | 最小安装 | 推荐，按需安装 |
| **Anaconda** | ~3GB | 250+ 预装包 | 数据科学入门 |

> **推荐**：使用 Miniconda，按需安装包。

### conda 基本使用

```bash
# 安装包
conda install numpy

# 安装指定版本
conda install numpy=1.24.0

# 安装多个包
conda install numpy pandas matplotlib

# 升级包
conda update numpy

# 卸载包
conda remove numpy

# 搜索包
conda search numpy

# 列出已安装的包
conda list
```

### conda 环境管理

```bash
# 创建环境
conda create -n myenv python=3.11

# 激活环境
conda activate myenv

# 退出环境
conda deactivate

# 列出所有环境
conda env list

# 删除环境
conda env remove -n myenv

# 导出环境
conda env export > environment.yml

# 从文件创建环境
conda env create -f environment.yml
```

### environment.yml

```yaml
name: myenv
channels:
  - defaults
  - conda-forge
dependencies:
  - python=3.11
  - numpy=1.24
  - pandas
  - matplotlib
  - pip:
    - some-pip-package
```

---

## 五、poetry：现代包管理工具

### 什么是 poetry？

poetry 是一个现代的 Python 包管理工具，集依赖管理、打包、发布于一体。

### poetry vs pip + venv

| 特性 | pip + venv | poetry |
|------|------------|--------|
| **依赖文件** | requirements.txt | pyproject.toml |
| **依赖解析** | 手动 | 自动 |
| **锁文件** | 无 | poetry.lock |
| **打包** | 需额外工具 | 内置 |
| **虚拟环境** | 手动创建 | 自动管理 |

### poetry 基本使用

```bash
# 安装 poetry
pip install poetry

# 创建新项目
poetry new myproject

# 初始化已有项目
poetry init

# 添加依赖
poetry add requests

# 添加开发依赖
poetry add --group dev pytest

# 安装所有依赖
poetry install

# 运行脚本
poetry run python main.py

# 激活虚拟环境
poetry shell
```

### pyproject.toml

```toml
[tool.poetry]
name = "myproject"
version = "0.1.0"
description = "My awesome project"
authors = ["Your Name <your.email@example.com>"]

[tool.poetry.dependencies]
python = "^3.9"
requests = "^2.31.0"
flask = "^3.0"

[tool.poetry.group.dev.dependencies]
pytest = "^7.0"
black = "^23.0"

[build-system]
requires = ["poetry-core"]
build-backend = "poetry.core.masonry.api"
```

---

## 六、工具选择建议

| 场景 | 推荐工具 |
|------|----------|
| **初学者** | pip + venv |
| **通用开发** | pip + venv 或 poetry |
| **数据科学** | conda（Miniconda） |
| **库开发** | poetry |
| **团队协作** | poetry 或 pip + requirements.txt |

### 推荐组合

```
日常开发：pip + venv + requirements.txt
现代项目：poetry + pyproject.toml
数据科学：conda + environment.yml
```

---

## 七、常见问题

### pip 安装慢

```bash
# 使用国内镜像
pip install requests -i https://pypi.tuna.tsinghua.edu.cn/simple

# 或永久配置
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
```

### 虚拟环境激活失败（Windows PowerShell）

```powershell
# 执行策略限制，需要允许脚本执行
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### 包版本冲突

```bash
# 查看依赖树
pip install pipdeptree
pipdeptree

# 查看冲突
pip check
```
