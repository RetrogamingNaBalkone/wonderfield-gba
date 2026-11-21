# Рабочая ветка

- Вся разработка, включая мультиплеер, ведётся в ветке `main`. Ветка `multiplayer` устарела и полностью вошла в `main`. Имя `work` может использоваться локальной средой для стартового checkout.

# Release publishing

- Upload only the standalone ROM (`.gba`) and `SHA256SUMS` as release assets.
- Keep screenshots, audio, verification reports and developer materials in the repository.
- Release notes describe changes for players, save compatibility and how to download and play. Omit verification procedures, QA details and internal implementation history.
- CHANGELOG.MD records released changes, fixes and compatibility only. Keep test runs, measurements, verification reports and implementation narratives out of it.

# Передача сборок пользователю

- После изменения игры собирать ROM из актуального кода и выполнять подходящие проверки. Готовые ROM хранить вне Git.
- Для передачи использовать имя `pole.<версия>.gba` с полной версией, например `pole.2.0beta3.gba`. Перед передачей сверять SHA-256 файла с собранным ROM.
- Создавать GitHub Release только по явному запросу пользователя.
