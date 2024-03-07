cc_library(
    name = "kero_log",
    srcs = ["src/kero_log.cc"],
    hdrs = ["src/kero_log.h"],
    copts = ["-std=c++20"],
    deps = [
        "@kero_mpsc",
    ],
)

cc_test(
    name = "kero_log_test",
    srcs = ["src/kero_log_test.cc"],
    copts = ["-std=c++20"],
    deps = [
        ":kero_log",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "kero_log_example",
    srcs = ["src/kero_log_example.cc"],
    copts = ["-std=c++20"],
    deps = [":kero_log"],
)
