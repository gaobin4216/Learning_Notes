# Python 解释器与运行机制

## 一、python.exe 是什么？

**python.exe（Unix 上叫 python3）是 Python 语言的官方解释器——CPython 的可执行文件。** 它的工作很简单：读取 `.py` 源文件，转成字节码，然后在 Python 虚拟机里逐条执行。

```
my_script.py  →  python.exe  →  字节码(.pyc)  →  Python 虚拟机执行
```

理解这个模型的几个关键点：

1. **python.exe 是"翻译官"，不是"编译器"**。它不会产出独立的 .exe 文件，目标机器上必须有 python.exe 才能运行 .py 代码。
2. **代码补全、语法检查、调试——这些不是 python.exe 自己做的**，而是编辑器（VS Code 等）调用 python.exe 或语言服务器完成的。
3. **一台机器可以同时安装多个 python.exe**（不同版本、不同虚拟环境），编辑器需要知道"用哪一个"——这是后面环境管理和编辑器配置的核心问题。

---

## 二、编译型 vs 解释型

```
C/C++（编译型）：
  源代码 → 编译器 → 目标代码 → 链接器 → 可执行文件(.exe) → 直接运行

Python（解释型）：
  源代码 → 解释器(python.exe) → 字节码(.pyc) → Python 虚拟机执行
```

| 特性 | 编译型（C/C++） | 解释型（Python） |
|------|-----------------|------------------|
| 执行方式 | 先编译，产物可直接运行 | 运行时边解释边执行 |
| 运行速度 | 快（机器码） | 较慢（经过解释层） |
| 开发效率 | 低（编译-调试循环长） | 高（修改即运行） |
| 跨平台 | 需重新编译 | 源码到处可用（只要有解释器） |

> `.pyc` 是编译产物缓存（字节码），加速下次启动，但它仍然是字节码，仍需 python.exe 执行，不是机器码。

---

## 三、CPython 与其他实现

**CPython** 是官方参考实现（C 语言编写），就是你去 python.org 下载的那个。绝大多数场景用它即可。

| 实现 | 语言 | 特点 |
|------|------|------|
| **CPython** | C | 官方标准，生态最全，有 GIL |
| **PyPy** | RPython | JIT 编译，纯 Python 代码可快 5-10 倍 |
| **Jython** | Java | 跑在 JVM 上，可调 Java 库 |
| **IronPython** | C# | 跑在 .NET CLR 上 |
| **MicroPython** | C | 精简版，用于嵌入式/单片机 |

**GIL（全局解释器锁）**：CPython 的多线程受限于 GIL——同一时刻只有一个线程执行 Python 字节码。CPU 密集型任务用多进程（`multiprocessing`）而不是多线程。

---

## 四、Python 版本演进

Python 2 已于 **2020 年 1 月 1 日**停止支持，新项目必须用 Python 3。

| 版本 | 年份 | 关键特性 |
|------|------|----------|
| 3.6 | 2016 | f-string 格式化 |
| 3.7 | 2018 | dataclasses、`breakpoint()` |
| 3.8 | 2019 | 海象运算符 `:=` |
| 3.9 | 2020 | 字典合并 `|` |
| 3.10 | 2021 | `match/case` 结构化模式匹配 |
| 3.11 | 2022 | 性能提升 10-60%、异常组 |
| 3.12 | 2023 | f-string 改进、更好的错误消息 |
| 3.13 | 2024 | 自由线程模式（实验性，逐步移除 GIL） |

选择建议：用当前最新的稳定版（3.12+），除非依赖库有版本限制。

---

## 五、Python 的四种执行方式

### 1. 交互模式（REPL）

```bash
$ python          # 或 python3
>>> 2 + 3
5
>>> print("hello")
hello
>>> exit()
```

适合快速验证、学习语法。

### 2. 脚本模式

```bash
$ python hello.py     # python.exe 读取文件，逐行执行
```

这是编辑器"运行"按钮的本质：编辑器帮你调了这个命令。

### 3. 模块执行

```bash
$ python -m http.server 8000   # 直接运行标准库模块
$ python -m venv .venv         # 创建虚拟环境
```

### 4. Shebang（Unix）

```python
#!/usr/bin/env python3
print("Hello!")
```

```bash
$ chmod +x hello.py
$ ./hello.py
```

---

## 六、Windows 上的 py 启动器

Windows 上除了 `python` 和 `python3`，还有一个特殊的 **py 启动器**（安装 Python 时自动附带）：

```bash
py --list              # 列出所有已安装的 Python 版本
py -3.12 script.py     # 用 3.12 版本运行
py -3.10 -m venv .venv # 用 3.10 创建虚拟环境
```

`py` 启动器帮你自动选择已安装的 Python 版本，省去记路径的麻烦。它读取 `py.ini` 或环境变量来定位各版本的 python.exe。

---

## 七、关键概念速查

| 概念 | 你该知道什么 |
|------|------------|
| **python.exe** | 就是 CPython 解释器的可执行文件，执行 `.py` 代码 |
| **CPython** | Python 的官方实现，python.exe 就是它 |
| **GIL** | 多线程性能瓶颈，CPU 密集型用多进程 |
| **py 启动器** | Windows 特有，方便切换多版本 |
| **字节码 .pyc** | 编译缓存，不是机器码，仍需解释器 |
