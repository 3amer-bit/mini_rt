*This project has been created as part of the 42 curriculum by amajdi, aalemami*
---
## Description

This project is a simple ray tracing renderer.
Its goal is to simulate light behavior in a 3D environment using mathematical models to generate images from virtual scenes.

A key aspect of this project is the **conversion of mathematical equations into executable C code**.
All geometric and lighting behavior is derived from formulas and implemented directly in code.
These mathematical concepts are translated into structured C functions and data models to compute pixel colors and render a 3D scene.W
The project focuses on:
- Ray object intersection (spheres, planes and cylinders)
- Phong lighting model (ambient, diffuse, specular reflection)
- Camera coordinate system construction
- Basic lighting system with multiple light sources
- Scene assembly using modular objects

## Instructions

To build and run this project, you need:

- A Unix-like operating system (Linux or macOS)
- A **C compiler** (e.g. `gcc` or `clang`)
- `make` (GNU Make)

### Compilation

To compile the project, run:

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Full rebuild (fclean + make)
```
## Resources
- [Ray Tracing in One Weekend (Peter Shirley)](https://raytracing.github.io/)
- [Scratchapixel](https://scratchapixel.com/)
- [The Cherno ray tracer series](https://www.youtube.com/watch?v=gfW1Fhd9u9Q&list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl)
### Use of AI
Artificial Intelligence tools were used as a development assistant during this project.
AI contributions included:
- Helping translate mathematical models into code structure, such as:
	- ray sphere and ray plane intersection equations
	- camera coordinate system construction (forward/right/up basis)
	- Phong lighting model (ambient, diffuse and specular computation)
- Assisting in understanding and clarifying core concepts:
	- how rays are constructed and evaluated per pixel
	- how intersection tests are derived from geometric equations
	- how shading models approximate real-world lighting behavior
- Debugging scene configuration issues such as object ordering, coordinate setup, and lighting balance
- Generating alternative scene layouts for testing visual variations