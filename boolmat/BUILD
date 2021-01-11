cc_library(
    name = "boolmat", 
    srcs = glob(["src/*.cpp"]),
    hdrs = glob(["include/*.hpp"]),
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