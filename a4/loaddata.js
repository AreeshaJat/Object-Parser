// original code taken from MDN Web Docs
// https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API/Tutorial/Lighting_in_WebGL

var distance;
var vertex_count;
var vertices;
var normals;
var text_coords;
var vertex_indices;
var texture;
var height, width;

function save_obj_data(obj_data) {
	var name_check = obj_data[0];
	if (name_check != "OBJ") {
		return -1;
	}

	var indices = new Array();
	var vertice_array = new Array();
	var text_coords_array = new Array();
	var normals_array = new Array();

	obj_data = obj_data.slice(1);
	obj_data.forEach(element => {
		separated_strings = element.split(",");
		index = Number(separated_strings[0]);
		
		let vertice_string = separated_strings.slice(1,4);
		let texture_coords_string = separated_strings.slice(4,6);
		let normals_string = separated_strings.slice(6);
		if (!indices.includes(index)) {
			for (let i = 0; i < vertice_string.length; i++) {
				vertice_array.push(parseFloat(vertice_string[i]));
				normals_array.push(parseFloat(normals_string[i]));
			}
			text_coords_array.push(parseFloat(texture_coords_string[0]));
			text_coords_array.push(parseFloat(texture_coords_string[1]));
		}

		indices.push(index);

	});

	savevertexindices(indices);
	savevertices(vertice_array);
	savetextcoords(text_coords_array);
	savenormals(normals_array);

	setVertexCount(indices.length);	
}

function save_ppm_data(ppm_data) {
	var name_check = ppm_data[0];
	if (name_check != "PPM") {
		return -1;
	}

	height_width = ppm_data[1].split(",");
	height_int = Number(height_width[0]);
	width_int = Number(height_width[1]);

	var texture_data = new Array();
	str_texture_data = ppm_data.slice(2);
	str_texture_data.forEach(element => {
		let pxls = element.split(",");
		pxls.forEach(element2 => {
			texture_data.push(Number(element2));
		});
	});
	saveheight(height_int);
	savewidth(width_int);
	savetexture(new Uint8Array(texture_data));
}

function loadAllData() {
	var width = loadwidth();
	var height = loadheight();
	var texture = loadtexture();

	var indices = loadvertexindices()
	var vertices = loadvertices();
	var text_coords = loadtextcoords();
	var normals = loadnormals();
	var vertex_count = getVertexCount();
	
	//texture: [].slice.call(texture),
	var jsonData = {
		width: width,
		height: height,
		texture: texture,
		indices: indices, 
		vertices: vertices, 
		text_coords: text_coords, 
		normals: normals, 
		vertex_count: vertex_count
	}

	//[width, height, texture, indices, vertices, text_coords, normals, vertex_count];
	return jsonData;
}

function saveAllData(allData) {
	saveheight(parseInt(allData["height"]));
	savewidth(parseInt(allData["width"]));
	savetexture(new Uint8Array(allData["texture"].slice(1,-1).split(',').map(Number)));

	savevertexindices(allData["indices"].slice(1,-1).split(',').map(Number));
	savevertices(allData["vertices"].slice(1,-1).split(',').map(Number));
	savetextcoords(allData["text_coords"].slice(1,-1).split(',').map(Number));
	savenormals(allData["normals"].slice(1,-1).split(',').map(Number));

	setVertexCount(parseInt(allData["vertex_count"]));	
}

// return the number of vertices in the object
// an integer
function getVertexCount() {
   return vertex_count;
}

function setVertexCount(new_vertex_count) {
	vertex_count = new_vertex_count;
}

// scale image - move away from viewpoint
// larger negative numbers will result in smaller objects
// return a negative decimal number
function getdistance() {
   return -6.0;
}

function setdistance(newDistance) {
	distance = newDistance;
}

// position array
// vertex positions
// v data
function loadvertices() {
	return vertices;
}

function savevertices(new_vertices) {
	vertices = new_vertices;
}

// normals array
// vn data
function loadnormals() {
   return normals;
}

function savenormals(new_normals) {
	normals = new_normals;
 }


// texture coordinates
// vt data
function loadtextcoords() {
	return  text_coords;
}

function savetextcoords(new_text_coords) {
	text_coords = new_text_coords;
}


// load vertex indices
// calculate index data and store it here
function loadvertexindices() {
   return vertex_indices;
}

function savevertexindices(new_vertex_indices) {
	vertex_indices = new_vertex_indices;
}


// texture array size and data
// width and height of the ppm file
function loadwidth() {
   return width;
}

function loadheight() {
   return width;
} 

function savewidth(new_width) {
	width = new_width; 
}
  
function saveheight(new_height) {
	height = new_height;
}

function loadtexture() {
	return texture;
}

function savetexture(new_texture) {
	texture = new_texture;
}

