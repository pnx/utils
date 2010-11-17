#!/bin/bash
#
# Simple script to be used with cronjob to change location (daily) 
# where quakelive demos should be stored

BASEDIR=~/ql
REPLAYDIR=replays

OLDTARGET=$(/bin/basename `readlink -s "${BASEDIR}/demos"`)
NEWTARGET=$(/bin/date '+%Y-%m-%d')

if [ "${REPLAYDIR}/${OLDTARGET}" != "${REPLAYDIR}/${NEWTARGET}" ]; then

    # create newtarget
    if [ ! -d "${BASEDIR}/${REPLAYDIR}/${NEWTARGET}" ]; then
        /bin/mkdir -p "${BASEDIR}/${REPLAYDIR}/${NEWTARGET}"
    fi
    
    # change the symlink to point to newtarget
    /bin/ln -snf "${REPLAYDIR}/${NEWTARGET}" "${BASEDIR}/demos"
    
    # remove oldtarget if empty
    if [ `/bin/ls "${BASEDIR}/${REPLAYDIR}/${OLDTARGET}/" | /bin/wc -l` -eq 0 ]; then
        /bin/rm -fr "${BASEDIR}/${REPLAYDIR}/${OLDTARGET}/"
    fi
fi
