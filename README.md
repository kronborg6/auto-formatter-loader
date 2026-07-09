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



## Config and Templates

By default, `auto-formatter` looks for the config file here:

```sh
~/.auto-formatter.yaml
```

The default template folder is:

```sh
~/.config/autoFormatter/templates
```

## Required Files

To run `auto-formatter`, you need:

- A config file at `~/.auto-formatter.yaml`
- A template folder at `~/.config/autoFormatter/templates`

<details>
<summary><code>~/.auto-formatter.yaml</code></summary>

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
<summary><code>Template folder layout</code></summary>

```text
~/.config/autoFormatter/
└── templates/
    ├── .clang-format
    ├── .rustfmt.toml
    ├── odinfmt.json
    └── .editorconfig
```

</details>

## Running

Run normally:

```sh
./auto-formatter
```

Run in the background:

```sh
./auto-formatter > auto-formatter.log 2>&1 &
```

This starts `auto-formatter` in the background and writes output to `auto-formatter.log`.

To see background jobs in the current shell:

```sh
jobs
```

To bring the program back to the foreground:

```sh
fg
```

## Build from Source

```sh
cmake -S . -B build
cmake --build build
```

For a release build:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
