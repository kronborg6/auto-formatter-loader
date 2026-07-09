# formant setup

### what is this for

this project is for me MUHAHAHA
im not sure if it a good idea to make this in C++

but her it goes

i just hate setting up new project
at the moment im learning cmake and cpp
so im not gona make a script or somfing for that

but what i hate even more is when the formant scuks
so my idea is
to make a project that ehiter get run with nvim or somfig so i make a alias or somfig that runs this project and start neovim up
or se if i can make it run in the backgound and get wait for a IDE to start
then i wan't it to check if they is a .clang-format if it a c++ project if not create one
maby im not sure about this but when i queit the ide maby delete the formanter or i need to add it to .gitignore
becus i don't wan't to force my format onto any one



## Config and Template

the config standard path is in the home folder with the name .auto-formatter.yaml
the standard path for the Template folder is ~/.dotfile/auto-formatter/templates


## How to run

to run this you need a 
`~/.auto-formatter.yaml`
`~/.config/autoFormatter/templates`

<details>
<summary><code>auto-formatter.yaml</code></summary>

```yaml
IDE:
  - "nvim"
  - "code"

depth: 2

excludeFolders:
  - ".git"
  - "build"
  - "target"

formatters:
  - cpp:
      formatter: ".clang-format"
      filetypes:
        - ".cpp"
        - ".hpp"
        - ".h"
  - c:
      formatter: ".clang-format"
      filetypes:
        - ".c"
        - ".h"
  - rust:
      formatter: ".rustfmt.toml"
      filetypes:
        - ".rs"
  - odin:
      formatter: "odinfmt.json"
      filetypes:
        - ".odin"
  - csharp:
      formatter: ".editorconfig"
      filetypes:
        - ".cs"
```

</details>

<details>
<summary><code>autoFormatter Folder Layout</code></summary>

```text
autoFormatter/
└── templates/
    ├── .clang-format
    ├── .rustfmt.toml
    ├── odinfmt.json
    └── .editorconfig
```

</details>

```sh
./auto-formatter
```



## Build from source (Recommend)
```sh
cmake -S . -B build
cmake --build build
```
