#/bin/sh

CURL=/usr/bin/curl
IFCONFIG=/sbin/ifconfig
IP_CMD=/bin/ip

function ifconfig_inet4_addr {

	if [ -x "${IFCONFIG}" ]; then
		${IFCONFIG} "${1}" | grep -e 'inet\ \(addr\)\?' | \
				awk '{print $2}' | sed 's/addr://' 2> /dev/null
	fi
}

function ip_inet4_addr {

	if [ ! -x "${IP_CMD}" ]; then
		return
	fi

	PATTERN='[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}'

	${IP_CMD} -o -f inet addr show | grep "${1}" | \
		awk '{print $4}' | grep -Eo ${PATTERN} 2> /dev/null
}

function lookup_public_addr {

	${CURL} -s dns.loopia.se/checkip/checkip.php | sed 's/^.*: \([^<]*\).*$/\1/'; echo
}

# interface
function inet4_addr {

	if [ "lookup" = "${1}" ]; then
		echo $(lookup_public_addr)
		return
	fi

	IP=$(ip_inet4_addr "${1}")

	# fallback on ifconfig
	if [ "x" == "x${IP}" ]; then
		IP=$(ifconfig_inet4_addr "${1}")
	fi

	echo $IP
}

# user
# password
# domain/s (separated by comma)
# interface
function loopia_update {

	IP=$(inet4_addr ${4})

	if [ "x" == "x${IP}" ]; then
		echo "Can't find IP for inteface '${4}'"
		return
	fi

	for i in $(echo ${3} | tr ',' '\n'); do

		echo "Updating ${IP} -> ${i}"

		$CURL -v --user "${1}:${2}" \
			"http://dns.loopia.se/XDynDNSServer/XDynDNS.php?hostname=${i}&myip=${IP}"
	done
}

# loopia_update <user> <pass> <domain1>,<domain2> <interface>
