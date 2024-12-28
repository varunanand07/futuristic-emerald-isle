# Toward a Futuristic Emerald Isle

![Project Logo](title/logo.png)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Screenshots](#screenshots)
- [Installation](#installation)
- [Usage](#usage)
- [Dependencies](#dependencies)
- [Build Instructions](#build-instructions)
- [Controls](#controls)
- [Performance](#performance)
- [Acknowledgements](#acknowledgements)
- [License](#license)

## Introduction

**"Toward a Futuristic Emerald Isle"** is a 3D simulation project developed in C++ using shader-based OpenGL 3.3. The application presents a dynamic and visually captivating futuristic cityscape featuring buildings of varying heights and a fleet of spaceships navigating the skies above. The project emphasizes rendering optimization, realistic animations, and user interactivity to create an immersive virtual environment.

## Features

- **Dynamic Spaceships:** Twenty spaceships fly at varying altitudes and orientations, each programmed to navigate smoothly without colliding with buildings.
- **Collision Avoidance:** Mechanisms ensure that spaceships maintain safe vertical and horizontal distances from buildings, preventing overlaps and enhancing realism.
- **Varying Building Heights:** A sprawling cityscape with 400 buildings of randomized heights creates a diverse and realistic skyline.
- **Instanced Rendering:** Efficient rendering of multiple buildings using Instanced Rendering minimizes draw calls, significantly improving performance.
- **Basic Environment Lighting:** Fundamental lighting techniques illuminate the scene, adding depth and enhancing visual appeal.
- **Infinite Scene Simulation:** An endless cityscape allows the camera to move seamlessly in any direction without encountering boundaries.
- **User Interaction and Camera Control:** Intuitive controls enable users to navigate the environment using keyboard and mouse inputs.

## Screenshots

### Initial OpenGL Setup

![Initial Setup](screenshots/initial_setup.png)

### Adding Buildings

![Added Buildings](screenshots/added_buildings.png)

### Introducing Spaceships

![Added Spaceships](screenshots/added_spaceships.png)

### Implementing Collision Avoidance

![Collision Avoidance](screenshots/collision_avoidance.png)

### Optimizing with Instanced Rendering

![Instanced Rendering](screenshots/instanced_rendering.png)

## Installation

### Prerequisites

- **Operating System:** Windows, macOS, or Linux
- **Compiler:** GCC or Clang supporting C++11 or higher
- **Graphics Card:** Latest generation GPU (e.g., NVIDIA RTX 4090) for optimal performance
- **Libraries:**
  - [GLFW](https://www.glfw.org/) - Window and input management
  - [GLEW](http://glew.sourceforge.net/) - OpenGL extension wrangler
  - [GLM](https://glm.g-truc.net/0.9.9/index.html) - Mathematics library for graphics software
  - [STB Image](https://github.com/nothings/stb) - Image loading library
  - [Assimp](https://www.assimp.org/) - Model loading library

### Clone the Repository

```bash
git clone https://github.com/yourusername/FuturisticEmeraldIsle.git
cd FuturisticEmeraldIsle
