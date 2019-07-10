# Makefile stuff
include_directories(.)
add_library(board OBJECT board.cc board.h)
target_compile_features(board PUBLIC cxx_auto_type cxx_return_type_deduction cxx_noexcept cxx_decltype cxx_delegating_constructors cxx_alias_templates PRIVATE cxx_trailing_return_types)
target_include_directories(board PUBLIC "${CURSES_INCLUDE_DIRS}")
add_executable(graph main.cc)
target_include_directories(graph PRIVATE "${CURSES_INCLUDE_DIRS}")
target_link_libraries(graph board "${CURSES_LIBRARIES}")
#[[
target_include_directories(game PRIVATE "${CURSES_INCLUDE_DIRS}")
target_compile_features(game PRIVATE cxx_lambdas cxx_decltype)
target_link_libraries(game "${CURSES_LIBRARIES}")
add_executable(battle battle.cc health_bar stats.h correct_curses.h)
target_compile_features(battle PRIVATE cxx_noexcept cxx_auto_type cxx_decltype)
target_include_directories(battle PRIVATE "${CURSES_INCLUDE_DIRS}")
target_link_libraries(battle "${CURSES_LIBRARIES}")
#]]
