cc_library(
    name = "kero_log",
    hdrs = ["kero_log.h"],
)

cc_test(
    name = "kero_log_test",
    srcs = ["kero_log_test.cc"],
    deps = [
        ":kero_log",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "kero_log_example",
    srcs = ["kero_log_example.cc"],
    deps = [":kero_log"],
)
