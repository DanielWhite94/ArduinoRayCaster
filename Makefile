all: raycast


raycast: force_check
	cd raycast && make


clean:
	cd raycast && make clean

force_check:
	@true
