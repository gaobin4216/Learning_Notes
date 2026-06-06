# WPF（Windows Presentation Foundation）

> **一句话：微软老牌 Windows 桌面 UI 框架，XAML 写界面 + C# 写逻辑，比 WinUI3 成熟稳定，比 WinForm 现代强大。**

---

## 一、WPF 是什么

WPF 是 2006 年随 .NET 3.0 推出的 Windows 桌面 UI 框架，用来替代 WinForm。引入了 XAML 声明式 UI、数据绑定、样式模板等现代理念，至今仍是 Windows 桌面开发主力。

**核心定位：**
- 比 WinForm 现代（矢量图形、动画、3D、样式模板）
- 比 WinUI3 成熟（18 年积累，生态完善，坑少）
- 仅限 Windows，不跨平台

### WinForm vs WPF vs WinUI3

| | WinForm | WPF | WinUI3 |
|---|---|---|---|
| 年代 | 2002 | 2006 | 2021 |
| UI 写法 | C# 拖控件 | XAML 声明式 | XAML 声明式 |
| 渲染 | GDI（像素级） | DirectX（GPU 加速） | DirectX（GPU 加速） |
| 布局 | 绝对定位为主 | Grid/StackPanel 等自适应容器 | Grid/StackPanel 等 |
| 数据绑定 | 几乎没有 | 强大的绑定 + MVVM | 强大的绑定 + MVVM |
| 高 DPI | 差（容易模糊） | 好（矢量渲染） | 好 |
| 现状 | 维护模式 | 活跃维护 | 积极发展 |
| 适合 | 简单工具 | 企业应用、复杂 UI | 新项目、Fluent Design |

> WPF 和 WinUI3 都用 XAML + C# + MVVM，技能可以迁移。

---

## 二、核心概念

### XAML

XAML 用 XML 语法声明 UI 元素，负责"界面长什么样"，C# 负责"点了之后干什么"。

```xml
<Window x:Class="MyApp.MainWindow" Title="我的应用" Height="450" Width="800">
    <Grid>
        <StackPanel VerticalAlignment="Center" HorizontalAlignment="Center">
            <TextBlock Text="Hello WPF" FontSize="24" Margin="0,0,0,10"/>
            <Button Content="点击我" Click="Button_Click" Padding="20,10"/>
        </StackPanel>
    </Grid>
</Window>
```

### 数据绑定

WPF 最强大的特性——UI 自动同步数据，不用手动赋值。

```csharp
// ViewModel
public class MainViewModel : INotifyPropertyChanged
{
    private string _name = "World";
    public string Name
    {
        get => _name;
        set { _name = value; OnPropertyChanged(); }
    }
    public event PropertyChangedEventHandler PropertyChanged;
    protected void OnPropertyChanged([CallerMemberName] string prop = null)
        => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
}
```

```xml
<TextBlock Text="{Binding Name}" FontSize="24"/>
<TextBox Text="{Binding Name, UpdateSourceTrigger=PropertyChanged}"/>
```

修改 TextBox 内容，TextBlock 自动更新——数据绑定的威力。

### MVVM 模式

```
View (XAML)  ←→  ViewModel (C#)  ←→  Model (数据)
界面展示          数据绑定/命令          业务逻辑
```

- **View**：XAML 界面，不写业务逻辑
- **ViewModel**：暴露属性和命令给 View 绑定
- **Model**：纯粹的数据和业务逻辑

---

## 三、常用布局容器

| 容器 | 用途 | 类比 |
|------|------|------|
| **Grid** | 网格布局，最灵活 | CSS Grid |
| **StackPanel** | 水平/垂直堆叠 | Flexbox |
| **DockPanel** | 停靠布局 | CSS float |
| **WrapPanel** | 自动换行流式布局 | Flexbox + wrap |
| **Canvas** | 绝对定位 | position: absolute |

```xml
<Grid>
    <Grid.RowDefinitions>
        <RowDefinition Height="Auto"/>   <!-- 标题 -->
        <RowDefinition Height="*"/>      <!-- 内容区 -->
        <RowDefinition Height="Auto"/>   <!-- 底部 -->
    </Grid.RowDefinitions>
    <TextBlock Grid.Row="0" Text="标题" FontSize="20"/>
    <ContentControl Grid.Row="1" Content="{Binding MainContent}"/>
    <Button Grid.Row="2" Content="确定"/>
</Grid>
```

---

## 四、开发环境

1. 安装 **Visual Studio 2022**（Community 版免费）
2. 勾选 **".NET 桌面开发"** 工作负载
3. 新建项目 → 搜索 "WPF" → 选择 WPF 应用程序
4. 选择 .NET 版本（推荐 .NET 8）

> 新项目强烈建议 .NET 8，性能更好。虽然 WPF 本身不跨平台，但业务逻辑层可以跨平台复用。

---

## 五、项目结构

```
MyWpfApp/
├── App.xaml / App.xaml.cs          ← 应用入口
├── MainWindow.xaml / .xaml.cs      ← 主窗口（View）
├── ViewModels/
│   └── MainViewModel.cs           ← ViewModel
├── Models/
│   └── User.cs                    ← 数据模型
├── Converters/
│   └── BoolToVisibilityConverter.cs ← 值转换器
└── Resources/
    └── Styles.xaml                ← 全局样式
```

---

## 六、优缺点

| 优点 | 缺点 |
|------|------|
| 成熟稳定，18 年积累 | 仅限 Windows |
| 生态丰富（DevExpress、Telerik 等控件库） | 学习曲线较陡（绑定/模板/样式体系庞大） |
| XAML + MVVM 开发体验好 | 启动速度较慢（加载 .NET 运行时） |
| GPU 加速渲染，矢量图形 | 打包体积较大 |
| 高 DPI、多显示器支持好 | |
