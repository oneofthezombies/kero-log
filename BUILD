cc_library(
    name = "kero_log",
    srcs = ["src/kero_log.cc"],
    hdrs = ["src/kero_log.h"],
    deps = [
        "@kero_mpsc//:kero_mpsc",
    ],
    copts = ["-std=c++20"],
)

cc_test(
    name = "kero_log_test",
    srcs = ["src/kero_log_test.cc"],
    deps = [
        ":kero_log",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "kero_log_example",
    srcs = ["src/kero_log_example.cc"],
    deps = [":kero_log"],
)
