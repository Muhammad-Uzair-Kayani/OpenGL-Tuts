# OpenGL Renderer

A modern OpenGL renderer built in **C++17** using **GLFW**, **GLAD**. This project serves as a foundation for learning graphics programming while gradually evolving into a modular rendering framework and, eventually, a custom game engine renderer.

## Objectives

* Learn modern OpenGL from first principles.
* Build a clean and modular rendering architecture.
* Understand GPU rendering pipelines.
* Implement reusable rendering abstractions.
* Prepare the rendering backend for integration into a future game engine.

---

## Current Stack

* **Language:** C++17
* **Graphics API:** OpenGL
* **Windowing:** GLFW
* **OpenGL Loader:** GLAD
* **Build System:** Premake5
* **IDE:** Visual Studio 2022

---
---

## Features

### Current

* Modern OpenGL setup
* GLFW window creation
* GLAD initialization
* Premake-based build system
* Modular project organization

### Planned

* Shader abstraction
* Vertex Buffer (VBO)
* Vertex Array Object (VAO)
* Element Buffer Object (EBO)
* Texture system
* Camera implementation
* Transform system
* Mesh abstraction
* Material system
* Lighting
* Model loading
* Scene management
* Framebuffers
* Post-processing
* Skybox
* Physically Based Rendering (PBR)
* Deferred Rendering
* Shadow Mapping
* Instanced Rendering
* Compute Shaders

---

## Building

Run build.bat to generate vs2022 project solution

### Requirements

* Visual Studio 2022 -- Can modify build.bat to make other other files--
* Premake5
* Git

### Clone

```bash
git clone https://github.com/Muhammad-Uzair-Kayani/OpenGL---Renderer.git
cd OpenGL---Renderer
```

---

## Learning Roadmap

This repository follows a progressive graphics programming roadmap.

1. OpenGL Fundamentals
2. Buffers and Vertex Specification
3. Shader Programming
4. Transformations
5. Texturing
6. Camera System
7. Lighting
8. Model Loading
9. Framebuffers
10. Advanced Rendering Techniques
11. Renderer Architecture
12. Engine Integration

Each milestone focuses on understanding the underlying graphics concepts before introducing abstractions.

---

## Purpose

This project is not intended to be another rendering library. It is a long-term educational project focused on understanding how modern rendering systems work internally and how professional game engines structure their rendering pipelines.

The renderer will ultimately become the graphics subsystem of a custom C++ game engine currently under development.

---

## License

This project is licensed under the MIT License.
