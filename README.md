# Object-Parser
/**
* Author: Areesha Jat
* Due Date: November 26, 2021
* Assignment 4
*/

# General Description
The overall idea of this project is to create a web-based 3D Object Viewer with a backend that involves file handling, 
database management, and WebGL-based 3D graphics rendering. The system allows users to upload, view, delete, and manage 
3D object files in the OBJ and PPM formats.

# What the program files do:
a1.c: A C command-line tool for reading OBJ and PPM files, dynamically generating filenames, parsing and printing file content, and returning error/success status.

config.php: A PHP script establishing a MySQL connection, creating tables if not exist, using transactions, committing changes, and setting autocommit.

config2.php: Another PHP script defining MySQL credentials, connecting to '3D_Objects' database, and terminating with an error message if connection fails.

create.php: An HTML and PHP file handling OBJ and PPM file upload, processing, system commands execution, MySQL database update, and JavaScript for data handling.

create2.php: A PHP script inserting data into MySQL tables, decoding JSON input, and retrieving object ID from the 'objects' table.

delete.php: An HTML and PHP file for deleting records from MySQL tables, providing a deletion form, a home page button, and refreshing the page after deletion.

deleteAll.php: A PHP script deleting all records from MySQL tables, displaying success messages, and redirecting to the home page using JavaScript.

error.php: An HTML file displaying an error message for invalid requests, styled with Bootstrap, including a link to go back to the home page.

index.php: An HTML file serving as a WebGL-based 3D Object Viewer, allowing file uploads, deletion, and visualization with PHP interacting with a MySQL database.

loaddata.js: A JavaScript file handling loading and saving 3D object data and textures for WebGL rendering, parsing data from PPM and OBJ files, and managing parameters.

mySqli.html: An HTML file with embedded PHP demonstrating MySQLi usage, including connection, table creation, record insertion, search, display, and table drop.

ppm.c and ppm.h: C files implementing PPM image file handling, defining structures, reading content, and providing memory management.

read.php: A PHP file retrieving and displaying employee and object information from a database, integrating WebGL and utilizing localStorage for file data.

readppm.py: A Python file defining functions for reading PPM files, distinguishing between P3 and P6 formats, and extracting relevant components.

table.css and table.html: CSS file styling a dark-themed table and HTML file displaying a table with buttons for adding, updating, and removing records.

update.php: A PHP script handling employee record updates in a MySQL database, validating form data, executing SQL UPDATE statements, and displaying an edit form.

upload.php: A PHP script handling file uploads, checking for errors, verifying extensions, and executing commands for reading and storing OBJ file data.

wavefront.c and wavefront.h: C files implementing functions for handling Wavefront (.obj) files, defining structures, parsing, printing, and deallocating memory.

webgl-demo.js: A JavaScript file implementing a WebGL-based 3D graphics demo, rendering a rotating cube with lighting effects.

webgl.css: CSS file applying styling rules to HTML elements, including a 2px solid black border and black background for the canvas element and hiding the video element.

# Limitations:
With the Transfer button the user must select 2 files together in order for the button to work. If the user
enters the files individually it will not work. 
Choose Files only chooses the file, does not display.

### NOTE: "Go home" button is the "return" button. 

# How to run the program:
Start off by ssh'ing into cis2750.socs.uoguelph.ca. On the linux school server make sure you are in the correct 
directory. The correct directory is /srv/'your username' directory.

After you have done that, run the following commands:

make clean

make

Go to google chrome and input the following url: "https://cis2750.socs.uoguelph.ca/~ajat/index.php"