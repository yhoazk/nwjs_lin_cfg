
var fs = require('fs');
var json_cfg;


fs.readFile('./LIN_configuration.txt', 'utf-8', function (error, contents) {
//	if(error) throw error;
	// console.log(contents);
	// console.log(typeof contents);
	//json_cfg = JSON.parse(contents);
//	console.log(obj);
	parseCfgFile(contents);
	document.write(contents);

});

/**



*/





function parseCfgFile(file_raw) {
		var reader = new FileReader();
		// reader.onload = function (progress) {
			var lines = file_raw.split('\n')
			for(var line = 0; line < lines.length; line++)
			{
				console.log("Lnum:" + line + "-> " + lines[line]);
			}
		// }

}


//var bnt_gen =
