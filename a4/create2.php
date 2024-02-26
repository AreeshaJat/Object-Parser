<?php

     function insertIntoPPM_filesTable($object_id, $width, $height, $texture)
    {
        require "config.php";

        $sql = "INSERT INTO ppm_files(object_id, width, height, texture) VALUES (" . $object_id . "," . $width . ", ".$height .", '[" . implode(', ',array_values($texture)) . "]' )";
    
        if ($conn->query($sql) === TRUE) {
            echo "<br>New PPM record created successfully<br>";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }

    function insertIntoOBJ_filesTable($object_id, $obj_file_size, $vertices, $text_coords, $normals, $indices, $vertex_count)
    {
        require "config.php"; 
        
        $vertices = "'[". implode(', ',array_values($vertices)) . "]'";
        $text_coords = "'[". implode(', ',array_values($text_coords)) . "]'";
        $normals = "'[". implode(', ',array_values($normals)) . "]'";
        $indices = "'[". implode(', ',array_values($indices)) . "]'";
        
        $sql = "INSERT INTO obj_files(object_id, obj_file_size, vertices, text_coords, normals, indices, vertex_count) VALUES (" . $object_id . "," . $obj_file_size . "," . $vertices . "," . $text_coords . "," . $normals . "," . $indices . "," . $vertex_count . ")";

        if ($conn->query($sql) === TRUE) {
            echo "<br>New OBJ record created successfully<br>";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }

        $conn->close();
    }

    function getLastRecordId()
    {
        require_once "config.php";

        $sql = "SELECT MAX(id) FROM objects;";
        $stmt = $conn->prepare($sql);
        $stmt->execute();
    
        /* bind result variables */
        $stmt->bind_result($maxID);
    
        /* fetch values */
        $stmt->fetch();
        
        $stmt->close();
        $conn->close();

        return $maxID;
    }

    $json = file_get_contents("php://input");
    $data = json_decode($json, true);

    echo "data<br>";
    echo "<br>content : " . $data;
    echo "<br>gettype : " . gettype($data);

    foreach($data as $key => $value)
    {
        echo "<br>";
        echo "key : " . $key . ", value : " . $value . "<br>";
        print_r($value);
        echo "<br>";
    }

    echo "<br>decode_data width : " . $data["width"];
    echo "<br>decode_data texture : " . implode(', ',array_values($data["texture"])) ;

    $obj_file_size = 10; 
    
    $object_id = getLastRecordId();
    echo "<br> object_id : " . $object_id;
    
    insertIntoPPM_filesTable($object_id, $data["width"], $data["height"], $data["texture"]);
    insertIntoOBJ_filesTable($object_id, $obj_file_size, $data["vertices"], $data["text_coords"], $data["normals"], $data["indices"], $data["vertex_count"]);
