#!/bin/sh
#
# simple portage update script

PORTAGE=$(which emerge)
ARGS='-NDu world'

LOGFILE=/root/log/sysupdate.log

if [ "$1" == "--help" ] || [ "$1" == "-h" ]; then
    /bin/echo "usage: ${0} [--help|-h|-l]"
    /bin/echo "  -h --help   : show this help"
    /bin/echo "  -l          : list the packages that whould be updated (dry run)"
    exit 0
fi

if [ "$1" == "-l" ]; then
    echo -e " \033[33m>>\033[0m List packages to be updated"
    ${PORTAGE} -pv ${ARGS}
    exit 0
fi

${PORTAGE} ${ARGS}

test $? -eq 0 && echo "sysupdate run: `date`" >> ${LOGFILE}
