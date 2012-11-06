#/bin/sh

CURL=/usr/bin/curl

# interface
function ifconfig_inet4_addr {

	/sbin/ifconfig "${1}" | grep 'inet addr' | \
		awk '{print $2}' | sed 's/addr://' 2> /dev/null
}

# user
# password
# domain/s (separated by comma)
# interface
function loopia_update {

	IP=$(ifconfig_inet4_addr ${4})

	for i in $(echo ${3} | tr ',' '\n'); do

		echo "Updating ${IP} -> ${i}"
	
		$CURL -v --user \'${1}:${2}\' \
			"http://dns.loopia.se/XDynDNSServer/XDynDNS.php?hostname=${i}\&myip=${IP}"
	done
}

# loopia_update <user> <pass> <domain1>,<domain2> <interface>
