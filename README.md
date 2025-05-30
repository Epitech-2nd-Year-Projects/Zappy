# Zappy Monorepo

This repository groups all components of **Zappy** into a single monorepo:
- **zappy_server/** — game server (C)
- **zappy_ai/**     — AI client (Python)
- **zappy_client/** — graphical client (Unreal Engine/C++)

---

## Project Structure

```bash
.
├── zappy_server/      # Server (C)
│   ├── include/       # Public headers
│   ├── src/           # .c source files
│   ├── Makefile       # Build rules
│   └── .gitignore     # C-specific ignores
│
├── zappy_ai/          # AI client (Python)
│   ├── src/           # .py modules
│   ├── tests/         # Unit tests
│   ├── requirements.txt
│   └── .gitignore     # Python-specific ignores
│
└── zappy_client/      # Unreal Engine client
    ├── Config/
    ├── Content/
    ├── Source/
    ├── ZappyClient.uproject
    └── .gitignore     # Unreal-specific ignores
```

## Quick Start

### Clone the repo

```bash
git clone <repo-url>
cd <repo-folder>
```

### Build / Run

#### Server (C)

```bash
cd zappy_server
make
./zappy_server -p 1234 -x 20 -y 20 -n TeamA TeamB -c 5 -f 100
```

#### AI (Python)

```bash
cd zappy_ai
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
python src/main.py --host localhost --port 1234 --team TeamA
```

#### Client (Unreal Engine)

Open `zappy_client/ZappyClient.uproject` in Unreal Editor and click Play.

## Simplified Git Workflow

We use a single working branch (main). All features come from Linear-based feature branches.

### Main branch

`main` — always deployable code.

### Feature branches

**Naming format:**
```
<firstname><lastname>/zap-<ticket>-<short-description>
```

**Example:**
```bash
gregsternat/zap-1-initialize-monorepo-structure
```

### Feature lifecycle

```bash
# Create branch from main
git checkout main
git pull origin main
git checkout -b gregsternat/zap-42-add-inventory-management

# Develop & commit
git add .
git commit -m "feat(server): basic inventory management"

# Push & open PR
git push -u origin gregsternat/zap-42-add-inventory-management

# Open PR on GitHub → review → merge into main

# Cleanup
git checkout main
git pull origin main
git branch -d gregsternat/zap-42-add-inventory-management
git push origin --delete gregsternat/zap-42-add-inventory-management
```

### Commit conventions

Follow Conventional Commits:
```
<type>(<scope>): <short description>
```

**Types:** feat, fix, docs, style, refactor, test, chore

**Examples:**
```
feat(ai): add pathfinding logic
fix(client): correct texture rendering
```