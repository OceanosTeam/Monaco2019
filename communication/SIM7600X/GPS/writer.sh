load_file () {
. $1
}
$ONHOST="sql126.main-host.eu"
$ONUSER="u322154547_root"
$ONDB="test"
$ONPASS="oceanos_2019"
CONF="./database_installer.rc"
load_file $CONF
MYDB="$MYSQLPATH -h $OCDBHOST -u $OCUSER -D $OCDB --password=$OCPASS"
ONLINEDB="$MYSQLPATH -h $ONBHOST -u $ONUSER -D $ONDB --password=$ONPASS"

if [ $1 -eq 1 ]; then
	$MYDB < reset_gps.sql &> /dev/null
fi
mysql --user=$OCUSER --database=$OCDB --password=$OCPASS -e "INSERT INTO gps (Latitude, Longitude, Speed) VALUES ('$2', '$3', '$4');"
mysql --user=$ONUSER --database=$ONDB --password=$ONPASS -e "INSERT INTO gps (Latitude, Longitude, Speed) VALUES ('$2', '$3', '$4');"
