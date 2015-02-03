SCHEMAROOT=../../RedfishSchema

CSDLFILES= \
    $(SCHEMAROOT)/AccountService.0.9.2.metadata \
    $(SCHEMAROOT)/Chassis.0.9.2.metadata \
    $(SCHEMAROOT)/ComputerSystem.0.9.2.metadata \
    $(SCHEMAROOT)/DMTFExtensions.0.9.2.metadata \
    $(SCHEMAROOT)/Errors.0.9.2.metadata \
    $(SCHEMAROOT)/EthernetNetworkInterface.0.9.2.metadata \
    $(SCHEMAROOT)/Event.0.9.2.metadata \
    $(SCHEMAROOT)/EventService.0.9.2.metadata \
    $(SCHEMAROOT)/Firmware.0.9.2.metadata \
    $(SCHEMAROOT)/IPAddresses.0.9.2.metadata \
    $(SCHEMAROOT)/ListenerDestination.0.9.2.metadata \
    $(SCHEMAROOT)/LogEntry.0.9.2.metadata \
    $(SCHEMAROOT)/LogService.0.9.2.metadata \
    $(SCHEMAROOT)/Manager.0.9.2.metadata \
    $(SCHEMAROOT)/ManagerAccount.0.9.2.metadata \
    $(SCHEMAROOT)/ManagerNetworkService.0.9.2.metadata \
    $(SCHEMAROOT)/Messages.0.9.2.metadata \
    $(SCHEMAROOT)/MiscMetrics.0.9.2.metadata \
    $(SCHEMAROOT)/PowerMetrics.0.9.2.metadata \
    $(SCHEMAROOT)/Redundancy.0.9.2.metadata \
    $(SCHEMAROOT)/Resource.0.9.2.metadata \
    $(SCHEMAROOT)/SerialInterface.0.9.2.metadata \
    $(SCHEMAROOT)/ServiceRoot.0.9.2.metadata \
    $(SCHEMAROOT)/Session.0.9.2.metadata \
    $(SCHEMAROOT)/SimpleStorage.0.9.2.metadata \
    $(SCHEMAROOT)/Task.0.9.2.metadata \
    $(SCHEMAROOT)/TaskService.0.9.2.metadata \
    $(SCHEMAROOT)/ThermalMetrics.0.9.2.metadata \
    $(SCHEMAROOT)/VirtualMedia.0.9.2.metadata

CFILES = \
    AccountService.c \
    Chassis.c \
    ComputerSystem.c \
    DMTFExtensions.c \
    Errors.c \
    EthernetNetworkInterface.c \
    Event.c \
    EventService.c \
    Firmware.c \
    IPAddresses.c \
    ListenerDestination.c \
    LogEntry.c \
    LogService.c \
    ManagerAccount.c \
    Manager.c \
    ManagerNetworkService.c \
    Messages.c \
    MiscMetrics.c \
    PowerMetrics.c \
    Redundancy.c \
    Resource.c \
    SerialInterface.c \
    ServiceRoot.c \
    Session.c \
    SimpleStorage.c \
    Task.c \
    TaskService.c \
    ThermalMetrics.c \
    VirtualMedia.c

OFILES = $(CFILES:.c=.o)

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

#VG=valgrind --tool=memcheck --leak-check=full --show-reachable=yes

all:
	$(VG) ../csdl2c $(CSDLFILES)
	$(MAKE) comp

CFLAGS = -Werror -m32 -Wall -Os -fvisibility=hidden
INCLUDES = -I../..

define NL


endef

comp:
	$(foreach i, $(SOURCES), gcc -c $(CFLAGS) $(INCLUDES) $i $(NL) )
	gcc $(CFLAGS) -shared -o libmetadata.so $(OBJECTS)

clean:
	rm -f $(CFILES) $(OFILES) main.o libmetadata.so
