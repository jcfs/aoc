sed -r 's/[^[:digit:]-]/\ /g;s/[\ ]+/\+/g;s/^\+//;s/\+$//' in | bc
