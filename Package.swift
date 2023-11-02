// swift-tools-version:5.3

import PackageDescription

let package = Package(
    name: "ZXingCpp",
    products: [
        .library(
            name: "ZXingCpp",
            targets: ["ZXingCpp"]
        ),
    ],
    dependencies: [
        .package(name: "CppZXingCpp", url: "https://github.com/t-ae/zxing-cpp", .branch("swiftpm")),
    ],
    targets: [
        .target(
            name: "CZXingCpp",
            dependencies: ["CppZXingCpp"]
        ),
        .target(
            name: "ZXingCpp",
            dependencies: ["CZXingCpp"]
        ),
    ],
    cxxLanguageStandard: .cxx1z
)
