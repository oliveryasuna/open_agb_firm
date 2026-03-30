# open_agb_firm (fork)

open_agb_firm is a bare metal interface for *natively* running GBA games and homebrew using the 3DS's built-in GBA hardware.

See the original project [here](https://github.com/profi200/open_agb_firm).

This fork adds the following features:
- Cheat support (Action Replay)

## Cheats

Similar to save files, which are stored at `sdmc:/3ds/open_agb_firm/saves/{ROM_FILENAME}.sav`, cheats are stored at `sdmc:/3ds/open_agb_firm/cheats/{ROM_FILENAME}.cht`.

Example cheat file for Pokemon Emerald:

```
# Walk through walls
7881A409 E2026E0C
8E883EFF 92E9660D
```

This fork also supports the configuration option `useCheatsFolder`.
It behaves the same as `useSavesFolder`, but for cheats instead of saves.
