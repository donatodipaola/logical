cc_library(
    name = "boolmat", 
    srcs = ["src/boolmat.cpp"],
    hdrs = ["include/boolmat.hpp"],
    includes = ["include"],
    visibility = ["//visibility:public"],
)

cc_test (
    name = "boolmat_test",
    srcs = glob(["test/*.cpp"]),
    deps = [
        "@gtest//:gtest",
        "boolmat",
    ],
)