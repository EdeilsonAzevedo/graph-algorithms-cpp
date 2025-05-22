#!/bin/bash

BINARIO="../bin//pagerank"
INPUT_DIR="./inputs"
TOP_K=5
DAMPING=0.85

if [ ! -x "$BINARIO" ]; then
    echo "Erro: binário $BINARIO não encontrado ou não executável."
    exit 1
fi

if [ ! -d "$INPUT_DIR" ]; then
    echo "Erro: diretório $INPUT_DIR não encontrado."
    exit 1
fi

echo "📊 Executando PageRank nos arquivos em '$INPUT_DIR'..."
echo

for file in "$INPUT_DIR"/*.dat; do
    if [ -f "$file" ]; then
        echo "📁 Arquivo: $file"
        "$BINARIO" -f "$file" -d "$DAMPING" -k "$TOP_K"
        echo "---------------------------------------------"
    fi
done
