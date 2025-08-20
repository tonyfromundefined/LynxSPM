// swift-tools-version:5.5
// Package.swift

import PackageDescription

let package = Package(
    name: "LynxSPM",
    platforms: [.iOS(.v13)],
    products: [
        .library(name: "LynxSPM", targets: ["LynxSPM"]),
    ],
    dependencies: [],
    targets: [
        .binaryTarget(name: "PrimJS", path: "./Sources/PrimJS.xcframework"),
        .binaryTarget(name: "SDWebImageWebPCoder", path: "./Sources/SDWebImageWebPCoder.xcframework"),
        .binaryTarget(name: "SDWebImage", path: "./Sources/SDWebImage.xcframework"),
        .binaryTarget(name: "Lynx", path: "./Sources/Lynx.xcframework"),
        .binaryTarget(name: "LynxService", path: "./Sources/LynxService.xcframework"),

        .target(
            name: "LynxSPM",
            dependencies: [
                "LynxService",
                "Lynx",
                "SDWebImage",
                "SDWebImageWebPCoder",
                "PrimJS"
            ],
            path: "Sources/LynxSPM"
        )
    ]
)
