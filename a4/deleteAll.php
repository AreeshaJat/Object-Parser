<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
</head>

<body>

    <?php

        require "config.php";

        $sql = "DELETE FROM ppm_files";

        if ($conn->query($sql) === TRUE) {
            echo "<br>PPM records deleted successfully<br>";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }

        $sql = "DELETE FROM obj_files";

        if ($conn->query($sql) === TRUE) {
            echo "<br>OBJ records deleted successfully<br>";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }

        $sql = "DELETE FROM objects";

        if ($conn->query($sql) === TRUE) {
            echo "<br>Object records deleted successfully<br>";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }

        $conn->close();

    ?>
    <br>
    <button onclick="foo()" >Go Home</button><br>

    <script>
    function foo() {
        window.location.replace("index.php");
    }
  </script>

</body>

</html>