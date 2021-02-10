load("//mediapipe/framework/port:build_config.bzl", "mediapipe_proto_library")

cc_library(
    name = "hand-gesture-recognition-zoom-calculator",
    srcs = ["hand-gesture-recognition-zoom-calculator.cc"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:landmark_cc_proto",
        "//mediapipe/framework/formats:rect_cc_proto",
        "//mediapipe/framework/formats:classification_cc_proto",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/port:ret_check",
    ],
    alwayslink = 1,
)