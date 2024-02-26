<?php
/* Check existence of id parameter before processing further */
if (isset($_GET["id"]) && !empty(trim($_GET["id"]))) {
    /* Include config file */
    require_once "config.php";

    /* Prepare a select statement */
    $sql = "SELECT * FROM employees WHERE id = ?";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        /* output data of each row */
        while ($row = $result->fetch_assoc()) {
            echo "id: " . $row["id"] . " - Name: " . $row["name"] . " - ppm_file: " . $row["ppm_file"] . " - obj_file: " . $row["obj_file"] ."<br>";
        }
    } else {
        echo "0 results";
    }
    $conn->close();
} else {
    /* URL doesn't contain id parameter. Redirect to error page */
    header("location: error.php");
    exit();
}
?>

<!doctype html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <title>WebGL Demo</title>
  <link rel="stylesheet" href="./webgl.css" type="text/css">
  <link rel="stylesheet" href="./table.css" type="text/css">
  <script src="https://cdnjs.cloudflare.com/ajax/libs/gl-matrix/2.8.1/gl-matrix-min.js" integrity="sha512-zhHQR0/H5SEBL3Wn6yYSaTTZej12z0hVZKOv3TwCUXT1z5qeqGcXJLLrbERYRScEDDpYIJhPC1fk31gqR783iQ==" crossorigin="anonymous" defer>
  </script>


</head>

<body id="body">
  <h2 class="pull-left">3D Object Viewer</h2>
  <?php

  /* Include config file */
  require_once "config.php";

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
      <th>Action</th>
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
        echo "<td>";
        echo "<div class=\"left;\">";
        echo "<form method=\"post\"><input type=\"submit\" name=\"action\" value=\"Display\"/>";
        echo "<input type=\"hidden\" name=\"id\" value=\"<?php echo" . $row['id'] . "; ?>\"/></form>";
        echo "</div>";
        echo "</td>";
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
  ?>

  <script>
    function foo() {
      const myNode = document.getElementById("body");
      myNode.innerHTML = 'EXIT';
    }
  </script>
  <canvas id="glcanvas" width="640" height="480"></canvas>
  <script src="webgl-demo.js" defer></script>
  <script src="loaddata.js"></script>
  <script>
    var tempData = localStorage.getItem("data");
    if (tempData) {
      var data = JSON.parse(tempData);
      var ppm_start_index = data.indexOf("PPM");
      var obj_data = data.slice(0, ppm_start_index);
      var ppm_data = data.slice(ppm_start_index);

      save_ppm_data(ppm_data);
      save_obj_data(obj_data);
    }
  </script>

</body>

</html>