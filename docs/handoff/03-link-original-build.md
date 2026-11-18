# Задача 4. Контрольная сборка из оригинала

18 ноября 2026 года ROM версии 2.0beta2 воспроизведён из приложенного
`Pole_Chudes.rar` на коммите `6267611deaaba57a8b9d05e1dafa837993d9a221`.
В пустом дереве импортер проверил размер и SHA-256 всех шести файлов.
Сборка извлекла 495 пар слов и тем. Побайтовое сравнение с
`downloads/pole.2.0beta2.gba` прошло для обеих выходных копий.
Размер ROM — 1 048 576 байт, SHA-256 —
`ff25c5f0ab6e59c00f47964f18379543801224c2118a77e7f2762c49d19a6521`.
Копия ROM, скачанная с GitHub по полному SHA коммита, также совпала побайтно.
[Отчёт с контрольными суммами](../verification/link-original-build.json).

## Воспроизведение

Из корня репозитория выполните команды ниже. Укажите абсолютный путь к
архиву в `POLE_ARCHIVE`. Команды используют Linux, Python 3.12.14 и окружение
проекта с Zig 0.13.0 и libarchive-c 5.3.

```sh
set -eu
: "${POLE_ARCHIVE:?Укажите абсолютный путь к Pole_Chudes.rar}"
export WONDERFIELD_TOOLS_DIR="${WONDERFIELD_TOOLS_DIR:-/workspace/.tools/wonderfield}"
check_dir="$(mktemp -d)"
git archive 6267611deaaba57a8b9d05e1dafa837993d9a221 -o "$check_dir/source.tar"
tar -xf "$check_dir/source.tar" -C "$check_dir"
cd "$check_dir"
"$WONDERFIELD_TOOLS_DIR/bin/python" scripts/import-cloud-originals.py "$POLE_ARCHIVE"
python3 scripts/build-cloud.py
(cd downloads && sha256sum --check SHA256SUMS)
cmp build/gba/pole.gba downloads/pole.2.0beta2.gba
cmp 'dist/pole 2.0beta2.gba' downloads/pole.2.0beta2.gba
```

## Что дальше

Для задачи 5 используйте проверенный ROM и запишите результаты кабельных
испытаний на двух и трёх GBA с его SHA-256. Подбор пауз в задаче 6 зависит
от показаний реальных консолей в задаче 5. [План проверок](../link-roadmap.md).
