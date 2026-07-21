# Formatter Setup

## What is this for?

This project was made because I got tired of copying formatter config files into every new project, or manually adding formatter setup to my editor each time.

The idea is simple: run `auto-formatter` in the background, and when you open a supported project, it links the correct formatter config into the project root.

That means your formatter is enabled automatically without needing to copy config files manually. When the project is closed or refreshed, the linked formatter config is cleaned up again.



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

# Optional. Default: true
overrideFormatter: true

# Optional. Default: true
addToGitIgnore: true

# Optional. Default: 3
depth: 3

# Optional. Default: [".git", "build", "target"]
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
<summary><code>Minimal config</code></summary>

```yaml
IDE:
  - "nvim"

formatters:
  - cpp:
      formatter: ".clang-format"
      filetypes:
        - ".cpp"
        - ".hpp"
        - ".h"
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

To stop the background process:

```sh
kill %1
```

## Build from Source

```sh
cmake -S . -B build
cmake --build build
```

For an optimized release build:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
<details>
<summary><code>About this README</code></summary>



I used ChatGPT to help write and clean up parts of this README, since I am dyslexic and English is not my first language.

The project and code are still my own work.

</details>
