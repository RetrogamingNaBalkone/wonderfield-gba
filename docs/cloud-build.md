# Сборка в Codex Cloud (Linux)

Проверено 9 ноября 2026 года на x86_64 Linux, Python 3.12 и Zig 0.13.0,
ревизия `14bf63055c62da8bfeaf37d13c6eccbd619f7488`.
Makefile в проекте нет. devkitPro, devkitARM, libgba и PowerShell для этого
Linux-пути не нужны. Компилятор и линкер поставляются с пакетом `ziglang`.
`build-cloud.py` повторяет флаги, набор модулей и порядок линковки `build.ps1`.
Игровой код и ресурсы не изменяются.

## Подготовка

```bash
cd /workspace/wonderfield-gba
bash scripts/setup-cloud.sh
```

Скрипт устанавливает `ziglang==0.13.0` и `libarchive-c==5.3` в отдельное
окружение `/workspace/.tools/wonderfield`. Нужны Python 3 с модулем `venv`,
доступ к `pypi.org` и `files.pythonhosted.org`, а для импорта RAR — системная
`libarchive.so` (уже есть в проверенной облачной машине). Root не требуется.
`WONDERFIELD_TOOLS_DIR` позволяет выбрать другой путь к инструментам.

Исходные DOS-файлы отсутствуют в Git. В текущей машине загруженный пользователем
`Pole_Chudes.rar` сохранён вне репозитория:
`/workspace/.tools/wonderfield-input/Pole_Chudes.rar`.
SHA-256 архива:
`56ddae3a4a121c9df7112ea76b76200f822d8a83c44c67afbeaf995accaef75c`.
Если архив есть по этому пути, setup автоматически импортирует его.
Иной путь можно передать через `WONDERFIELD_ORIGINAL_ARCHIVE`.

Для новой машины без сохранённого снимка загрузите архив в чат Codex и выполните:

```bash
/workspace/.tools/wonderfield/bin/python scripts/import-cloud-originals.py /path/to/Pole_Chudes.rar
```

Импорт извлекает только шесть файлов, перечисленных в `analysis/originals.json`,
проверяет размеры и SHA-256 до записи и не заменяет отличающиеся существующие
файлы. Они сохраняются в игнорируемом `originals/Wonderfield`.
Ссылка на скачивание не обязательна: доступ к хосту архива в этой среде был
запрещён прокси (`CONNECT 403`), поэтому использована загрузка файла в чат.
Секреты не нужны.

## Сборка и результат

```bash
cd /workspace/wonderfield-gba
python3 scripts/build-cloud.py
file 'dist/pole 2.0.gba'
sha256sum 'dist/pole 2.0.gba'
cat build/gba/build-report.json
```

Скрипт проверяет версию Zig и оригинальные файлы, копирует необходимые входы
в игнорируемый `build/cloud-source`, запускает штатные `extract.py`, `pack.py`,
компиляцию шести модулей, линковку и `finish_rom.py`. Все подпроцессы должны
завершиться успешно. Отслеживаемые `assets` и `analysis` не перезаписываются.
Кэш Zig находится в `build/zig-cache`: стандартный пользовательский каталог
кэша в облачной песочнице недоступен для записи.
Для своего установленного Zig можно передать `ZIG_EXE=/absolute/path/to/zig`.

Результаты:

- `dist/pole 2.0.gba` — ROM для запуска;
- `build/gba/pole.gba` — идентичная рабочая копия;
- `build/gba/pole.elf`, `pole.map` — символы и карта линковки;
- `build/gba/build-report.json` — размер, SHA-256 и контрольная сумма заголовка;
- `build/generated` — сгенерированные исходники.

Два последовательных полных прогона завершились с кодом 0 без ошибок и
предупреждений компилятора (`-Wall -Wextra -Werror`). ROM: **1 048 576 байт**,
SHA-256 `f4ca9f79753b73e8cdb32c5cadf0971983c980faaf2b1d81bab4117d9c64e7d4`.
`file` распознал Game Boy Advance ROM, заголовок `POLE CHUDES `, код `PC01`,
ревизию 1. Проверены ARM ELF32 little-endian, точка входа `0x08000000`,
ветвление ARM в начале ROM, обязательный байт `0x96`, контрольная сумма
заголовка `0xD0` и совпадение рабочей и итоговой копий ROM.
Штатный `finish_rom.py` также записал логотип GBA и проверил сумму заголовка.

Эмуляторные и релизные проверки не выполнялись: существующий `emulator.py`
загружает Windows DLL mGBA через `LOCALAPPDATA`. Для проверки игрового поведения
на Linux потребуется отдельная адаптация пути к libretro core. Это не является
зависимостью компиляции ROM.

## Повторное использование среды

Задачи Cloud уже изолированы: используйте существующий checkout, не создавайте
Git worktree без явного запроса пользователя. Постоянные сервисы не требуются.
Не коммитьте ROM, оригиналы, инструменты, кэши и промежуточные результаты.
Каталоги `build`, `dist` и `originals` уже включены в `.gitignore`.

Для поля **install_script** в настройках среды:

```bash
set -euo pipefail
cd /workspace/wonderfield-gba
bash scripts/setup-cloud.sh
python3 scripts/build-cloud.py
```

Для поля **start_skill**:

```text
Use the existing checkout /workspace/wonderfield-gba. Cloud tasks are isolated;
do not create a Git worktree unless explicitly requested. Read AGENTS.md and
docs/cloud-build.md. No services or devkitARM are required. Run
bash scripts/setup-cloud.sh and python3 scripts/build-cloud.py.
Check build/gba/build-report.json and file 'dist/pole 2.0.gba'.
If originals are missing, import the user-supplied archive using
/workspace/.tools/wonderfield/bin/python scripts/import-cloud-originals.py ARCHIVE.
Never commit ROMs, originals, caches or tools. Claim a successful build only
after compilation, linking and finish_rom.py complete successfully.
```

Оба сценария выполнены в текущей машине. Автоматическое сохранение полей через
инструмент настройки вернуло `INVALID_ARGUMENT` («saving the draft could not
be confirmed»), поэтому сохранение черновика **не подтверждено**. Точные
значения приведены выше для настройки среды. Публикация снимка пользователем и
восстановление в новой задаче пока не проверены; текущая машина полностью
подготовлена для сборки.
