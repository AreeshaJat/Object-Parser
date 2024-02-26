<!doctype html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <title>WebGL Demo</title>
  <link rel="stylesheet" href="./webgl.css" type="text/css">
  <link rel="stylesheet" href="./table.css" type="text/css">
  <script src="https://cdnjs.cloudflare.com/ajax/libs/gl-matrix/2.8.1/gl-matrix-min.js" integrity="sha512-zhHQR0/H5SEBL3Wn6yYSaTTZej12z0hVZKOv3TwCUXT1z5qeqGcXJLLrbERYRScEDDpYIJhPC1fk31gqR783iQ==" crossorigin="anonymous" defer>
  </script>

<style>
    .custom-file-input::-webkit-file-upload-button {
      visibility: hidden;
      width: 1px;
    }

    .custom-file-input::before {
      content: 'Transfer';
      display: inline-block;
      border: 1px solid #999;
      border-radius: 3px;
      padding: 1px 22px;
    }
  </style>

</head>

<body id="body">
  <h2 class="pull-left">3D Object Viewer</h2>


  <?php

  error_reporting(0);

  /* Include config file */
  require_once "config.php";

  echo <<<_END
    <div>
      <form method="post" action="create.php" enctype="multipart/form-data">
        <input type="file" name="uploadfilename2[]" id="uploadfilename2" multiple="multiple">
        <br>
        <input type="file" name="uploadfilename[]" id="uploadfilename" multiple="multiple" class="custom-file-input" onchange="form.submit()">
      </form>
    </div>
    <br>
    _END;
    echo <<<_END
    <div>
      <form action="delete.php">
        <input type="submit" value="Delete" style="width:95px; border: 1px solid #999; border-radius: 3px">
      </form>
    </div>
  _END;
  echo <<<_END
    <div>
      <form action="deleteAll.php">
        <input type="submit" value="Delete Tables" style="width:95px; border: 1px solid #999; border-radius: 3px">
      </form>
    </div>
  _END;
  echo <<<_END
  <div>
      <button onclick="foo()" style="width:95px; border: 1px solid #999; border-radius: 3px" >Exit</button><br>
  </div>
<br>
_END;


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
        if (explode(".", $row['ppm_file'])[0] != explode(".", $row['obj_file'])[0] ) {
          echo "<form method=\"post\"><input type=\"submit\" name=\"action\" value=\"Display\" disabled/>";
          echo "<input type=\"hidden\" name=\"id\" value=" . $row['id'] . "></form>";
        }else {
          echo "<form method=\"post\"><input type=\"submit\" name=\"action\" value=\"Display\"/>";
          echo "<input type=\"hidden\" name=\"id\" value=" . $row['id'] . "></form>";
        }
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

  $object_data = null;
  if ($_POST['action'] && $_POST['id']) {
    if ($_POST['action'] == 'Display') {
      $id = $_POST['id'];
  
      require "config.php";
  
      /* Prepare a select statement */
      $sql = "SELECT * FROM objects WHERE id = " . $id;
      $result = $conn->query($sql);
      
      $ppm = 0;
      $obj = 0;
      if ($result->num_rows > 0) {
          /* output data of each row */
          while ($object = $result->fetch_assoc()) {
          }
  
          $ppm_sql = "SELECT * FROM ppm_files WHERE object_id = " . $id;
          $result = $conn->query($ppm_sql);
          if ($result->num_rows > 0) {
            /* output data of each row */
            $ppm = $result->fetch_assoc();
          }
  
          $obj_sql = "SELECT * FROM obj_files WHERE object_id = " . $id;
          $result = $conn->query($obj_sql);
          if ($result->num_rows > 0) {
            /* output data of each row */
            $obj = $result->fetch_assoc();
          }
  
          /* [width, height, texture, indices, vertices, text_coords, normals, vertex_count]; */
          $object_data = array('width' => $ppm["width"], 'height' => $ppm["height"], 'texture' => $ppm["texture"], 'indices' => $obj["indices"], 'vertices' => $obj["vertices"], 'text_coords' => $obj["text_coords"], 'normals' => $obj["normals"], 'vertex_count' => $obj["vertex_count"]);
  
      } else {
          echo "<br>0 results";
      }
      $conn->close();
    }
  }
  ?>

  <script>
    function foo() {
      const myNode = document.getElementById("body");
      myNode.innerHTML = "EXIT";

    }
  </script>
  <canvas id="glcanvas" width="640" height="480"></canvas>
  <script src="webgl-demo.js" defer></script> 
  <script src="loaddata.js"></script>
  <script>
    var allData = <?php echo json_encode($object_data); ?>;
        if (allData != [] && allData != null) {
          saveAllData(allData);

        }
  </script>


</body>

</html>
