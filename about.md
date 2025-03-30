# BringBack1.6 Mod

Welcome to **BringBack1.6**, a Geometry Dash mod that brings back the nostalgic look and feel of older versions (like 1.6 and 2.2) to specific UI layers! This mod modifies the `LevelInfoLayer`, `CreatorLayer`, and `EditorPauseLayer` with toggleable "old style" layouts, complete with a handy button to switch between styles on the fly.

Built with <3. Laugh at my "shit code" if you want to! :p


## Features

- **Toggleable Old Style UI**: Switch between modern and retro layouts in real-time with a single button.
- **All Layers**: Adjusts positions, scales, and visibility of elements to mimic older GD versions.
- **Custom Settings**: Option to hide custom songs in `LevelInfoLayer`.


## Usage

- Look for the "1.6" button in the top-right corner of modified layers:
- Click it to switch styles instantly—your preference is saved!


## Screenshots

### LevelInfoLayer
- **2.2 Style**  
  ![LevelInfoLayer Modern](https://raw.githubusercontent.com/noxygalaxy/bringback1.6/refs/heads/main/images/levelinfolayer_modern.png)
- **1.6 Style**  
  ![LevelInfoLayer Old](https://raw.githubusercontent.com/noxygalaxy/bringback1.6/refs/heads/main/images/levelinfolayer_old.png)

### CreatorLayer
- **2.2 Style**  
  ![CreatorLayer Modern](https://raw.githubusercontent.com/noxygalaxy/bringback1.6/refs/heads/main/images/creatorlayer_modern.png)
- **1.6 Style**  
  ![CreatorLayer Old](https://raw.githubusercontent.com/noxygalaxy/bringback1.6/refs/heads/main/images/creatorlayer_old.png)

### EditorPauseLayer
- **2.2 Style**  
  ![EditorPauseLayer Modern](https://raw.githubusercontent.com/noxygalaxy/bringback1.6/refs/heads/main/images/editorpauselayer_modern.png)
- **1.6 Style**  
  ![EditorPauseLayer Old](https://raw.githubusercontent.com/noxygalaxy/bringback1.6/refs/heads/main/images/editorpauselayer_old.png)

## Settings

Customize the mod via the Geode settings menu:
- `Modify Level Info Layer`: Enable/disable changes to `LevelInfoLayer`.
- `Modify Creator Layer`: Enable/disable changes to `CreatorLayer`.
- `Modify Editor Pause Layer`: Enable/disable changes to `EditorPauseLayer`.
- `Hide Song Widget`: Hide the custom songs widget in `LevelInfoLayer` when in old style.

## Development

The mod hooks into `LevelInfoLayer`, `CreatorLayer`, and `EditorPauseLayer` to:
- Store original UI states.
- Apply custom positions/scales/visibility to mimic 1.6 style.
- Restore default 2.2 style when toggled off.

Check out the source code to see bad code but functional! :P Contributions welcome.

## Support  
If you encounter any issues, please report them on the [Issues](https://github.com/noxygalaxy/bringback1.6/issues) page. You can also join our [**Discord**](https://discord.gg/yvvJW2z9zB) for help, discussions and to see my new mod releases <3  

## Credits

- **Developer**: [noxygalaxy](https://github.com/noxygalaxy)
- **Inspiration**: Nostalgia for Geometry Dash 1.6.
