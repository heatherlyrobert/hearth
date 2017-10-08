#================================[[ beg-code ]]================================#



#===(manditory)============================================#
# basename of executable, header, and all code files
NAME_BASE  = hearth
# additional standard and outside libraries
LIB_STD    = -lncurses -lcrypt -lm
# all heatherly libraries used, debug versions whenever available
LIB_MINE   = -lyEXEC -lySEC -lySTR_debug
# directory for production code, no trailing slash
INST_DIR   = /sbin



#===(optional)=============================================#
# extra include directories required
INC_MINE   = 
# utilities generated, separate from main program
NAME_UTIL  = 
# libraries only for the utilities
LIB_UTIL   = 



#===(post-processing)======================================#
# create a rule for...
#install_prep       :
#remove_prep        :



#===(master template)======================================#
include /usr/local/sbin/make_program



#===(post-processing)======================================#
# create a rule for...
#install_post       :
#remove_post        :



#================================[[ end-code ]]================================#

##*============================---(source-start)---============================*#
#
##*---(current variables)--------------*#
#HESTIA  = hestia
#AUDIT   = hestia_audit
#HEARTH  = hearth
##UNIT    = hestias_unit
#
##*---(standard variables)-------------*#
#COMP    = gcc -c -g -Wall
#INC     = 
#LINK    = gcc
#LIBS    = -L/usr/local/lib   -Wl,-Bstatic   -lyLOG -lyEXEC -lySEC   -Wl,-Bdynamic  -lncurses -lcrypt -lm
#COPY    = cp -f
#CLEAN   = rm -f
#PRINT   = @printf
#
#
#all                : ${HESTIA} ${HEARTH}
#
#
#
##*---(hestia)--------------------------#
#${HESTIA}          : ${HESTIA}.o
#	${LINK}  -o ${HESTIA}   ${HESTIA}.o ${LIBS}
#
#${HESTIA}.o        : ${HESTIA}.h ${HESTIA}.c
#	${COMP}  ${INCS} ${HESTIA}.c
#
#
##*---(hearth)--------------------------#
#${HEARTH}          : ${HEARTH}.o ${HEARTH}_main.o ${AUDIT}.o
#	${LINK}  -o ${HEARTH}   ${HEARTH}.o ${HEARTH}_main.o ${AUDIT}.o   ${LIBS}
#
#${HEARTH}.o        : ${HESTIA}.h ${HEARTH}.h ${HEARTH}.c
#	${COMP}  ${INCS} ${HEARTH}.c
#
#${HEARTH}_main.o   : ${HESTIA}.h ${HEARTH}_main.c
#	${COMP}  ${INCS} ${HEARTH}_main.c
#
#
##*---(support)-------------------------#
#${AUDIT}             : ${HESTIA}.h ${AUDIT}.c
#	${COMP}  ${INCS} ${AUDIT}.c
#
##${HESTIA}s_unit      : ${HEARTH}.o ${HESTIA}s_unit.o ${AUDIT}.o 
##	${LINK}  -o ${HESTIA}s_unit   ${HEARTH}.o ${HESTIA}s_unit.o ${HESTIA}_audit.o   ${LIBS} -lyUNIT -lyVAR 
#
## ${HESTIA}s_unit.o    : ${HESTIA}s.unit
##	uUNIT    ${HESTIA}s
##	${COMP}  -x c ${HESTIA}s_unit.code
##	mv ${HESTIA}s_unit.code ${HESTIA}s_unit.c
##	${COMP}  ${HESTIA}s_unit.c
#
#
##*---(housecleaning)------------------*#
#clean              :
#	${PRINT}  "\n--------------------------------------\n"
#	${PRINT}  "cleaning out local object, backup, and temp files\n"
#	${CLEAN}  *.o
#	${CLEAN}  *~
#	${CLEAN}  temp*
#	${CLEAN}  ${HESTIA}
#	${CLEAN}  ${HEARTH}
#
#bigclean           :
#	${PRINT}  "\n--------------------------------------\n"
#	${PRINT}  "clean out local swap files\n"
#	${CLEAN}  .*.swp
#
#install            : ${BASE}
#	${PRINT}  "\n--------------------------------------\n"
#	#---(hestia)------------------------#
#	${PRINT}  "install ${HESTIA} into production\n"
#	cp -f     ${HESTIA}      /sbin/
#	chown     root:root      /sbin/${HESTIA}
#	chmod     0711           /sbin/${HESTIA}
#	@sha1sum  ${HESTIA}
#	rm -f       /usr/share/man/man8/${HESTIA}.8.bz2
#	cp -f       ${HESTIA}.8  /usr/share/man/man8/
#	bzip2       /usr/share/man/man8/${HESTIA}.8
#	chmod 0644  /usr/share/man/man8/${HESTIA}.8.bz2
#	#---(hearth)------------------------#
#	${PRINT}  "install ${HEARTH} into production\n"
#	cp -f     ${HEARTH}      /sbin/
#	chown     root:root      /sbin/${HEARTH}
#	chmod     0711           /sbin/${HEARTH}
#	@sha1sum  ${HEARTH}
#	rm -f       /usr/share/man/man8/${HEARTH}.8.bz2
#	cp -f       ${HEARTH}.8  /usr/share/man/man8/
#	bzip2       /usr/share/man/man8/${HEARTH}.8
#	chmod 0644  /usr/share/man/man8/${HEARTH}.8.bz2
#
#remove             :
#	${PRINT}  "\n--------------------------------------\n"
#	${PRINT}  "remove ${HESTIA} from production\n"
#	${CLEAN}  /sbin/${HESTIA}
#	rm -f     /usr/share/man/man8/${HESTIA}.8.bz2
#	${PRINT}  "remove ${HEARTH} from production\n"
#	${CLEAN}  /sbin/${HEARTH}
#	rm -f     /usr/share/man/man8/${HEARTH}.8.bz2
#	${PRINT}  "remove hestias_veil from production\n"
#	${CLEAN}  /sbin/hestias_veil
#	rm -f     /usr/share/man/man8/hestias_veil.8.bz2
#
#
##*============================----(source-end)----============================*#
