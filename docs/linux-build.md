# Сборка на Linux

Нужны Python 3 и Zig 0.13.0. Сборщик ищет Zig в `PATH`. Путь к другому
исполняемому файлу можно задать через `ZIG_EXE`. Если Zig отсутствует в `PATH`,
сборщик использует пакет `ziglang` из текущего окружения Python.

## Оригинальные ресурсы

Поместите файлы DOS-игры из [списка оригиналов](../analysis/originals.json)
в `originals/Wonderfield`. Если у вас архив `Pole_Chudes.rar`, его можно
импортировать из корня репозитория. Для импорта на Linux нужна системная
библиотека libarchive.

```sh
python3 -m venv .venv
.venv/bin/python -m pip install 'ziglang==0.13.0' 'libarchive-c==5.3'
.venv/bin/python scripts/import-originals.py /path/to/Pole_Chudes.rar
.venv/bin/python scripts/build.py
```

Если Zig уже установлен и оригиналы распакованы, достаточно выполнить
`python3 scripts/build.py`. Сборщик проверяет размеры и SHA-256 оригиналов.

## Результаты и проверки

- `dist/pole.2.0.gba` — ROM для эмулятора или флеш-картриджа.
- `build/gba/pole.gba` — рабочая копия ROM.
- `build/gba/pole.elf` и `build/gba/pole.map` — символы и карта линковки.
- `build/gba/build-report.json` — размер ROM, SHA-256 и контрольная сумма заголовка.

Готовые файлы сборки находятся в игнорируемых каталогах `build` и `dist`.
Для тестов с mGBA задайте путь к ядру libretro.

```sh
export MGBA_LIBRETRO=/path/to/mgba_libretro.so
python3 scripts/test-title-timing.py
python3 scripts/test-multiplayer.py
python3 scripts/test-match-rules.py
```

Для кабельной проверки `scripts/test-link.py` нужна отдельная сборка libmgba
с заголовками. [Инструкции по проверкам](multiplayer.md).
