
========
GNU Make
========
* `Your Makefiles are wrong <https://tech.davis-hansson.com/p/make/>`_

Changing defaults
#################

.. code-block:: make
   :force:

   # Use strict mode Bash instead of /bin/sh
   SHELL := bash
   .SHELLFLAGS := -eu -o pipefail -c

   # Run each recipe in single shell session instead of a shell per line.
   # Lets you do bash loops, variable assignments etc
   .ONESHELL

   # Delete target file if rule fails.
   # Lets you properly re-run failed rule, guards against broken files.
   .DELETE_ON_ERROR

   # Warns you if you try to use a non-existent variable
   MAKEFLAGS += --warn-undefined-variables

   # Disable magic
   MAKEFLAGS += --no-builtin-rules

   # Use `>` instead of tabs
   ifeq ($(origin .RECIPEPREFIX), undefined)
     $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
   endif
   .RECIPEPREFIX = >


Writing Makefile
################

.. code-block:: make
   :force:

   # Default rule
   .PHONY: build
   build: out/image-id

   # Clean up the output directories;
   # since all the sentinel files go under tmp,
   # this will cause everything to get rebuilt
   .PHONY: clean
   clean:
   > rm -rf tmp
   > rm -rf out

   # Tests - re-ran if any file under src has been changed
   # since tmp/.tests-passed.sentinel was last touched
   tmp/.tests-passed.sentinel: $(shell find src -type f)
   > mkdir -p $(@D)
   > node run test
   > touch $@

   # Webpack - re-built if the tests have been rebuilt
   # (and so, by proxy, whenever the source files have changed)
   tmp/.packed.sentinel: tmp/.tests-passed.sentinel
   > mkdir -p $(@D)
   > webpack ..
   > touch $@

   # Docker image - re-built if the webpack output has been rebuilt
   out/image-id: tmp/.packed.sentinel
   > mkdir -p $(@D)
   > image_id="example.com/my-app:$$(pwgen -1)"
   > docker build --tag="$${image_id}
   > echo "$${image_id}" > out/image-id
