#!/usr/bin/bash



ssh -p 65002 u322154547@153.92.6.43 'cd ./Monaco2019; git pull origin master; cd ./database/tools; ./db_installer.sh'
