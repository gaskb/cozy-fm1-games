# Changelog

All notable changes to **Cozy FM-1 Games** are documented in this file.

## [0.8] - 2026-11-26

### Added
- **Per-game LED mapping** (`arcade_update_leds`): active buttons and piano keys light up automatically to match the current screen (`PLAY` lit during gameplay, `HOME` lit to return to menu).
- **Real-hardware showcase** in `photos/` and `README.md` (`menu.gif`, `outrun-title.gif`, `outrun-play.gif`, `fm1-arcade-demo.gif`).
- **The Firmware Hub manifest** (`fmhub.json`) and unique package identity **`FM-1_02700800`** (`FM-1_027xyyzz`).

## [0.7] - 2026-11-19

### Added
- **Chrome Dino Run**: offline T-Rex runner with jumping, ducking, cacti, pterodactyls, and day/night cycles.
- **Flappy Bird**: pipe-dodging flyer with pentatonic synth notes on every flap.

## [0.6] - 2026-11-17

### Added
- **Synth Hero**: Guitar Hero-style rhythm game synced to the OutRun MIDI tracks, with **BASE** (7 white keys) and **HIGH** (12 chromatic keys) modes.
- **Frogger**: 13-row road & river crossing with 5 home lilypads.
- **Galaga**: scrolling starfield, swaying alien formation, dive-bombers, and twin-laser starfighter.
- **Pac-Man**: 19×19 maze, dots, blinking power pellets, and 4 colored ghosts.
- Scrollable 8-in-1 Arcade menu.

## [0.5] - 2026-11-17

### Added
- **OutRun OST from real MIDI**: 4-voice 2-op FM synthesis + synthesized drums (`Kick`, `Snare`, `Hi-Hat`) playing *Magical Sound Shower*, *Passing Breeze*, and *Splash Wave*.

### Changed
- Reduced OutRun traffic to 1 opponent car at a time for smoother gameplay.

## [0.4] - 2026-11-17

### Added
- **OutRun**: pseudo-3D raster road racer with sunset parallax, palm trees, checkpoints, and Testarossa sprite.

## [0.3] - 2026-11-17

### Added
- **3-in-1 Arcade menu** with persistent flash high scores.
- **Tetris**: classic 10×20 board, wall kicks, NEXT preview, hard drop, and 2-voice *Korobeiniki* chiptune BGM.
- **Arkanoid**: 5×9 colored bricks, Q8 fixed-point physics, and rotary paddle control via `KNOB1` / `SELECT`.

## [0.1 - 0.2] - 2026-11-17

### Added
- Initial **Snake** firmware on Dinghy (`STORE_MAGIC = "SNK1"`) with chiptune SFX and piano D-pad mapping (`C` = Left, `D` = Down, `E` = Right, `C#`/`D#` = Up).
