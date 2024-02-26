<?php
/* Database credentials. Assuming you are running MySQL server with default setting */
define('DB_SERVER', 'dursley.socs.uoguelph.ca');
define('DB_USERNAME', 'ajat');
define('DB_PASSWORD', '1078815');
define('DB_NAME', 'ajat');
 
/* Attempt to connect to MySQL database 
 * Create connection 
 */
$conn = new mysqli(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

/* Check connection */
if ($conn->connect_error) {
    die("Database connection failed: " . $conn->connect_error);
}

$conn->autocommit(FALSE);
try {
  $conn->query("CREATE TABLE IF NOT EXISTS objects(
                id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
                name CHAR(50),
                ppm_file CHAR(50),
                obj_file CHAR(50),
                UNIQUE(name))");
  $conn->query("CREATE TABLE IF NOT EXISTS ppm_files(
                object_id INT NOT NULL,
                width INT,
                height INT,
                texture LONGTEXT)");
  $conn->query("CREATE TABLE IF NOT EXISTS obj_files(
                object_id INT NOT NULL,
                obj_file_size INT,
                vertices LONGTEXT,
                text_coords LONGTEXT,
                normals LONGTEXT,
                indices LONGTEXT,
                vertex_count INT)");
} catch (Exception $e) {
  $conn->rollback();
  die("Database error: " . $conn->error);
}
$conn->commit();
$conn->autocommit(TRUE);
?>
