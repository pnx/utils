#!/bin/sh

OUTPUT_PATH=exported

mkdir -p ${OUTPUT_PATH}

echo "Start packing to directory '${OUTPUT_PATH}'"

for dir in $(git ls-tree -d --name-only HEAD .); do

    ARCH_FILE="${OUTPUT_PATH}/${dir}.tar.gz"

    if [ -e "${ARCH_FILE}" ]; then
        echo "archive ${dir} (${ARCH_FILE}) exists already, skipping."
    else
        echo "Creating archive for ${dir}"
        git archive --format=tar HEAD "${dir}" | gzip > "${ARCH_FILE}"
    fi
done
