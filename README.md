# FPS Unlocker (Geode mod)

Мод для Geode, который сам просит систему повысить частоту
обновления экрана до 120 Гц через стандартный Android API
(WindowManager.LayoutParams.preferredRefreshRate), без Shizuku,
root и кабеля — потому что выполняется внутри процесса самой игры
с её обычными правами.

## Установка на телефон

1. Скачайте `.geode` файл из Artifacts последней успешной сборки
   в GitHub Actions.
2. Переименуйте/оставьте расширение `.geode`.
3. Скопируйте файл в:
   `/storage/emulated/0/Android/media/com.geode.launcher/game/geode/mods/`
   (через файловый менеджер на телефоне).
4. Перезапустите Geometry Dash через Geode — мод должен появиться
   в списке модов и включиться автоматически.
