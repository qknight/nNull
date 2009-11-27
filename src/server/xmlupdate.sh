#!/bin/bash
# this script should be run if the interface.xml description changes,
# this won't happen often and it will overwrite your custom changes
# in nm_adaptor.h and nm_adaptor.cpp
# you might want to use git to return to an older revision of these files
cp ../interface.xml .
qdbusxml2cpp -c NmAdaptor \
             -a src/nm_adaptor.h:src/nm_adaptor.cpp \
             interface.xml
