CMAKE_MINIMUm_REQUIRED(VERSION 2.6) # 最低版本说明
PROJECT(HELLO)	# 项目名称
SET(CMAKE_INSTALL_PREFIX  ${CMAKE_BINARY_DIR})  # 设置项目前缀
ADD_SUBDIRECTORY(src bin)	# 添加子目录src，输出目录bin

#########################################################################################
# Parameters setting

set_property(GLOBAL
             PROPERTY
             FOO
             1
             2
             3)

set(numbers 1 2 3)
set_property(GLOBAL
             PROPERTY
             GOO
             "${numbers}")

get_cmake_property(foo_value FOO)
message(STATUS "value of FOO is ${foo_value}")

get_cmake_property(goo_value GOO)
message(STATUS "value of GOO is ${goo_value}")

# The values written behind the 1st arg of set() will all considered as a string.
set(my_list 4 5 6)
set(target DIRECTORY "${PROJECT_SOURCE_DIR}")
# If there is no "" outside of ${}, it means that each parameters separated by "space"...
# ... will be considered as an individual value.
set_property(${target}
             PROPERTY FOO
             ${my_list})

# get_cmake_property() is specifically used to call GLOBAL parameters.
get_property(foo_value ${target} PROPERTY FOO)
message(STATUS "value of FOO is ${foo_value}")

#########################################################################################
# Function logic

function(func_name arg1 arg2)
    message(STATUS "First arg: ${arg1} | Second arg: ${arg2}")
endfunction()

func_name(1 2)

# If we do not know how many arguments will be received in a function, this can help:
function(func_name arg1 arg2 arg3)
    foreach(arg IN LISTS ARGN)
        # ARGN will only get those extra parameters out of the range of arg123.
        message(STATUS "Got argn: ${arg}")
    endforeach()

    foreach(arg IN LISTS ARGV)
        # ARGV will get all parameters regardless of the predefined arg position in function()
        message(STATUS "Got argv: ${arg}")
    endforeach()
endfunction()

func_name(1 2 3 4 5 6)

#########################################################################################
# Scope

set(GLOBAL_VAR 10)

function(func_name)
    message(STATUS "Global var in func: ${GLOBAL_VAR}")
    set(GLOBAL_VAR 11)
    # If we want to change the global variable in a func, use the following line of code.
    # set(GLOBAL_VAR 11 PARENT_SCOPE)
    message(STATUS "Global var in func: ${GLOBAL_VAR}")
endfunction()

func_name()
message(STATUS "Global var out of func: ${GLOBAL_VAR}")

#########################################################################################
# Dereference

function(increment var)
    # If we only use ${var}, dereferencing only once, it will be "value".
    # In order to get the variable behind "value", ${} should be applied twice.
    message(STATUS "Value before increment is ${${var}}")
    math(EXPR new_value "${${var}} + 1")
    message(STATUS "Value after increment is ${new_value}")
    set(${var} ${new_value} PARENT_SCOPE)
endfunction()

set(value 14)
increment(value)
increment(value)
message(STATUS "Final value: ${value}")

function(sum out var1 var2)
    math(EXPR res "${var1} + ${var2}")
    set(${out} ${res} PARENT_SCOPE)
endfunction()

sum(value 9 71)
message(STATUS "Sum num: ${value}")
