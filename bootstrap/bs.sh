#!/bin/sh

YEAR=2016
COOKIE=`cat bootstrap/cookie`

if [ "$#" -ne 1 ]; then
  echo "invalid arguments"
  exit
fi
  

mkdir $YEAR/$1
cp -n bootstrap/p1.c $YEAR/$1


curl 'http://adventofcode.com/2017/day/$1/input' -H 'Accept-Encoding: gzip, deflate, sdch' -H 'Accept-Language: pt-PT,pt;q=0.8,en-US;q=0.6,en;q=0.4' -H 'Upgrade-Insecure-Requests: 1' -H 'User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.95 Safari/537.36' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8' -H 'Cache-Control: max-age=0' -H "Cookie: session=$COOKIE; _gat=1; _ga=GA1.2.971055603.1480598422" -H 'Connection: keep-alive' -s --compressed > $YEAR/$1/in
