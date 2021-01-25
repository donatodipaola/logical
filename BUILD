cc_library(
    name = "logical", 
    hdrs = ["include/logical.hpp"],
    includes = ["include"],
    visibility = ["//visibility:public"],
)

cc_test (
    name = "logical_test",
    srcs = glob(["test/*.cpp"]),
    deps = [
        "@gtest//:gtest",
        "logical",
    ],
)