# EngineSampleProject

EngineSampleProject is a Java-based sample project that showcases modular development and integrates with the [Engine](https://github.com/Przemek2122/Engine) submodule. It also includes build scripts for creating builds for supported platforms.

## Project Structure

The project is organized as follows:

- **`Project/config/`**: This directory contains build scripts for building the project on various supported platforms. You can use these scripts to set up builds efficiently.
- **`Project/CMakeLists.txt`**: The main CMake configuration file for building the project. This file defines the build process and dependencies.
- **`Project/Source/`**: This directory contains the core application source code.
- **`Project/SourcesTest/`**: This directory contains test code implemented using Google Test. These tests are designed to ensure the reliability and correctness of the project's functionalities.
- **Engine Submodule**: The project includes the [Engine](https://github.com/Przemek2122/Engine) as a submodule, providing additional functionality.

**Important:** The `build` directory is the output directory where builds created using the `config` scripts will be stored.

## Getting Started

1. **Clone the repository**:
   ```bash
   git clone --recurse-submodules https://github.com/Przemek2122/EngineSampleProject.git
   cd EngineSampleProject
   ```

2. **Navigate to the `Project` directory**:
   ```bash
   cd Project
   ```

3. **Adjust the configuration**:
   Build the project using the appropriate scripts in the `config` directory. Modify the build scripts as needed to suit your specific platform or requirements.

4. **Run the application**:
   The built application will be available in the `build` directory.

5. **Run the tests**:
   - Navigate to the `SourcesTest` directory.
   - Use CMake to build and execute the tests:
     ```bash
     cmake --build build --target test
     ```

## Engine Submodule

This project depends on the [Engine](https://github.com/Przemek2122/Engine) submodule. Ensure that you have initialized and updated the submodule when cloning the repository:
```bash
git submodule update --init --recursive
```
And after downloading Engine submodule init Engine submodules
```bash
cd Engine
git submodule update --init --recursive
```

---

## License

This project doesn’t specify a license. For any usage or distribution inquiries, please contact the repository owner, [Przemek2122](https://github.com/Przemek2122).

---

## About the Author

The repository is maintained by [Przemek2122](https://github.com/Przemek2122). Feedback, ideas, and collaboration are warmly invited.
