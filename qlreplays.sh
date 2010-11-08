#!/bin/bash
#
# Simple script to be used with cronjob to change location (daily) 
# where quakelive demos should be stored

BASEDIR=~/.quakelive/quakelive/home/baseq3
REPLAYDIR=replays/`/bin/date '+%Y-%m-%d'`

if [ "`readlink "${BASEDIR}/demos"`" != "${REPLAYDIR}" ]; then

    if [ ! -d "${BASEDIR}/${REPLAYDIR}" ]; then
        /bin/mkdir -p "${BASEDIR}/${REPLAYDIR}"
    fi
    
    /bin/ln -snf "${REPLAYDIR}" "${BASEDIR}/demos"
fi
