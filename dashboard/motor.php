<?php
/*
	Copyright (C) 2019  Oceanos NTUA Team

	This program is free software: you can redistribute 
	it and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation, either version 3 of the 
	License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	You can contact Técnico Solar Boat by email at: tecnico.solarboat@gmail.com
    or via our facebook page at https://fb.com/tecnico.solarboat 
*/

$DB_HOST = 'localhost';
$DB_NAME = 'ocdb';
$DB_USER = 'root';
$DB_PASS = 'YOUR PASSWORD';
$mysqli = new mysqli($DB_HOST, $DB_USER, $DB_PASS, $DB_NAME);

if (mysqli_connect_errno()) {
	printf("Connect failed: %s\n", mysqli_connect_error());
	exit();
}


$result = $mysqli->query('SELECT * FROM motor ORDER By id DESC LIMIT 1;');
$lol = (string) rand(-10,10);
if ($result->num_rows > 0) {
 	$row = $result->fetch_assoc();
    $table = [
			'VoltageIn' => $row['VoltageIn'],
			'RPM'=> $row['RPM']+$lol,
			'PowerIn' => $row['PowerIn'],
			'Temperature' => $row['Temperature'],

			'CurrentIn' => $row['CurrentInput'],
 			/*'Heartbeat' => $row['Heartbeat'],*/

			'time'=> $row['time'],
			'id'=> $row['id']];
}
else {
	$table = null;
}
echo json_encode($table);
?>
