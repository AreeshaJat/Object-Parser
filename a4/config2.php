<?php
/* Database credentials. Assuming you are running MySQL server with default setting */
define('DB_SERVER', 'localhost');
define('DB_USERNAME', 'root');
define('DB_PASSWORD', '');
define('DB_NAME', '3D_Objects');

/* Attempt to connect to MySQL database 
 * Create connection 
 */
$conn = new mysqli(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

/* Check connection */
if ($conn->connect_error) {
    die("Database connection failed: " . $conn->connect_error);
  }
?>