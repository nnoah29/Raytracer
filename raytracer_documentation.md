# RAYTRACER Project Documentation

## Overview
The RAYTRACER project is a C++ application designed to render 3D scenes using ray tracing techniques. It supports dynamic plugins and utilizes the SFML library for graphics rendering.

## Authors
- Noah TOFFA
- Hermes AGANI
- Chance TOSSOU

## Project Structure
- **app/**: Contains the main application entry point.
- **includes/**: Header files for various components.
- **src/**: Source files for core functionalities.
- **utilitaires/**: Utility functions and helpers.
- **plugins/**: Dynamic plugins for additional features.

## Implemented Features
- **Primitives**:
  - Sphere
  - Plane
  - Cylinder
  - Cone
  - Limited cylinder (0.5)
  - Limited cone (0.5)

- **Transformations**:
  - Translation
  - Rotation
  - Scale (0.5)
  - Shear (0.5)
  - Transformation matrix (2)

- **Lighting**:
  - Directional light
  - Ambient light
  - Multiple directional lights (0.5)
  - Multiple point lights (1)
  - Drop shadows

- **Material**:
  - Flat color

- **Scene Configuration**:
  - Add primitives to scene
  - Set up lighting
  - Set up camera

- **Optimizations**:
  - Multithreading (1)

## Setup Instructions
1. **Prerequisites**:
   - CMake 3.16 or higher
   - SFML 2.5 or higher
   - C++20 compatible compiler

2. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd RAYTRACER
   ```

3. **Build the Project**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

## Usage
- **Running the Application**:
  ```bash
  ./raytracer <scene-file> -p <plugin-path>
  ```
  Replace `<scene-file>` with the path to your scene configuration file and `<plugin-path>` with the path to your plugin.

## Example Configuration File
Here's an example of a configuration file that specifies a scene and uses a plugin:

```plaintext
# Camera configuration
camera : {
    resolution = { width = 1920; height = 1080; };
    position = { x = 0.0; y = 0.0; z = 20.0; };
    rotation = { x = 0.0; y = 0.0; z = 0.0; };
    fieldOfView = 90.0; # In degree
};

# Primitives in the scene
primitives : {
    # List of spheres
    spheres = (
        { x = 0.0; y = 0.0; z = -10.0; r = 5.0; color = { r = 64.0; g = 255.0; b = 64.0; }; shininess = 64.0 },
    );

    # List of planes
    planes = (
        { axis = "Y"; position = -3.0; color = { r = 64.0; g = 64.0; b = 255.0; }; shininess = 64.0 }
    );

    # List of cones
    cones = (
        # { axis = "Y"; x = 0.0; y = 0.0; z = -10.0; h = 50.0; corner = 40.0; color = { r = 255.0; g = 64.0; b = 64.0; }; shininess = 64.0; rotation = { x = 0.0; y = 15.0; z = 0.0; at = "axis" } }
    );

    # List of cylinders
    cylinders = (
        # { x = 21.0; y = 0.0; z = -10.0; r = 15.0; h = 50.0; color = { r = 255.0; g = 64.0; b = 64.0; }; shininess = 64.0 }
    );
};

# Light configuration
lights : {
    ambient = 0.4; # Multiplier of ambient light
    diffuse = 0.6; # Multiplier of diffuse light

    # List of point lights
    point = (
        { x = 20.0; y = 10.0; z = 20.0; color = { r = 64.0; g = 64.0; b = 255.0; }; },
        # { x = 0.0; y = -20.0; z = -0.0; }
    );

    # List of directional lights
    directional = (
        { x = 20.0; y = 10.0; z = 10.0; }
    );
};
```

## Build Process
- **CMake Configuration**: The project uses CMake for build configuration. The `CMakeLists.txt` file defines the build targets and dependencies.
- **Dynamic Plugins**: Plugins are built as shared libraries and placed in the `plugins/` directory.

## Testing
- **Unit Tests**: The project includes unit tests using Criterion. To build and run tests:
  ```bash
  make tests
  ./tests
  ```

## Contributing
- Contributions are welcome. Please follow the project's coding standards and submit pull requests for review.

## Contact
For questions or support, please contact the project maintainers at [noah.toffa@epitech.eu].