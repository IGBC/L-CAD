
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(PICAD_SRC
	main.c
    IO.c
    wires.c
	fileparser.c
	)

add_executable(picad ${PICAD_SRC})
target_link_libraries(picad 
					  lcadengine
					  wiringPi
					  )
