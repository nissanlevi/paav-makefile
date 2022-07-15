##########################################################################
# Generic GNU makefile template for MSIL CAD
# GNUmakefile - Describes build structure of a project
#
# Customized for CRG
# Last Update: $Id: GNUmakefile,v 1.94 2012/01/15 08:27:02 nissanl Exp $
#
# $Log: GNUmakefile,v $
# Revision 1.94  2012/01/15 08:27:02  nissanl
# removing of old STABLE-RANDOM. Add class Stable_Rand_Unit
#
# Revision 1.93  2012/01/10 07:44:19  nissanl
# *** empty log message ***
#
# Revision 1.60  2008/03/23 15:52:24  nissanl
# *** empty log message ***
#
# Revision 1.59  2008/03/19 11:18:07  robs
# Added crg_random_set
#
#
##########################################################################

#RELEASE_TARGETS = opt
RELEASE_TARGETS = crg_version_release_target

##########################################################################
# Section 1 - Main build targets (applications, libraries, tests)
##########################################################################

# Applications and tests should list the base names of the executable files
# Libraries should list the base names of the library (without "lib" or ".a"),
# but if you like you can include the "lib" prefix as well.
# Ignore extensions to indicate optimized code; this is handled separately.
# Shared libraries are handled just like regular libraries. The same library
# can listed in both places to build both versions.
#
APPLICATIONS := run
LIBRARIES := 
TESTS := 
SHARED_LIBRARIES := 

# User-defined targets should also be declared here, though they will be
# defined at the end of the makefile.
#
# To declare user-defined targets, define variables named ???_OTHER_TARGETS, 
# where ??? is the name of the standard makefile target which should invoke
# your new target.
#
# ??? can be one of the following: all, debug, opt, apps_g, apps, tests_g,
# tests, libs_g, libs, shlibs_g, shlibs, install, strip, clean, tags.
# For each such variable you define, list the full names (including
# subdirectories if necessary) of the targets that should be built when
# that standard target is built.
#
# If your target doesn't require automatic dependency file generation,
# disable the inclusion of dependency files by also adding the target
# to the variable noinclude_OTHER_TARGETS as well.
#
# To specify actions to be taken by the release tools after the project is
# checked out or updated from CVS, list them in POSTCHECKOUT_TARGETS.
#
#all_OTHER_TARGETS := $(BIN)/mytarget


# Specify default targets
#
# a. DEFAULT_TARGETS: Default targets to be built when 'gmake' is invoked
#      without arguments. Remove or add targets to change default behavior.
#
DEFAULT_TARGETS := libs_g apps_g 

# b. RELEASE_TARGETS: Default targets to be built when project is released
#      to CAD repository. Remove or add targets to change default behavior.
#
#RELEASE_TARGETS := all 

RELEASE_PLATFORMS := linux 

##########################################################################
# Section 2 - Dependencies on other CAD projects and libraries
##########################################################################

# 2a. Other project versions used
#

WORK_ON_TEMP:=FALSE
#WORK_ON_TEMP:=TRUE

ifeq ($(WORK_ON_TEMP), TRUE)
   CAD_PROJECTS := 
else
   CAD_PROJECTS := 
endif

#CRG_DEVELOP:=FALSE
#CRG_DEVELOP:=TRUE

#CRG_TESTING:=FALSE
#CRG_TESTING:=TRUE


# To include all the project versions used by another project in this
# dependency list, use the following approach:
#
# CAD_SUBPROJECTS := subproj-2.3
# CAD_PROJECTS = $(CAD_SUBPROJECT_PROJECTS) otherproj-3.4
#
# This project now depends on version 2.3 of subproj, along with all the
# project versions it uses too.


# For temporary use by developer: LOCAL_PROJECTS is like CAD_PROJECTS,
# but looks for projects somewhere other than the CAD repository.
# Just copy the CAD_PROJECTS entry to LOCAL_PROJECTS and define ???_ROOT,
# where ??? is the name of the project. ???_ROOT should end at the
# /projects subdirectory.
#
# LOCAL_PROJECTS must be empty when a stable/bugfix version is released.
# LOCAL_PROJECTS overrides CAD_PROJECTS.
#
#LOCAL_PROJECTS := idmio-.release
#idmio_ROOT := /home/parsa/jasone/projects


