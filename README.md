<div align="center">
  <div>
    <img src="logo.png" width="150" alt="Bring Back 1.6! Logo"/>  
  </div>
  <h1>Bring Back 1.6!</h1>
  <img src="https://img.shields.io/github/downloads/noxygalaxy/bringback1.6/total?style=for-the-badge"></img>  
  <a href="https://discord.gg/yvvJW2z9zB"><img src="https://dcbadge.limes.pink/api/server/yvvJW2z9zB"></img></a>  
  <img src="https://img.shields.io/github/created-at/noxygalaxy/bringback1.6?style=for-the-badge"></img>  
</div>

**Bring Back 1.6!** - is a Geometry Dash mod that brings back the nostalgic look and feel of older versions (1.6) to specific UI layers! This mod modifies the `LevelInfoLayer`, `CreatorLayer`, and `EditorPauseLayer` with toggleable "old style" layouts, complete with a handy button to switch between styles on the fly.

Built with <3. Laugh at my "shit code" if you want to! :p

## Features

- **Toggleable Old Style UI**: Switch between modern and retro layouts in real-time with a single button.
- **All Layers**: Adjusts positions, scales, and visibility of elements to mimic older GD versions.
- **Custom Settings**: Option to hide custom songs in `LevelInfoLayer`.

## Installation

1. **Prerequisites**:
   - Install the [Geode SDK](https://geode-sdk.org/) for Geometry Dash.

2. **Download**:
   - Grab the latest release from the [Releases page](https://github.com/noxygalaxy/bringback1.6/). ["Direct Download"](https://github.com/noxygalaxy/bringback1.6/releases/latest/download)

3. **Install**:
   - Place the `.geode` file in your Geometry Dash `mods` folder.
   - Launch Geometry Dash and enable the mod via the Geode mod menu.

4. **Configure**:
   - Open the mod settings in-game to toggle features like `change-levelinfolayer`, `change-creatorlayer`, `change-editorpauselayer`, and `hide-custom-songs`.


## Usage

- Look for the "1.6" button in the top-right corner of modified layers:
- Click it to switch styles instantly—your preference is saved!


## Screenshots

### LevelInfoLayer
- **2.2 Style**  
  ![LevelInfoLayer Modern](images/levelinfolayer_modern.png)
- **1.6 Style**  
  ![LevelInfoLayer Old](images/levelinfolayer_old.png)

### CreatorLayer
- **2.2 Style**  
  ![CreatorLayer Modern](images/creatorlayer_modern.png)
- **1.6 Style**  
  ![CreatorLayer Old](images/creatorlayer_old.png)

### EditorPauseLayer
- **2.2 Style**  
  ![EditorPauseLayer Modern](images/editorpauselayer_modern.png)
- **1.6 Style**  
  ![EditorPauseLayer Old](images/editorpauselayer_old.png)

---

## Settings

Customize the mod via the Geode settings menu:
- `Modify Level Info Layer`: Enable/disable changes to `LevelInfoLayer`.
- `Modify Creator Layer`: Enable/disable changes to `CreatorLayer`.
- `Modify Editor Pause Layer`: Enable/disable changes to `EditorPauseLayer`.
- `Hide Song Widget`: Hide the custom songs widget in `LevelInfoLayer` when in old style.

---

## Development

The mod hooks into `LevelInfoLayer`, `CreatorLayer`, and `EditorPauseLayer` to:
- Store original UI states.
- Apply custom positions/scales/visibility for "old style."
- Restore defaults when toggled off.

Check out the source code to see bad code but functional! :P Contributions welcome.

---

## Credits

- **Developer**: [noxygalaxy](https://github.com/noxygalaxy)
- **Inspiration**: Nostalgia for Geometry Dash 1.6.
