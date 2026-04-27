# AI coding assistant instructions

## Critical: file encoding

All `.pwn` and `.inc` source files in this repo are **Windows-1257 encoded** (required for Lithuanian characters). The default UTF-8 read/write used by most AI coding tools will silently corrupt these files.

**Never use built-in file edit tools on `.pwn` or `.inc` files.**

Instead, always edit them via a shell script that handles the encoding explicitly:

```python
path = 'gamemodes/LSG.pwn'  # or whichever file

with open(path, 'rb') as f:
    text = f.read().decode('windows-1257')

text = text.replace('old string', 'new string', 1)

with open(path, 'wb') as f:
    f.write(text.encode('windows-1257'))
```

After any edit, verify with `git diff --stat` that only the intended lines changed (not hundreds of lines due to re-encoding).

## Project overview

SA:MP (San Andreas Multiplayer) roleplay server written in Pawn. Main gamemode is `gamemodes/LSG.pwn` with includes under `gamemodes/LSG/`. See `README.md` for full setup instructions.
