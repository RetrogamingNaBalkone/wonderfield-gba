# Release publishing

- Upload only the standalone ROM (`.gba`) and `SHA256SUMS` as release assets.
- Keep screenshots, audio, verification reports and developer materials in the repository.
- Release notes describe changes for players, save compatibility and how to download and play. Omit verification procedures, QA details and internal implementation history.
- CHANGELOG.MD records released changes, fixes and compatibility only. Keep test runs, measurements, verification reports and implementation narratives out of it.

# Передача сборок пользователю

- До явной отмены пользователем передавать релизы и тестовые сборки через собранный ROM, сохранённый в Git и отправленный в рабочую ветку проекта.
- Для текущей версии обновлять существующий `downloads/pole.2.0.gba` и `downloads/SHA256SUMS`. Не создавать отдельный GitHub Release для передачи сборки, если пользователь явно не попросил об этом.
- После изменения игры собирать ROM из актуального кода, выполнять подходящие проверки, обновлять ROM и контрольную сумму в `downloads`, коммитить и отправлять изменения в рабочую ветку.
- В ответе давать прямую ссылку на скачивание ROM из Git, привязанную к полному SHA коммита, содержащего переданную сборку, чтобы повторное скачивание не зависело от кеша ссылки на ветку.
- Перед передачей проверять, что файл по ссылке доступен и его SHA-256 совпадает с собранным ROM. Не выдавать старую сборку за новую при неудачной сборке или отправке.
