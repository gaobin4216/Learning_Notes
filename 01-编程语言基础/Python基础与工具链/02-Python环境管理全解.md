# Python 环境管理全解

## 一、核心问题：为什么需要"环境"？

不同项目需要不同版本的依赖包：

```
项目 A → Django 3.2 + Python 3.8
项目 B → FastAPI 0.100 + Python 3.12
项目 C → PyTorch 2.0 + Python 3.10
```

如果把所有包都装在全局 python.exe 的 `site-packages` 里，版本会打架。

**环境管理的本质**：为每个项目创建**一套独立的 `python.exe` + `pip` + `site-packages`**，互不干扰。

---

## 二、虚拟环境的本质

### 2.1 它到底创建了什么？

```bash
python -m venv .venv
```

执行后，`.venv/` 目录结构：

```
.venv/
├── Scripts/          # Windows（Unix 上是 bin/）
│   ├── python.exe    # ← 这是当前项目的独立解释器
│   ├── pip.exe       # ← 独立的 pip，装包时安装到 .venv/Lib/
│   └── activate      #     激活脚本：把 .venv/Scripts 临时加到 PATH 最前面
├── Lib/              # site-packages/ 在这里（Unix 上是 lib/）
│   └── site-packages/
├── Include/
└── pyvenv.cfg        # 记录用哪个系统 python.exe 创建的
```

### 2.2 "激活"到底做了什么？

```bash
# Windows
.venv\Scripts\activate

# Unix
source .venv/bin/activate
```

**激活就是临时修改 `PATH` 环境变量**，把 `.venv/Scripts`（或 `bin/`）插到最前面。之后你在终端敲 `python` 或 `pip`，系统找到的是 `.venv/` 里的那个，而不是系统全局的。

```
激活前: python → C:\Python312\python.exe（全局）
激活后: python → D:\myproject\.venv\Scripts\python.exe（项目独立）
```

退出环境：`deactivate`（恢复原来的 PATH）。

### 2.3 关键认知

- 虚拟环境**不是虚拟机、不是容器**，就是一个目录
- 删除 `.venv/` 目录 = 彻底删除这个环境
- `.venv/` **不要提交到 Git**（加到 `.gitignore`）
- 每个项目成员自己 `python -m venv .venv` 创建，用 `requirements.txt` 同步装什么包

---

## 三、venv：标准库虚拟环境（推荐入门）

venv 是 Python 3.3+ 内置的，无需额外安装。

```bash
# 创建（使用当前默认的 python.exe）
python -m venv .venv

# 用指定版本的 python.exe 创建
py -3.12 -m venv .venv        # Windows
python3.12 -m venv .venv      # Unix

# 激活 + 使用
.venv\Scripts\activate         # Windows
source .venv/bin/activate     # Unix
pip install requests flask
pip freeze > requirements.txt # 导出依赖清单
deactivate
```

---

## 四、pip：Python 包管理器

pip 是 Python 官方的包安装工具，从 **PyPI**（Python Package Index，pypi.org）下载包。

### 基本命令

```bash
pip install requests              # 安装最新版
pip install requests==2.31.0      # 精确版本
pip install "requests>=2.28,<3.0" # 版本范围
pip install --upgrade requests    # 升级
pip uninstall requests            # 卸载
pip list                          # 查看已安装
pip show requests                 # 查看某个包的详情
```

### requirements.txt

```txt
# requirements.txt
requests==2.31.0
flask>=3.0.0
numpy~=1.24.0     # ~= 表示兼容版本：>=1.24.0 且 <1.25.0
```

```bash
pip install -r requirements.txt   # 批量安装
pip freeze > requirements.txt     # 导出当前环境
```

### 换国内镜像（加速下载）

```bash
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
```

常用镜像：清华（tuna）、阿里云（aliyun）、中科大（ustc）。

---

## 五、conda：跨语言环境管理（数据科学首选）

### 5.1 conda 与 pip 的核心区别

| | pip + venv | conda |
|---|---|---|
| 包来源 | PyPI（只有 Python 包） | conda-forge + PyPI |
| 管非 Python 依赖 | 不行 | 可以（C 库、CUDA 等） |
| Python 版本管理 | 不管（需 pyenv） | 内置——可直接装任意 Python 版本 |
| 环境管理 | 需配合 venv | 内置 |
| 适用场景 | 纯 Python 项目 | 数据科学、科学计算 |

