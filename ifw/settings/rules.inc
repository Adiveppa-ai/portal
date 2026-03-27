##################################################################
# $Id: rules.inc,v 1.17 2001/05/16 13:43:44 bt Exp $
#
# generic rules
##################################################################

SUBDIR_DUMMY=${OBJECT_SUBDIR}/${OBJECT_SUBDIR}.DUMMY

${SUBDIR_DUMMY}:
	@if [ -z "${OBJECT_SUBDIR}" ] ; then \
	  ${ECHO} "empty object subdir variable !!!" ; exit 1 ; fi
	@if [ ! -d "${OBJECT_SUBDIR}" ] ; then mkdir ${OBJECT_SUBDIR} ; fi
	@touch ${SUBDIR_DUMMY}

${OBJECT_SUBDIR}/%.dep: %.cpp ${SUBDIR_DUMMY}
	@if [ -z "${OBJECT_SUBDIR}" ] ; then \
	  ${ECHO} "empty object subdir variable !!!" ; exit 1 ; fi
	@if [ ! -d "${OBJECT_SUBDIR}" ] ; then \
	  ${ECHO} "object subdir does not exists !!!" ; exit 1 ; fi
	@if [ -z "${nodep}" ] ; then \
	${ECHO} "GENERATE OBJECT DEPENDENCY FILE $@" ; \
	${CPP} ${CPPDEPOPTS} ${CFLAGS} $< > $@.tmp ; \
	if [ $$? -eq 0 ] ; then \
	  sed 's/\($*\)\.o[ :]*/${dir ${subst /,\/,$@}}\1.o ${subst /,\/,$@} : /g' \
	  $@.tmp > $@ ; rm -f $@.tmp ; [ -s $@ ] || rm -f $@ ; \
	  [ ! -f $*.o ] || rm -f $*.o ; \
	else rm -f $@.tmp ; exit 1 ; fi ; fi

${OBJECT_SUBDIR}/%.dep: %.c ${SUBDIR_DUMMY}
	@if [ -z "${OBJECT_SUBDIR}" ] ; then \
	  ${ECHO} "empty object subdir variable !!!" ; exit 1 ; fi
	@if [ ! -d "${OBJECT_SUBDIR}" ] ; then \
	  ${ECHO} "object subdir does not exists !!!" ; exit 1 ; fi
	@if [ -z "${nodep}" ] ; then \
	${ECHO} "GENERATE OBJECT DEPENDENCY FILE $@" ; \
	${CPP} ${CPPDEPOPTS} ${CFLAGS} $< > $@.tmp ; \
	if [ $$? -eq 0 ] ; then \
	  sed 's/\($*\)\.o[ :]*/${dir ${subst /,\/,$@}}\1.o ${subst /,\/,$@} : /g' \
	  $@.tmp > $@ ; rm -f $@.tmp ; [ -s $@ ] || rm -f $@ ; \
	  [ ! -f $*.o ] || rm -f $*.o ; \
	else rm -f $@.tmp ; exit 1 ; fi ; fi

${OBJECT_SUBDIR}/%.o: %.cpp ${SUBDIR_DUMMY}
	@if [ -z "${OBJECT_SUBDIR}" ] ; then \
	  ${ECHO} "empty object subdir variable !!!" ; exit 1 ; fi
	@if [ ! -d "${OBJECT_SUBDIR}" ] ; then \
	  ${ECHO} "object subdir does not exists !!!" ; exit 1 ; fi
	cd ${OBJECT_SUBDIR} ; ${CC} ${CFLAGS} -c ../$< -o ${notdir $@}

${OBJECT_SUBDIR}/%.o: %.c ${SUBDIR_DUMMY}
	@if [ -z "${OBJECT_SUBDIR}" ] ; then \
	  ${ECHO} "empty object subdir variable !!!" ; exit 1 ; fi
	@if [ ! -d "${OBJECT_SUBDIR}" ] ; then \
	  ${ECHO} "object subdir does not exists !!!" ; exit 1 ; fi
	cd ${OBJECT_SUBDIR} ; ${CC} ${CFLAGS} -c ../$< -o ${notdir $@}

%.Client.cpp: %.idl
	${IDLCOMP} ${IDLFLAGS_CLIENT} $<

%.Server.cpp: %.idl
	${IDLCOMP} ${IDLFLAGS_SERVER} $<

cleanobj:
	@if [ -d "${OBJECT_SUBDIR}" ] ; then \
		${ECHO} "${RM} ${OBJECT_SUBDIR}" ; ${RM} ${OBJECT_SUBDIR} ; fi
	${RM} core *~ *% *.o *.i a.out

cleanall: cleanobj
	@if [ -f "${TARGET_LIB}" ] ; then \
		${ECHO} "${RM} ${TARGET_LIB}" ; ${RM} ${TARGET_LIB} ; fi
	@if [ -f "${TARGET_BIN}" ] ; then \
		${ECHO} "${RM} ${TARGET_BIN}" ; ${RM} ${TARGET_BIN} ; fi
	@if [ ${MAKELEVEL} -ne 0 ] ; then \
		if [ -n "${purify}" ] && [ -d "${PURIFY_CACHE}" ] ; then \
			${ECHO} "${RM} ${PURIFY_CACHE}" ; ${RM} ${PURIFY_CACHE} ; fi ; \
		if [ -n "${quantify}" ] && [ -d "${QUANTIFY_CACHE}" ] ; then \
			${ECHO} "${RM} ${QUANTIFY_CACHE}" ; ${RM} ${QUANTIFY_CACHE} ; fi ; fi

ifdef objclean
  clean: cleanobj cleanlib 
else
  clean: cleanall cleanlib cleanbin
endif

cutcr:
	${D2U} *.hpp *.cpp *.idl *.h *.c

ifeq "$(findstring clean,${MAKECMDGOALS})" ""
  ifeq "$(findstring cutcr,${MAKECMDGOALS})" ""
    ifeq "$(findstring doc++,${MAKECMDGOALS})" ""
      ifdef OBJECTS
        -include ${OBJECTS:.o=.dep}
      endif
    endif
  endif
endif

