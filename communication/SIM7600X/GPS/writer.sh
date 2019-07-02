load_file () {
. $1
}

CONF="./database_installer.rc"
load_file $CONF
MYDB="$MYSQLPATH -h $OCDBHOST -u $OCUSER -D $OCDB --password=$OCPASS"

if [ $1 -eq 1 ]; then
	$MYDB < reset_gps.sql &> /dev/null
fi
mysql --user=$OCUSER --database=$OCDB --password=$OCPASS -e "INSERT INTO gps (Latitude, Longitude, Speed) VALUES ('$2', '$3', '$4');"
