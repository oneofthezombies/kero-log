cc_library(
    name = "kero_log",
    srcs = [
        "src/internal/center.cc",
        "src/internal/center.h",
        "src/internal/core.cc",
        "src/internal/core.h",
        "src/internal/error_code.cc",
        "src/internal/error_code.h",
        "src/internal/global_context.cc",
        "src/internal/global_context.h",
        "src/internal/local_context.cc",
        "src/internal/local_context.h",
        "src/internal/log_builder.cc",
        "src/internal/log_builder.h",
        "src/internal/runner_event.cc",
        "src/internal/runner_event.h",
        "src/internal/transport.cc",
        "src/internal/transport.h",
        "src/internal/utils.cc",
        "src/internal/utils.h",
    ],
    hdrs = [
        "src/kero_common.h",
        "src/kero_log.h",
    ],
    copts = ["-std=c++20"],
    includes = ["src"],
    visibility = ["//visibility:public"],
    deps = [
        "@kero_mpsc",
        "@kero_spsc",
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

cc_test(
    name = "kero_common_test",
    srcs = [
        "src/kero_common.h",
        "src/kero_common_test.cc",
    ],
    copts = ["-std=c++20"],
    deps = [
        "@googletest//:gtest_main",
    ],
)
