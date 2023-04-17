let contaJson = [];
async function notaFiscalApi(){
    let contaConexao = await fetch("http://localhost:3000/conta");
    let produtosConexao = await fetch("http://localhost:3000/produtos");

    contaJson = await contaConexao.json();
    console.log(contaConexao);
}

notaFiscalApi();