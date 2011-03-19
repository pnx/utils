#!/bin/bash
#
# Simple script to be used with cronjob to change location (daily) 
# where quakelive demos should be stored

BASEDIR=~/ql
REPLAYDIR=replays

if [ ! -h "${BASEDIR}/demos" ]; then
    
    if [ -d "${BASEDIR}/demos" ] && [`/bin/ls "${BASEDIR}/demos" | /bin/wc -l` -eq 0 ]; then
        /bin/rm -fr "${BASEDIR}/demos" 2> /dev/null
    else 
        # move if not empty or is a file
        /bin/mv "${BASEDIR}/demos" "${BASEDIR}/demos-bkp" 2> /dev/null
        if [ $? -eq 1 ]; then
            /bin/echo "Error: can't backup '${BASEDIR}/demos'; please do it yourself"
            return 1
        fi
    fi
fi

OLDTARGET=$(/bin/basename `readlink -s "${BASEDIR}/demos"`)
NEWTARGET=$(/bin/date '+%Y-%m-%d')

if [ "${REPLAYDIR}/${OLDTARGET}" != "${REPLAYDIR}/${NEWTARGET}" ]; then

    # create newtarget
    if [ ! -d "${BASEDIR}/${REPLAYDIR}/${NEWTARGET}" ]; then
        /bin/mkdir -p "${BASEDIR}/${REPLAYDIR}/${NEWTARGET}" 2> /dev/null
    fi
    
    # change the symlink to point to newtarget
    /bin/ln -snf "${REPLAYDIR}/${NEWTARGET}" "${BASEDIR}/demos"
    
    # remove oldtarget if empty
    if [ `/bin/ls "${BASEDIR}/${REPLAYDIR}/${OLDTARGET}/" | /bin/wc -l` -eq 0 ]; then
        /bin/rm -fr "${BASEDIR}/${REPLAYDIR}/${OLDTARGET}/" 2> /dev/null
    fi
fi
