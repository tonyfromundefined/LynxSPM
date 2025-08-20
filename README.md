# LynxSPM

[![SPM Compatible](https://img.shields.io/badge/SPM-Compatible-brightgreen.svg)](https://swift.org/package-manager/)
[![Platform](https://img.shields.io/badge/platform-iOS-lightgrey.svg)](https://img.shields.io/badge/platform-iOS-lightgrey.svg)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

Swift Package Manager (SPM) support for the [Lynx](https://github.com/lynx-family/lynx) rendering engine.

This package distributes the library as a pre-compiled `XCFramework`, enabling easy integration and significantly faster build times for your project.

## 🚀 Why Use LynxSPM?

The original Lynx project officially supports integration via CocoaPods. This repository was created to provide a modern, simple way to integrate Lynx into projects using Swift Package Manager, removing the need for CocoaPods as a dependency.

### Features
*   **Swift Package Manager Support:** Integrate Lynx using Xcode's native dependency manager.
*   **Pre-compiled Binary:** As a pre-compiled `XCFramework`, it won't slow down your project's clean build times.
*   **Simple & Clean:** Keeps your project structure clean by managing all dependencies through SPM.

## 📦 Installation

You can add LynxSPM to your project using Xcode's built-in package manager.

1.  In Xcode, open your project and navigate to **File > Add Packages...**
2.  In the search bar, paste the repository URL:
    ```
    https://github.com/tonyfromundefined/LynxSPM
    ```
3.  For `Dependency Rule`, select **Up to Next Major Version**.
4.  Click **Add Package** and wait for it to resolve.
5.  Choose the `LynxSPM` product and add it to your app's target.

That's it! You can now `import Lynx` in your source files.
