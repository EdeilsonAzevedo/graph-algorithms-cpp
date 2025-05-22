set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXPECTED="${SCRIPT_DIR}/expected_costs.txt"
INPUT_DIR="${SCRIPT_DIR}/inputs"
EXEC="${SCRIPT_DIR}/../bin/kruskal"

echo "🔍 Testando custo da AGM (via Kruskal)"

while read -r FILE EXPECTED_COST; do
    INPUT_PATH="${INPUT_DIR}/${FILE}"
    if [[ ! -f "${INPUT_PATH}" ]]; then
        echo "⚠️  Arquivo não encontrado: ${INPUT_PATH}"
        continue
    fi

    # 1) Testa apenas o custo
    ACTUAL_COST="$(${EXEC} -f "${INPUT_PATH}" | head -n1)"
    if [[ "${ACTUAL_COST}" == "${EXPECTED_COST}" ]]; then
        echo "✅ ${FILE} → custo correto (${ACTUAL_COST})"
    else
        echo "❌ ${FILE} → custo esperado: ${EXPECTED_COST}, obtido: ${ACTUAL_COST}"
    fi
done < "${EXPECTED}"