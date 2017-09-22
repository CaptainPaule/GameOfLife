cdef extern from "game.h" namespace pb:
	cdef cppclass game:
		game(int, char*)
		start(int)
