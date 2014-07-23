#!/bin/sh
#
# Deployment hook. should be run as an "post-update" hook.
#
# Author: Henrik Hautakoski

#
# update <deploydir> <remotename> <remotebranch> <localbranch>
#
function update {

	DEPLOY=$1
	REMOTENAME=$2
	REMOTEBRANCH=$3
	LOCALBRANCH=$4

	echo "> Deploy changes to: ${DEPLOY}"

	cd "${DEPLOY}"

	unset GIT_DIR
	git reset --hard HEAD && \
		git fetch -f ${REMOTENAME} +${LOCALBRANCH}:refs/remotes/${REMOTENAME}/${REMOTEBRANCH} && \
		git checkout -f ${LOCALBRANCH} && git reset --hard ${REMOTENAME}/${REMOTEBRANCH}

	echo "--- Deployment done ---"
}

DEPLOY_TEST_PATH="<some/path>"

# Update test deploy path if test branch changes.
if [ "$1" == "refs/heads/test" ]; then

	update ${DEPLOY_TEST_PATH} origin test test
fi