conda 的核心优势：它不仅能装 Python 包，还能装 C/C++ 库、CUDA 运行时等。对 numpy/pandas/PyTorch 这类底层有 C 扩展的库，conda 能处理复杂的二进制依赖。

### 5.2 Miniconda vs Anaconda

- **Anaconda**：3GB+，预装 250+ 包，适合零基础
- **Miniconda**：~80MB，最小安装，按需装包（**推荐**）

### 5.3 常用命令

```bash
# 创建环境（同时指定 Python 版本）
conda create -n myproject python=3.12

# 激活/退出
conda activate myproject
conda deactivate

# 装包
conda install numpy pandas
conda install -c conda-forge jupyterlab   # 从 conda-forge 渠道安装

# 查看环境列表
conda env list

# 导出/导入
conda env export > environment.yml
conda env create -f environment.yml

# 删除环境
conda env remove -n myproject
```

---

## 六、pyenv：管理 Python 版本本身

venv/conda 管的是"项目用什么包"，**pyenv 管的是"机器上装了几个 Python 版本"**。

```bash
pyenv install 3.12.0    # 安装某个 Python 版本
pyenv install 3.10.13
pyenv versions          # 查看已安装的所有版本
pyenv global 3.12.0     # 设全局默认
pyenv local 3.10.13     # 当前项目用 3.10（写到 .python-version 文件）
```

**Windows** 上用 [pyenv-win](https://github.com/pyenv-win/pyenv-win)，或者直接用 Python 自带的 `py` 启动器。

### 工具分工关系

```
pyenv   → 管理"机器上装了几个 Python 版本"（python.exe 本身的版本）
venv    → 用某个版本的 python.exe，为项目创建隔离环境
pip     → 在某个环境里装/卸 Python 包
conda   → 同时做上面三件事（Python 版本 + 环境 + 包）
poetry  → 同时做后两件事（环境 + 包，现代项目管理）
```

---

## 七、poetry：现代项目管理工具

poetry 把**依赖管理、虚拟环境、打包发布**合为一体，用 `pyproject.toml` 替代 `requirements.txt`。

```bash
pip install poetry

# 新项目
poetry new myproject

# 已有项目
cd myproject && poetry init

# 添加依赖
poetry add requests flask
poetry add --group dev pytest black   # 开发依赖

# 安装所有依赖（自动创建虚拟环境）
poetry install

# 在项目环境中运行命令
poetry run python main.py
poetry run pytest

# 进入项目环境的 shell
poetry shell
```

poetry 的核心文件：

```toml
# pyproject.toml
[tool.poetry]
name = "myproject"
version = "0.1.0"
python = "^3.9"

[tool.poetry.dependencies]
requests = "^2.31.0"
flask = "^3.0"

[tool.poetry.group.dev.dependencies]
pytest = "^7.0"
black = "^23.0"
```

> `^2.31.0` 表示兼容版本：>=2.31.0 且 <3.0.0

poetry 会生成 `poetry.lock` 锁定精确版本，确保团队和 CI 环境一致。

---

## 八、工具选择

| 场景 | 推荐方案 |
|------|----------|
| 初学者 | pip + venv |
| 通用 Web/后端开发 | pip + venv 或 poetry |
| 数据科学/机器学习 | conda（Miniconda） |
| 库/包开发 | poetry |
| 团队协作 | poetry（有 lock 文件） |

---

## 九、常见问题

**Q: pip install 装到了全局而不是虚拟环境？**

先确认虚拟环境已激活——终端提示符前应该显示 `(.venv)`。如果没显示，重新激活。
```bash
# 不激活也可以直接指定：
.venv\Scripts\pip install requests   # Windows
.venv/bin/pip install requests       # Unix
```

**Q: PowerShell 报"无法加载文件"？**

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

**Q: 虚拟环境能拷贝到其他机器吗？**

不能。路径硬编码了，换机器就失效。正确做法：每台机器自己 `python -m venv .venv`，然后 `pip install -r requirements.txt`。
