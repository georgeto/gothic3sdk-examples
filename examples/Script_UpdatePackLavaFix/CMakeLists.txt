add_library(Script_UpdatePackLavaFix SHARED)

target_link_libraries(Script_UpdatePackLavaFix PRIVATE g3sdk::SDK)

target_gothic_script_options(Script_UpdatePackLavaFix)

target_tree_sources(Script_UpdatePackLavaFix
  PRIVATE
    Script_UpdatePackLavaFix.cpp
)
