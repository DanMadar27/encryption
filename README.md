# Encryption Algorithm

This project is implementation of public key encryption algorithm.


## Getting Started


* Use run.sh/bat file in tools/operating_system/prod directory to run the project.

* Use run.mk makefile in tools/operating_system/prod directory to add files to compile when running the project.


### Prerequisites

* gcc compiler and be able to use it in shell/cmd.

* make executable in order to use makefiles.

* if using windows, use cygwin to be able to include unix headers.


### Installing

Check if need to change:

* CC variable in makefiles.

* MAKE variable in sh/bat files.


## Running The Tests

* Use run.sh/bat file in tools/operating_system/test/test_name directory to run the wanted test.

* Use run.mk makefile in tools/operating_system/test/test_name directory to add files to compile when running the wanted test.


### Types Of Tests

* random strings - encryption of random strings.

* files - encryption of files.

* messages - usage of server and client with message encryption.