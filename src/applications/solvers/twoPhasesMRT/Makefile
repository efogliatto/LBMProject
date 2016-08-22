HEADERS = data.h
OBJECTS = twoPhasesMRT.o \
	readTime.o \
	readLatticeProperties.o \
	readFieldsProperties.o \
	readScalarField.o \
	readVectorField.o \
	readPdfField.o \
	readNeighbours.o \
	collideCahnHilliard.o \
	latticeVel.o \
	latticeWeights.o \
	sourceTermCH.o \
	sourceMatrix.o \
	collisionMatrix.o \
	lbModelM.o \
	lbModelInvM.o \
	CHequilibrium.o

default: twoPhasesMRT

%.o: %.c $(HEADERS)
	gcc -c -O3 $< -o $@

twoPhasesMRT: $(OBJECTS)
	gcc $(OBJECTS) -O3 -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f twoPhasesMRT

install:
	cp twoPhasesMRT ~/LBMProject_v3/bin
