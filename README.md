# Stardew Valley OOPL Project

|Keys   |Function           |
|:-----:|:-----------------:|
|W/A/S/D|movement|
|X|go to next level if on exit|

## Debug

|Keys   |Function           |
|:-----:|:-----------------:|
|J/K    |next/previousmap   |
|E      |create random exit |
|O      |create random rocks|
|Shift+O|clear all rocks    |

## Known bugs:
- If rocks are not cleared before entering next level, rocks will remain on last levels locations
- If player spawns on said rocks, game will freeze
- Hitbox is still WIP, actual hitbox is different from sprite

# TODO
- [x] Map data
  - [x] python preprosses TMX to [Custom format](https://github.com/jykuo-love-shiritori/tileset-image-cropper/tree/master/tmx_preprocess/txm2bin)
- [x] Steal texture from original game
  - [x] [jykuo-love-shiritori/tileset-image-cropper](https://github.com/jykuo-love-shiritori/tileset-image-cropper)

Ores:
  - [ ] Copper ore
  - [ ] Iron ore
  - [ ] Gold ore
  - [ ] Iridium ore

Gems:
  - [ ] Amethyst
  - [ ] Topaz
  - [ ] Quartz
  - [ ] Earth crystal
  - [ ] Aquamarine
  - [ ] Frozen tear
  - [ ] Jade
  - [ ] Diamond
  - [ ] Emeraldg
  - [ ] Fire quartz
  - [ ] Ruby

Monsters:
  - [ ] Green slime
  - [ ] Duggy
  - [ ] Bug
  - [ ] Rock crab
  - [ ] Grub
  - [ ] Cave fly
  - [ ] Bat
  - [ ] Stone golem
  - [ ] Frost jelly
  - [ ] Frost bat
  - [ ] Dust sprite
  - [ ] Ghost
  - [ ] Skeleton
  - [ ] Red sludge
  - [ ] Lava bat
  - [ ] Lava crab
  - [ ] Shadow brute
  - [ ] Shadow shaman
  - [ ] Metal head
  - [ ] Squid head

Mechanics:
  - [ ] Randomize rock formation?
  - [ ] Randomize monster spawns?
  - [ ] Ladders spawn from rocks
  - [ ] Monster behavior
  - [ ] Infested and mushroom floors
