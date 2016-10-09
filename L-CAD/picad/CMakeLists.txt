set(PICAD_SRC
	src/main.c
	)

add_executable(picad ${PICAD_SRC})
target_link_libraries(testmain 
					  lcadengine
					  wiringPi
					  )