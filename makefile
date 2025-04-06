CC = gcc
CFLAGS = -Wall -g
LDFLAGS =
OBJFILES = main.o patient.o doctor.o TUI.o file.o patientsList.o scheduleFile.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) *~
	rm *.txt
