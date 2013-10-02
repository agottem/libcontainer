# The C container library is licensed under the simplified BSD license:
#
# Copyright 2013, Andrew Gottemoller
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# Redistributions of source code must retain the above copyright notice, this list of
# conditions and the following disclaimer:
#
# Redistributions in binary form must reproduce the above copyright notice, this list
# of conditions and the following disclaimer in the documentation and/or other materials
# provided with the distribution.
#
# Neither the name Andrew Gottemoller nor the names of its contributors may be used to
# endorse or promote products derived from this software without specific prior written
# permission.


CC ?= gcc

example_programs := ex_bal   \
                    ex_bst   \
                    ex_clist \
                    ex_hash  \
                    ex_queue \
                    ex_slist \
                    ex_stack

define example_program_rule
    .PHONY : $(1)
    $(1) : bin/$(1)

    bin/$(1) : source/$(1).c
    bin/$(1) : source_file := source/$(1).c
endef


.PHONY : all
all : $(example_programs)

.PHONY : clean
clean :
	rm -rf bin


$(foreach example,$(example_programs),$(eval $(call example_program_rule,$(example))))

$(addprefix bin/,$(example_programs)) : $(MAKEFILE_LIST) | bin
	$(CC) -Wall -pedantic -g $(source_file) -std=c99 -o $@ -lcontainer

bin :
	mkdir -p bin
