cc_library(
    name = "kero_log",
    srcs = [
        "src/center.cc",
        "src/center.h",
        "src/core.cc",
        "src/core.h",
        "src/internal/event.cc",
        "src/internal/event.h",
        "src/internal/runner.cc",
        "src/internal/runner.h",
        "src/log_builder.cc",
        "src/log_builder.h",
        "src/logger.cc",
        "src/logger.h",
    ],
    hdrs = [
        "src/kero_log.h",
    ],
    copts = ["-std=c++20"],
    includes = ["src"],
    visibility = ["//visibility:public"],
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
