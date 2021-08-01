cmake_minimum_required(VERSION 3.19)
project(C_code_examples C)

set(CMAKE_C_STANDARD 99)

add_executable(C_code_examples FSM_Table.c FSM_TDD.c)
#add_executable(C_code_examples leitor_escritor.c) #produtor_consumidor.c