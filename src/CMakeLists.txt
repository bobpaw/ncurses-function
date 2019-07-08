# Makefile stuff
include_directories(.)
add_library(app OBJECT app.cc app.h)
target_compile_features(app PUBLIC cxx_auto_type $<IF:$<COMPILE_FEATURES:cxx_return_type_deduction>,cxx_return_type_deduction,cxx_trailing_return_types> cxx_noexcept cxx_nullptr cxx_decltype)
#[[
add_library(health_bar OBJECT health_bar.cc health_bar.h)
target_compile_features(health_bar PUBLIC cxx_noexcept cxx_uniform_initialization cxx_nullptr cxx_decltype)
target_include_directories(health_bar PUBLIC "${CURSES_INCLUDE_DIRS}")

target_include_directories(game PRIVATE "${CURSES_INCLUDE_DIRS}")
target_compile_features(game PRIVATE cxx_lambdas cxx_decltype)
target_link_libraries(game "${CURSES_LIBRARIES}")
add_executable(battle battle.cc health_bar stats.h correct_curses.h)
target_compile_features(battle PRIVATE cxx_noexcept cxx_auto_type cxx_decltype)
target_include_directories(battle PRIVATE "${CURSES_INCLUDE_DIRS}")
target_link_libraries(battle "${CURSES_LIBRARIES}")
#]]
