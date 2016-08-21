HEADERS = data.h
OBJECTS = twoPhasesMRT.o readTime.o readLatticeProperties.o readFieldsProperties.o

default: twoPhasesMRT

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

twoPhasesMRT: $(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f twoPhasesMRT
