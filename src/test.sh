#!/usr/bin/env bash
# Testes de comportamento: roda a corrida várias vezes e verifica as invariantes.
set -euo pipefail
cd "$(dirname "$0")"

falhas=0
verifica() { if eval "$2"; then echo "ok   - $1"; else echo "FAIL - $1"; falhas=$((falhas + 1)); fi; }

for n in 1 4 16 64; do
    saida=$(./corrida "$n" 50)
    verifica "$n threads: exatamente uma vencedora" '[ "$(grep -c "venceu!" <<<"$saida")" -eq 1 ]'
    verifica "$n threads: toda thread conta até o fim" '[ "$(grep -cE "^Thread [0-9]+: 50$" <<<"$saida")" -eq "$n" ]'
    vencedora=$(sed -n "s/^Thread vencedora: //p" <<<"$saida")
    verifica "$n threads: vencedora anunciada é válida" '[ "$vencedora" -ge 0 ] && [ "$vencedora" -lt "$n" ]'
done

verifica "rejeita execução sem argumentos" '! ./corrida 2>/dev/null'
verifica "rejeita número inválido" '! ./corrida abc 2>/dev/null && ! ./corrida 0 2>/dev/null'

[ "$falhas" -eq 0 ] && echo "Todos os testes passaram." || { echo "$falhas teste(s) falharam."; exit 1; }
