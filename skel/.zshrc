# /etc/skel/.zshrc
# default Zshell config

case ${TERM} in
    xterm*)
        chpwd() {print -Pn "\e]0;%n/%m:%~\a"}
        ;;
esac

# setup the user's enviorment
if [ -e "${HOME}/.envrc" ]; then
    source ${HOME}/.envrc
fi

# the promts
PROMPT=$'%n/%{\e[01;34m%}%M%{\e[0m%} %~ %# '
RPROMPT=''