# 2b. Libraries linked with
#
# Unlike CAD_LIBS, MISCLIBS will not have debugging extensions added
CAD_LIBS :=
MISCLIBS :=
SYSLIBS := nsl 

# The default link library order is CAD_LIBS, followed by MISCLIBS and SYSLIBS
# If you need a different order, define LIBORDER below. It should contain
# a list of the link library names in link order.
#LIBORDER := 


# 2c. Include and library search directories

# The following variables enable the user to customize the link library list,
# and the lists of directories to be searched for include files and link
# libraries.
#
# Directories containing the projects listed above should not be listed
# here as well.
#
INCLUDE_DIRS := 
LIBRARY_DIRS := 


##########################################################################
# Section 3 - Source files by file type
##########################################################################

HFILES := \
	assertion.h \
	assigned_val.h  command.h  expr.h  line_command.h  logger.h  pa_parser.tab.h  program.h  traverse.h  yacc_functions.h \
	crg_prs_global_items.h \
	crg_range.h \

CCFILES := assertion.cc  assigned_val.cc  command.cc  expr.cc  line_command.cc  logger.cc  main.cc  program.cc  traverse.cc  yacc_functions.cc

CFILES := \



# To use the new approach for Yacc and Lex files, uncomment the below line
# setting LEX_YACC_HANDLER := new. With this approach, the parser and lexer
# files must come in pairs which differ only in their suffixes:
# for example, MyParser.y and MyParser.l
#
# The intermediate C files will be written out to MyParser.y.c MyParser.l.c
# They do *not* need to be included under CFILES above. The parser header
# file will be called MyParser.ytab.h, and it does *not* need to be included
# under HFILES above.
# 
# The object files will be called MyParser.y.o and MyParser.l.o
#
# To use the old technique for lex/yacc, change below to LEX_YACC_HANDLER := old
# and enter prefixes as appropriate below:
#YACCPREFIX := <prefix>
#c/Parsefile2.c c/Lexfile2.c: YACCPREFIX := <prefix2>
#
# To generate C++ object files using flex, change below to LEX_YACC_HANDLER := flex++
# Object files will be named as with the old technique (.o, not .l.o)
#
LEX_YACC_HANDLER := new

#c/crg_prs_yacc.cc c/crg_prs_lex.cc: YACCPREFIX = crg_prs

YFILES := pa_parser.y
LFILES := pa_parser.l


##########################################################################
# Section 4 - Object files for each main build target
##########################################################################

# Object files generated by the project in its object file directory
#
# "Common" object files will be linked with all targets (apps, libs & tests)
COMMON_OFILES := \
#	<file.o> \

# Object files generated externally but to be linked with this project
# Must be listed with full pathnames!
COMMON_EXTERN_OFILES := \
#	<full/path/name/file.o>

# Object files to be linked only with particular targets
# Use the form ???_OFILES, where ??? is the target name
#idmfilter_OFILES := \
#	<file.o>

run_OFILES = pa_parser.y.o pa_parser.l.o assertion.o  assigned_val.o  command.o  expr.o  line_command.o  logger.o  main.o  program.o  traverse.o  yacc_functions.o



# As above, but generated externally; need full pathnames
#???_EXTERN_OFILES := \
#	<file.o>

# If EXTERN_OFILES_NOOPT is defined, external object files will be assumed 
# only to exist in one form (optimized or debugging) and their suffixes will
# not be changed. This will apply to individual project ???_EXTERN_OFILES as 
# well as COMMON_EXTERN_OFILES
#
#EXTERN_OFILES_NOOPT := dummy

# If any of the executables need special linker flags, list them in
# ???_EXTRA_LDFLAGS (where ??? is the target name) or ???_EXTRA_LIBFLAGS


