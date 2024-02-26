<!DOCTYPE html>
<html>
    <head>
        <script src="loaddata.js"></script>
    </head>

    <body>

        <?php
            if ($_FILES["uploadfilename"]["error"] > 0 and $_FILES["uploadfilename2"]["error"] > 0)
            {
                echo "Error: " . $_FILES["uploadfilename"]["error"] . "<br>";
            } else{
                $obj_name = $_FILES["uploadfilename"]["name"];
                $obj_name = explode(".", $obj_name);

                $ppm_name = $_FILES["uploadfilename2"]["name"];
                $ppm_name = explode(".", $ppm_name);

                if ($obj_name[1] != "obj") 
                {
                    echo "ERROR: Wrong file extension. It must be obj file.<br>";
                } elseif ($ppm_name[1] != "ppm") 
                {
                    echo "ERROR: Wrong file extension. It must be ppm file.<br>";
                } elseif ($obj_name[0] != $ppm_name[0]) 
                {
                    echo "ERROR: .obj and .ppm files must be the same name.<br>";
                } elseif (!is_null($obj_name[0])) 
                {
                    $command = "./a1 readppm readppm " . $obj_name[0];
                    echo $command . "<br>";
                    exec($command, $output, $retval);
                    if ($retval) {
                        echo "exec faild. <br>";
                    }else {
                        $idx = array_search("OBJ", $output);
                        $output = array_slice($output, $idx);
                        echo $obj_name[0] . " file was read.<br>";
                    }
                }
            }
        ?>

        <script type="text/javascript">
            var data = <?php echo json_encode($output); ?>;
            debugger
            if (data != [] && data != null) {
                localStorage.setItem("data", JSON.stringify(data));
                window.history.back();
            }else{
                console.log("file was not read");
            }

        </script>
       


    </body>
</html>
