/*
    Copyright 2009,2010 Luigi Auriemma

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

    http://www.gnu.org/licenses/gpl-2.0.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MYDOWN_GLOBAL_COOKIE
    #error "you must use -DMYDOWN_GLOBAL_COOKIE"
#endif
#ifndef MYDOWN_SSL
    #error "you must use -DMYDOWN_SSL"
#endif
#include "mydownlib.h"

typedef unsigned char   u8;



#define VER     "0.1.1"
#define QLURL1  "https://secure.quakelive.com/user/login"   // was "http://www."
#define QLURL2  "http://www.quakelive.com/user/load"



u8 *fgetz(u8 *msg);
u8 *show_qldata(u8 *data, int datalen);



int main(int argc, char *argv[]) {
    mydown_options  opt;
    int     len;
    u8      content[1024],
            *buff   = NULL,
            *mail   = NULL,
            *pass   = NULL,
            *xaid;

    fputs("\n"
        "Quakelive xmpp.quakelive.com password retriever "VER"\n"
        "by Luigi Auriemma\n"
        "e-mail: aluigi@autistici.org\n"
        "web:    aluigi.org\n"
        "\n", stdout);

    if(argc < 3) {
        printf("\n"
            "Usage: %s [mail_address] [password]\n"
            "\n", argv[0]);
        //exit(1);
    }

    if(argc >= 2) mail = argv[1];
    if(argc >= 3) pass = argv[2];

    if(!mail) mail = strdup(fgetz("enter the mail address of the account"));
    if(!pass) pass = strdup(fgetz("enter the password of the account"));

    if(!strchr(mail, '@')) {
        printf("\nError: you must insert your account mail address, not the username\n");
        goto quit;
    }

    memset(&opt, 0, sizeof(opt));
    opt.verbose     = 0; //-1;
    opt.filedata    = &buff;
    opt.referer     = "http://www.quakelive.com/";
    opt.more_http   = "Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n"
                      /*"X-Requested-With: XMLHttpRequest\r\n"*/;

    //snprintf(content, sizeof(content), "u=%s&p=%s&r=0", mail, pass);
    snprintf(content, sizeof(content), "submit=&email=%s&pass=%s", mail, pass);
    opt.get         = "POST";
    opt.content     = content;
    printf("- send mail and password to %s\n", QLURL1);
    len = mydown(QLURL1, NULL, &opt);
    if((len < 0) /*|| !buff*/) {
        printf("\nError: something wrong on the quakelive.com webserver\n");
        goto quit;
    }
    if(len > 0) buff[len - 1] = 0;  // don't want to realloc for one byte

    /*
    if(!strstr(buff, "CODE\":0")) {
        if(len < 0) len = 0;
        printf("\n"
            "Error: seems that your account has not been accepted:\n"
            "       %.*s\n", len, buff);
        goto quit;
    }
    */
    free(buff);

    opt.get         = "GET";
    opt.content     = NULL;
    opt.more_http   = "Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n"
                      "X-Requested-With: XMLHttpRequest\r\n";
    printf("- get session informations from %s\n", QLURL2);
    len = mydown(QLURL2, NULL, &opt);
    if((len < 0) || !buff) {
        printf("\nError: something wrong on the quakelive.com webserver\n");
        goto quit;
    }
    if(len > 0) buff[len - 1] = 0;  // don't want to realloc for one byte

    xaid = strstr(buff, "\"XAID\":");
    if(!xaid) {
        printf("\n"
            "Error: no XAID field found, check the reply received from the server\n"
            "\n"
            "%s\n"
            "\n", buff);
    }

    xaid = show_qldata(buff, len);

    /*
    xaid = strchr(xaid, ':') + 1;
    if(xaid[0] == '\"') {
        xaid++;
        l = strchr(xaid, '\"');
    } else {
        l = strchr(xaid, ',');
    }
    if(l) *l = 0;
    */

    printf(
        "- your current xmpp.quakelive.com password (XAID) is\n"
        "\n"
        "  %s\n"
        "\n", xaid);
    free(buff);

quit:
    fgetz("press RETURN to quit");
    return(0);
}



u8 *fgetz(u8 *msg) {
    static u8   buff[1024];
    u8      *p;

    printf("\n- %s:\n  ", msg);
    if(!fgets(buff, sizeof(buff), stdin)) exit(1);  //return(NULL);
    for(p = buff; *p && (*p != '\n') && (*p != '\r'); p++);
    *p = 0;
    return(buff);
}



u8 *show_qldata(u8 *data, int datalen) {   // all the code of this tool is very basic... lame
    int     i,
            t,
            found   = 0;
    u8      *p,
            *l,
            *limit,
            *xaid   = NULL;

    printf("\n");
    limit = data + datalen - 1;
    if(datalen > 0) *limit = 0;  // the last byte is not important for this function, '}'

    p = data;
    while(p < limit) {
        while((*p == '{') || (*p == '}') || (*p == ',')) p++;
        for(i = 0; i < 2; i++) {
            l = p;
            if(*p == '\"') {
                p++;
                l = strchr(p, '"');
                if(l) {
                    *l++ = 0;
                } else {
                    l = p;
                }
            }

            t = 0;
            for(; *l && (l < limit); l++) {
                if((*l == '\"') || (*l == ':') || (*l == ',')) {
                    *l = 0;
                    t++;
                } else {
                    if(t) break;
                }
            }

            if(!i) {    // parameter
                if(!strcmp(p, "INFO")) {    // the rest is not that important
                    p = limit;
                    break;
                }
                if(!strcmp(p, "XAID")) found++;
                printf("  %-20s ", p);
            } else {    // value
                if(found == 1) {
                    xaid = p;
                    found++;
                }
                printf("%s\n", p);
            }

            p = l;
            if(p >= limit) break;
        }
    }
    printf("  ... the rest has been skipped since not useful\n\n");
    return(xaid);
}


