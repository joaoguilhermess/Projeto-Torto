import fs from "fs";

var itens = fs.readFileSync("portugues.dict").toString();

itens = itens.split("\n\n\n");

var ignorar = ["...", "-", "ç", "ã", "á", "à", "é", "è", "ê", "ẽ", "í", "ô", "õ", "ú", "ù", "û", "ũ", "ý"];

itens = itens.filter(function(item) {
	var linhas = item.split("\n");

	for (let i = 0; i < linhas.length; i++) {
		for (let k = 0; k < ignorar.length; k++) {
			if (linhas[0].includes(ignorar[k])) return false;
		}

		if (linhas[i].includes("<i>")) {
			var categorias = linhas[i].split(">")[1].split("<")[0].split(" ");

			for (let c = 0; c < categorias.length; c++) {
				if (["v."].includes(categorias[c])) return true;
			}

			// if (["m.", "f."].includes(categorias)) return true;

			return false;
		}
	}
});

for (let i = 0; i < itens.length; i++) {
	itens[i] = itens[i].split("\n")[0];
}

fs.writeFileSync("filtrado.txt", itens.join("\n"));