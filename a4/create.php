<!DOCTYPE html>
<html>

<head>
    <script src="loaddata.js"></script>
</head>
<body>
    <?php

    function insertIntoObjectsTable($name, $ppm_file, $obj_file)
    {
        require_once "config.php";

        /* Prepare an insert statement */
        $sql = "INSERT INTO objects (name, ppm_file, obj_file) VALUES (?, ?, ?)";
        $stmt = $conn->prepare($sql);

        $stmt->bind_param("sss", $name, $ppm_file, $obj_file);
        $stmt->execute();

        $stmt->close();
        $conn->close();

    }

    /* Count the number of uploaded files in array */
    if ($_FILES["uploadfilename"]["error"][0] > 0) {
        echo "ERROR CODE : " . $_FILES["uploadfilename"]["error"][0];
    } else {

        if (count($_FILES['uploadfilename']['name']) > 2) {
            echo "ERROR : It can not be more than 2 files.<br>";
            return;
        }

        $objCheck = false;
        $obj_name = null;
        $ppmCheck = false;
        $ppm_name = null;

        $total = count($_FILES['uploadfilename']['name']);
        echo "total : " . $total . "<br>";

        /* looping through each file */
        for ($i = 0; $i < $total; $i++) {

            $name = $_FILES['uploadfilename']['name'][$i];
            $size = $_FILES['uploadfilename']['size'][$i];
            $tmp_name = $_FILES['uploadfilename']['tmp_name'][$i];

            echo "File informations : <br>";
            echo "Name : " . $name . "<br>";
            echo "Size : " . $size . "<br>";
            echo "tmp_name : " . $tmp_name . "<br>";

            move_uploaded_file($tmp_name, $name);

            $name = explode(".", $name);

            if ($name[1] == "obj") {
                $objCheck = true;
                $obj_name = $name[0];
            } elseif ($name[1] == "ppm") {
                $ppmCheck = true;
                $ppm_name = $name[0];
            }
        }

        if (($obj_name == $ppm_name) && ($objCheck && $ppmCheck)) {
            $command = "./a1 readppm readppm " . $obj_name;

            echo $command . "<br>";
            exec($command, $output, $retval);

            if (file_exists($obj_name . ".obj"))
              unlink($obj_name . ".obj");
            if (file_exists($obj_name . ".ppm"))
              unlink($obj_name . ".ppm");

            if ($retval) {
                echo "exec faild. <br>";
                return;
            } else {
                $idx = array_search("OBJ", $output);
                $output = array_slice($output, $idx);
                echo $obj_name . " file was read.<br>";

                insertIntoObjectsTable($obj_name, $ppm_name . ".ppm", $obj_name . ".obj");
            }
        }else {
            insertIntoObjectsTable($obj_name, $ppm_name . ".ppm", $obj_name . ".obj");
        }
    }
    ?>

    <script>
        var data = <?php echo json_encode($output); ?>;
        if (data != [] && data != null) {
            var ppm_start_index = data.indexOf("PPM");
            var obj_data = data.slice(0, ppm_start_index);
            var ppm_data = data.slice(ppm_start_index);

            save_ppm_data(ppm_data);
            save_obj_data(obj_data);

            /* [width, height, texture, indices, vertices, text_coords, normals, vertex_count] */
            var json_all_data = loadAllData();
            json_all_data = JSON.stringify(json_all_data);

            console.log(json_all_data);

            xmlhttp = new XMLHttpRequest();
            xmlhttp.onload = function() {
            document.getElementById("demo").innerHTML = this.responseText;
            }
            xmlhttp.open("POST", "create2.php", false);
            xmlhttp.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
            xmlhttp.send(json_all_data);
            

            window.location.replace("index.php");

        } else {
            console.log("file was not read");
            window.location.replace("index.php");
        }
    </script>

</body>

</html>