##########################################################################
# Section 5 - Files to be installed (scripts, manpages, ugli files)
##########################################################################

SCRIPTS := \


#	<scriptfile>

MAN_PAGES := \
#	<manpage.1>

UGLI_FILES := \
#	<uglifile>


# User-defined: list any miscellaneous files you want to be deleted
# when 'make clean' is invoked
CLEAN_FILES := \
#	<filetoclean>


##########################################################################
# Section 6 - Other files to be released
##########################################################################

# All files which should be released to the CAD repository must be included below
# (unless they've already been listed above under CCFILES, CFILES, YFILES,
# LFILES, SCRIPTS, MAN_PAGES, or UGLI_FILES)
#
# Only list source files or documents, not files which will be created by make.

DOC_FILES := \

TEST_FILES := \
#	<docfile>

# Misc files should include the directory name (i.e., demo/testfile.txt)
MISC_FILES := \

#	<subdirectory/miscfile>

# User files which affect the compilation of one or more build targets.
# If one of these files has changed, the release scripts will force an
# incremental rebuild.
MISC_BUILD_FILES := \
#	<subdirectory/miscfile>

MAKE_FILES := \
	GNUmakefile \
	GNUmakefile.cfg

# Non-CVS release files should include the directory name (i.e., demo/testfile.txt)
NON_CVS_ROOT := # /home/host/myhome/projects/myproj/myproj-1.2
NON_CVS_RELEASE := \

clean_OTHER_TARGETS = 
libs_OTHER_TARGETS = 
libs_g_OTHER_TARGETS = 
apps_g_OTHER_TARGETS = 



##########################################################################
# Section 7 - Include other makefiles
##########################################################################

# Directory and flag configuration file
# User can customize this as necessary
include GNUmakefile.cfg

# Standard CAD makefile - user shouldn't modify this
include $(CADMAKEFILE)

