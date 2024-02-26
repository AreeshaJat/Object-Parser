<!doctype html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="./table.css" type="text/css">
</head>

<body id="body">

    <h2 class="pull-left">DELETE OBJECT</h2>
    <?php

    /* including config file */
    require "config.php";

    echo <<<_END
    <div>
        <form method="post">  
            Enter the object id that you want to delete:<br>
            <input type="number" name="number1" /><br><br>  
            <input  type="submit" name="submit" value="Delete"><br><br>
        </form>  
    </div>
    _END;

    echo <<<_END
    <div>
        <button onclick="foo()" >Go Home</button><br>
    </div>
    <br>
    _END;

    if (isset($_POST['submit'])) {
        $id = $_POST['number1'];

        deleteRecord($id);
        echo $id . "nd record was deleted.<br>";
    }

    /* Attempt select query execution */
    $sql = "SELECT * FROM objects";
    if ($result = $conn->query($sql)) {
        if ($result->num_rows > 0) {
            echo <<< _END
      <table class="darkTable id="darkTable">
      <thead>
      <tr>
      <th>ID</th>
      <th>Name</th>
      <th>PPM File</th>
      <th>OBJ File</th>
      </tr>
      </thead>
      <tbody>
      _END;
            while ($row = $result->fetch_assoc()) {
                echo "<tr>";
                echo "<td>" . $row['id'] . "</td>";
                echo "<td>" . $row['name'] . "</td>";
                echo "<td>" . $row['ppm_file'] . "</td>";
                echo "<td>" . $row['obj_file'] . "</td>";
                echo "</tr>";
            }
            echo "</tbody>";
            echo "</table>";
            echo "<br>";
        } else {
            echo '<div class="alert alert-danger"><em>No records were found.</em></div>';
        }
    } else {
        echo "Oops! Something went wrong. Please try again later.";
    }

    /* Close connection */
    $conn->close();

    function deleteRecord($id)
    {
        require "config.php";

        $sql = "DELETE FROM `ppm_files` WHERE object_id =" .$id;

        if ($conn->query($sql) === TRUE) {
            echo "<br>Record deleted successfully<br>";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }

        $sql = "DELETE FROM `obj_files` WHERE object_id =" .$id;

        if ($conn->query($sql) === TRUE) {
            echo "<br>Record deleted successfully<br>";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }

        $sql = "DELETE FROM `objects` WHERE id =" .$id;

        if ($conn->query($sql) === TRUE) {
            echo "<br>Record deleted successfully<br>";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }

        $conn->close();

        header("Refresh:0");

        return;
    }
    ?>

<script>
    function foo() {
        window.location.replace("index.php");
    }
  </script>

</body>

</html>