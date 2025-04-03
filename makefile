CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = main.o patient.o doctor.o TUI.o file.o patientsList.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
	# Change the target name
