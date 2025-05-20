CPMAddPackage(
  NAME protobuf
  GIT_TAG bba83652e1be610bdb7ee1566ad18346d98b843c # v2.6.1
  GITHUB_REPOSITORY protocolbuffers/protobuf
  GIT_SHALLOW YES
  DOWNLOAD_ONLY YES
)

add_library(protobuf STATIC)

target_gothic_lib_options(protobuf)
target_compile_definitions(protobuf PRIVATE _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS)
target_include_directories(protobuf
  PUBLIC ${protobuf_SOURCE_DIR}/src ${protobuf_SOURCE_DIR}/vsprojects
)

# libprotobuf-lite
target_tree_sources(protobuf
  ROOT ${protobuf_SOURCE_DIR}
  BASE ${protobuf_SOURCE_DIR}/src
  PRIVATE
    google/protobuf/extension_set.cc
    google/protobuf/extension_set.h
    google/protobuf/generated_message_util.cc
    google/protobuf/generated_message_util.h
    google/protobuf/message_lite.cc
    google/protobuf/message_lite.h
    google/protobuf/repeated_field.cc
    google/protobuf/repeated_field.h
    google/protobuf/wire_format_lite.cc
    google/protobuf/wire_format_lite.h
    google/protobuf/wire_format_lite_inl.h

    google/protobuf/io/coded_stream.cc
    google/protobuf/io/coded_stream.h
    google/protobuf/io/coded_stream_inl.h
    google/protobuf/io/zero_copy_stream.cc
    google/protobuf/io/zero_copy_stream.h
    google/protobuf/io/zero_copy_stream_impl_lite.cc
    google/protobuf/io/zero_copy_stream_impl_lite.h

    google/protobuf/stubs/atomicops.h
    google/protobuf/stubs/atomicops_internals_x86_msvc.cc
    google/protobuf/stubs/atomicops_internals_x86_msvc.h
    google/protobuf/stubs/common.cc
    google/protobuf/stubs/common.h
    google/protobuf/stubs/hash.h
    google/protobuf/stubs/map_util.h
    google/protobuf/stubs/once.cc
    google/protobuf/stubs/once.h
    google/protobuf/stubs/platform_macros.h
    google/protobuf/stubs/stl_util.h
    google/protobuf/stubs/stringprintf.cc
    google/protobuf/stubs/stringprintf.h
    google/protobuf/stubs/template_util.h
    google/protobuf/stubs/type_traits.h

  BASE ${imgui_SOURCE_DIR}
    vsprojects/config.h
)
