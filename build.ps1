$ErrorActionPreference = "Stop"

if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

gcc -std=c11 -Wall -Wextra -pedantic -Iinclude `
    src/main.c src/adj_list_graph.c src/adj_matrix_graph.c `
    -o build/graph_practice.exe

Write-Host "Built build/graph_practice.exe"
