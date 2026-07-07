# Swarm

A top-down twin-stick wave-survival shooter built in **Unreal Engine 5** with C++,
using a hybrid C++/Blueprint workflow. This is a solo learning project focused on
UE5 gameplay-framework and systems programming — built from a blank C++ project
rather than a template, so the framework wiring (GameMode, PlayerController, Pawn,
Enhanced Input, movement, and combat) is implemented from the ground up.

## About

The player controls a character in an enclosed arena viewed from above. Enemies spawn
and seek the player, who survives as long as possible while shooting them down. It's an
endurance loop with no win state — the goal is a high score.

Core mechanics implemented so far:

- Top-down camera rig (spring arm + camera) with a fixed overhead angle
- WASD movement in world space (independent of aim), via `UFloatingPawnMovement`
- Mouse aiming through cursor-to-world deprojection onto the play plane
- Projectile firing along the aim direction, rate-limited and self-expiring

## Requirements

- **Unreal Engine 5.8.0** (use this engine version to open and build the project)
- A C++ toolchain for Unreal on your platform:
  - **Windows:** Visual Studio with the "Game development with C++" workload (MSVC + Windows SDK)
- **Git LFS** — this repository stores binary assets (`.uasset`, `.umap`) via Git LFS.
  You **must** have Git LFS installed before cloning, or you'll get small pointer text
  files instead of the actual assets.

## Getting Started

1. **Install Git LFS** (if you haven't):
   ```bash
   git lfs install
   ```

2. **Clone the repository:**
   ```bash
   git clone <repo-url>
   ```
   With Git LFS installed, the binary assets download automatically. If you cloned
   without LFS, install it and run `git lfs pull` to fetch the real assets.

3. **Generate project files:** right-click `Swarm.uproject` and choose
   *Generate Visual Studio project files* (or use your IDE's equivalent — e.g. Rider
   opens the `.uproject` directly).

4. **Build** the project from your IDE (Development Editor configuration), with the
   Unreal Editor closed.

5. **Open** `Swarm.uproject` and press Play.

## Controls

| Input | Action |
|-------|--------|
| WASD | Move |
| Mouse | Aim |
| Left Mouse Button | Fire |

## Project Structure

Organized by feature, with `Source/` (C++) and `Content/` mirroring each other:

- `Source/Swarm/Core/` — framework classes (GameMode, PlayerController)
- `Source/Swarm/Player/` — the player pawn
- `Source/Swarm/Weapons/` — projectiles
- `Source/Swarm/Enemies/` — enemy classes
- `Source/Swarm/Components/` — reusable components (e.g. health)
- `Content/Swarm/` — Blueprints, input assets, and maps, mirroring the source layout

## License

The game's own **source code and original assets** are licensed under the MIT License —
see [LICENSE](LICENSE).

This project is built on **Unreal Engine**. Unreal Engine and any associated engine
code or content are the property of Epic Games and are governed by Epic's licensing
terms, not by this repository's MIT license. See
[Epic's licensing](https://www.unrealengine.com/eula) for details.
