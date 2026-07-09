# Graph Practice - B 角色：邻接矩阵图实现

本工程完成实验二中 **B 角色：邻接矩阵存储结构的图实现**。

## 已实现功能

- 创建图 `graph_create`
- 添加景点 `graph_add_spot`
- 添加路径 `graph_add_path`
- 显示景区图 `graph_display`
- 显示景点链表 `graph_display_spots`
- 显示邻接矩阵 `graph_display_matrix`
- 释放图内存 `graph_destroy`

## 工程目录结构

```text
Graph_Practice/
├── include/
│   └── graph_matrix.h      # 邻接矩阵图模块头文件
├── src/
│   ├── graph_matrix.c      # 邻接矩阵图模块实现
│   └── main.c              # 功能验证入口
├── Makefile                # 自动化编译脚本
└── README.md               # 项目说明
```

## 编译与运行

如果已安装 GCC 和 Make：

```bash
make
make run
```

Windows 下也可直接使用 GCC 编译：

```powershell
gcc -std=c11 -Wall -Wextra -Iinclude src/main.c src/graph_matrix.c -o scenic_matrix.exe
.\scenic_matrix.exe
```

Linux/macOS 下直接编译：

```bash
gcc -std=c11 -Wall -Wextra -Iinclude src/main.c src/graph_matrix.c -o scenic_matrix
./scenic_matrix
```

## 示例输出说明

程序会创建一个无向景区图，添加 5 个景点和 6 条路径，然后依次输出：

1. 景点链表
2. 邻接矩阵
3. 景区路径图

邻接矩阵中：

- `0` 表示景点自身到自身距离为 0
- `∞` 表示两个景点之间暂无直接路径
- 正整数表示两个景点之间的路径距离，单位为米

## Git 协作建议

B 角色可以在独立分支完成本模块：

```bash
git checkout -b feature/matrix-graph
git add .
git commit -m "feat: implement matrix graph for role B"
git push origin feature/matrix-graph
```

然后在 GitHub 上发起 Pull Request，合并到主分支。
