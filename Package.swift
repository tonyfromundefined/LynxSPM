// swift-tools-version:5.5
// Package.swift

import PackageDescription

let package = Package(
    name: "LynxSPM",
    platforms: [
        .iOS(.v13)
    ],
    products: [
        .library(name: "Lynx", targets: ["Lynx"]),
        .library(name: "LynxService", targets: ["LynxService"]),
    ],
    dependencies: [],
    targets: [
        .binaryTarget(
            name: "PrimJS",
            path: "./Sources/PrimJS.xcframework"
        ),
        .binaryTarget(
            name: "SDWebImageWebPCoder",
            path: "./Sources/SDWebImageWebPCoder.xcframework"
        ),
        .binaryTarget(
            name: "SDWebImage",
            path: "./Sources/SDWebImage.xcframework"
        ),
        .binaryTarget(
            name: "Lynx",
            path: "./Sources/Lynx.xcframework",
            dependencies: [
                "PrimJS"
            ]
        ),
        .binaryTarget(
            name: "LynxService",
            path: "./Sources/LynxService.xcframework",
            dependencies: [
                "Lynx",
                "SDWebImage",
                "SDWebImageWebPCoder"
            ]
        )
    ]
)
