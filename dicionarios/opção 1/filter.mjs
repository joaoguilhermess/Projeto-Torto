import fs from "fs";

var lines = fs.readFileSync("portugues.txt").toString().split("\n");

lines = lines.filter(function(item) {
	if (item.length >= 3 && item.length <= 10) {
		return true;
	}
});

for (let i = 0; i < lines.length; i++) {
	lines[i] = lines[i].toUpperCase();
}

fs.writeFileSync("filtrado.txt", lines.join("\n"));