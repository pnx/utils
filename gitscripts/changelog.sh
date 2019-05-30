#!/bin/sh
# Builds a changelog for changes between last tag and HEAD

if [ -n "${1}" ]; then
	OUTFILE=${1}
else
	OUTFILE=./.changelog
fi

LAST_TAG=$(git log --tags --pretty=format:'%H' -n 1)

if [ -n "${LAST_TAG}" ]; then
	/bin/echo -e "\n\n" 1> ${OUTFILE}
	git shortlog --no-merges ${LAST_TAG}..HEAD 1>> ${OUTFILE}
fi