# This code need to be defined after CAD makefile is included in order to override values
# Notice there would still be warnings of "No such file or directory" due to different dependency generation
# in CodeWarrior compiler
ifeq ($(CWPPC),1)
GCC_DEPENDOPT = -gccdep -MD 
CXXFLAGS := -i- $(patsubst -I%,-i %,$(CXXFLAGS))
PPC_DEPEND_DIR = $(OBJ)
-include $(PPC_DEPEND_DIR)/*.d
endif

ifeq ($(CWSC),1)
GCC_DEPENDOPT := 
SC_DEPEND_DIR := $(OBJ)
-include $(SC_DEPEND_DIR)/*.d
endif

#ifeq ($(ARMRVDS),1)
#GCC_DEPENDOPT := --depend_format=unix_escaped --no_depend_system_headers 
#ARM_DEPEND_DIR := $(OBJ)
#-include $(ARM_DEPEND_DIR)/*.d
#endif

##########################################################################
# Section 8 - User-defined targets
##########################################################################

# The user-defined targets which are defined in this section should also
# be declared in section 1 of the makefile above.
#
# In this section, define your target as you would define any makefile
# target. See the GNU Make manual for more details.
#
# This is also the place to *override* standard makefile target rules, if
# necessary. Any makefile rules redefined here will take precedence over
# the versions which appear in the standard CAD makefile. Overriding rules
# is not recommended, but it is sometimes necessary.

#$(BIN)/mytarget: $(OBJ)/myfile.o
#	 ...your definition here...


postcheckout: make_soft_links_to_default_versions

.PHONY: make_soft_links_to_default_versions


crg_version_release_target: apps libs build_64_libs build_PPC_libs
	-echo "FINISH  crg_version_release_target (-: (-: (-: (-: "
#	-bin/crg_version_release $(PROJECT_VER)

build_2953_libs:
ifeq ($(ARCH_SUFFIX),L)
	-mkdir -p objL_2953 libL_2953
	bsub -Ip -R "linux32" $(MAKE) libs \
	EGCS_VERSION=/usr/local/egcs/2.95.3_ws3 \
	OBJ=objL_2953 LIB=libL_2953 \
	DEPEND_DIR=c/_makedependL_2953 \
	cool_LIBDIR=libL_ver cool_OBJDIR=objL_ver \
	ARCH_SUFFIX=L
endif

build_64_libs:
	-mkdir -p $(OBJ_64) $(LIB_64)
	$(MAKE) libs \
	EGCS_VERSION=/pkg/gnu-gcc-/4.1.2/x86_64-linux \
	OBJ=$(OBJ_64) LIB=$(LIB_64) \
	DEPEND_DIR=c/_makedependL_64 \
	ARCH_SUFFIX=L

build_64_libs_g:
	$(MAKE) libs_g \
	EGCS_VERSION=/pkg/gnu-gcc-/4.1.2/x86_64-linux \
	OBJ=$(OBJ_64) LIB=$(LIB_64) \
	DEPEND_DIR=c/_makedependL_64 \
	ARCH_SUFFIX=L

#build_ARM_libs:
#	$(MAKE) libs ARMRVDS=1

build_PPC_libs:
	$(MAKE) CWPPC=1 libPPC32/librandom.a libPPC32/librandom_play.a 

build_SC_libs:
	$(MAKE) libs CWSC=1



build_2953_libs_g_private:
	-mkdir -p objS_2953 libS_2953 
	bsub -Ip -R "solaris" $(MAKE) libs_g \
		EGCS_VERSION=/usr/local/egcs/2.95.3-12_02 \
		OBJ=objS_2953 LIB=libS_2953 \
		DEPEND_DIR=c/_makedependS_2953 \
		cool_LIBDIR=libS_ver cool_OBJDIR=objS_ver \
		ARCH_SUFFIX=S

clean_2953_all:
	-rm -rf objS_2953 libS_2953 objL_2953 libL_2953

clean_sc32_all:
	-rm -rf objSC3850 libSC3850

#clean_arm32_all:
#	-rm -rf objArmA8 libArmA8

clean_ppc32_all:
	-rm -rf objPPC32 libPPC32

clean_depend_dir:
	-rm -rf c/_makedepend* c/*.version.c

clean_64_all:
	-rm -rf $(OBJ_64) $(LIB_64)

clean_all:
	-rm -rf $(OBJ_64) $(LIB_64) $(OBJ) $(LIB) $(BIN)

copy_opt_to_g:
ifeq ($(CWPPC), 1)
	-echo "In copy_opt_to_g for PPC. Nothing to do"
else 
ifeq ($(CWSC), 1)
	-echo "In copy_opt_to_g for SC. Nothing to do"
else
	-cd $(LIB); ln -s librandom.a librandom_g.a          ;  cd ..
	-cd $(LIB); ln -s librandom_play.a librandom_play_g.a;  cd ..
	-cd $(LIB); ln -s liboptimizer.a liboptimizer_g.a;  cd ..
	-echo "In Regular copy_opt_to_g"
endif
endif

copy_g_to_opt:
	-cd $(LIB); ln -s librandom_g.a librandom.a          ;  cd ..
	-cd $(LIB); ln -s librandom_play_g.a librandom_play.a;  cd ..
	-cd $(LIB); ln -s liboptimizer_g.a liboptimizer.a;  cd ..

copy_g_to_opt_apps:
	-cd $(BIN); ln -s CrgCompiler_g     CrgCompiler      ;  cd ..
	-cd $(BIN); ln -s linux2ppc_g       linux2ppc        ;  cd ..
	-cd $(BIN); ln -s print_dump_file_g print_dump_file  ;  cd ..
	-cd $(BIN); ln -s CrgDC_g CrgDC  ;  cd ..

make_soft_links_to_default_versions:
	-ln -s libL_412 libL_411
	-ln -s libL_412 libL_41x
	-ln -s libL_64_412 libL_64_411
	-ln -s libL_64_412 libL_64_41x

# used for printing variables , like print-ALL_BLOCKS
print-%: ; @$(warning $* is $($*)) 
