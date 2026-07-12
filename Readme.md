# Task Tracker

A simple command-line task tracker written in C++. Tasks are stored as JSON in a
local `tasks.json` file, so your list persists between runs.

## Features

- Add, update, and remove tasks
- List all tasks
- Automatic, unique IDs for every task
- Human-readable JSON storage (`tasks.json`)

## Requirements

- A C++17 (or newer) compiler — e.g. `g++` 11+
- [nlohmann/json](https://github.com/nlohmann/json) — a header-only library,
  already vendored in this repo at `include/nlohmann/json.hpp`

No external build system is required; the JSON library is a single header.

## Building

```bash
g++ -std=c++17 -I include main.cpp -o task-tracker.exe
```

The `-I include` flag tells the compiler where to find `nlohmann/json.hpp`.

## Usage

```
task-tracker <command> [options]
```

| Command                 | Description                          | Example                          |
| ----------------------- | ------------------------------------ | -------------------------------- |
| `add <description>`     | Add a new task                       | `task-tracker add "Buy milk"`    |
| `update <id> <text>`    | Change the description of a task     | `task-tracker update 1 "Buy tea"`|
| `remove <id>`           | Delete a task by its ID              | `task-tracker remove 1`          |
| `list`                  | Show all tasks                       | `task-tracker list`              |
| `--version`             | Print the app version                | `task-tracker --version`         |

Running with no command prints usage instructions.

### Example session

```bash
$ task-tracker add "Buy milk"
Added Task: Buy milk

$ task-tracker add "Write code"
Added Task: Write code

$ task-tracker list
1: Buy milk
2: Write code

$ task-tracker update 1 "Buy oat milk"
Updated Task: 1

$ task-tracker remove 2
Removed Task: 2

$ task-tracker list
1: Buy oat milk
```

## Data format

Tasks are stored in `tasks.json` in the working directory. Each task is an object:

```json
[
  {
    "id": 1,
    "desc": "Buy milk",
    "done": false
  }
]
```

The file is created automatically on the first `add`. If it doesn't exist, the app
starts with an empty task list.

## Roadmap

Planned features not yet implemented:

- Mark a task as **in progress** or **done**
- List only tasks that are **done**
- List only tasks that are **not done**
- List only tasks that are **in progress**

## Project structure

```
Task_Tracker_Cpp/
├── main.cpp                  # Application entry point and command handling
├── include/
│   └── nlohmann/
│       └── json.hpp          # Vendored JSON library (header-only)
├── tasks.json                # Task storage (created at runtime)
└── Readme.md
```