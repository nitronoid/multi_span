
BASE_OPTS = ["-Wall", "-Wextra", "-pedantic", "-Wno-array-bounds",]

MULTI_SPAN_TESTS_COPTS = select({
    "@bazel_tools//src/conditions:windows": [].extend(BASE_OPTS),
    "//conditions:default": [].extend(BASE_OPTS),
})

MULTI_SPAN_TESTS_DEFINES = ["MULTI_SPAN_THROW_ON_CONTRACT_VIOLATION"]

cc_library(
    name = "test_main",
    srcs = ["src/tests.cpp"],
    deps = [
        "@catch2//:catch2",
    ],
    alwayslink = True,
)

cc_test(
    name = "bounds_tests",
    size = "small",
    srcs = [
        "src/bounds_tests.cpp",
    ],
    copts = MULTI_SPAN_TESTS_COPTS,
    defines = MULTI_SPAN_TESTS_DEFINES,
    deps = [
        ":test_main",
        "//:multi_span",
        "@catch2//:catch2",
    ],
)

cc_test(
    name = "multi_span_tests",
    size = "small",
    srcs = [
        "src/multi_span_tests.cpp",
    ],
    copts = MULTI_SPAN_TESTS_COPTS,
    defines = MULTI_SPAN_TESTS_DEFINES,
    deps = [
        ":test_main",
        "//:multi_span",
        "@catch2//:catch2",
    ],
)

cc_test(
    name = "strided_span_tests",
    size = "small",
    srcs = [
        "src/strided_span_tests.cpp",
    ],
    copts = MULTI_SPAN_TESTS_COPTS,
    defines = MULTI_SPAN_TESTS_DEFINES,
    deps = [
        ":test_main",
        "//:multi_span",
        "@catch2//:catch2",
    ],
)
