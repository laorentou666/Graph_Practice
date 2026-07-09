# Graph Practice

数据结构实践实验二：景区路径规划系统中的图存储结构实现。

- A 角色：邻接表实现，包含创建图、添加景点、添加路径、显示景区图、显示景点链表。
- B 角色：邻接矩阵实现，已从 `feature/matrix-graph` 分支合并到主分支。

## 工程目录

```text
Graph_Practice/
|-- include/
|   |-- adj_list_graph.h
|   |-- graph_matrix.h
|   `-- scenic_graph.h
|-- src/
|   |-- adj_list_graph.c
|   |-- graph_matrix.c
|   `-- main.c
|-- Makefile
|-- build.ps1
`-- README.md
```

## Build

Windows PowerShell:

```powershell
.\build.ps1
.\build\graph_practice.exe
```

Make:

```bash
make run
```

## 已实现功能

- A 角色邻接表：创建图、添加景点、添加路径、显示景区图、显示景点链表、释放链表内存。
- B 角色邻接矩阵：创建图、添加景点、添加路径、显示景点链表、显示邻接矩阵、显示景区路径图、释放图内存。

## Git 协作建议

A/B 角色分别在独立分支完成后合并到 `main`：

```bash
git switch -c role-a
git add .
git commit -m "Implement role A adjacency list graph"
git switch main
git merge --no-ff role-a
git merge --no-ff origin/feature/matrix-graph
```
