# cgram
Native library for Telegram bots

## Building
```
poetry install
poetry run python -m cgram_generator vendor/telegram-bot-api-spec/api.json include/cgram src/types
cmake -B build .
cmake --build build
```

## Test
```
build/cli/cgram-cli BOT_TOKEN CHAT_ID
```
