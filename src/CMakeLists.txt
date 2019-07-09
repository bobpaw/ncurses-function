# Makefile stuff
include_directories(.)
add_library(board OBJECT board.cc board.h)
target_compile_features(board PUBLIC cxx_auto_type $<IF:$<COMPILE_FEATURES:cxx_return_type_deduction>,cxx_return_type_deduction,cxx_trailing_return_types> cxx_noexcept cxx_nullptr cxx_decltype)
target_include_directories(board PUBLIC "${CURSES_INCLUDE_DIRS}")
add_executable(graph main.cc board)
target_include_directories(graph PRIVATE "${CURSES_INCLUDE_DIRS}")
target_link_libraries(graph "${CURSES_LIBRARIES}")
#[[
target_include_directories(game PRIVATE "${CURSES_INCLUDE_DIRS}")
target_compile_features(game PRIVATE cxx_lambdas cxx_decltype)
target_link_libraries(game "${CURSES_LIBRARIES}")
add_executable(battle battle.cc health_bar stats.h correct_curses.h)
target_compile_features(battle PRIVATE cxx_noexcept cxx_auto_type cxx_decltype)
target_include_directories(battle PRIVATE "${CURSES_INCLUDE_DIRS}")
target_link_libraries(battle "${CURSES_LIBRARIES}")
#]]
