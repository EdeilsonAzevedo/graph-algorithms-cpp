#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXPECTED="$SCRIPT_DIR/expected_costs.txt"
INPUT_DIR="$SCRIPT_DIR/inputs"
EXEC="$SCRIPT_DIR/../../Kruskal/kruskal"

echo "🔍 Testando custo da AGM (Kruskal ou Prim)"

while read line; do
    FILE=$(echo $line | awk '{print $1}')
    EXPECTED_COST=$(echo $line | awk '{print $2}')
    INPUT_PATH="$INPUT_DIR/$FILE"

    if [ ! -f "$INPUT_PATH" ]; then
        echo "⚠️  Arquivo não encontrado: $INPUT_PATH"
        continue
    fi

    ACTUAL_COST=$($EXEC < "$INPUT_PATH" | head -n 1)

    if [ "$ACTUAL_COST" = "$EXPECTED_COST" ]; then
        echo "✅ $FILE → custo correto ($ACTUAL_COST)"
    else
        echo "❌ $FILE → esperado: $EXPECTED_COST, obtido: $ACTUAL_COST"
    fi
done < "$EXPECTED"
