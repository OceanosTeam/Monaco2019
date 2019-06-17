configure() {
echo "#############################################"
echo "# You entered script configuration area     #"
echo "# No change will be performed in your DB    #"
echo "# I will just ask you some questions about  #"
echo "# your hosts and DB.                        #"
echo "#############################################"
MYSQLDUMPPATH=`which mysqldump 2>/dev/null`
MYSQLPATH=`which mysql 2>/dev/null`
if [ $? -ne 0 ]; then
echo "We were unable to find MySQL binaries on your path"
while :
 do
  echo -ne "\nPlease enter MySQL binaries directory (no trailing slash): "
  read MYSQLBINPATH
    if [ -e "$MYSQLBINPATH" ] && [ -d "$MYSQLBINPATH" ] && [ -e "$MYSQLBINPATH/mysqldump" ] && [ -e "$MYSQLBINPATH/mysql" ]; then
       MYSQLDUMPPATH="$MYSQLBINPATH/mysqldump"
       MYSQLPATH="$MYSQLBINPATH/mysql"
       break
    else
       echo "The data you entered is invalid. Please verify and try again."
       exit 1
    fi
 done
fi
#DB
echo -ne "\nPlease enter Oceanos MySQL Dashboard Server hostname (default localhost): "
read OCDBHOST
if [ -z "$OCDBHOST" ]; then
  OCDBHOST="localhost"
fi
echo -ne "\nPlease enter Oceanos MySQL Dashboard Server database name (default ocdb): "
read OCDB
if [ -z "$OCDB" ]; then
  OCDB="ocdb"
fi
echo -ne "\nPlease enter Oceanos MySQL Dashboard Server user (default root): "
read OCUSER
if [ -z "$OCUSER" ]; then
  OCUSER="root"
fi
echo -ne "\nPlease enter Oceanos MySQL Dashboard Server $OCUSER's password (won't be displayed) :"
stty -echo
read OCPASS
stty echo
echo ""
if [ -z "$OCPASS" ]; then
  echo "Hum.. I'll let it be but don't be stupid and avoid empty passwords"
elif [ "$OCUSER" == "$OCPASS" ]; then
  echo "Your password is the same as your user, consider changing that."
fi
save_config $1
}

save_config() {
if [ -n "$1" ]; then
CONF="$1"
else 
CONF="database_installer.rc"
fi
echo ""
echo "With these data I can generate a configuration file which can be read"
echo "on future updates. WARNING: this file will contain clear text passwords!"
echo -ne "Shall I generate config file $CONF? (Y/n):"
read SAVE
if [ "$SAVE" == "y" -o "$SAVE" == "Y" -o "$SAVE" == "" ]; then
cat <<EOF>$CONF
#Configuration settings for Oceanos-Dashboard database installer script
MYSQLDUMPPATH=$MYSQLDUMPPATH
MYSQLPATH=$MYSQLPATH
OCDBHOST=$OCDBHOST
OCDB=$OCDB
OCUSER=$OCUSER
OCPASS=$OCPASS
EOF
chmod 600 $CONF
echo "Configuration saved as $CONF"
echo "Permissions changed to 600 (rw- --- ---)"
elif [ "$SAVE" != "n" -a "$SAVE" != "N" ]; then
  save_config
fi
}

load_config() {
if [ -n "$1" ]; then
CONF="$1"
else 
CONF="database_installer.rc"
fi
if [ -e "$CONF" ] && [ -f "$CONF" ]; then
. $CONF
else
echo "Settings file not found: $CONF"
echo "You can specify an alternate settings filename:"
echo $0 config_filename
echo ""
echo "If file doesn't exist it can be created"
echo "If nothing is specified script will try to work with ./database_installer.rc"
echo ""
configure $CONF
fi
}

askdatabase(){
echo "#############################################"
echo "# WARNING: This section of the script CAN   #"
echo "# destroy your whole database informatio    #"
echo "# Read questions carefully before you reply #"
echo "#############################################"
echo ""
echo "Choose full (f) if you don't have any table or would"
echo "prefer to erase the existing tables information."
echo "Choose skip (s) to skip Oceanos DB installation and go to"
echo -ne "Oceanos DB install type: (f) full, (q) quit? "
read OCDBPROMPT
case "$OCDBPROMPT" in
	"f"|"F") dbinstall; dbupgrade;;
	"q"|"Q") finish;;
	*) askdatabase;;
esac
}

dbinstall(){
echo "Deleting database tables for new content."
#$MYDB < login_install.sql &> /dev/null
sudo $MYSQLDUMPPATH --add-drop-table -h $OCDBHOST -u $OCUSER --password=$OCPASS $OCDB --no-data | grep ^DROP | $MYDB
}

dbupgrade(){
echo "Installling new Oceanod Database content."
$MYDB < ../sql/gps.sql &> /dev/null
$MYDB < ../sql/motor.sql &> /dev/null
}

ocdbackup(){
while :
  do
   echo ""
   echo -ne "Do you want to make a backup copy of your OCDB? (Y/n): "
   read BKUP
   if [ "$BKUP" == "Y" -o "$BKUP" == "y" -o "$BKUP" == "" ]; then
     echo "Making a backup of the original Oceanos Dashboard database."
     echo ""
     sudo $MYSQLDUMPPATH --add-drop-table -h $OCDBHOST -u $OCUSER --password=$OCPASS $OCDB > oceanosdb_backup.sql
     if [ $? -ne 0 ];then
        echo ""
        echo "There was a problem accesing your Oceanos database, either it wasnt created or authentication data is incorrect."
        exit 1
     fi
     break
   elif [ "$BKUP" == "n" -o "$BKUP" == "N" ]; then
     break
   fi
  done 
}

createdatabase(){
echo "Creating Database if it doesn't exist"
mysql --user=$OCUSER --password=$OCPASS -e "CREATE DATABASE IF NOT EXISTS $OCDB;"
}

finish(){
echo ""
echo "Script execution finished."
exit 0
}

clear

load_config $1
createdatabase
MYDB="$MYSQLPATH -h $OCDBHOST -u $OCUSER --password=$OCPASS -D $OCDB"
ocdbackup
askdatabase
