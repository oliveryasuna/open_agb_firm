# open_agb_firm (fork)

open_agb_firm is a bare metal interface for *natively* running GBA games and homebrew using the 3DS's built-in GBA hardware.

See the original project [here](https://github.com/profi200/open_agb_firm).

This fork adds the following features:
- Cheat support (Action Replay)
- Bottom screen OSD

## Cheats

This fork adds support for Action Replay (PARv3) cheat codes. Cheat files use the `.cht` extension and contain one code per line in `XXXXXXXX YYYYYYYY` format. Lines starting with `#` or `;` are treated as comments.

By default (`useCheatsFolder=true` in `config.ini`), cheat files are loaded from:

```
sdmc:/3ds/open_agb_firm/cheats/{ROM_NAME}.cht
```

When `useCheatsFolder=false`, the `.cht` file is loaded from the same directory as the ROM.

Up to 25 cheat codes are supported per game. RAM write codes (8/16/32-bit) are applied every VBlank. ROM patch codes are applied directly at load time.

**Example** (`sdmc:/3ds/open_agb_firm/cheats/Pokemon - Emerald Version (USA, Europe).cht`):

```
# Walk through walls
7881A409 E2026E0C
8E883EFF 92E9660D
```

## Bottom Screen OSD

When enabled, the bottom 3DS screen displays game info, battery level, and the current time while a GBA game is running on the top screen.

Set `showOsd=true` under `[general]` in `config.ini` (or in a per-game `.ini` file) to enable it. Default is `false`.
